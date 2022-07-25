/***************************************************************************************************
 * File Name     : bd6tx_gpioCPU2.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              MODEFY by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6TX_GPIOCPU2_H_
#define SOURCE_L1_BD6TX_GPIOCPU2_H_


/***************************************************************************************************
 * GPIO Definitions
 **************************************************************************************************/
#define ON                  (1U)
#define OFF                 (0U)
#define nON                 (0U)
#define nOFF                (1U)

#if 0 //bd6f0 source
#define SET_PORTA   (*(volatile uint32_t *)(GPIODATA_BASE+0x02U))   /* GPIO 0~31    */
#define SET_PORTB   (*(volatile uint32_t *)(GPIODATA_BASE+0x0AU))   /* GPIO 32~63   */
#define SET_PORTC   (*(volatile uint32_t *)(GPIODATA_BASE+0x12U))   /* GPIO 64~95   */
#define SET_PORTD   (*(volatile uint32_t *)(GPIODATA_BASE+0x1AU))   /* GPIO 96~127  */
#define SET_PORTE   (*(volatile uint32_t *)(GPIODATA_BASE+0x22U))   /* GPIO 128~159 */
#define SET_PORTF   (*(volatile uint32_t *)(GPIODATA_BASE+0x2AU))   /* GPIO 160~168 */

#define CLR_PORTA   (*(volatile uint32_t *)(GPIODATA_BASE+0x04U))   /* GPIO 0~31    */
#define CLR_PORTB   (*(volatile uint32_t *)(GPIODATA_BASE+0x0CU))   /* GPIO 32~63   */
#define CLR_PORTC   (*(volatile uint32_t *)(GPIODATA_BASE+0x14U))   /* GPIO 64~95   */
#define CLR_PORTD   (*(volatile uint32_t *)(GPIODATA_BASE+0x1CU))   /* GPIO 96~127  */
#define CLR_PORTE   (*(volatile uint32_t *)(GPIODATA_BASE+0x24U))   /* GPIO 128~159 */
#define CLR_PORTF   (*(volatile uint32_t *)(GPIODATA_BASE+0x2CU))   /* GPIO 160~168 */

#define RD_PORTA    (*(volatile uint32_t *)(GPIODATA_BASE+0x00U))   /* GPIO 0~31    */
#define RD_PORTB    (*(volatile uint32_t *)(GPIODATA_BASE+0x08U))   /* GPIO 32~63   */
#define RD_PORTC    (*(volatile uint32_t *)(GPIODATA_BASE+0x10U))   /* GPIO 64~95   */
#define RD_PORTD    (*(volatile uint32_t *)(GPIODATA_BASE+0x18U))   /* GPIO 96~127  */
#define RD_PORTE    (*(volatile uint32_t *)(GPIODATA_BASE+0x20U))   /* GPIO 128~159 */
#define RD_PORTF    (*(volatile uint32_t *)(GPIODATA_BASE+0x28U))   /* GPIO 160~168 */

#define WR_PORTA    (*(volatile uint32_t *)(GPIODATA_BASE+0x00U))   /* GPIO 0~31    */
#define WR_PORTB    (*(volatile uint32_t *)(GPIODATA_BASE+0x08U))   /* GPIO 32~63   */
#define WR_PORTC    (*(volatile uint32_t *)(GPIODATA_BASE+0x10U))   /* GPIO 64~95   */
#define WR_PORTD    (*(volatile uint32_t *)(GPIODATA_BASE+0x18U))   /* GPIO 96~127  */
#define WR_PORTE    (*(volatile uint32_t *)(GPIODATA_BASE+0x20U))   /* GPIO 128~159 */
#define WR_PORTF    (*(volatile uint32_t *)(GPIODATA_BASE+0x28U))   /* GPIO 160~168 */

