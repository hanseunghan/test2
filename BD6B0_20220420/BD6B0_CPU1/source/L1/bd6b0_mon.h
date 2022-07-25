/***************************************************************************************************
 * File Name     : bd6b0_mon.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6B0_MON_H_
#define SOURCE_L1_BD6B0_MON_H_

#include "MS_TIF.h"

/* Analog-read-variables */
extern  INT16   Analog_tst, mTemp1_x10, mExCurr_x10;
extern  UINT16  mExVolt_x10, m24V_x10,
        m5p0V_x100, m3p3V_x100, m1p2V_x100,
        mExDI_Raw, mExDI_Fil, wInLED, wExLED,
        wTypeDI, wTypeDO, wDO1, wDO2,
        wExPWR, mTaskTake_NS, mTaskPeriod_US, wTypeLED,
        mBTN1, mBTN2, mBTN3, mBTN4,
        mBTN5, mBTN6, mDI1, mDI2;

/* Digital-read-variables */
extern  UINT16  Digital_tst;

/* Write-variables */
extern  INT16   Write_tst;
extern  UINT16  wInLED, wExLED, wTypeDI,
        wTypeDO, wDO1, wDO2, wExPWR,
        wTypeLED;

#endif /* SOURCE_L1_BD6B0_MON_H_ */
