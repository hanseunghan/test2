/***************************************************************************************************
 * File Name     : bd6b0_drvCPU1.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L0_BD6B0_DRVCPU1_H_
#define SOURCE_L0_BD6B0_DRVCPU1_H_

/***************************************************************************************************
 * Base Define
 **************************************************************************************************/
#define CPU1_TASK_TIME              (1000U)     /* us */

/***************************************************************************************************
 * SCI A,B,C & D DEFINE
 **************************************************************************************************/
#define SCIA_RXBUFSIZE              (100U)
#define SCIA_TXBUFSIZE              (50U)
#define SCIA_BAUDRATE               (115200) /* max 256000 by depend on HW */
#define SCIA_RXST_RXRDY             (HWREGH(SCIA_BASE + SCI_O_RXST) & SCI_RXST_RXRDY)
#define SCIA_RXBUF                  (HWREGH(SCIA_BASE + SCI_O_RXBUF) & 0xFFU)
#define SCIA_CTL2_TXRDY             (HWREGH(SCIA_BASE + SCI_O_CTL2) & SCI_CTL2_TXRDY)
#define SCIA_TXBUF                  (HWREGH(SCIA_BASE + SCI_O_TXBUF))

#define SCIB_RXBUFSIZE              (100U)
#define SCIB_TXBUFSIZE              (50U)
#define SCIB_BAUDRATE               (3125000)   /* TRM 3545page max 3.125Mbps */
#define SCIB_RXST_RXRDY             (HWREGH(SCIB_BASE + SCI_O_RXST) & SCI_RXST_RXRDY)
#define SCIB_RXBUF                  (HWREGH(SCIB_BASE + SCI_O_RXBUF) & 0xFFU)
#define SCIB_CTL2_TXRDY             (HWREGH(SCIB_BASE + SCI_O_CTL2) & SCI_CTL2_TXRDY)
#define SCIB_TXBUF                  (HWREGH(SCIB_BASE + SCI_O_TXBUF))

#define SCIC_RXBUFSIZE              (100U)
#define SCIC_TXBUFSIZE              (50U)
#define SCIC_BAUDRATE               (3125000)   /* TRM 3545page max 3.125Mbps */
#define SCIC_RXST_RXRDY             (HWREGH(SCIC_BASE + SCI_O_RXST) & SCI_RXST_RXRDY)
#define SCIC_RXBUF                  (HWREGH(SCIC_BASE + SCI_O_RXBUF) & 0xFFU)
#define SCIC_CTL2_TXRDY             (HWREGH(SCIC_BASE + SCI_O_CTL2) & SCI_CTL2_TXRDY)
#define SCIC_TXBUF                  (HWREGH(SCIC_BASE + SCI_O_TXBUF))

#define SCID_RXBUFSIZE              (100U)
#define SCID_TXBUFSIZE              (50U)
#define SCID_BAUDRATE               (3125000)   /* TRM 3545page max 3.125Mbps */
#define SCID_RXST_RXRDY             (HWREGH(SCID_BASE + SCI_O_RXST) & SCI_RXST_RXRDY)
#define SCID_RXBUF                  (HWREGH(SCID_BASE + SCI_O_RXBUF) & 0xFFU)
#define SCID_CTL2_TXRDY             (HWREGH(SCID_BASE + SCI_O_CTL2) & SCI_CTL2_TXRDY)
#define SCID_TXBUF                  (HWREGH(SCID_BASE + SCI_O_TXBUF))

/***************************************************************************************************
 * SPI DEFINE
 * SPIA's App. : EEPROM
 * SPIB's App. : Accelerometer Sensor
 * SPIC's App. : IO-Link Transmitter I/F
 **************************************************************************************************/
#define SPIA_FREQ                   (8000000U)  /* M95M04-DR, MAX. 10,000,000U */
#define SPIA_TXBUF_REG              (HWREGH(SPIA_BASE + SPI_O_TXBUF))
#define SPIA_RXBUF_REG              (HWREGH(SPIA_BASE + SPI_O_RXBUF))
#define SPIA_INT_FLAG               (HWREGH(SPIA_BASE + SPI_O_STS) & SPI_STS_INT_FLAG)

#define SPIB_FREQ                   (8000000U)  /* KX132-1211, MAX. 10,000,000U */
#define SPIB_TXBUF_REG              (HWREGH(SPIB_BASE + SPI_O_TXBUF))
#define SPIB_RXBUF_REG              (HWREGH(SPIB_BASE + SPI_O_RXBUF))
#define SPIB_INT_FLAG               (HWREGH(SPIB_BASE + SPI_O_STS) & SPI_STS_INT_FLAG)

#define SPIC_FREQ                   (8000000U)  /* MAX. 8000000U */
#define SPIC_TXBUF_REG              (HWREGH(SPIC_BASE + SPI_O_TXBUF))
#define SPIC_RXBUF_REG              (HWREGH(SPIC_BASE + SPI_O_RXBUF))
#define SPIC_INT_FLAG               (HWREGH(SPIC_BASE + SPI_O_STS) & SPI_STS_INT_FLAG)

/***************************************************************************************************
 * API Functions
 **************************************************************************************************/
uint32 InitDRV(void);
uint32 InitCPUTimer012(void);
uint32 configCPUTimer(uint32 base_reg, uint32 period);
uint32 initADCs(void);
uint32 InitGPIO(void);

uint16 InitSCIA(void);
sint08 SCIA_TxReady(void);
void SCIA_SendFrame(sint16 s16Num, uint08 *u8Buf);
sint08 SCIA_GetRxBufByte(uint08 *u8Data);

uint16 InitSCIB(void);
sint08 SCIB_TxReady(void);
void SCIB_SendFrame(sint16 s16Num, uint08 *u8Buf);
sint08 SCIB_GetRxBufByte(uint08 *u8Data);

uint16 InitSCIC(void);
sint08 SCIC_TxReady(void);
void SCIC_SendFrame(sint16 s16Num, uint08 *u8Buf);
sint08 SCIC_GetRxBufByte(uint08 *u8Data);

uint16 InitSCID(void);
sint08 SCID_TxReady(void);
void SCID_SendFrame(sint16 s16Num, uint08 *u8Buf);
sint08 SCID_GetRxBufByte(uint08 *u8Data);
//uint16 InitSCIA(uint32 u32BaudRate, uint16 u16DataLength, uint16 u16Parity, uint16 u16StopBit);

#endif /* SOURCE_L0_BD6B0_DRVCPU1_H_ */
/* EOF */
