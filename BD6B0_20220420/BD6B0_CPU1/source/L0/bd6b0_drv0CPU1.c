/***************************************************************************************************
 * File Name     : bd6tx_drv0CPU1.c
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

extern __interrupt void task_cpu1(void);
/***************************************************************************************************
 * Driver Init
 **************************************************************************************************/
uint32 InitDRV(void)
{
    InitCPUTimer012();  /* T0: task, T1: no-used, T2: time check */

    initADCs();

    InitSCIA();         /* DEBUG */

    configCPUTimer(CPUTIMER0_BASE, CPU1_TASK_TIME); /* Config CPU-Timer0 to interrupt every second */
    Interrupt_register(INT_TIMER0, &task_cpu1);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);                   /* Enable TINT0 in the PIE: Group 1 interrupt 7 */

    CPUTimer_startTimer(CPUTIMER0_BASE);            /* Starts CPU-Timer 0 */
    //CPUTimer_startTimer(CPUTIMER1_BASE);          /* Starts CPU-Timer 1 */
    CPUTimer_startTimer(CPUTIMER2_BASE);            /* Starts CPU-Timer 2 */

    return (0U);
}

/***************************************************************************************************
 * CPUTimer Init
 **************************************************************************************************/
uint32 InitCPUTimer012(void)
{
    /* Initializes the CPU Timers. */
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF); /* Timer period to maximum */
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0U);      /* pre-scale counter to divide by 1(SYSCLKOUT) */
    CPUTimer_stopTimer(CPUTIMER0_BASE);             /* Make sure timer is stopped */
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);    /* Reload all counter register with period value */

    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0U);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);

    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0U);
    CPUTimer_stopTimer(CPUTIMER2_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    /* Initializes timer control register. The timer is stopped, reloaded, free run disabled
       Additionally, the free and soft bits are set */
    CPUTimer_stopTimer(CPUTIMER2_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);
    CPUTimer_setEmulationMode(CPUTIMER2_BASE, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);

    return (0U);
}

/***************************************************************************************************
 * CPUTimer Configure
 **************************************************************************************************/
uint32 configCPUTimer(uint32 base_reg, uint32 period)
{
    uint32 u32Temp = 0U;
    uint32 u32Freq = DEVICE_SYSCLK_FREQ;

    /* Initialize timer period */
    u32Temp = ((u32Freq / 1000000) * period);
    CPUTimer_setPeriod(base_reg, u32Temp);

    /* Set pre-scale counter to divide by 1(SYSCLKOUT) */
    CPUTimer_setPreScaler(base_reg, 0);

    /* Initializes timer control register. The timer is stopped, reloaded, free run disabled
       Additionally, the free and soft bits are set */
    CPUTimer_stopTimer(base_reg);
    CPUTimer_reloadTimerCounter(base_reg);
    CPUTimer_setEmulationMode(base_reg, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);

    return (0U);
}

/***************************************************************************************************
 * ADC-A,B Initial & Configure
 **************************************************************************************************/
uint32 initADCs(void)
{
    /***********************************************************************************************
     * ADC-A Init & Configure
     **********************************************************************************************/
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);                       /* Set ADCCLK divider to /4 */
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);/* Set resolution and signal mode and load corresponding trims. */
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);        /* Set pulse positions to late */

    ADC_enableConverter(ADCA_BASE); /* Power up the ADCs and then delay for 1 ms */
    DEVICE_DELAY_US(1000);

    /* Configure SOCs be triggered by software a sampling window of 15(75 ns at a 200MHz SYSCLK rate)
     * will be used. */
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 15);   /* AIN_TEMP1   */
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 15);   /* AIN_EX_P24V */
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 15);   /* AIN_EX_IOUT */

    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER4); /* Set SOC1 to set the interrupt 1 flag. */
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);                     /* Enable the interrupt and make */
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);                /* sure its flag is cleared. */

    /***********************************************************************************************
     * ADC-B Init & Configure
     **********************************************************************************************/
    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCB_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setInterruptPulseMode(ADCB_BASE, ADC_PULSE_END_OF_CONV);

    ADC_enableConverter(ADCB_BASE); /* Power up the ADCs and then delay for 1 ms */
    DEVICE_DELAY_US(1000);

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 15);   /* AIN_P24V */
    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 15);   /* AIN_P5V0 */
    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 15);   /* AIN_P3V3 */
    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, 15);   /* AIN_P1V2 */

    ADC_setInterruptSource(ADCB_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER5); /* Set SOC1 to set the interrupt 1 flag. */
    ADC_enableInterrupt(ADCB_BASE, ADC_INT_NUMBER2);                     /* Enable the interrupt and make */
    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2);                /* sure its flag is cleared. */

