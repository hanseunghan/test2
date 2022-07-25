/***************************************************************************************************
 * File Name     : bd6b0_cvCPU1.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L2_BD6B0_CVCPU1_H_
#define SOURCE_L2_BD6B0_CVCPU1_H_

/***************************************************************************************************
 *  Shared RAM Variables
 **********************************************************************************************100*/
extern uint16 u16rwCPU1rCPU2[1800];
extern uint16 u16rCPU1rwCPU2[1800];
extern uint16 u16rwCPU1rCM[1800];
extern uint16 u16rCPU1rwCM[1800];

extern stDiFilter1 stExDI;

/***************************************************************************************************
 * BD6B0 Operation Variables
 **********************************************************************************************100*/
typedef struct st_Ope_BD6B0 { /* BD6B0 Operation Sequence */
    union {
        uint32 ALL;
        struct {                        /* [Low Bit] */
            uint32 EX_LED_CMD: 4;       /*  */
            uint32 rsvd0: 4;            /*  */
            uint32 EX_LED_TYPE: 1;      /* 0: Blink, 1: Solid           */
            uint32 EX_PWR_CMD: 1;       /* External Power 0: 0V, 1: 24V */
//            uint32 BRK_CMD: 1;          /*  */
//            uint32 PWM_EN_CMD: 1;       /*  */
//            uint32 LED_CMD: 1;          /*  */
//            uint32 RGB_CMD: 3;          /*  */
            uint32 : 22;
        } BIT;                          /* [High Bit] */
    };
} stOpeBD6B0;

typedef struct st_Adc_BD6B0 { /* BD6B0 Voltage Sensing ADC */

    sint16 s16Temp_x10;
    uint16 u16ExVolt_x10;
    uint16 u16ExCurr_x10;
    uint16 u16P24V_x10;
    uint16 u16P5p0V_x100;
    uint16 u16P3p3V_x100;
    uint16 u16P1p2V_x100;
} stAdcBD6B0;

typedef struct st_Button_DI { /* BD6B0 Button Reading DI */

    union {
        uint16 ALL;
        struct {
            uint16 Ch1: 1;
            uint16 Ch2: 1;
            uint16 Ch3: 1;
            uint16 Ch4: 1;
            uint16 Ch5: 1;
            uint16 : 11;
        } BIT;
    };
} stBtnDI;

typedef struct st_Tool_DIO { /* BD6B0 Tool Interface by DIO */

    uint16 DI_TYPE;
    union {
        uint16 ALL;
        struct {
            uint16 Ch1: 1;
            uint16 Ch2: 1;
            uint16 : 13;
        } BIT;
    } DI;

    uint16 DO_TYPE;
    union {
        uint16 ALL;
        struct {
            uint16 Ch1: 1;
            uint16 Ch2: 1;
            uint16 : 13;
        } BIT;
    } DO;
} stToolDIO;

/***************************************************************************************************
 * Tool Port Setting
 **********************************************************************************************100*/
typedef struct st_Tool_Port { /* BD6B0 Tool Port Setting */

    uint32 u32BaudRate;
    uint08 u08DataLength;
    uint08 u08Parity;
    uint08 u08StopBits;
} stToolPort;

/***************************************************************************************************
 * Tool ModBus Data
 **********************************************************************************************100*/
typedef struct st_Tool_ModBus_Data { /* BD6B0 Tool Port Setting */

    uint08 u08Tx[260];
    uint08 u08Rx[260];
} stToolMB_Data;

typedef struct st_CV_BD6B0 {

    stOpeBD6B0      OPE;
    stAdcBD6B0      ADC;
    stBtnDI         BTN;

    stToolDIO       ToolDIO;

    stToolPort      ToolPort1;
    stToolMB_Data   ToolMB1;
//    stToolMB_Data   ToolMB2;

    stToolPort      ToolPort2;
    stToolMB_Data   ToolMB2;
} stCVBD6B0;

extern stCVBD6B0 cvBD6B0;

/***************************************************************************************************
 *  API Functions
 **********************************************************************************************100*/
uint16 InitCV(void);

#endif /* SOURCE_L2_BD6TX_CVCPU1_H_ */
/* EOF */
