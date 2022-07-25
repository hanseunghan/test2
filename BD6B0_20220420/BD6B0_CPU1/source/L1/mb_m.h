/***************************************************************************************************
 * File Name     : mb_m.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              ORG by KO
 *                                                                              MODEFY by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_MB_M_H_
#define SOURCE_L1_MB_M_H_

/***************************************************************************************************
 * Base Define
 **************************************************************************************************/
#define MBM_INTERFRAMEGAPCNT    1U  /* Inter frame gap detection count = 5mSec(1)/5mSec(2) */
                                    /* (1) Inter frame gap time = 5mSec */
                                    /* (2) "MBM_GetFrame()" call time = 5mSec */
#define MBM_RXBUF_SIZE          100U
#define MBM_TXBUF_SIZE          50U

/* Externs */
extern uint08 MBM_RxBuf[];

/***************************************************************************************************
 * API Functions
 **************************************************************************************************/
void MBM_Init(void);
sint16 MBM_GetCRCOKFrame(void);
sint16 MBM_GetFrame(uint08* buf, sint16 s16BufSize);
void MBM_SendWithCRC(uint08* u8Buf, int length);
uint16 MBM_GetCRC(uint08* u8Buf, int length);

void MBM_RequestFunc0x03(uint08 u8ID, uint16 u16StartAddr, uint16 u16Quantity);
void MBM_RequestFunc0x06(uint08 u8ID, uint16 u16RegAddr, uint16 u16Value);
void MBM_RequestFunc0x10(uint08 u8ID, uint16 u16StartAddr, uint16 u16Quantity, uint08* u8Buf);
void MBM_RequestFunc0x17(uint08 u8ID, uint16 u16RdAddr, uint16 u16RdQuantity,
                         uint16 u16WrAddr, uint16 u16WrQuantity, uint08* u8Buf);

#endif /* SOURCE_L1_MB_M_H_ */
/* EOF */
