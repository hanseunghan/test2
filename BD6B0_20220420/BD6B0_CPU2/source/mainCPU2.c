/***************************************************************************************************
 * File Name     : mainCPU2.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **********************************************************************************************100*/
#include "entryL0CPU2.h"
#include "entryL1CPU2.h"
#include "entryL2CPU2.h"

/***************************************************************************************************
 * CPU2 main
 **************************************************************************************************/
void main(void)
{
    Device_init(); /* Initialize device clock and peripherals */

    /* Initialize GPIO and configure the GPIO pin as a push-pull output
       This is configured by CPU1. */

    Interrupt_initModule();         /* Initialize PIE and clear PIE registers. Disables CPU interrupts. */
    Interrupt_initVectorTable();    /* Initialize the PIE vector table with pointers to the shell
                                       Interrupt Service Routines (ISR). */
    InitDRV();
    InitCV();


    /* Self IPC Clear & Synchronize CPU1 & CPU2 */
    IPC_clearFlagLtoR(IPC_CPU2_L_CPU1_R, IPC_FLAG_ALL);
    SYNC_CPU2_TO_CPU1;

    /* Enable Global Interrupt (INTM) and real-time interrupt (DBGM) */
    EINT;
    ERTM;

    /***********************************************************************************************
     * Infinite Loop
     **********************************************************************************************/
    while(1U) {

    }
}
/* EOF */

