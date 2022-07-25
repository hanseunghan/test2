/***************************************************************************************************
 * File Name     : bd6b0_drv1CPU1.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"
#include "entryL2CPU1.h"

/***************************************************************************************************
 * SCIA's App. : Debug
 * SCIB's App. : IO-Link Transmitter I/F
 * SCIC's App. : Modbus1 RTU 8Pins Connector
 * SCID's App. : Modbus2 RTU 4Pins Connector
 *
 * SPIA's App. : EEPROM
 * SPIB's App. : 가속도 센서
 * SPIC's App. : IO-Link Transmitter I/F
 **************************************************************************************************/

/***************************************************************************************************
 * Static SCIA
 * App. : Debug
 **************************************************************************************************/
__interrupt void scia_rx_isr(void);
__interrupt void scia_tx_isr(void);

static uint08 u8SCIA_RxBuf[SCIA_RXBUFSIZE], u8SCIA_TxBuf[SCIA_TXBUFSIZE];
static uint16 u16SCIA_RxBufPtr, u16SCIA_RxReadPtr;
static uint16 u16SCIA_TxBufPtr, u16SCIA_TxDataNum;

/***************************************************************************************************
 * SCIA Initial
 **************************************************************************************************/
uint16 InitSCIA(void)
{
    uint16 i;

    /* Gathering Variables Initial */
    for(i=0; i<SCIA_RXBUFSIZE; i++) {
        u8SCIA_RxBuf[i] = 0U;
    }
    for(i=0; i<SCIA_TXBUFSIZE; i++) {
        u8SCIA_TxBuf[i] = 0U;
    }

    u16SCIA_RxBufPtr  = 0U;
    u16SCIA_TxBufPtr  = 0U;
    u16SCIA_RxReadPtr = 0U;
    u16SCIA_TxDataNum = 0U;

    Interrupt_register(INT_SCIA_RX, &scia_rx_isr);
    Interrupt_register(INT_SCIA_TX, &scia_tx_isr);

    /* 8 char bits, 1 stop bit, no parity. Baud rate is SCIA_BAUDRATE */
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, SCIA_BAUDRATE, (SCI_CONFIG_WLEN_8
                                                               | SCI_CONFIG_STOP_ONE
                                                               | SCI_CONFIG_PAR_NONE));
//  SCI_enableModule(SCIA_BASE);
    SCI_resetChannels(SCIA_BASE);

    /* RX and TX Interrupts Enabled */
    SCI_enableInterrupt(SCIA_BASE,  (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));
    SCI_disableInterrupt(SCIA_BASE, (SCI_INT_RXERR | SCI_INT_TXFF | SCI_INT_RXFF));

    SCI_performSoftwareReset(SCIA_BASE);

    SCI_clearInterruptStatus(SCIA_BASE, (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));

    /* Interrupts that are used in this example are re-mapped to
       ISR functions found within this file. */
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enable(INT_SCIA_TX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9); //TRM 168page

    return (0U);
}

/***************************************************************************************************
 * SCIA Rx Interrupt
 **************************************************************************************************/
