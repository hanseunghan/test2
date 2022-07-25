/***************************************************************************************************
 * File Name     : bd6b0_gpioCPU1.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              MODEFY by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6B0_GPIOCPU1_H_
#define SOURCE_L1_BD6B0_GPIOCPU1_H_

/***************************************************************************************************
 * GPIO Definitions
 **************************************************************************************************/
#define ON                  (1U)
#define OFF                 (0U)
#define nON                 (0U)
#define nOFF                (1U)

#define PNP_TYPE            (0U)
#define NPN_TYPE            (1U)

#define LED_BLINK           (0U)
#define LED_SOLID           (1U)

#define LED_BLUE            (0U)
#define LED_GREEN           (1U)
#define LED_RED             (2U)
#define LED_WHITE           (3U)
#define LED_YELLOW          (4U)
#define LED_PURPLE          (5U)

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

/***************************************************************************************************
 * GPIO DOUT Definitions
 **************************************************************************************************/
#define EX_PWR_ON           SET_PORTA = 0x00000100U     /* GPIO 8 */
#define EX_PWR_OFF          CLR_PORTA = 0x00000100U

#define EX_LED_GREEN_ON     SET_PORTA = 0x00000400U
#define EX_LED_GREEN_OFF    CLR_PORTA = 0x00000400U     /* GPIO 10 */
#define EX_LED_RED_ON       SET_PORTA = 0x00000800U
#define EX_LED_RED_OFF      CLR_PORTA = 0x00000800U     /* GPIO 11 */
#define EX_LED_BLUE_ON      SET_PORTA = 0x00001000U
#define EX_LED_BLUE_OFF     CLR_PORTA = 0x00001000U     /* GPIO 12 */

#define DO1_ON              SET_PORTB = 0x00000001U     /* GPIO 32 */
#define DO1_OFF             CLR_PORTB = 0x00000001U
#define DO2_ON              SET_PORTB = 0x00000002U     /* GPIO 33 */
#define DO2_OFF             CLR_PORTB = 0x00000002U

#define DI_TYPE_PNP         SET_PORTB = 0x00000010U     /* GPIO 36 */
#define DI_TYPE_NPN         CLR_PORTB = 0x00000010U

#define MB1_TXEN_ON         SET_PORTB = 0x00000100U     /* GPIO 40 */
#define MB1_TXEN_OFF        CLR_PORTB = 0x00000100U

#define MB2_TXEN_ON         SET_PORTB = 0x00000400U     /* GPIO 42 */
#define MB2_TXEN_OFF        CLR_PORTB = 0x00000400U

#define IO_TXEN_ON          SET_PORTB = 0x00020000U     /* GPIO 49 */
#define IO_TXEN_OFF         CLR_PORTB = 0x00020000U

#define IO_WUEN_ON          SET_PORTB = 0x08000000U     /* GPIO 59 */
#define IO_WUEN_OFF         CLR_PORTB = 0x08000000U

#define DO_TYPE_PNP         SET_PORTD = 0x00800000U, CLR_PORTD = 0x01000000U     /* GPIO 119,120 */
#define DO_TYPE_NPN         CLR_PORTD = 0x00800000U, SET_PORTD = 0x01000000U

#define LED_RED_ON          CLR_PORTD = 0x04000000U     /* GPIO 122 */
#define LED_RED_OFF         SET_PORTD = 0x04000000U
#define LED_BLUE_ON         CLR_PORTD = 0x08000000U     /* GPIO 123 */
#define LED_BLUE_OFF        SET_PORTD = 0x08000000U
#define LED_GREEN_ON        CLR_PORTD = 0x10000000U     /* GPIO 124 */
#define LED_GREEN_OFF       SET_PORTD = 0x10000000U

/***************************************************************************************************
 * GPIO DIN Definitions
 **************************************************************************************************/
#define DI1                 ((RD_PORTB & 0x00000004U)>>2U)   /* GPIO 34 */
#define DI2                 ((RD_PORTB & 0x00000008U)>>3U)   /* GPIO 35 */
#define DI_TOTAL            ((RD_PORTB & 0x0000000CU)>>2U)   /* GPIO 34,35 */

#define IO_UV               ((RD_PORTB & 0x01000000U)>>24U)  /* GPIO 56 */
#define IO_LI               ((RD_PORTB & 0x02000000U)>>25U)  /* GPIO 57 */
#define IO_nIRQ             ((RD_PORTB & 0x04000000U)>>26U)  /* GPIO 58 */

#define BTN1                ((RD_PORTC & 0x01000000U)>>24U)  /* GPIO 88 */
#define BTN2                ((RD_PORTC & 0x02000000U)>>25U)  /* GPIO 89 */
#define BTN3                ((RD_PORTC & 0x04000000U)>>26U)  /* GPIO 90 */
#define BTN4                ((RD_PORTC & 0x08000000U)>>27U)  /* GPIO 91 */
#define BTN5                ((RD_PORTC & 0x10000000U)>>28U)  /* GPIO 92 */
#define BTN_TOTAL           ((RD_PORTC & 0x1F000000U)>>24U)  /* GPIO */

#define ACM_TRIG            ((RD_PORTD & 0x00000080U)>>7U)   /* GPIO 103 */
#define ACM_INT1            ((RD_PORTD & 0x00000100U)>>8U)   /* GPIO 104 */
#define ACM_INT2            ((RD_PORTD & 0x00000200U)>>9U)   /* GPIO 105 */

/***************************************************************************************************
 * Macro Definitions
 **************************************************************************************************/
//#define TOGGLE_OTHER(data)  ((data==OFF)? ON : OFF)
//#define TOGGLE(data)        data = ((data==OFF)? ON : OFF)

#endif /* SOURCE_L1_BD6B0_GPIOCPU1_H_ */
/* EOF */

