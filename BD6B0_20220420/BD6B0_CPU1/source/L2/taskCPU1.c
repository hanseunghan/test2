/***************************************************************************************************
 * File Name     : taskCPU1.c
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

#define SUB_TASK_PERIOD             (5U)

extern void bd6b0_hw_test(void);
/***************************************************************************************************
 * ISR : Task 1ms
 **************************************************************************************************/
__interrupt void task_cpu1(void)
{
    static uint32 u32BaseTimeCnt = 0U;

    /***********************************************************************************************
     * Time Check : Task of Interval Time & Take Start Time
     **********************************************************************************************/
    mTaskPeriod_US = (U16)(usGetElapse(0U));
    nsGetElapse(0U);

    /* Read ShareRAM of CPU2 & CM */
    ReadShareRAM_C2toC1();
    ReadShareRAM_CMtoC1();

    /***********************************************************************************************
     * Main-Task
     **********************************************************************************************/
    bd6b0_hw_test();

    /***********************************************************************************************
     * Sub-Task Period
     **********************************************************************************************/
    switch(u32BaseTimeCnt%SUB_TASK_PERIOD) {

        case 0U: break;
        case 1U: break;
        case 2U: break;
        case 3U: break;
        case 4U: break;
        default: break;
    }

    /* Write ShareRAM of CPU2 & CM */
    WriteShareRAM_C1toC2();
    WriteShareRAM_C1toCM();

    /***********************************************************************************************
     * Time Check : Task Take End Time
     **********************************************************************************************/
    if(u32BaseTimeCnt++ >= 1000U) {u32BaseTimeCnt = 0U;}
    mTaskTake_NS = (U16)(nsGetElapse(0U));

    /* Acknowledge this interrupt to receive more interrupts from group 1 */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
/* EOF */


