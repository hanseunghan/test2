/***************************************************************************************************
 * File Name     : bd6tx_ipcCPU1.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#include <string.h>
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"
#include "entryL2CPU1.h"

/***************************************************************************************************
 * WriteShareRAM_C1toC2
 **************************************************************************************************/
uint16 WriteShareRAM_C1toC2(void)
{
    static uint16 u16NoWriteCnt = 0U;

    if(IPC_isFlagBusyLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG11) == OFF) {

        /* Test Code */
//        if(u16rwCPU1rCPU2[0]>=0xFFFF)   u16rwCPU1rCPU2[0] = 0;
//        else                            u16rwCPU1rCPU2[0] = u16rwCPU1rCPU2[0]+1;
        //memset(u16rwCPU1rCPU2, 0, sizeof(u16rwCPU1rCPU2));  //about 13us
        //memcpy(u16rwCPU1rCPU2, u16rCPU1rwCPU2, sizeof(u16rwCPU1rCPU2));  //about 9us

        IPC_setFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG11);
        u16NoWriteCnt = 0U;
    }
    else {
        u16NoWriteCnt++;
    }

    return (u16NoWriteCnt);
}

/***************************************************************************************************
 * WriteShareRAM_C1toCM
 **************************************************************************************************/
uint16 WriteShareRAM_C1toCM(void)
{
    static uint16 u16NoWriteCnt = 0U;

    if(IPC_isFlagBusyLtoR(IPC_CPU1_L_CM_R, IPC_FLAG13) == OFF) {

        /* Test Code */
        if(u16rwCPU1rCM[0]>=0xFFFF) u16rwCPU1rCM[0] = 0;
        else                        u16rwCPU1rCM[0] = u16rwCPU1rCM[0]+1;

        IPC_setFlagLtoR(IPC_CPU1_L_CM_R, IPC_FLAG13);
        u16NoWriteCnt = 0U;
    }
    else {
        u16NoWriteCnt++;
    }

    return (u16NoWriteCnt);
}

uint16 u16Temp;
/***************************************************************************************************
 * ReadShareRAM_C2toC1
 **************************************************************************************************/
uint16 ReadShareRAM_C2toC1(void)
{
    static uint16 u16NoReadCnt = 0U;

    if(IPC_isFlagBusyRtoL(IPC_CPU2_L_CPU1_R, IPC_FLAG12) == ON) {

        u16Temp = u16rCPU1rwCPU2[0];

        IPC_ackFlagRtoL(IPC_CPU2_L_CPU1_R, IPC_FLAG12);
        u16NoReadCnt = 0U;
    }
    else {
        u16NoReadCnt++;
    }

    return (u16NoReadCnt);
}

/***************************************************************************************************
 * ReadShareRAM_CMtoC1
 **************************************************************************************************/
uint16 ReadShareRAM_CMtoC1(void)
{
    static uint16 u16NoReadCnt = 0U;

    if(IPC_isFlagBusyRtoL(IPC_CPU1_L_CM_R, IPC_FLAG14) == ON) {

        u16Temp = u16rCPU1rwCM[0];

        IPC_ackFlagRtoL(IPC_CPU1_L_CM_R, IPC_FLAG14);
        u16NoReadCnt = 0U;
    }
    else {
        if(u16NoReadCnt++ > 100U) {
            u16NoReadCnt = 100;
        }
    }

    return (u16NoReadCnt);
}
/* EOF */
