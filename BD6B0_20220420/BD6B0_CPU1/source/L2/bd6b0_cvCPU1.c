/***************************************************************************************************
 * File Name     : bd6b0_cvCPU1.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#include <string.h>
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"
#include "entryL2CPU1.h"

#pragma DATA_SECTION(u16rwCPU1rCPU2, "MSGRAM_CPU1_TO_CPU2") /* origin=0x03A000, length=0x800 */
uint16 u16rwCPU1rCPU2[1800];
#pragma DATA_SECTION(u16rCPU1rwCPU2, "MSGRAM_CPU2_TO_CPU1") /* origin=0x03B000, length=0x800 */
uint16 u16rCPU1rwCPU2[1800];
#pragma DATA_SECTION(u16rwCPU1rCM, "MSGRAM_CPU_TO_CM")      /* origin=0x039000, length=0x800 */
uint16 u16rwCPU1rCM[1800];
#pragma DATA_SECTION(u16rCPU1rwCM, "MSGRAM_CM_TO_CPU")      /* origin=0x038000, length=0x800 */
uint16 u16rCPU1rwCM[1800];

stCVBD6B0 cvBD6B0;

stDiFilter1 stExDI;

//Test Code
//#pragma DATA_SECTION(cvOPR, "CPU1_RAMGS0")                  /* origin=0x00D000, length=0x001000 */
//stOprBD6Tx   cvOPR;
//stVoltAdc stVolt;
//stBtnDI stBtn;
//st_ToolDIO stToolDIO;

/***************************************************************************************************
 *  Control Variables Initial
 **********************************************************************************************100*/
uint16 InitCV(void)
{
    memset(u16rwCPU1rCPU2, 0, sizeof(u16rwCPU1rCPU2));
    memset(u16rwCPU1rCM, 0, sizeof(u16rwCPU1rCM));

    DiFilter1_Init(&stExDI);



    return (0U);
}
/* EOF */