//#define RD_PORTA    (*(volatile uint32_t *)(GPIODATAREAD_BASE+0x00U))   /* GPIO 0~31    */
//#define RD_PORTB    (*(volatile uint32_t *)(GPIODATAREAD_BASE+0x02U))   /* GPIO 32~63   */
//#define RD_PORTC    (*(volatile uint32_t *)(GPIODATAREAD_BASE+0x04U))   /* GPIO 64~95   */
//#define RD_PORTD    (*(volatile uint32_t *)(GPIODATAREAD_BASE+0x06U))   /* GPIO 96~127  */
//#define RD_PORTE    (*(volatile uint32_t *)(GPIODATAREAD_BASE+0x08U))   /* GPIO 128~159 */
//#define RD_PORTF    (*(volatile uint32_t *)(GPIODATAREAD_BASE+0x0AU))   /* GPIO 160~168 */

/***************************************************************************************************
 * GPIO DOUT Definitions
 **************************************************************************************************/
#define AB_DO_ON            SET_PORTA = 0x00000800U     /* GPIO 0~31 11-0= 11, GPIO 11 */
#define AB_DO_OFF           CLR_PORTA = 0x00000800U

#define SPIA_CS_HIGH        SET_PORTA = 0x00080000U     /* GPIO 0~31 19-0= 19, GPIO 11 */
#define SPIA_CS_LOW         CLR_PORTA = 0x00080000U

#define AB_COM_DO0_ON       SET_PORTA = 0x01000000U     /* GPIO 0~31 24-0= 24, GPIO 24 */
#define AB_COM_DO0_OFF      CLR_PORTA = 0x01000000U
#define AB_COM_DO1_ON       SET_PORTA = 0x02000000U     /* GPIO 0~31 25-0= 25, GPIO 25 */
#define AB_COM_DO1_OFF      CLR_PORTA = 0x02000000U
#define A_STO1_ON           SET_PORTD = 0x00001000U     /* GPIO 96~127 108-96= 12, GPIO 108 */
#define A_STO1_OFF          CLR_PORTD = 0x00001000U
#define B_STO2_ON           SET_PORTD = 0x00001000U     /* GPIO 96~127 108-96= 12, GPIO 108 */
#define B_STO2_OFF          CLR_PORTD = 0x00001000U
#define A_T1_ON             SET_PORTD = 0x00002000U     /* GPIO 96~127 109-96= 13, GPIO 109 */
#define A_T1_OFF            CLR_PORTD = 0x00002000U
#define B_T2_ON             SET_PORTD = 0x00002000U     /* GPIO 96~127 109-96= 13, GPIO 109 */
#define B_T2_OFF            CLR_PORTD = 0x00002000U
#define A_PLC_EMOUT1_ON     SET_PORTD = 0x00004000U     /* GPIO 96~127 110-96= 14, GPIO 110 */
#define A_PLC_EMOUT1_OFF    CLR_PORTD = 0x00004000U
#define B_PLC_EMOUT2_ON     SET_PORTD = 0x00004000U     /* GPIO 96~127 110-96= 14, GPIO 110 */
#define B_PLC_EMOUT2_OFF    CLR_PORTD = 0x00004000U
#define A_PLC_T0_EN_ON      SET_PORTD = 0x00008000U     /* GPIO 96~127 111-96= 15, GPIO 111 */
#define A_PLC_T0_EN_OFF     CLR_PORTD = 0x00008000U
#define AB_WDI_ON           SET_PORTD = 0x00200000U     /* GPIO 96~127 117-96= 21, GPIO 117 */
#define AB_WDI_OFF          CLR_PORTD = 0x00200000U
#define AB_nWDE_ON          CLR_PORTD = 0x00400000U     /* GPIO 96~127 118-96= 22, GPIO 118 */
#define AB_nWDE_OFF         SET_PORTD = 0x00400000U
#define AB_LED_RED_ON       CLR_PORTD = 0x00800000U     /* GPIO 96~127 119-96= 23, GPIO 119 */
#define AB_LED_RED_OFF      SET_PORTD = 0x00800000U
#define AB_LED_BLUE_ON      CLR_PORTD = 0x01000000U     /* GPIO 96~127 120-96= 24, GPIO 120 */
#define AB_LED_BLUE_OFF     SET_PORTD = 0x01000000U
#define AB_LED_GREEN_ON     CLR_PORTD = 0x02000000U     /* GPIO 96~127 121-96= 25, GPIO 121 */
#define AB_LED_GREEN_OFF    SET_PORTD = 0x02000000U

