/***************************************************************************************************
 * File Name     : bd6b0_hw_test.c
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

/***************************************************************************************************
 * ISR : Task 1ms
 **************************************************************************************************/
void bd6b0_hw_test(void)
{
    static uint32 u32TaskCnt = 0U;

/* mon-star test */
    if(Analog_tst++ > 30000) Analog_tst = -30000;

/* ADC Check start */
    ADC_TOTAL_CONV_START;               /* ADC-A,B,C,D Conversion Start */

    while(ADCB_INT_ST == OFF) {}        /* Wait for ADCC to complete, then acknowledge flag */
    ADC_TOTAL_INT_CLR;

    mTemp1_x10  = cvBD6B0.ADC.s16Temp_x10   = CalcTemp_TMP235(ADCA_RESULT(2U));
    mExVolt_x10 = cvBD6B0.ADC.u16ExVolt_x10 = P24V_CALC(ADCA_RESULT(3U));
    mExCurr_x10 = cvBD6B0.ADC.u16ExCurr_x10 = P24V_CALC(ADCA_RESULT(4U));

    m24V_x10   = cvBD6B0.ADC.u16P24V_x10   = P24V_CALC(ADCB_RESULT(2U));
    m5p0V_x100 = cvBD6B0.ADC.u16P5p0V_x100 = P5V0_CALC(ADCB_RESULT(3U));
    m3p3V_x100 = cvBD6B0.ADC.u16P3p3V_x100 = P3V3_CALC(ADCB_RESULT(4U));
    m1p2V_x100 = cvBD6B0.ADC.u16P1p2V_x100 = P1V2_CALC(ADCB_RESULT(5U));
/* ADC Check end */

/* DI Check start */
    stExDI.u32RawData = (U32)(((DI_TOTAL << 0U) | (BTN_TOTAL << 2U)) & 0x0000007FU);
    DiFilter1(&stExDI);
    mExDI_Raw = (U16)(stExDI.u32RawData);
    mExDI_Fil = (U16)(stExDI.u32FilterData);

    cvBD6B0.BTN.ALL = (U16)((stExDI.u32FilterData >> 2U) & 0x001FU);
    cvBD6B0.ToolDIO.DI.ALL = (U16)((stExDI.u32FilterData >> 0U) & 0x0003U);

    mBTN1 = (~((cvBD6B0.BTN.ALL) >> 2U)) & 1U;
    mBTN2 = (~((cvBD6B0.BTN.ALL) >> 4U)) & 1U;
    mBTN3 = (~((cvBD6B0.BTN.ALL) >> 3U)) & 1U;
    mBTN4 = (~((cvBD6B0.BTN.ALL) >> 1U)) & 1U;
    mBTN5 = (~((cvBD6B0.BTN.ALL) >> 0U)) & 1U;

    mDI1 = (~(cvBD6B0.ToolDIO.DI.BIT.Ch1) & 1U);
    mDI2 = (~(cvBD6B0.ToolDIO.DI.BIT.Ch2) & 1U);
/* DI Check end */

/* DO Check start */
    cvBD6B0.OPE.BIT.EX_LED_TYPE = wTypeLED;
    cvBD6B0.OPE.BIT.EX_LED_CMD = wExLED;

    if(u32TaskCnt < 500U) {

        switch(cvBD6B0.OPE.BIT.EX_LED_CMD) {
            case LED_BLUE:      EX_LED_RED_OFF, EX_LED_GREEN_OFF, EX_LED_BLUE_ON;  break;
            case LED_GREEN:     EX_LED_RED_OFF, EX_LED_GREEN_ON,  EX_LED_BLUE_OFF; break;
            case LED_RED:       EX_LED_RED_ON,  EX_LED_GREEN_OFF, EX_LED_BLUE_OFF; break;
            case LED_YELLOW:    EX_LED_RED_ON,  EX_LED_GREEN_ON,  EX_LED_BLUE_OFF; break;
            case LED_PURPLE:    EX_LED_RED_ON,  EX_LED_GREEN_OFF, EX_LED_BLUE_ON;  break;
            case LED_WHITE:     EX_LED_RED_ON,  EX_LED_BLUE_ON,   EX_LED_GREEN_ON; break;
            default:            EX_LED_RED_OFF, EX_LED_GREEN_OFF, EX_LED_BLUE_ON;  break;
        }

        switch(wInLED) {
            case LED_BLUE:      LED_RED_OFF, LED_GREEN_OFF, LED_BLUE_ON;  break;
            case LED_GREEN:     LED_RED_OFF, LED_GREEN_ON,  LED_BLUE_OFF; break;
            case LED_RED:       LED_RED_ON,  LED_GREEN_OFF, LED_BLUE_OFF; break;
            case LED_YELLOW:    LED_RED_ON,  LED_GREEN_ON,  LED_BLUE_OFF; break;
            case LED_PURPLE:    LED_RED_ON,  LED_GREEN_OFF, LED_BLUE_ON;  break;
            case LED_WHITE:     LED_RED_ON,  LED_BLUE_ON,   LED_GREEN_ON; break;
            default:            LED_RED_OFF, LED_GREEN_OFF, LED_BLUE_ON;  break;
        }
    }
    else {

        if(cvBD6B0.OPE.BIT.EX_LED_TYPE == LED_BLINK) {
            EX_LED_RED_OFF, EX_LED_BLUE_OFF, EX_LED_GREEN_OFF;
        }

        LED_RED_OFF, LED_BLUE_OFF, LED_GREEN_OFF;
    }

    cvBD6B0.ToolDIO.DI_TYPE = wTypeDI;
    if(cvBD6B0.ToolDIO.DI_TYPE == PNP_TYPE) DI_TYPE_PNP;
    else                                    DI_TYPE_NPN;

    cvBD6B0.ToolDIO.DO_TYPE = wTypeDO;
    if(cvBD6B0.ToolDIO.DO_TYPE == PNP_TYPE) DO_TYPE_PNP;
    else                                    DO_TYPE_NPN;

    cvBD6B0.ToolDIO.DO.BIT.Ch1 = wDO1;
    if(cvBD6B0.ToolDIO.DO.BIT.Ch1 == OFF)   DO1_OFF;
    else                                    DO1_ON;
    cvBD6B0.ToolDIO.DO.BIT.Ch2 = wDO2;
    if(cvBD6B0.ToolDIO.DO.BIT.Ch2 == OFF)   DO2_OFF;
    else                                    DO2_ON;

    cvBD6B0.OPE.BIT.EX_PWR_CMD = wExPWR;
    if(cvBD6B0.OPE.BIT.EX_PWR_CMD == ON)    EX_PWR_ON;
    else                                    EX_PWR_OFF;
/* DO Check end */

    if(u32TaskCnt++ >= 1000U) {
        u32TaskCnt = 0U;
    }
}
/* EOF */


