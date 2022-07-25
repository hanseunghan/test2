/***************************************************************************************************
 * File Name     : di_filter.c
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

/***************************************************************************************************
 *  DiFilter0_Init
 **********************************************************************************************100*/
void DiFilter0_Init(stDiFilter0 *pData)
{
    uint32 i;

    pData->u32MaxBuf = DI_BUFF_SIZE0;
    pData->u32CurBuf = 0U;
    pData->u32RawData = 0U;

    for(i=0; i<DI_BUFF_SIZE0; i++) {
        pData->u32RawData_Array[i] = 0U;
    }

    pData->u32FilterData = 0U;
}

/***************************************************************************************************
 *  DiFilter0
 **********************************************************************************************100*/
uint32 DiFilter0(stDiFilter0 *pData)
{
    uint32 i,j;
    uint32 u32Cnt = 0U;
    uint32 u32BitNum = 0U;
    uint32 u32Result = 0U;

    if((pData->u32MaxBuf<1U)||(pData->u32MaxBuf>DI_BUFF_SIZE0)) {
        pData->u32MaxBuf = 1U;
    }
    if(pData->u32CurBuf >= pData->u32MaxBuf) {
        pData->u32CurBuf = 0U;
    }

    pData->u32RawData_Array[(pData->u32CurBuf)] = pData->u32RawData;

    for(i=0U; i<DI_CH_MAX0; i++) {

        u32BitNum = (1U<<i);
        u32Cnt = 0U;

        for(j=0U; j<DI_BUFF_SIZE0; j++) {

            if((pData->u32RawData_Array[j])&u32BitNum)
                u32Cnt++;
        }

        if      (u32Cnt == DI_BUFF_SIZE0)   u32Result |= (1U << i);
        else if (u32Cnt == 0U)              u32Result |= (0U << i);
        else                                u32Result |= ((pData->u32FilterData)&(1U<<i));
    }

    pData->u32FilterData = u32Result;
    pData->u32CurBuf++;

    return (pData->u32FilterData);
}

/***************************************************************************************************
 *  DiFilter1_Init
 **********************************************************************************************100*/
void DiFilter1_Init(stDiFilter1 *pData)
{
    uint32 i;

    pData->u32MaxBuf = DI_BUFF_SIZE1;
    pData->u32CurBuf = 0U;
    pData->u32RawData = 0U;

    for(i=0; i<DI_BUFF_SIZE1; i++) {
        pData->u32RawData_Array[i] = 0U;
    }

    pData->u32FilterData = 0U;
}

/***************************************************************************************************
 *  DigFilter1
 **********************************************************************************************100*/
uint32 DiFilter1(stDiFilter1 *pData)
{
    uint32 i,j;
    uint32 u32Cnt = 0U;
    uint32 u32BitNum = 0U;
    uint32 u32Result = 0U;

    if((pData->u32MaxBuf<1U) || (pData->u32MaxBuf>DI_BUFF_SIZE1)) {
        pData->u32MaxBuf = 1U;
    }
    if(pData->u32CurBuf >= pData->u32MaxBuf) {
        pData->u32CurBuf = 0U;
    }

    pData->u32RawData_Array[(pData->u32CurBuf)] = pData->u32RawData;

    for(i=0U; i<DI_CH_MAX1; i++) {

        u32BitNum = (1U<<i);
        u32Cnt = 0U;

        for(j=0U; j<DI_BUFF_SIZE1; j++) {

            if((pData->u32RawData_Array[j])&u32BitNum)
                u32Cnt++;
        }

        if      (u32Cnt == DI_BUFF_SIZE1)   u32Result |= (1U << i);
        else if (u32Cnt == 0U)              u32Result |= (0U << i);
        else                                u32Result |= ((pData->u32FilterData)&(1U<<i));
    }

    pData->u32FilterData = u32Result;
    pData->u32CurBuf++;

    return (pData->u32FilterData);
}
/* EOF */

