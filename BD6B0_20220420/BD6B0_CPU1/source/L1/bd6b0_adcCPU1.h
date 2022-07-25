/***************************************************************************************************
 * File Name     : bd6b0_adcCPU1.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v10.1.1.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6B0_ADCCPU1_H_
#define SOURCE_L1_BD6B0_ADCCPU1_H_

/***************************************************************************************************
 * ADC Register Define
 **************************************************************************************************/
#define ADCA_CONV_START         HWREGH(ADCA_BASE + ADC_O_SOCFRC1) = (0x001CU)
#define ADCB_CONV_START         HWREGH(ADCB_BASE + ADC_O_SOCFRC1) = (0x003CU)

#define ADC_TOTAL_CONV_START    ADCA_CONV_START;  \
                                ADCB_CONV_START

#define ADCA_INT_CLR            HWREGH(ADCA_BASE + ADC_O_INTFLGCLR) = (1U << 0U)
#define ADCB_INT_CLR            HWREGH(ADCB_BASE + ADC_O_INTFLGCLR) = (1U << 1U)

#define ADC_TOTAL_INT_CLR       ADCA_INT_CLR; \
                                ADCB_INT_CLR

#define ADCA_INT_ST             (HWREGH(ADCA_BASE + ADC_O_INTFLG) >> 0U) & (1U)
#define ADCB_INT_ST             (HWREGH(ADCB_BASE + ADC_O_INTFLG) >> 1U) & (1U)

#define ADCA_RESULT(ch)         HWREGH(ADCARESULT_BASE + ch)
#define ADCB_RESULT(ch)         HWREGH(ADCBRESULT_BASE + ch)

/***************************************************************************************************
 * ADC Scale Define
 **************************************************************************************************/
#define TEMP_SCALE              (8.0586080586080586E-1) /* (3.3/4095)*1000 dependent on HW  */
#define P24V_SCALE              (8.8644688644689000E-2) /* (240/2707.44)   dependent on HW  */
#define P5V0_SCALE              (1.6117216117216100E-1) /* (500/3102.27)   dependent on HW  */
#define P3V3_SCALE              (1.6117216117216100E-1) /* (330/2047.5)    dependent on HW  */
#define P1V2_SCALE              (8.0586080586081000E-2) /* (120/1489.09)   dependent on HW  */

#define P24V_MANUE              (11.919191919191919E-1) /* Real Measure compensation */
#define P5V0_MANUE              (12.106537530266343E-1) /* Real Measure compensation */
#define P3V3_MANUE              (10.443037974683544E-1) /* Real Measure compensation */
#define P1V2_MANUE              (10.000000000000000E-1) /* Real Measure compensation */

/***************************************************************************************************
 *  ADC Scales Macro Define
 **************************************************************************************************/
#define P24V_CALC(data)         (U16)(data*P24V_SCALE*P24V_MANUE) /* Ex 24.[V] -> 240 */
#define P5V0_CALC(data)         (U16)(data*P5V0_SCALE*P5V0_MANUE) /* Ex 5.0[V] -> 500 */
#define P3V3_CALC(data)         (U16)(data*P3V3_SCALE*P3V3_MANUE) /* Ex 3.3[V] -> 330 */
#define P1V2_CALC(data)         (U16)(data*P1V2_SCALE*P1V2_MANUE) /* Ex 1.2[V] -> 120 */

/***************************************************************************************************
 * API Functions
 **************************************************************************************************/
sint16 CalcTemp_TMP235(uint16 u16RawData);

#endif /* SOURCE_L1_BD6B0_ADCCPU1_H_ */
/* EOF */
