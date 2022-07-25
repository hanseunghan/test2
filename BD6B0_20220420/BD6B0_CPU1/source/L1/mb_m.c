/***************************************************************************************************
 * File Name     : mb_m.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 ***************************************************************************************************
 * ORG History   : MODBUS Master Protocol(RTU Mode) Handling V1.10
 *                 By ko young cheol, In 2008. 2. 27.
 *                                                                              ORG by KO
 *                                                                              MODEFY by A414999
 **************************************************************************************************/
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"

/* CRC tables */
extern const uint08 CRCHiTable[];
extern const uint08 CRCLoTable[];

sint16 MBM_NoRxCnt = 0, MBM_RxBufPtr = 0;
uint08 MBM_RxBuf[MBM_RXBUF_SIZE], MBM_TxBuf[MBM_TXBUF_SIZE];

/***************************************************************************************************
 *  Modbus Master Initialize
 **************************************************************************************************/
void MBM_Init(void)
{
    MBM_NoRxCnt = 0;
    MBM_RxBufPtr = 0;
}

/***************************************************************************************************
 *  Modbus Master Get CRC OK frame
 *  : This function should be called per "MBM_GetFrame()" call time.
 **************************************************************************************************/
sint16 MBM_GetCRCOKFrame(void)
{
    sint16 s16FrameLength;
    uint16 u16CRC = 0U;

    s16FrameLength = MBM_GetFrame(MBM_RxBuf, MBM_RXBUF_SIZE);

    /* No frame ? */
    if(s16FrameLength <= 0) {
        return 0;
    }

    /* For debugging */
    /*Debug_Print(MBM_RxBuf,s16FrameLength);*/

    /* Check u16CRC ---> ????? u16CRC location is strange ????? */
    u16CRC = (((U16)MBM_RxBuf[s16FrameLength-2U]<<8U) | (U16)MBM_RxBuf[s16FrameLength-1U]);
    if(u16CRC != MBM_GetCRC(MBM_RxBuf, (s16FrameLength-2U))) {
        return 0;
    }

    /* OK frame received !!! */
    return s16FrameLength;
}

/***************************************************************************************************
 *  Modbus Master GetFrame
 *  Detect & get MODBUS frame
 *  MODBUS protocol assumes a silent interval of at least 3.5
 *  character times to be mark of the frame start & end.
 *  Detecting frame end can be delayed due to the function call period.
 **************************************************************************************************/
sint16 MBM_GetFrame(uint08* u8Buf, sint16 s16BufSize)
{
    uint08 u8RxData;
    uint08 u8RxFlag = OFF;
    sint16 s16FrameLength;

    while(SCIA_GetRxBufByte(&u8RxData)) {

        u8RxFlag = ON;
        /* Buffering */
        if(MBM_RxBufPtr >= s16BufSize) {
            MBM_RxBufPtr = 0;
        }
        u8Buf[MBM_RxBufPtr++] = u8RxData;
    }

    if(u8RxFlag == OFF) {

        if(++MBM_NoRxCnt >= MBM_INTERFRAMEGAPCNT) {

            s16FrameLength = MBM_RxBufPtr;
            if(s16FrameLength<4U) {
                s16FrameLength = 0;
            }
            /* For next frame */
            MBM_NoRxCnt = 0;
            MBM_RxBufPtr = 0;

            return s16FrameLength;
        }
    }
    else {
        MBM_NoRxCnt = 0;
    }

    return 0;
}

/***************************************************************************************************
 *  Modbus Master SendWithCRC
 *  Send modbus frame after appending CRC
 **************************************************************************************************/
void MBM_SendWithCRC(uint08* u8Buf, sint16 s16Length)
{
    uint16 u16CRC = 0U;

    /* ????? u16CRC location is strange ????? */
    u16CRC = MBM_GetCRC(u8Buf, s16Length);
    u8Buf[s16Length+0] = (U08)(u16CRC>>8U);
    u8Buf[s16Length+1] = (U08)(u16CRC);

    if(SCIA_TxReady()) {
        SCIA_SendFrame((s16Length+2U), u8Buf);
    }
}

/***************************************************************************************************
 *  Modbus Master Get CRC
 **************************************************************************************************/
uint16 MBM_GetCRC(uint08* u8Buf, sint16 s16Length)
{
    uint08 u8CRC_Hi = 0xFFU, u8CRC_Lo = 0xFFU;
    uint16 u16CRC = 0U;
    sint16 s16Index = 0;

    while(s16Length--) {

        s16Index = u8CRC_Hi ^ *u8Buf++;
        s16Index = s16Index & 0x00FFU; /* ????? For TI DSP ????? */
        u8CRC_Hi = u8CRC_Lo ^ CRCHiTable[s16Index];
        u8CRC_Lo = CRCLoTable[s16Index];
    }

    u16CRC = (((((U16)u8CRC_Hi)<<8U)&0xFF00U) | (((U16)u8CRC_Lo)&0x00FFU));

    return (u16CRC);
}

/***************************************************************************************************
 *  Modbus Master Function Code Ox03 Request
 *  Read Holding Registers
 *  Slave 장치 내부의 메모리에 저장되어 있는 Analog 설정값을 읽을 때 사용
 *  u16StartAddr : 0x0000 ~ 0xFFFF
 *  u16Quantity  : 1 ~ 125(0x7D)
 **************************************************************************************************/
