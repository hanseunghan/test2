/***************************************************************************************************
 * File Name     : bd6tx_utilCPU1.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6B0_UTILCPU1_H_
#define SOURCE_L1_BD6B0_UTILCPU1_H_

/***************************************************************************************************
 * Define
 **************************************************************************************************/
#define GET_CPUTMR2_CNT         HWREG(CPUTIMER2_BASE)
#define CPUTMR2_DIFF(now, base) \
        (((now)<(base)) ? ((base)-(now)) : ((U32)((HWREG(CPUTIMER2_BASE+0x02U)-(now)))+(base)))

#define TMR2_US_SCALE           (5.E-3) /* 200MHz */
#define TMR2_NS_SCALE           (5.E-0) /* 200MHz */

/***************************************************************************************************
 * API Functions
 **************************************************************************************************/
uint32 usGetElapse(uint08 u8Idx);
uint32 usGetElapse_max(uint08 u8Idx, uint08 u8MaxOn);
uint32 nsGetElapse(uint08 u8Idx);

#endif /* SOURCE_L1_BD6TX_UTILCPU1_H_ */
/* EOF */
