/***************************************************************************************************
 * File Name     : mainCPU1.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **********************************************************************************************100*/
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"
#include "entryL2CPU1.h"

/***************************************************************************************************
 * CPU1 main
 **************************************************************************************************/
void main(void)
{
    Device_init(); /* Initialize device clock and peripherals */

    /* Boot CPU2 & CM core */
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
    Device_bootCM(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
    Device_bootCM(BOOTMODE_BOOT_TO_S0RAM);
#endif

    InitGPIO();

    Interrupt_initModule();         /* Initialize PIE and clear PIE registers. Disables CPU interrupts. */
    Interrupt_initVectorTable();    /* Initialize the PIE vector table with pointers to the shell
                                       Interrupt Service Routines (ISR). */
    InitDRV();


    MSKAMPS_Init(1);

    InitCV();


    /* Self IPC Clear & Synchronize CPU1,CPU2 & CM */
    IPC_clearFlagLtoR(IPC_CPU1_L_CM_R, IPC_FLAG_ALL);
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG_ALL);
    SYNC_CPU1_TO_CM;
    SYNC_CPU1_TO_CPU2;

    /* Enable Global Interrupt (INTM) and real-time interrupt (DBGM) */
    EINT;
    ERTM;

    /***********************************************************************************************
     * Infinite Loop
     **********************************************************************************************/
    while(1U) {

        MSKAMPS_Handle();
    }
}
/* EOF */

