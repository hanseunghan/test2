/***************************************************************************************************
 * File Name     : bd6tx_utilCPU2.c
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

/***************************************************************************************************
 * usGetElapse
 * [CAUTION] It can measure less than ???ms.
 **************************************************************************************************/
uint32 usGetElapse(uint08 u8Idx)
{
    static uint32 u32LastTime[20] = {0,};
    uint32 u32CurTime, u32ElapseTime;

    if(u8Idx > 20U) {
        return 0;
    }

    u32CurTime = (U32)(GET_CPUTMR2_CNT);
    u32ElapseTime = CPUTMR2_DIFF(u32CurTime, u32LastTime[u8Idx]);

    u32LastTime[u8Idx] = u32CurTime;
    u32ElapseTime = (U32)(u32ElapseTime*TMR2_US_SCALE);

    return u32ElapseTime;
}

/***************************************************************************************************
 * usGetElapse_max
 * [CAUTION] It can measure less than ???ms.
 **************************************************************************************************/
uint32 usGetElapse_max(uint08 u8Idx, uint08 u8MaxOn)
{
    static uint32 MaxTime[20] = {0,};
    uint32        ElapseTime_Max;

    ElapseTime_Max = usGetElapse(u8Idx);

    if(u8MaxOn) {

        if(MaxTime[u8Idx] < ElapseTime_Max)
            MaxTime[u8Idx] = ElapseTime_Max;

        ElapseTime_Max = MaxTime[u8Idx];
    }

    return ElapseTime_Max;
}

/***************************************************************************************************
 * nsGetElapse
 * [CAUTION] It can measure less than ???us.
 **************************************************************************************************/
uint32 nsGetElapse(uint08 u8Idx)
{
    static uint32 u32LastTime[20] = {0,};

    uint32 u32CurTime, u32ElapseTime;

    if(u8Idx > 20) {
        return 0;
    }

    u32CurTime = (U32)(GET_CPUTMR2_CNT);
    u32ElapseTime = CPUTMR2_DIFF(u32CurTime, u32LastTime[u8Idx]);

    u32LastTime[u8Idx] = u32CurTime;
    u32ElapseTime = (U32)(u32ElapseTime*TMR2_NS_SCALE);

    return u32ElapseTime;
}
/* EOF */