#if 0U
    /***********************************************************************************************
     * ADC-C Init & Configure
     **********************************************************************************************/
    ADC_setPrescaler(ADCC_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setInterruptPulseMode(ADCC_BASE, ADC_PULSE_END_OF_CONV);

    ADC_enableConverter(ADCC_BASE);
    DEVICE_DELAY_US(1000);

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 15);
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 15);
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 15);
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, 15);

    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER5);
    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER3);
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER3);

    /***********************************************************************************************
     * ADC-D Init & Configure
     **********************************************************************************************/
    ADC_setPrescaler(ADCD_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setInterruptPulseMode(ADCD_BASE, ADC_PULSE_END_OF_CONV);

    ADC_enableConverter(ADCD_BASE);
    DEVICE_DELAY_US(1000);

    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN14, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN15, 15);

    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER15);
    ADC_enableInterrupt(ADCD_BASE, ADC_INT_NUMBER4);
    ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER4);
#endif

    return (0U);
}

/***************************************************************************************************
 * GPIO Init
 **************************************************************************************************/
uint32 InitGPIO(void)
{
    Device_initGPIO();  /* Initialize GPIO and configure the GPIO pin as a push-pull output */

#if 0 //EVM TEST
    GPIO_setPadConfig(31U, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(31U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(34U, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(34U, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(34U, GPIO_CORE_CPU2);

    GPIO_setPadConfig(145U, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(145U, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(145U, GPIO_CORE_CM);
#endif //EVM TEST

    /* No connection (input mode with internal pull up enabled) */
    /* GPIO 0,1,2,3,4,5,6,7 */
    GPIO_setPadConfig(0U, GPIO_PIN_TYPE_PULLUP);    /* Enable pull-up   */
    GPIO_setPinConfig(GPIO_0_GPIO0);                /* GPIO mode        */
    GPIO_setDirectionMode(0U, GPIO_DIR_MODE_IN);    /* Input mode       */

    GPIO_setPadConfig(1U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_1_GPIO1);
    GPIO_setDirectionMode(1U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(2U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_2_GPIO2);
    GPIO_setDirectionMode(2U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(3U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_3_GPIO3);
    GPIO_setDirectionMode(3U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(4U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(4U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(5U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_5_GPIO5);
    GPIO_setDirectionMode(5U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(6U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_6_GPIO6);
    GPIO_setDirectionMode(6U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(7U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_7_GPIO7);
    GPIO_setDirectionMode(7U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 8, EX_PWR_ON */
    GPIO_setPadConfig(8U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_8_GPIO8);
    GPIO_setDirectionMode(8U, GPIO_DIR_MODE_OUT);
    EX_PWR_OFF;

    /* NC, GPIO 9 */
    GPIO_setPadConfig(9U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_9_GPIO9);
    GPIO_setDirectionMode(9U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 10,11,12, LED_GREEN, LED_RED, LED_BLUE */
    GPIO_setPadConfig(10U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_10_GPIO10);
    GPIO_setDirectionMode(10U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(11U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_11_GPIO11);
    GPIO_setDirectionMode(11U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(12U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_12_GPIO12);
    GPIO_setDirectionMode(12U, GPIO_DIR_MODE_OUT);

    EX_LED_GREEN_OFF;
    EX_LED_RED_OFF;
    EX_LED_BLUE_OFF;

    /* NC, GPIO 13,14,15 */
    GPIO_setPadConfig(13U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_13_GPIO13);
    GPIO_setDirectionMode(13U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(14U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_14_GPIO14);
    GPIO_setDirectionMode(14U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(15U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_15_GPIO15);
    GPIO_setDirectionMode(15U, GPIO_DIR_MODE_IN);

    /* SPI-A on GPIO16,17,18,19 */
    GPIO_setPadConfig(16U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(17U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(18U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(19U, GPIO_PIN_TYPE_STD);

    GPIO_setQualificationMode(16U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(17U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(18U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(19U, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_16_SPIA_SIMO);
    GPIO_setPinConfig(GPIO_17_SPIA_SOMI);
    GPIO_setPinConfig(GPIO_18_SPIA_CLK);
    GPIO_setPinConfig(GPIO_19_GPIO19);
    GPIO_setDirectionMode(19, GPIO_DIR_MODE_OUT);

    /* NC, GPIO 20,21 */
    GPIO_setPadConfig(20U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_20_GPIO20);
    GPIO_setDirectionMode(20U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(21U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_21_GPIO21);
    GPIO_setDirectionMode(21U, GPIO_DIR_MODE_IN);

    /* SPI-B on GPIO 22,23,24,25 */
    GPIO_setPadConfig(22U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(23U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(24U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(25U, GPIO_PIN_TYPE_STD);

    GPIO_setQualificationMode(22U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(23U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(24U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(25U, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_22_SPIB_CLK);
    GPIO_setPinConfig(GPIO_23_GPIO23);
    GPIO_setDirectionMode(23, GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(GPIO_24_SPIB_SIMO);
    GPIO_setPinConfig(GPIO_25_SPIB_SOMI);

    /* NC, GPIO 26,27 */
    GPIO_setPadConfig(26U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_26_GPIO26);
    GPIO_setDirectionMode(26U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(27U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_27_GPIO27);
    GPIO_setDirectionMode(27U, GPIO_DIR_MODE_IN);

    /* SCI-A, GPIO 28,29 */
    GPIO_setPadConfig(29U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_29_SCIA_TX);
    GPIO_setPadConfig(28U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(29U, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_28_SCIA_RX);

    /* NC, GPIO 30,31 */
    GPIO_setPadConfig(30U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_30_GPIO30);
    GPIO_setDirectionMode(30U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(31U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_31_GPIO31);
    GPIO_setDirectionMode(31U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 32,33, DO1, DO2 */
    GPIO_setPadConfig(32U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_32_GPIO32);
    GPIO_setDirectionMode(32U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(33U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_33_GPIO33);
    GPIO_setDirectionMode(33U, GPIO_DIR_MODE_OUT);

    DO1_OFF;
    DO2_OFF;

    /* DI, GPIO 34,35, DI1, DI2 */
    GPIO_setPadConfig(34U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_34_GPIO34);
    GPIO_setDirectionMode(34U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(35U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setDirectionMode(35U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 36, DI_TYPE */
    GPIO_setPadConfig(36U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_36_GPIO36);
    GPIO_setDirectionMode(36U, GPIO_DIR_MODE_OUT);
    DI_TYPE_PNP;

    /* NC, GPIO 37 */
    GPIO_setPadConfig(37U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_37_GPIO37);
    GPIO_setDirectionMode(37U, GPIO_DIR_MODE_IN);

    /* SCI-C, GPIO 38,39 */
    GPIO_setPadConfig(38U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_38_SCIC_TX);

    GPIO_setPadConfig(39U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(39U, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_39_SCIC_RX);

    /* DO, GPIO 40, MB1_TXEN */
    GPIO_setPadConfig(40U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_40_GPIO40);
    GPIO_setDirectionMode(40U, GPIO_DIR_MODE_OUT);
    MB1_TXEN_ON;

    /* NC, GPIO 41 */
    GPIO_setPadConfig(41U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_41_GPIO41);
    GPIO_setDirectionMode(41U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 42, MB2_TXEN */
    GPIO_setPadConfig(42U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_42_GPIO42);
    GPIO_setDirectionMode(42U, GPIO_DIR_MODE_OUT);
    MB2_TXEN_ON;

    /* NC, GPIO 43,44,45 */
    GPIO_setPadConfig(43U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_43_GPIO43);
    GPIO_setDirectionMode(43U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(44U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_44_GPIO44);
    GPIO_setDirectionMode(44U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(45U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_45_GPIO45);
    GPIO_setDirectionMode(45U, GPIO_DIR_MODE_IN);

    /* SCI-D, GPIO 46,47 */
    GPIO_setPadConfig(46U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_46_SCID_RX);

    GPIO_setPadConfig(47U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(47U, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_47_SCID_TX);

    /* NC, GPIO 48 */
    GPIO_setPadConfig(48U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_48_GPIO48);
    GPIO_setDirectionMode(48U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 49, IO_TXEN */
    GPIO_setPadConfig(49U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_49_GPIO49);
    GPIO_setDirectionMode(49U, GPIO_DIR_MODE_OUT);
    IO_TXEN_ON;

    /* SPI-C on GPIO 50,51,52,53 */
    GPIO_setPadConfig(50U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(51U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(52U, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(53U, GPIO_PIN_TYPE_STD);

    GPIO_setQualificationMode(50U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(51U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(52U, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(53U, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_50_SPIC_SIMO);
    GPIO_setPinConfig(GPIO_51_SPIC_SOMI);
    GPIO_setPinConfig(GPIO_52_SPIC_CLK);
    GPIO_setPinConfig(GPIO_53_GPIO53);
    GPIO_setDirectionMode(53U, GPIO_DIR_MODE_OUT);

    /* SCI-B, GPIO 54,55 */
    GPIO_setPadConfig(54U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_54_SCIB_TX);

    GPIO_setPadConfig(55U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(55U, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_55_SCIB_RX);

    /* DI, GPIO 56,57,58, IO_UV, IO_LI, IO_nIRQ */
    GPIO_setPadConfig(56U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_56_GPIO56);
    GPIO_setDirectionMode(56U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(57U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_57_GPIO57);
    GPIO_setDirectionMode(57U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(58U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_58_GPIO58);
    GPIO_setDirectionMode(58U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 59, IO_WUEN */
    GPIO_setPadConfig(59U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_59_GPIO59);
    GPIO_setDirectionMode(59U, GPIO_DIR_MODE_OUT);

    /* NC, GPIO 60,61,62,63,64,65,66,67,68,69 */
    GPIO_setPadConfig(60U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_60_GPIO60);
    GPIO_setDirectionMode(60U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(61U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_61_GPIO61);
    GPIO_setDirectionMode(61U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(62U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_62_GPIO62);
    GPIO_setDirectionMode(62U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(63U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_63_GPIO63);
    GPIO_setDirectionMode(63U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(64U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_64_GPIO64);
    GPIO_setDirectionMode(64U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(65U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_65_GPIO65);
    GPIO_setDirectionMode(65U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(66U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_66_GPIO66);
    GPIO_setDirectionMode(66U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(67U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_67_GPIO67);
    GPIO_setDirectionMode(67U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(68U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_68_GPIO68);
    GPIO_setDirectionMode(68U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(69U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_69_GPIO69);
    GPIO_setDirectionMode(69U, GPIO_DIR_MODE_IN);

    /* NC, GPIO 70,71,72,73,74,75,76 */
    GPIO_setPadConfig(70U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_70_GPIO70);
    GPIO_setDirectionMode(70U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(71U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_71_GPIO71);
    GPIO_setDirectionMode(71U, GPIO_DIR_MODE_IN);

    //GPIO_setPadConfig(72U, GPIO_PIN_TYPE_PULLUP);
    //GPIO_setPinConfig(GPIO_72_GPIO72);
    //GPIO_setDirectionMode(72U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(73U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_73_GPIO73);
    GPIO_setDirectionMode(73U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(74U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_74_GPIO74);
    GPIO_setDirectionMode(74U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(75U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_75_GPIO75);
    GPIO_setDirectionMode(75U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(76U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_76_GPIO76);
    GPIO_setDirectionMode(76U, GPIO_DIR_MODE_IN);

    /* ETHERCAT GPIO 77,78,79,80,81,82,83 ENDING LINE */

    /* NC, GPIO 84,85,86,87 */
    //GPIO_setPadConfig(84U, GPIO_PIN_TYPE_PULLUP);
    //GPIO_setPinConfig(GPIO_84_GPIO84);
    //GPIO_setDirectionMode(84U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(85U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_85_GPIO85);
    GPIO_setDirectionMode(85U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(86U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_86_GPIO86);
    GPIO_setDirectionMode(86U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(87U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_87_GPIO87);
    GPIO_setDirectionMode(87U, GPIO_DIR_MODE_IN);

    /* DI, GPIO 88,89,90,91,92, BTN1 ~ BTN5 */
    GPIO_setPadConfig(88U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_88_GPIO88);
    GPIO_setDirectionMode(88U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(89U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_89_GPIO89);
    GPIO_setDirectionMode(89U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(90U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_90_GPIO90);
    GPIO_setDirectionMode(90U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(91U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_91_GPIO91);
    GPIO_setDirectionMode(91U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(92U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_92_GPIO92);
    GPIO_setDirectionMode(92U, GPIO_DIR_MODE_IN);

    /* NC, GPIO 93,94,95,96,97,98,99 */
    GPIO_setPadConfig(93U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_93_GPIO93);
    GPIO_setDirectionMode(93U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(94U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_94_GPIO94);
    GPIO_setDirectionMode(94U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(95U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_95_GPIO95);
    GPIO_setDirectionMode(95U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(96U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_96_GPIO96);
    GPIO_setDirectionMode(96U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(97U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_97_GPIO97);
    GPIO_setDirectionMode(97U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(98U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_98_GPIO98);
    GPIO_setDirectionMode(98U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(99U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_99_GPIO99);
    GPIO_setDirectionMode(99U, GPIO_DIR_MODE_IN);

    /* NC, GPIO 100,101,102 */
    GPIO_setPadConfig(100U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_100_GPIO100);
    GPIO_setDirectionMode(100U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(101U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_101_GPIO101);
    GPIO_setDirectionMode(101U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(102U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_102_GPIO102);
    GPIO_setDirectionMode(102U, GPIO_DIR_MODE_IN);

    /* DI, GPIO 103,104,105, ACM_TRIG, ACM_INT1, ACM_INT2 */
    GPIO_setPadConfig(103U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_103_GPIO103);
    GPIO_setDirectionMode(103U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(104U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_104_GPIO104);
    GPIO_setDirectionMode(104U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(105U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_105_GPIO105);
    GPIO_setDirectionMode(105U, GPIO_DIR_MODE_IN);

    /* NC, GPIO 106,107,108,109 */
    GPIO_setPadConfig(106U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_106_GPIO106);
    GPIO_setDirectionMode(106U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(107U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_107_GPIO107);
    GPIO_setDirectionMode(107U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(108U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_108_GPIO108);
    GPIO_setDirectionMode(108U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(109U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_109_GPIO109);
    GPIO_setDirectionMode(109U, GPIO_DIR_MODE_IN);

    /* NC, GPIO 110,111,112,113,114,115,116,117,118 */
    GPIO_setPadConfig(110U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_110_GPIO110);
    GPIO_setDirectionMode(110U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(111U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_111_GPIO111);
    GPIO_setDirectionMode(111U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(112U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_112_GPIO112);
    GPIO_setDirectionMode(112U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(113U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_113_GPIO113);
    GPIO_setDirectionMode(113U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(114U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_114_GPIO114);
    GPIO_setDirectionMode(114U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(115U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_115_GPIO115);
    GPIO_setDirectionMode(115U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(116U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_116_GPIO116);
    GPIO_setDirectionMode(116U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(117U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_117_GPIO117);
    GPIO_setDirectionMode(117U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(118U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_118_GPIO118);
    GPIO_setDirectionMode(118U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 119,120, DO_PNP, DO_NPN */
    GPIO_setPadConfig(119U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_119_GPIO119);
    GPIO_setDirectionMode(119U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(120U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_120_GPIO120);
    GPIO_setDirectionMode(120U, GPIO_DIR_MODE_OUT);

    DO_TYPE_PNP;

    /* NC, GPIO 121 */
    GPIO_setPadConfig(121U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_121_GPIO121);
    GPIO_setDirectionMode(121U, GPIO_DIR_MODE_IN);

    /* DO, GPIO 122,123,124, LED_R, LED_B, LED_G */
    GPIO_setPadConfig(122U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_122_GPIO122);
    GPIO_setDirectionMode(122U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(123U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_123_GPIO123);
    GPIO_setDirectionMode(123U, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(124U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_124_GPIO124);
    GPIO_setDirectionMode(124U, GPIO_DIR_MODE_OUT);

    LED_RED_OFF;
    LED_BLUE_OFF;
    LED_GREEN_OFF;

    /* NC, GPIO 125,126,127,128 */
    GPIO_setPadConfig(125U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_125_GPIO125);
    GPIO_setDirectionMode(125U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(126U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_126_GPIO126);
    GPIO_setDirectionMode(126U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(127U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_127_GPIO127);
    GPIO_setDirectionMode(127U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(128U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_128_GPIO128);
    GPIO_setDirectionMode(128U, GPIO_DIR_MODE_IN);

    /* ETHERCAT GPIO 129,130,131,132, ENDING LINE */

    /* NC, GPIO 133 */
    GPIO_setPadConfig(133U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_133_GPIO133);
    GPIO_setDirectionMode(133U, GPIO_DIR_MODE_IN);

    /* ETHERCAT GPIO 134,135,136,137,138,139,140,141,142,143,144,145,146, ENDING LINE */

    /* NC, GPIO 147 */
    GPIO_setPadConfig(147U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_147_GPIO147);
    GPIO_setDirectionMode(147U, GPIO_DIR_MODE_IN);

    /* ETHERCAT GPIO 148,149,150,151,152,153,154,155,156,157,158,159,160,161, ENDING LINE */

    /* NC, GPIO 162,163,164,165,166,167,168 */
    GPIO_setPadConfig(162U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_162_GPIO162);
    GPIO_setDirectionMode(162U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(163U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_163_GPIO163);
    GPIO_setDirectionMode(163U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(164U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_164_GPIO164);
    GPIO_setDirectionMode(164U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(165U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_165_GPIO165);
    GPIO_setDirectionMode(165U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(166U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_166_GPIO166);
    GPIO_setDirectionMode(166U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(167U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_167_GPIO167);
    GPIO_setDirectionMode(167U, GPIO_DIR_MODE_IN);

    GPIO_setPadConfig(168U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPinConfig(GPIO_168_GPIO168);
    GPIO_setDirectionMode(168U, GPIO_DIR_MODE_IN);

#if 0
    /* EtherCAT Ports */
    GPIO_setPinConfig(GPIO_152_ESC_MDIO_CLK);
    GPIO_setPinConfig(GPIO_153_ESC_MDIO_DATA);
    GPIO_setPinConfig(GPIO_155_ESC_PHY_RESETN);
    GPIO_setPinConfig(GPIO_154_ESC_PHY_CLK);

    GPIO_setPinConfig(GPIO_157_ESC_TX0_CLK);
    GPIO_setPinConfig(GPIO_156_ESC_TX0_ENA);
    GPIO_setPinConfig(GPIO_158_ESC_TX0_DATA0);
    GPIO_setPinConfig(GPIO_159_ESC_TX0_DATA1);
    GPIO_setPinConfig(GPIO_160_ESC_TX0_DATA2);
    GPIO_setPinConfig(GPIO_161_ESC_TX0_DATA3);

    GPIO_setPinConfig(GPIO_79_ESC_RX0_ERR);
    GPIO_setPinConfig(GPIO_77_ESC_RX0_CLK);
    GPIO_setPinConfig(GPIO_78_ESC_RX0_DV);
    GPIO_setPinConfig(GPIO_80_ESC_RX0_DATA0);
    GPIO_setPinConfig(GPIO_81_ESC_RX0_DATA1);
    GPIO_setPinConfig(GPIO_82_ESC_RX0_DATA2);
    GPIO_setPinConfig(GPIO_83_ESC_RX0_DATA3);

    GPIO_setPinConfig(GPIO_148_ESC_PHY0_LINKSTATUS);
    GPIO_setPinConfig(GPIO_149_ESC_PHY1_LINKSTATUS);

    GPIO_setPinConfig(GPIO_143_ESC_LED_LINK0_ACTIVE);
    GPIO_setPinConfig(GPIO_144_ESC_LED_LINK1_ACTIVE);
    GPIO_setPinConfig(GPIO_146_ESC_LED_RUN);
    GPIO_setPinConfig(GPIO_145_ESC_LED_ERR);

    GPIO_setPinConfig(GPIO_130_ESC_TX1_CLK);
    GPIO_setPinConfig(GPIO_129_ESC_TX1_ENA);
    GPIO_setPinConfig(GPIO_131_ESC_TX1_DATA0);
    GPIO_setPinConfig(GPIO_132_ESC_TX1_DATA1);
    GPIO_setPinConfig(GPIO_134_ESC_TX1_DATA2);
    GPIO_setPinConfig(GPIO_135_ESC_TX1_DATA3);

    GPIO_setPinConfig(GPIO_138_ESC_RX1_ERR);
    GPIO_setPinConfig(GPIO_137_ESC_RX1_CLK);
    GPIO_setPinConfig(GPIO_136_ESC_RX1_DV);
    GPIO_setPinConfig(GPIO_139_ESC_RX1_DATA0);
    GPIO_setPinConfig(GPIO_140_ESC_RX1_DATA1);
    GPIO_setPinConfig(GPIO_141_ESC_RX1_DATA2);
    GPIO_setPinConfig(GPIO_142_ESC_RX1_DATA3);

    GPIO_setPinConfig(GPIO_151_ESC_I2C_SCL);
    GPIO_setPinConfig(GPIO_150_ESC_I2C_SDA);

#endif

    return (0U);
}
/* EOF */