__interrupt void scia_rx_isr(void)
{
    //test
    //if(u16SciC_rx++ > 5000) u16SciC_rx = 0;
    while(SCIA_RXST_RXRDY != SCI_RXST_RXRDY) {
    }

    u8SCIA_RxBuf[u16SCIA_RxBufPtr++] = (U08)(SCIA_RXBUF);
    if(u16SCIA_RxBufPtr >= SCIA_RXBUFSIZE)
        u16SCIA_RxBufPtr = 0;

    SCI_clearOverflowStatus(SCIA_BASE);

    /* Issue PIE ack */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

/***************************************************************************************************
 * SCIA Tx Interrupt
 **************************************************************************************************/
__interrupt void scia_tx_isr(void)
{
    //test
    //if(u16SciC_tx++ > 5000) u16SciC_tx = 0;
    if(u16SCIA_TxBufPtr < u16SCIA_TxDataNum) {

        while(SCIA_CTL2_TXRDY != SCI_CTL2_TXRDY) {
        }
        SCIA_TXBUF = u8SCIA_TxBuf[u16SCIA_TxBufPtr++];
    }
    else {
    }

    // Issue PIE ACK
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

/***************************************************************************************************
 * SCIA_TxReady
 **************************************************************************************************/
sint08 SCIA_TxReady(void)
{
    /* Check if it is possible to transmit */
    return (SCIA_CTL2_TXRDY);
}

/***************************************************************************************************
 * SCIA_SendFrame
 **************************************************************************************************/
void SCIA_SendFrame(sint16 s16Num, uint08 *u8Buf)
{
    sint16 i;

    /* Copy data & set control variables */
    for(i=0; i<s16Num; i++) {
        u8SCIA_TxBuf[i] = u8Buf[i];
    }

    u16SCIA_TxDataNum = s16Num;
    u16SCIA_TxBufPtr = 1U;

    SCIA_TXBUF = u8SCIA_TxBuf[0];
}

/***************************************************************************************************
 * SCIA_GetRxBufByte
 **************************************************************************************************/
sint08 SCIA_GetRxBufByte(uint08 *u8Data)
{
    if(u16SCIA_RxBufPtr != u16SCIA_RxReadPtr) {

        *u8Data = u8SCIA_RxBuf[u16SCIA_RxReadPtr++];
        if(u16SCIA_RxReadPtr >= SCIA_RXBUFSIZE)
            u16SCIA_RxReadPtr = 0U;

        return 1;
    }
    else
        return 0;
}

/***************************************************************************************************
 * Static SCIB
 * App. : IO-Link Transmitter I/F
 **************************************************************************************************/
__interrupt void scib_rx_isr(void);
__interrupt void scib_tx_isr(void);

static uint08 u8SCIB_RxBuf[SCIB_RXBUFSIZE], u8SCIB_TxBuf[SCIB_TXBUFSIZE];
static uint16 u16SCIB_RxBufPtr, u16SCIB_RxReadPtr;
static uint16 u16SCIB_TxBufPtr, u16SCIB_TxDataNum;

/***************************************************************************************************
 * SCIB Initial
 **************************************************************************************************/
uint16 InitSCIB(void)
{
    uint16 i;

    /* Gathering Variables Initial */
    for(i=0; i<SCIB_RXBUFSIZE; i++) {
        u8SCIB_RxBuf[i] = 0U;
    }
    for(i=0; i<SCIB_TXBUFSIZE; i++) {
        u8SCIB_TxBuf[i] = 0U;
    }

    u16SCIB_RxBufPtr  = 0U;
    u16SCIB_TxBufPtr  = 0U;
    u16SCIB_RxReadPtr = 0U;
    u16SCIB_TxDataNum = 0U;

    Interrupt_register(INT_SCIB_RX, &scib_rx_isr);
    Interrupt_register(INT_SCIB_TX, &scib_tx_isr);

    /* 8 char bits, 1 stop bit, no parity. Baud rate is SCIB_BAUDRATE */
    SCI_setConfig(SCIB_BASE, DEVICE_LSPCLK_FREQ, SCIB_BAUDRATE, (SCI_CONFIG_WLEN_8
                                                               | SCI_CONFIG_STOP_ONE
                                                               | SCI_CONFIG_PAR_NONE));
//  SCI_enableModule(SCIB_BASE);
    SCI_resetChannels(SCIB_BASE);

    /* RX and TX Interrupts Enabled */
    SCI_enableInterrupt(SCIB_BASE,  (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));
    SCI_disableInterrupt(SCIB_BASE, (SCI_INT_RXERR | SCI_INT_TXFF | SCI_INT_RXFF));

    SCI_performSoftwareReset(SCIB_BASE);

    SCI_clearInterruptStatus(SCIB_BASE, (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));

    /* Interrupts that are used in this example are re-mapped to
       ISR functions found within this file. */
    Interrupt_enable(INT_SCIB_RX);
    Interrupt_enable(INT_SCIB_RX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9); //TRM 168page

    return (0U);
}

/***************************************************************************************************
 * SCIB Rx Interrupt
 **************************************************************************************************/
__interrupt void scib_rx_isr(void)
{
    while(SCIB_RXST_RXRDY != SCI_RXST_RXRDY) {
    }

    u8SCIB_RxBuf[u16SCIB_RxBufPtr++] = (U08)(SCIB_RXBUF);
    if(u16SCIB_RxBufPtr >= SCIB_RXBUFSIZE)
        u16SCIB_RxBufPtr = 0;

    SCI_clearOverflowStatus(SCIB_BASE);

    /* Issue PIE ack */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

/***************************************************************************************************
 * SCIB Tx Interrupt
 **************************************************************************************************/
__interrupt void scib_tx_isr(void)
{
    if(u16SCIB_TxBufPtr < u16SCIB_TxDataNum) {

        while(SCIB_CTL2_TXRDY != SCI_CTL2_TXRDY) {
        }
        SCIB_TXBUF = u8SCIB_TxBuf[u16SCIB_TxBufPtr++];
    }
    else {
    }

    // Issue PIE ACK
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

/***************************************************************************************************
 * SCIB_TxReady
 **************************************************************************************************/
sint08 SCIB_TxReady(void)
{
    /* Check if it is possible to transmit */
    return (SCIB_CTL2_TXRDY);
}

/***************************************************************************************************
 * SCIB_SendFrame
 **************************************************************************************************/
void SCIB_SendFrame(sint16 s16Num, uint08 *u8Buf)
{
    sint16 i;

    /* Copy data & set control variables */
    for(i=0; i<s16Num; i++) {
        u8SCIB_TxBuf[i] = u8Buf[i];
    }

    u16SCIB_TxDataNum = s16Num;
    u16SCIB_TxBufPtr = 1;

    SCIB_TXBUF = u8SCIB_TxBuf[0];
}

/***************************************************************************************************
 * SCIB_GetRxBufByte
 **************************************************************************************************/
sint08 SCIB_GetRxBufByte(uint08 *u8Data)
{
    if(u16SCIB_RxBufPtr != u16SCIB_RxReadPtr) {

        *u8Data = u8SCIB_RxBuf[u16SCIB_RxReadPtr++];
        if(u16SCIB_RxReadPtr >= SCIB_RXBUFSIZE)
            u16SCIB_RxReadPtr = 0U;

        return 1;
    }
    else
        return 0;
}

/***************************************************************************************************
 * Static SCIC
 * App. : Modbus1 RTU 8Pins Connector
 **************************************************************************************************/
__interrupt void scic_rx_isr(void);
__interrupt void scic_tx_isr(void);

static uint08 u8SCIC_RxBuf[SCIC_RXBUFSIZE], u8SCIC_TxBuf[SCIC_TXBUFSIZE];
static uint16 u16SCIC_RxBufPtr, u16SCIC_RxReadPtr;
static uint16 u16SCIC_TxBufPtr, u16SCIC_TxDataNum;

/***************************************************************************************************
 * SCIC Initial
 **************************************************************************************************/
uint16 InitSCIC(void)
{
    uint16 i;

    /* Gathering Variables Initial */
    for(i=0; i<SCIC_RXBUFSIZE; i++) {
        u8SCIC_RxBuf[i] = 0U;
    }
    for(i=0; i<SCIC_TXBUFSIZE; i++) {
        u8SCIC_TxBuf[i] = 0U;
    }

    u16SCIC_RxBufPtr  = 0U;
    u16SCIC_TxBufPtr  = 0U;
    u16SCIC_RxReadPtr = 0U;
    u16SCIC_TxDataNum = 0U;

    Interrupt_register(INT_SCIC_RX, &scic_rx_isr);
    Interrupt_register(INT_SCIC_TX, &scic_tx_isr);

    /* 8 char bits, 1 stop bit, no parity. Baud rate is SCIC_BAUDRATE */
    SCI_setConfig(SCIC_BASE, DEVICE_LSPCLK_FREQ, SCIC_BAUDRATE, (SCI_CONFIG_WLEN_8
                                                               | SCI_CONFIG_STOP_ONE
                                                               | SCI_CONFIG_PAR_NONE));
//  SCI_enableModule(SCIC_BASE);
    SCI_resetChannels(SCIC_BASE);

    /* RX and TX Interrupts Enabled */
    SCI_enableInterrupt(SCIC_BASE,  (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));
    SCI_disableInterrupt(SCIC_BASE, (SCI_INT_RXERR | SCI_INT_TXFF | SCI_INT_RXFF));

    SCI_performSoftwareReset(SCIC_BASE);

    SCI_clearInterruptStatus(SCIC_BASE, (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));

    /* Interrupts that are used in this example are re-mapped to
       ISR functions found within this file. */
    Interrupt_enable(INT_SCIC_RX);
    Interrupt_enable(INT_SCIC_RX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8); //TRM 145page

    return (0U);
}

/***************************************************************************************************
 * SCIC Rx Interrupt
 **************************************************************************************************/
__interrupt void scic_rx_isr(void)
{
    while(SCIC_RXST_RXRDY != SCI_RXST_RXRDY) {
    }

    u8SCIC_RxBuf[u16SCIC_RxBufPtr++] = (U08)(SCIC_RXBUF);
    if(u16SCIC_RxBufPtr >= SCIC_RXBUFSIZE)
        u16SCIC_RxBufPtr = 0;

    SCI_clearOverflowStatus(SCIC_BASE);

    /* Issue PIE ack */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

/***************************************************************************************************
 * SCIC Tx Interrupt
 **************************************************************************************************/
__interrupt void scic_tx_isr(void)
{
    if(u16SCIC_TxBufPtr < u16SCIC_TxDataNum) {

        while(SCIC_CTL2_TXRDY != SCI_CTL2_TXRDY) {
        }
        SCIC_TXBUF = u8SCIC_TxBuf[u16SCIC_TxBufPtr++];
    }
    else {
    }

    // Issue PIE ACK
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

/***************************************************************************************************
 * SCIC_TxReady
 **************************************************************************************************/
sint08 SCIC_TxReady(void)
{
    /* Check if it is possible to transmit */
    return (SCIC_CTL2_TXRDY);
}

/***************************************************************************************************
 * SCIC_SendFrame
 **************************************************************************************************/
void SCIC_SendFrame(sint16 s16Num, uint08 *u8Buf)
{
    sint16 i;

    /* Copy data & set control variables */
    for(i=0; i<s16Num; i++) {
        u8SCIC_TxBuf[i] = u8Buf[i];
    }

    u16SCIC_TxDataNum = s16Num;
    u16SCIC_TxBufPtr = 1;

    SCIC_TXBUF = u8SCIC_TxBuf[0];
}

/***************************************************************************************************
 * SCIC_GetRxBufByte
 **************************************************************************************************/
sint08 SCIC_GetRxBufByte(uint08 *u8Data)
{
    if(u16SCIC_RxBufPtr != u16SCIC_RxReadPtr) {

        *u8Data = u8SCIC_RxBuf[u16SCIC_RxReadPtr++];
        if(u16SCIC_RxReadPtr >= SCIC_RXBUFSIZE)
            u16SCIC_RxReadPtr = 0U;

        return 1;
    }
    else
        return 0;
}

/***************************************************************************************************
 * Static SCID
 * App. : Modbus2 RTU 4Pins Connector
 **************************************************************************************************/
__interrupt void scid_rx_isr(void);
__interrupt void scid_tx_isr(void);

static uint08 u8SCID_RxBuf[SCID_RXBUFSIZE], u8SCID_TxBuf[SCID_TXBUFSIZE];
static uint16 u16SCID_RxBufPtr, u16SCID_RxReadPtr;
static uint16 u16SCID_TxBufPtr, u16SCID_TxDataNum;

/***************************************************************************************************
 * SCID Initial
 **************************************************************************************************/
uint16 InitSCID(void)
{
    uint16 i;

    /* Gathering Variables Initial */
    for(i=0; i<SCID_RXBUFSIZE; i++) {
        u8SCID_RxBuf[i] = 0U;
    }
    for(i=0; i<SCID_TXBUFSIZE; i++) {
        u8SCID_TxBuf[i] = 0U;
    }

    u16SCID_RxBufPtr  = 0U;
    u16SCID_TxBufPtr  = 0U;
    u16SCID_RxReadPtr = 0U;
    u16SCID_TxDataNum = 0U;

    Interrupt_register(INT_SCID_RX, &scid_rx_isr);
    Interrupt_register(INT_SCID_TX, &scid_tx_isr);

    /* 8 char bits, 1 stop bit, no parity. Baud rate is SCIC_BAUDRATE */
    SCI_setConfig(SCID_BASE, DEVICE_LSPCLK_FREQ, SCID_BAUDRATE, (SCI_CONFIG_WLEN_8
                                                               | SCI_CONFIG_STOP_ONE
                                                               | SCI_CONFIG_PAR_NONE));
//  SCI_enableModule(SCID_BASE);
    SCI_resetChannels(SCID_BASE);

    /* RX and TX Interrupts Enabled */
    SCI_enableInterrupt(SCID_BASE,  (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));
    SCI_disableInterrupt(SCID_BASE, (SCI_INT_RXERR | SCI_INT_TXFF | SCI_INT_RXFF));

    SCI_performSoftwareReset(SCID_BASE);

    SCI_clearInterruptStatus(SCID_BASE, (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));

    /* Interrupts that are used in this example are re-mapped to
       ISR functions found within this file. */
    Interrupt_enable(INT_SCID_RX);
    Interrupt_enable(INT_SCID_RX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8); //TRM 145page

    return (0U);
}

/***************************************************************************************************
 * SCID Rx Interrupt
 **************************************************************************************************/
__interrupt void scid_rx_isr(void)
{
    while(SCID_RXST_RXRDY != SCI_RXST_RXRDY) {
    }

    u8SCID_RxBuf[u16SCID_RxBufPtr++] = (U08)(SCID_RXBUF);
    if(u16SCID_RxBufPtr >= SCID_RXBUFSIZE)
        u16SCID_RxBufPtr = 0;

    SCI_clearOverflowStatus(SCID_BASE);

    /* Issue PIE ack */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

/***************************************************************************************************
 * SCID Tx Interrupt
 **************************************************************************************************/
__interrupt void scid_tx_isr(void)
{
    if(u16SCID_TxBufPtr < u16SCID_TxDataNum) {

        while(SCID_CTL2_TXRDY != SCI_CTL2_TXRDY) {
        }
        SCID_TXBUF = u8SCID_TxBuf[u16SCID_TxBufPtr++];
    }
    else {
    }

    // Issue PIE ACK
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

/***************************************************************************************************
 * SCID_TxReady
 **************************************************************************************************/
sint08 SCID_TxReady(void)
{
    /* Check if it is possible to transmit */
    return (SCID_CTL2_TXRDY);
}

/***************************************************************************************************
 * SCID_SendFrame
 **************************************************************************************************/
void SCID_SendFrame(sint16 s16Num, uint08 *u8Buf)
{
    sint16 i;

    /* Copy data & set control variables */
    for(i=0; i<s16Num; i++) {
        u8SCID_TxBuf[i] = u8Buf[i];
    }

    u16SCID_TxDataNum = s16Num;
    u16SCID_TxBufPtr = 1;

    SCID_TXBUF = u8SCID_TxBuf[0];
}

/***************************************************************************************************
 * SCID_GetRxBufByte
 **************************************************************************************************/
sint08 SCID_GetRxBufByte(uint08 *u8Data)
{
    if(u16SCID_RxBufPtr != u16SCID_RxReadPtr) {

        *u8Data = u8SCID_RxBuf[u16SCID_RxReadPtr++];
        if(u16SCID_RxReadPtr >= SCID_RXBUFSIZE)
            u16SCID_RxReadPtr = 0U;

        return 1;
    }
    else
        return 0;
}
/* EOF */

#if 0U
/***************************************************************************************************
 * SCIA Initial
 **************************************************************************************************/
uint16 InitSCIA(uint32 u32BaudRate, uint16 u16DataLength, uint16 u16Parity, uint16 u16StopBit)
{
    uint16 i;
    uint32 u32SciConfig = 0U;
    uint16 u16ReturnVal = 0U;

    if((u32BaudRate<4800U)||(u32BaudRate>3000000U)) u16ReturnVal |= 0x0001U;    //return 1U;
    if((u16DataLength<1U)||(u16DataLength>8U))      u16ReturnVal |= 0x0002U;    //return 2U;
    if(u16Parity>=3U)                               u16ReturnVal |= 0x0004U;    //return 3U;
    if(u16StopBit>=2U)                              u16ReturnVal |= 0x0008U;    //return 4U;

    if(u16ReturnVal) return u16ReturnVal;



    /* Gathering Variables Initial */
    for(i=0; i<SCIA_RXBUFSIZE; i++) {
        u8SCIA_RxBuf[i] = 0U;
    }
    for(i=0; i<SCIA_TXBUFSIZE; i++) {
        u8SCIA_TxBuf[i] = 0U;
    }

    u16SCIA_RxBufPtr  = 0U;
    u16SCIA_TxBufPtr  = 0U;
    u16SCIA_RxReadPtr = 0U;
    u16SCIA_TxDataNum = 0U;

    Interrupt_register(INT_SCIA_RX, &scia_rx_isr);
    Interrupt_register(INT_SCIA_TX, &scia_tx_isr);

    u32SciConfig |= (U32)(u16DataLength-1U);

    switch(u16Parity) {

        case 0U : u32SciConfig |= SCI_CONFIG_PAR_NONE; break;
        case 1U : u32SciConfig |= SCI_CONFIG_PAR_ODD;  break;
        case 2U : u32SciConfig |= SCI_CONFIG_PAR_EVEN; break;
    }

    switch(u16StopBit) {

        case 0U : u32SciConfig |= SCI_CONFIG_STOP_ONE; break;
        case 1U : u32SciConfig |= SCI_CONFIG_STOP_TWO; break;
    }

    /* SCI Config Setting */
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, u32BaudRate, u32SciConfig);
//  SCI_enableModule(SCIA_BASE);
    SCI_resetChannels(SCIA_BASE);

    /* RX and TX Interrupts Enabled */
    SCI_enableInterrupt(SCIA_BASE,  (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));
    SCI_disableInterrupt(SCIA_BASE, (SCI_INT_RXERR | SCI_INT_TXFF | SCI_INT_RXFF));

    SCI_performSoftwareReset(SCIA_BASE);

    SCI_clearInterruptStatus(SCIA_BASE, (SCI_INT_TXRDY | SCI_INT_RXRDY_BRKDT));

    /* Interrupts that are used in this example are re-mapped to
       ISR functions found within this file. */
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enable(INT_SCIA_TX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9); //TRM 168page

    return (u16ReturnVal);
}
#endif