#define B_LAMP_START_ON     SET_PORTD = 0x08000000U     /* GPIO 96~127 123-96= 27, GPIO 123 */
#define B_LAMP_START_OFF    CLR_PORTD = 0x08000000U
#define B_LAMP_STOP_ON      SET_PORTD = 0x10000000U     /* GPIO 96~127 124-96= 28, GPIO 124 */
#define B_LAMP_STOP_OFF     CLR_PORTD = 0x10000000U
#define B_LAMP_MTR_ON       SET_PORTD = 0x20000000U     /* GPIO 96~127 125-96= 29, GPIO 125 */
#define B_LAMP_MTR_OFF      CLR_PORTD = 0x20000000U
#define B_LAMP_ERR_ON       SET_PORTD = 0x40000000U     /* GPIO 96~127 126-96= 30, GPIO 126 */
#define B_LAMP_ERR_OFF      CLR_PORTD = 0x40000000U
#define B_LAMP_PWR_ON       SET_PORTD = 0x80000000U     /* GPIO 96~127 127-96= 31, GPIO 127 */
#define B_LAMP_PWR_OFF      CLR_PORTD = 0x80000000U

/***************************************************************************************************
 * GPIO DIN Definitions
 **************************************************************************************************/
#define AB_DI               ((RD_PORTA & 0x00000400U)>>10U)  /* GPIO 0~31, 10-0 = 10, GPIO 10 */
#define EXAB_5V_PG          ((RD_PORTA & 0x00200000U)>>21U)  /* GPIO 0~31, 21-0 = 21, GPIO 21 */
#define AB_COM_DI0          ((RD_PORTA & 0x04000000U)>>26U)  /* GPIO 0~31, 26-0 = 26, GPIO 26 */
#define AB_COM_DI1          ((RD_PORTA & 0x08000000U)>>27U)  /* GPIO 0~31, 27-0 = 27, GPIO 27 */
#define MCU_TYPE            ((RD_PORTC & 0x00000008U)>>3U)   /* GPIO 64~95, 67-64 = 3, GPIO 67 */
#define A_nSTO1_FB          ((RD_PORTD & 0x00000008U)>>3U)   /* GPIO 96~127, 99-96 = 3, GPIO 99 */
#define B_nSTO2_FB          ((RD_PORTD & 0x00000008U)>>3U)
#define A_nT1_FB            ((RD_PORTD & 0x00000010U)>>4U)   /* GPIO 96~127, 100-96 = 4, GPIO 100 */
#define B_nT2_FB            ((RD_PORTD & 0x00000010U)>>4U)
#define A_nT1_FDK           ((RD_PORTD & 0x00000020U)>>5U)   /* GPIO 96~127, 101-96 = 5, GPIO 101 */
#define B_nT2_FDK           ((RD_PORTD & 0x00000020U)>>5U)
#define A_PLC_nES1          ((RD_PORTD & 0x00000040U)>>6U)   /* GPIO 96~127, 102-96 = 6, GPIO 102 */
#define B_PLC_nES2          ((RD_PORTD & 0x00000040U)>>6U)
#define A_PLC_nSG1          ((RD_PORTD & 0x00000080U)>>7U)   /* GPIO 96~127, 103-96 = 7, GPIO 103 */
#define B_PLC_nSG2          ((RD_PORTD & 0x00000080U)>>7U)

//#define RD_DIN_TOTAL    ((RD_PORTC >> 8U)&0xFFU)        /* GPIO 64~95   */
//#define WR_DOUT(data)   WR_PORTA &= (U32)(0xFFFF00FFU | ((data&0xFFU) << 8U))    /* GPIO 8~15   */

/***************************************************************************************************
 * Macro Definitions
 **************************************************************************************************/
//#define TOGGLE_OTHER(data)  ((data==OFF)? ON : OFF)
//#define TOGGLE(data)        data = ((data==OFF)? ON : OFF)
#endif

#endif /* SOURCE_L1_BD6TX_GPIOCPU2_H_ */
/* EOF */
