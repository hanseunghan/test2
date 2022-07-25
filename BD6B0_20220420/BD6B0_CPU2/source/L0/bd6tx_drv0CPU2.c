/***************************************************************************************************
 * File Name     : bd6tx_drv0CPU2.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#include "entryL0CPU2.h"
#include "entryL1CPU2.h"

extern __interrupt void task_cpu2(void);
/***************************************************************************************************
 * Driver Init
 **************************************************************************************************/
uint32 InitDRV(void)
{
    InitCPUTimer012();

    configCPUTimer(CPUTIMER0_BASE, CPU2_TASK_TIME); /* Config CPU-Timer0 to interrupt every second */
    Interrupt_register(INT_TIMER0, &task_cpu2);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);                   /* Enable TINT0 in the PIE: Group 1 interrupt 7 */

    CPUTimer_startTimer(CPUTIMER0_BASE);            /* Starts CPU-Timer 0 */
//  CPUTimer_startTimer(CPUTIMER1_BASE);            /* Starts CPU-Timer 1 */
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
/* EOF */










