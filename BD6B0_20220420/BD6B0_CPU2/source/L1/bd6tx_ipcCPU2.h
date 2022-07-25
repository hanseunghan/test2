/***************************************************************************************************
 * File Name     : bd6tx_ipcCPU2.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6TX_IPCCPU2_H_
#define SOURCE_L1_BD6TX_IPCCPU2_H_

/***************************************************************************************************
 * Define
 **************************************************************************************************/
#define SYNC_CPU2_TO_CPU1           IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG8)
#define SYNC_CPU2_TO_CM             IPC_sync(IPC_CPU2_L_CM_R, IPC_FLAG10)

/***************************************************************************************************
 * API Functions
 **************************************************************************************************/
uint16 WriteShareRAM_C2toC1(void);
uint16 WriteShareRAM_C2toCM(void);
uint16 ReadShareRAM_C1toC2(void);
uint16 ReadShareRAM_CMtoC2(void);


#endif /* SOURCE_L1_BD6TX_IPCCPU2_H_ */
/* EOF */
