/***************************************************************************************************
 * File Name     : taskCPU2.c
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
#include "entryL2CPU2.h"

#define SUB_TASK_PERIOD             (5U)
uint16 mIntervalTime = 0;
uint16 mTakeTime = 0;

uint32 u32TstCnt = 0;
uint32 u32TstSRam_C2Read = 0;
uint32 u32TstTemp0 = 0;

/***************************************************************************************************
 * ISR : Task 1ms
 **************************************************************************************************/
__interrupt void task_cpu2(void)
{
    static uint32 u32BaseTimeCnt = 0U;

    /***********************************************************************************************
     * Time Check : Task of Interval Time & Take Start Time
     **********************************************************************************************/
    mIntervalTime = (U16)(usGetElapse(0U));
    nsGetElapse(0U);

    /* Read ShareRAM of CPU1 & CM */
    ReadShareRAM_C1toC2();
    ReadShareRAM_CMtoC2();

//    /***********************************************************************************************
//     * Sub-Task Period
//     **********************************************************************************************/
//    switch(u32BaseTimeCnt%SUB_TASK_PERIOD) {
//
//        case 0U:
//            if(++u32TstCnt==100U) {
//
//                GPIO_togglePin(34U);
//                u32TstCnt = 0U;
//            }
//        break;
//
//        case 1U:
//        break;
//        case 2U:
//        break;
//        case 3U:
//        break;
//        case 4U:
//        break;
//        default: break;
//    }




    /* Write ShareRAM of CPU1 & CM */
    WriteShareRAM_C2toC1();
    WriteShareRAM_C2toCM();

    /***********************************************************************************************
     * Time Check : Task Take End Time
     **********************************************************************************************/
    if(u32BaseTimeCnt++ >= 1000U) {u32BaseTimeCnt = 0U;}
    mTakeTime = (U16)(nsGetElapse(0U));

    /* Acknowledge this interrupt to receive more interrupts from group 1 */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
/* EOF */



