/***************************************************************************************************
 * File Name     : bd6tx_cvCPU2.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#include <string.h>
#include "entryL0CPU2.h"
#include "entryL1CPU2.h"
#include "entryL2CPU2.h"

#pragma DATA_SECTION(u16rCPU2rwCPU1, "MSGRAM_CPU1_TO_CPU2")/* origin=0x03A000, length=0x800 */
uint16 u16rCPU2rwCPU1[1800];

#pragma DATA_SECTION(u16rwCPU2rCPU1, "MSGRAM_CPU2_TO_CPU1")/* origin=0x03B000, length=0x800 */
uint16 u16rwCPU2rCPU1[1800];

#pragma DATA_SECTION(u16rwCPU2rCM, "MSGRAM_CPU_TO_CM")     /* origin=0x039000, length=0x800 */
uint16 u16rwCPU2rCM[1800];

#pragma DATA_SECTION(u16rCPU2rwCM, "MSGRAM_CM_TO_CPU")     /* origin=0x038000, length=0x800 */
uint16 u16rCPU2rwCM[1800];

/***************************************************************************************************
 *  Control Variables Initial
 **********************************************************************************************100*/
uint16 InitCV(void)
{
    memset(u16rwCPU2rCPU1, 0, sizeof(u16rwCPU2rCPU1));
    memset(u16rwCPU2rCM, 0, sizeof(u16rwCPU2rCM));

    return (0U);
}


