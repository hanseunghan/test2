/***************************************************************************************************
 * File Name     : bd6tx_ipcCPU2.c
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

/***************************************************************************************************
 * WriteShareRAM_C2toC1
 **************************************************************************************************/
uint16 WriteShareRAM_C2toC1(void)
{
    static uint16 u16NoWriteCnt = 0U;

    if(IPC_isFlagBusyLtoR(IPC_CPU2_L_CPU1_R, IPC_FLAG12) == OFF) {

        /* Test Code */
        u16rwCPU2rCPU1[0] = u16rCPU2rwCPU1[0];
        IPC_setFlagLtoR(IPC_CPU2_L_CPU1_R, IPC_FLAG12);

        u16NoWriteCnt = 0U;
    }
    else {
        u16NoWriteCnt++;
    }

    return (u16NoWriteCnt);
}

/***************************************************************************************************
 * WriteShareRAM_C2toCM
 **************************************************************************************************/
uint16 WriteShareRAM_C2toCM(void)
{
    static uint16 u16NoWriteCnt = 0U;

    if(IPC_isFlagBusyLtoR(IPC_CPU2_L_CM_R, IPC_FLAG15) == OFF) {

        /* Test Code */
        if(u16rwCPU2rCM[0]>=0xFFFF) u16rwCPU2rCM[0] = 0;
        else                        u16rwCPU2rCM[0] = u16rwCPU2rCM[0]+1;

        IPC_setFlagLtoR(IPC_CPU2_L_CM_R, IPC_FLAG15);
        u16NoWriteCnt = 0U;
    }
    else {
        u16NoWriteCnt++;
    }

    return (u16NoWriteCnt);
}

/***************************************************************************************************
 * ReadShareRAM_C1toC2
 **************************************************************************************************/
uint16 ReadShareRAM_C1toC2(void)
{
    static uint16 u16NoReadCnt = 0U;

    if(IPC_isFlagBusyRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG11) == ON) {

        //u32TstSRam_C2Read = u16rCPU2rwCPU1[0];

        IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG11);
        u16NoReadCnt = 0U;
    }
    else {
        u16NoReadCnt++;
    }

    return (u16NoReadCnt);
}

uint16 u16Temp0 = 0;
/***************************************************************************************************
 * ReadShareRAM_CMtoC2
 **************************************************************************************************/
uint16 ReadShareRAM_CMtoC2(void)
{
    static uint16 u16NoReadCnt = 0U;

    if(IPC_isFlagBusyRtoL(IPC_CPU2_L_CM_R, IPC_FLAG16) == ON) {

        u16Temp0 = u16rCPU2rwCM[0];

        IPC_ackFlagRtoL(IPC_CPU2_L_CM_R, IPC_FLAG16);
        u16NoReadCnt = 0U;
    }
    else {
        u16NoReadCnt++;
    }

    return (u16NoReadCnt);
}
/* EOF */

