/***************************************************************************************************
 * File Name     : bd6tx_ipcCPU1.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_BD6B0_IPCCPU1_H_
#define SOURCE_L1_BD6B0_IPCCPU1_H_

/***************************************************************************************************
 * Define
 **************************************************************************************************/
#define SYNC_CPU1_TO_CPU2           IPC_sync(IPC_CPU1_L_CPU2_R, IPC_FLAG8)
#define SYNC_CPU1_TO_CM             IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG9)

/***************************************************************************************************
 * API Functions
 **************************************************************************************************/
uint16 WriteShareRAM_C1toC2(void);
uint16 WriteShareRAM_C1toCM(void);
uint16 ReadShareRAM_C2toC1(void);
uint16 ReadShareRAM_CMtoC1(void);




#endif /* SOURCE_L1_BD6TX_IPCCPU1_H_ */
/* EOF */
