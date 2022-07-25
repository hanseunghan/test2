/***************************************************************************************************
 * File Name     : bd6b0_mon.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v10.1.1.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"

/* Analog-read-variables */
  INT16   Analog_tst, mTemp1_x10, mExCurr_x10;
  UINT16  mExVolt_x10, m24V_x10,
        m5p0V_x100, m3p3V_x100, m1p2V_x100,
        mExDI_Raw, mExDI_Fil, wInLED, wExLED,
        wTypeDI, wTypeDO, wDO1, wDO2,
        wExPWR, mTaskTake_NS, mTaskPeriod_US, wTypeLED,
        mBTN1, mBTN2, mBTN3, mBTN4,
        mBTN5, mBTN6, mDI1, mDI2;

/* Digital-read-variables */
  UINT16  Digital_tst;

/* Write-variables */
  INT16   Write_tst;
  UINT16  wInLED, wExLED, wTypeDI,
        wTypeDO, wDO1, wDO2, wExPWR,
        wTypeLED;




