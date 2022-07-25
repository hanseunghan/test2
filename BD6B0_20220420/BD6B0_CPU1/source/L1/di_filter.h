/***************************************************************************************************
 * File Name     : di_filter.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_DI_FILTER_H_
#define SOURCE_L1_DI_FILTER_H_

/***************************************************************************************************
 *  DEFINE
 ********************************************************************************************[100]*/
#define DI_BUFF_SIZE0           5U  /* 1ms*5 = 5ms */
#define DI_CH_MAX0              32U /* Max Channel = 32ch */
#define DI_BUFF_SIZE1           10U /* 1ms*10 = 10ms */
#define DI_CH_MAX1              16U /* Max Channel = 32ch */

/***************************************************************************************************
 *  Structure Data Type
 ********************************************************************************************[100]*/
typedef struct st_Di_Filter0 {

    uint32 u32MaxBuf;
    uint32 u32CurBuf;
    uint32 u32RawData;
    uint32 u32RawData_Array[DI_BUFF_SIZE0];
    uint32 u32FilterData;

} stDiFilter0;

typedef struct st_Di_Filter1 {

    uint32 u32MaxBuf;
    uint32 u32CurBuf;
    uint32 u32RawData;
    uint32 u32RawData_Array[DI_BUFF_SIZE1];
    uint32 u32FilterData;

} stDiFilter1;

/***************************************************************************************************
 *  API Functions
 ********************************************************************************************[100]*/
void DiFilter0_Init(stDiFilter0 *pData);
uint32 DiFilter0(stDiFilter0 *pData);
void DiFilter1_Init(stDiFilter1 *pData);
uint32 DiFilter1(stDiFilter1 *pData);

#endif /* SOURCE_L1_DI_FILTER_H_ */
/* EOF */