void MBM_RequestFunc0x03(uint08 u8ID, uint16 u16StartAddr, uint16 u16Quantity)
{
    /* Make frame */
    MBM_TxBuf[0] = u8ID;
    MBM_TxBuf[1] = 0x03U;
    MBM_TxBuf[2] = (U08)(u16StartAddr>>8U);
    MBM_TxBuf[3] = (U08)(u16StartAddr);
    MBM_TxBuf[4] = (U08)(u16Quantity>>8U);
    MBM_TxBuf[5] = (U08)(u16Quantity);

    /* Send */
    MBM_SendWithCRC(MBM_TxBuf, 6U);
}

/***************************************************************************************************
 *  Modbus Master Function Code Ox06 Request
 *  write single register
 *  Slave 장치의 Analog 변수로 단일 값을 출력을 할 때 사용
 *  u16RegAddr : 0x0000 ~ 0xFFFF
 *  u16Value   : 0x0000 ~ 0xFFFF
 **************************************************************************************************/
void MBM_RequestFunc0x06(uint08 u8ID, uint16 u16RegAddr, uint16 u16Value)
{
    /* Make frame */
    MBM_TxBuf[0] = u8ID;
    MBM_TxBuf[1] = 0x06U;
    MBM_TxBuf[2] = (U08)(u16RegAddr>>8U);
    MBM_TxBuf[3] = (U08)(u16RegAddr);
    MBM_TxBuf[4] = (U08)(u16Value>>8U);
    MBM_TxBuf[5] = (U08)(u16Value);

    /* Send */
    MBM_SendWithCRC(MBM_TxBuf, 6U);
}

/***************************************************************************************************
 *  Modbus Master Function Code Ox10 Request
 *  write multiple registers
 *  Slave 장치의 연속된 Analog 변수를 여러개 묶어서 동시에 Analog 값을 출력할 때 사용
 *  u16StartAddr : 0x0000 ~ 0xFFFF
 *  u16Quantity  : 1 ~ 123(0x7B)
 **************************************************************************************************/
void MBM_RequestFunc0x10(uint08 u8ID, uint16 u16StartAddr, uint16 u16Quantity, uint08* u8Buf)
{
    uint16 i;

    /* Make frame */
    MBM_TxBuf[0] = u8ID;
    MBM_TxBuf[1] = 0x10U;
    MBM_TxBuf[2] = (U08)(u16StartAddr>>8U);
    MBM_TxBuf[3] = (U08)(u16StartAddr);
    MBM_TxBuf[4] = (U08)(u16Quantity>>8U);
    MBM_TxBuf[5] = (U08)(u16Quantity);
    MBM_TxBuf[6] = (U08)(u16Quantity*2U);

    /* Fill write values */
    for(i=0; i<(u16Quantity*2U); i++) {
        MBM_TxBuf[7+i] = u8Buf[i];
    }

    /* Send */
    MBM_SendWithCRC(MBM_TxBuf, (7U+(u16Quantity*2U)));
}

/***************************************************************************************************
 *  Modbus Master Function Code Ox17 Request
 *  read/write multiple registers
 *  Slave 장치의 Analog 값을 연속적으로 여러개 묶어서 동시에 읽고, 출력할 때 사용
 *  u16RdAddr : 0x0000 ~ 0xFFFF
 *  u16RdQuantity : 1 ~ 125(0x7D)
 *  u16WrAddr : 0x0000 ~ 0xFFFF
 *  u16WrQuantity : 1 ~ 121(0x79)
 **************************************************************************************************/
void MBM_RequestFunc0x17(uint08 u8ID, uint16 u16RdAddr, uint16 u16RdQuantity,
                         uint16 u16WrAddr, uint16 u16WrQuantity, uint08* u8Buf)
{
    uint16 i;

    /* Make frame */
    MBM_TxBuf[0]  = u8ID;
    MBM_TxBuf[1]  = 0x17U;
    MBM_TxBuf[2]  = (U08)(u16RdAddr>>8U);
    MBM_TxBuf[3]  = (U08)(u16RdAddr);
    MBM_TxBuf[4]  = (U08)(u16RdQuantity>>8U);
    MBM_TxBuf[5]  = (U08)(u16RdQuantity);
    MBM_TxBuf[6]  = (U08)(u16WrAddr>>8U);
    MBM_TxBuf[7]  = (U08)(u16WrAddr);
    MBM_TxBuf[8]  = (U08)(u16WrQuantity>>8U);
    MBM_TxBuf[9]  = (U08)(u16WrQuantity);
    MBM_TxBuf[10] = (U08)(u16WrQuantity*2U);

    /* Fill write values */
    for(i=0; i<(u16WrQuantity*2U); i++) {
        MBM_TxBuf[11+i] = u8Buf[i];
    }

    /* Send */
    MBM_SendWithCRC(MBM_TxBuf, (11U+(u16WrQuantity*2U)));
}
/* EOF */

#if 0
/* CRC tables 256EA, 256EA */
const uint08 CRCHiTable[] = {0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
                             0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};

const uint08 CRCLoTable[] = {0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2,
                             0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
                             0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
                             0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
                             0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
                             0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
                             0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,
                             0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
                             0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
                             0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
                             0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE,
                             0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
                             0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA,
                             0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
                             0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
                             0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
                             0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62,
                             0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
                             0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE,
                             0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
                             0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
                             0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
                             0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76,
                             0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
                             0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
                             0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
                             0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
                             0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
                             0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A,
                             0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
                             0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86,
                             0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40};
#endif






