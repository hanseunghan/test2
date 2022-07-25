/***************************************************************************************************
 * File Name     : bd6b0_adcCPU1.c
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

/***************************************************************************************************
 * CalcTemp_TMP235
 * Return Value : Temp. Data(ex: 588 -> 58.8[deg])
 **************************************************************************************************/
sint16 CalcTemp_TMP235(uint16 u16RawData)
{
    float32 f32Ramp[2] = {1.0E+0, 9.9E-1};    /* TMP235 */
    float32 f32Yin[2]  = {-500., -485.1485};  /* TMP235 */
    float32 f32Val[2]  = {1500., 3000.};      /* TMP235 */

    sint16 s16RetVal = 0;
    float32 f32Temp;
    uint08 i;

    f32Temp = (F32)(u16RawData*TEMP_SCALE);
    f32Temp = LIMIT(f32Temp, 0., 3000.);

    for(i=0; i<2; i++) {

        if(f32Temp <= f32Val[i]) {
            f32Temp = (f32Ramp[i]*f32Temp) + f32Yin[i];
            break;
        }
    }

    s16RetVal = LIMIT((S16)(f32Temp), -400, 1250);

    return s16RetVal;
}
/* EOF */
