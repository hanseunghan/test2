/***************************************************************************************************
 * File Name     : mainCM.c
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **********************************************************************************************100*/
//
// Included Files
//
#include "driverlib_cm.h"
#include "cm.h"

#pragma DATA_SECTION(u16rwCMrCPU1, "MSGRAM_CM_TO_CPU1")  /* origin=0x20082000, length=0x800 */
unsigned short u16rwCMrCPU1[1800];
#pragma DATA_SECTION(u16rCMrwCPU1, "MSGRAM_CPU1_TO_CM")  /* origin=0x20080000, length=0x800 */
unsigned short u16rCMrwCPU1[1800];
#pragma DATA_SECTION(u16rCMrwCPU2, "MSGRAM_CPU2_TO_CM")  /* origin=0x20084000, length=0x800 */
unsigned short u16rCMrwCPU2[1800];
#pragma DATA_SECTION(u16rwCMrCPU2, "MSGRAM_CM_TO_CPU2")  /* origin=0x20086000, length=0x800 */
unsigned short u16rwCMrCPU2[1800];

unsigned int u16TstSRam_CMReadC1 = 0;

#define SYNC_CM_TO_CPU1             IPC_sync(IPC_CM_L_CPU1_R, IPC_FLAG9);
#define SYNC_CM_TO_CPU2             IPC_sync(IPC_CM_L_CPU2_R, IPC_FLAG10)

#define CPU1_IPC13_FLAG_BUSY_R2L    IPC_isFlagBusyRtoL(IPC_CM_L_CPU1_R, IPC_FLAG13)
#define CPU1_IPC13_FLAG_SET_R2L     IPC_ackFlagRtoL(IPC_CM_L_CPU1_R, IPC_FLAG13)

#define CM_IPC14_FLAG_BUSY_L2R      IPC_isFlagBusyLtoR(IPC_CM_L_CPU1_R, IPC_FLAG14)
#define CM_IPC14_FLAG_SET_L2R       IPC_setFlagLtoR(IPC_CM_L_CPU1_R, IPC_FLAG14)

#define CPU2_IPC15_FLAG_BUSY_R2L    IPC_isFlagBusyRtoL(IPC_CM_L_CPU2_R, IPC_FLAG15)
#define CPU2_IPC15_FLAG_SET_R2L     IPC_ackFlagRtoL(IPC_CM_L_CPU2_R, IPC_FLAG15)

#define CM_IPC16_FLAG_BUSY_L2R      IPC_isFlagBusyLtoR(IPC_CM_L_CPU2_R, IPC_FLAG16)
#define CM_IPC16_FLAG_SET_L2R       IPC_setFlagLtoR(IPC_CM_L_CPU2_R, IPC_FLAG16)

static unsigned int ReadShareRAM_C1toCM(void);
static unsigned int WriteShareRAM_CMtoC1(void);
static unsigned int ReadShareRAM_C2toCM(void);
static unsigned int WriteShareRAM_CMtoC2(void);

/***************************************************************************************************
 * CM main
 **************************************************************************************************/
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    // This is configured by CPU1
    //

    u16rwCMrCPU1[0] = 0;




    /* Self IPC Clear & Synchronize CPU1 & CM */
    IPC_clearFlagLtoR(IPC_CM_L_CPU1_R, IPC_FLAG_ALL);
    SYNC_CM_TO_CPU1;

    /***********************************************************************************************
     * Infinite Loop
     **********************************************************************************************/
    while(1U) {

//        // Turn on LED
//        GPIO_writePin(145U, 0);
//
        // Delay for 500000uS.
        DEVICE_DELAY_US(500000);
//
        ReadShareRAM_C1toCM();
        ReadShareRAM_C2toCM();
//
//        // Turn off LED
//        GPIO_writePin(145U, 1);
//
        // Delay for 500000uS.
        DEVICE_DELAY_US(500000);
//
        WriteShareRAM_CMtoC1();
        WriteShareRAM_CMtoC2();
    }
}


/***************************************************************************************************
 * ReadShareRAM_C1toCM
 **************************************************************************************************/
//uint16 ReadShareRAM_C1toCM(void)
unsigned int ReadShareRAM_C1toCM(void)
{
    static unsigned int u16NoReadCnt = 0U; //uint16 u16NoReadCnt = 0U;

    if(CPU1_IPC13_FLAG_BUSY_R2L == 1) { //ON) {

        u16TstSRam_CMReadC1 = u16rCMrwCPU1[0];
        CPU1_IPC13_FLAG_SET_R2L;
        u16NoReadCnt = 0U;
    }
    else {
        u16NoReadCnt++;
    }

    return (u16NoReadCnt);
}

/***************************************************************************************************
 * WriteShareRAM_CMtoC1
 **************************************************************************************************/
//uint16 WriteShareRAM_CMtoC1(void)
unsigned int WriteShareRAM_CMtoC1(void)
{
    static unsigned int u16NoWriteCnt = 0U; //uint16 u16NoWriteCnt = 0U;

    if(CM_IPC14_FLAG_BUSY_L2R == 0) { //OFF) {

        u16rwCMrCPU1[0] = u16rCMrwCPU1[0];
        CM_IPC14_FLAG_SET_L2R;
        u16NoWriteCnt = 0U;
    }
    else {
        u16NoWriteCnt++;
    }

    return (u16NoWriteCnt);
}

/***************************************************************************************************
 * ReadShareRAM_C2toCM
 **************************************************************************************************/
unsigned int ReadShareRAM_C2toCM(void)
{
    static unsigned int u16NoReadCnt = 0U; //uint16 u16NoReadCnt = 0U;

    if(CPU2_IPC15_FLAG_BUSY_R2L == 1) { //ON) {

        //u16TstSRam_CMReadC1 = u16rCMrwCPU1[0];
        CPU2_IPC15_FLAG_SET_R2L;
        u16NoReadCnt = 0U;
    }
    else {
        u16NoReadCnt++;
    }

    return (u16NoReadCnt);
}

/***************************************************************************************************
 * WriteShareRAM_CMtoC2
 **************************************************************************************************/
unsigned int WriteShareRAM_CMtoC2(void)
{
    static unsigned int u16NoWriteCnt = 0U; //uint16 u16NoWriteCnt = 0U;

    if(CM_IPC16_FLAG_BUSY_L2R == 0) { //OFF) {

        u16rwCMrCPU2[0] = u16rCMrwCPU2[0];
        CM_IPC16_FLAG_SET_L2R;
        u16NoWriteCnt = 0U;
    }
    else {
        u16NoWriteCnt++;
    }

    return (u16NoWriteCnt);
}

/* EOF */

