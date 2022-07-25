/*
 *	MS_TIF.C : MonStar Target Interface Based on KAMP slave -- v1.01
 *	           By ko young cheol, In 2003. 12. 22.
 *
 *	Remarks :
 *	 (1) KAMP slave v1.0 was used.
 *	 (2) The original files of KAMP slave were mixed for monstar
 *	     target interface source code.
 *	 (3) If you want to add your processes in this protocol(KAMP),
 *	     use "User Process Addition" part of this file.
 *
 *	How to port this program in your target :
 *	 (1) Modify "User Modification 1" part in file "MS_TIF.h".
 *	 (2) Modify "User Modification 2" part of this file.
 *	 (3) Call "MSKAMPS_Init(1)" in system initialization routine.
 *	 (4) Call "MSKAMPS_Handle()" in the task(or interrupt).
 *	     This function handles KAMP slave protocol for communication
 *	     with MonStar.
 *	 (5) Call "MS_OSCHandle()" in the task(or interrupt), if this file
 *	     includes oscilloscope code. The task periods will be the
 *	     sampling time for the wave.
 *
 */

#include "MS_TIF.h"
#include "entryL0CPU1.h"
#include "entryL1CPU1.h"


/************************************************************************************
 *
 * 	<<<<< User Modification 2 >>>>>
 *	Serial Communication Driver Functions
 *
 *	Fill your codes that handle serial comm. device into these functions.
 *
 ************************************************************************************/

/* User modification 2 start mark <-- Don't modify this string */

/* Return whether the sender can send data */
BOOLx	MSKAMPS_IsSenderReady(void)
{
	return (SCIA_TxReady());
}

/*
 * Send frame.
 * Parameter "tx_buf" is a pointer of buffer which has data to send and
 * "length" is size of those data. "length" can be maximum 550.
 * This function should return immediately. To do so, actual transmission
 * will be performed in the background task.
 */
void	MSKAMPS_SendFrame(UINT8 *tx_buf,INT16 length)
{
    SCIA_SendFrame(length, tx_buf);
}

/*
 * Receive byte.
 * Parameter "rx_byte" is a pointer of memory which should be filled with
 * received byte. If "rx_byte" has received byte, TRUE is returned,
 * Otherwise, FALSE is returned.
 * This function should return immediately. To do so, received byte will be
 * extracted from the buffer in which the background task store received
 * data.
 */
BOOLx	MSKAMPS_ReceiveByte(UINT8 *rx_byte)
{
    return (SCIA_GetRxBufByte(rx_byte));
}

/* User modification 2 end mark <-- Don't modify this string */


/************************************************************************************
 *
 *	Variable Read/Write
 *
 ************************************************************************************/

#define MS_ARVCTSIZE		28
#define MS_WVPTSIZE		9

/* Analog-read-variables */
extern	INT16	Analog_tst, mTemp1_x10, mExCurr_x10;
extern	UINT16	mExVolt_x10, m24V_x10,
		m5p0V_x100, m3p3V_x100, m1p2V_x100,
		mExDI_Raw, mExDI_Fil, wInLED, wExLED,
		wTypeDI, wTypeDO, wDO1, wDO2,
		wExPWR, mTaskTake_NS, mTaskPeriod_US, wTypeLED,
		mBTN1, mBTN2, mBTN3, mBTN4,
		mBTN5, mBTN6, mDI1, mDI2;

/* Digital-read-variables */
extern	UINT16	Digital_tst;

/* Write-variables */
extern	INT16	Write_tst;
extern	UINT16	wInLED, wExLED, wTypeDI,
		wTypeDO, wDO1, wDO2, wExPWR,
		wTypeLED;

/* Analog-read-variables selector */
UINT32	MS_ARVS1 = 0, MS_ARVS2 = 0, MS_ARVS3 = 0, MS_ARVS4 = 0;

/* Analog-read-variables capture table */
UINT16	MS_ARVCT[MS_ARVCTSIZE];

/* Write-variables pointer table */
void	*MS_WVPT[MS_WVPTSIZE] = 
{
	&Write_tst, &wInLED, &wExLED, &wTypeDI,
	&wTypeDO, &wDO1, &wDO2, &wExPWR,
	&wTypeLED
};

/* Gather digital-read-variables value & fill it to buffer */
void	MS_GetRDVValue(UINT8 *buf)
{
	buf[0] = (Digital_tst<<7);
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = 0;
	buf[8] = 0;
	buf[9] = 0;
	buf[10] = 0;
	buf[11] = 0;
	buf[12] = 0;
	buf[13] = 0;
	buf[14] = 0;
	buf[15] = 0;
}

/* Capture analog-read-variables value */
void	MS_CaptureARVValue()
{
	MS_ARVCT[0] = Analog_tst;
	MS_ARVCT[1] = mTemp1_x10;
	MS_ARVCT[2] = mExVolt_x10;
	MS_ARVCT[3] = m24V_x10;
	MS_ARVCT[4] = m5p0V_x100;
	MS_ARVCT[5] = m3p3V_x100;
	MS_ARVCT[6] = m1p2V_x100;
	MS_ARVCT[7] = mExCurr_x10;
	MS_ARVCT[8] = mExDI_Raw;
	MS_ARVCT[9] = mExDI_Fil;
	MS_ARVCT[10] = wInLED;
	MS_ARVCT[11] = wExLED;
	MS_ARVCT[12] = wTypeDI;
	MS_ARVCT[13] = wTypeDO;
	MS_ARVCT[14] = wDO1;
	MS_ARVCT[15] = wDO2;
	MS_ARVCT[16] = wExPWR;
	MS_ARVCT[17] = mTaskTake_NS;
	MS_ARVCT[18] = mTaskPeriod_US;
	MS_ARVCT[19] = wTypeLED;
	MS_ARVCT[20] = mBTN1;
	MS_ARVCT[21] = mBTN2;
	MS_ARVCT[22] = mBTN3;
	MS_ARVCT[23] = mBTN4;
	MS_ARVCT[24] = mBTN5;
	MS_ARVCT[25] = mBTN6;
	MS_ARVCT[26] = mDI1;
	MS_ARVCT[27] = mDI2;
}


/************************************************************************************
 *
 * 	Process data by each OP. code.
 *
 *	1. Parameters
 *	   - rx_buf :
 *	     Pointer of buffer having data field of received frame
 *	   - length :
 *	     Number of data in rx_buf
 *	   - tx_buf :
 *	     Pointer of buffer in which send data should be filled
 *
 * 	2. Return
 *	   Number of data filled in tx_buf, when -1 is returned,
 *	   Nothing will be sended to master station.
 *
 ************************************************************************************/

/* For var-read set request frame(0x40) */
INT16	MSKAMPS_ProcessOP01Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	INT16 i;

	/* Set analog-read-variables selector */
	MS_ARVS1 = 0, MS_ARVS2 = 0, MS_ARVS3 = 0, MS_ARVS4 = 0;
	for(i=0;i<4;i++) {
	    MS_ARVS1 = MS_ARVS1 | ((UINT32)rx_buf[3-i] << i*8);
	    MS_ARVS2 = MS_ARVS2 | ((UINT32)rx_buf[7-i] << i*8);
	    MS_ARVS3 = MS_ARVS3 | ((UINT32)rx_buf[11-i] << i*8);
	    MS_ARVS4 = MS_ARVS4 | ((UINT32)rx_buf[15-i] << i*8);
	}

	return(MSKAMPS_ProcessOP02Data(rx_buf,length,tx_buf));
}

/* For var-read request frame(0x41) */
INT16	MSKAMPS_ProcessOP02Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	INT16 arvg1_num, arvg2_num, arvg3_num, arvg4_num;
	INT16 i, buf_ptr = 16;
	UINT32 roll_bit = 0x80000000;

	/* Get digital-read-variables value */
	MS_GetRDVValue(tx_buf);

	/* Capture analog-read-variables value */
	MS_CaptureARVValue();

	/* Get number of items of each analog-read-variables group */
	if(MS_ARVCTSIZE <= 32) {arvg1_num = MS_ARVCTSIZE, arvg2_num = 0, arvg3_num = 0, arvg4_num = 0;}
	else if(MS_ARVCTSIZE <= 64) {arvg1_num = 32, arvg2_num = MS_ARVCTSIZE - 32, arvg3_num = 0, arvg4_num = 0;}
	else if(MS_ARVCTSIZE <= 96) {arvg1_num = 32, arvg2_num = 32, arvg3_num = MS_ARVCTSIZE - 64, arvg4_num = 0;}
	else {arvg1_num = 32, arvg2_num = 32, arvg3_num = 32, arvg4_num = MS_ARVCTSIZE - 96;}

	/* Fill captured analog-read-variables value in send buffer */
	for(i=0;i<arvg1_num;i++) {
	    if(MS_ARVS1 & roll_bit) {
	       tx_buf[buf_ptr++] = MS_ARVCT[i] >> 8;
	       tx_buf[buf_ptr++] = MS_ARVCT[i];
	    }
	    roll_bit = roll_bit >> 1;
	}
	roll_bit = 0x80000000;
	for(i=0;i<arvg2_num;i++) {
	    if(MS_ARVS2 & roll_bit) {
	       tx_buf[buf_ptr++] = MS_ARVCT[32+i] >> 8;
	       tx_buf[buf_ptr++] = MS_ARVCT[32+i];
	    }
	    roll_bit = roll_bit >> 1;
	}
	roll_bit = 0x80000000;
	for(i=0;i<arvg3_num;i++) {
	    if(MS_ARVS3 & roll_bit) {
	       tx_buf[buf_ptr++] = MS_ARVCT[64+i] >> 8;
	       tx_buf[buf_ptr++] = MS_ARVCT[64+i];
	    }
	    roll_bit = roll_bit >> 1;
	}
	roll_bit = 0x80000000;
	for(i=0;i<arvg4_num;i++) {
	    if(MS_ARVS4 & roll_bit) {
	       tx_buf[buf_ptr++] = MS_ARVCT[96+i] >> 8;
	       tx_buf[buf_ptr++] = MS_ARVCT[96+i];
	    }
	    roll_bit = roll_bit >> 1;
	}

	return buf_ptr;
}

/* For var-write request frame(0x42) */
INT16	MSKAMPS_ProcessOP03Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	UINT8 wvpt_index, byte_size;

	wvpt_index = rx_buf[0];
	byte_size = rx_buf[1];
	if(wvpt_index >= MS_WVPTSIZE) return -1;

	switch(byte_size) {
	  case 1 :
	     *(UINT8*)MS_WVPT[wvpt_index] = rx_buf[5];
	     return 0;
	  case 2 :
	     *(UINT16*)MS_WVPT[wvpt_index] = ((UINT16)rx_buf[4] << 8) | (UINT16)rx_buf[5];
	     return 0;
	  case 4 :
	     *(UINT32*)MS_WVPT[wvpt_index] = ((UINT32)rx_buf[2] << 24) | ((UINT32)rx_buf[3] << 16)
	                                   | ((UINT32)rx_buf[4] << 8)  | (UINT32)rx_buf[5];
	     return 0;
	  default :
	     return -1;
	}
}

/* For var-write read request frame(0x43) */
INT16	MSKAMPS_ProcessOP04Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	UINT8 wvpt_index, byte_size;

	wvpt_index = rx_buf[0];
	byte_size = rx_buf[1];
	if(wvpt_index >= MS_WVPTSIZE) return -1;

	switch(byte_size) {
	  case 1 :
	     tx_buf[0] = 0;
	     tx_buf[1] = 0;
	     tx_buf[2] = 0;
	     tx_buf[3] = *(UINT8*)MS_WVPT[wvpt_index];
	     return 4;
	  case 2 :
	     tx_buf[0] = 0;
	     tx_buf[1] = 0;
	     tx_buf[2] = *(UINT16*)MS_WVPT[wvpt_index] >> 8;
	     tx_buf[3] = *(UINT16*)MS_WVPT[wvpt_index];
	     return 4;
	  case 4 :
	     tx_buf[0] = *(UINT32*)MS_WVPT[wvpt_index] >> 24;
	     tx_buf[1] = *(UINT32*)MS_WVPT[wvpt_index] >> 16;
	     tx_buf[2] = *(UINT32*)MS_WVPT[wvpt_index] >> 8;
	     tx_buf[3] = *(UINT32*)MS_WVPT[wvpt_index];
	     return 4;
	  default :
	     return -1;
	}
}

/* For mem-read request frame(0x44) */
INT16	MSKAMPS_ProcessOP05Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	INT16 i;
	UINT8 byte_size;
	UINT32 addr = 0;

	for(i=0;i<4;i++) addr = addr | ((UINT32)rx_buf[3-i] << i*8);
	byte_size = rx_buf[4];

	switch(byte_size) {
	  case 1 :
	     tx_buf[0] = 0;
	     tx_buf[1] = 0;
	     tx_buf[2] = 0;
	     tx_buf[3] = *(UINT8*)addr;
	     return 4;
	  case 2 :
	     tx_buf[0] = 0;
	     tx_buf[1] = 0;
	     tx_buf[2] = *(UINT16*)addr >> 8;
	     tx_buf[3] = *(UINT16*)addr;
	     return 4;
	  case 4 :
	     tx_buf[0] = *(UINT32*)addr >> 24;
	     tx_buf[1] = *(UINT32*)addr >> 16;
	     tx_buf[2] = *(UINT32*)addr >> 8;
	     tx_buf[3] = *(UINT32*)addr;
	     return 4;
	  default :
	     return -1;
	}
}

/* For mem-write request frame(0x45) */
INT16	MSKAMPS_ProcessOP06Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	INT16 i;
	UINT8 byte_size;
	UINT32 addr = 0;

	for(i=0;i<4;i++) addr = addr | ((UINT32)rx_buf[3-i] << i*8);
	byte_size = rx_buf[4];

	switch(byte_size) {
	  case 1 :
	     *(UINT8*)addr = rx_buf[8];
	     return 0;
	  case 2 :
	     *(UINT16*)addr = ((UINT16)rx_buf[7] << 8) | (UINT16)rx_buf[8];
	     return 0;
	  case 4 :
	     *(UINT32*)addr = ((UINT32)rx_buf[5] << 24) | ((UINT32)rx_buf[6] << 16)
	                    | ((UINT32)rx_buf[7] << 8)  | (UINT32)rx_buf[8];
	     return 0;
	  default :
	     return -1;
	}
}

/* For oscilloscope set request frame(0x46) */
INT16	MSKAMPS_ProcessOP07Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	return(-1);
}

/* For oscilloscope data request frame(0x47) */
INT16	MSKAMPS_ProcessOP08Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf)
{
	return(-1);
}


/************************************************************************************
 *
 *	KAMP Slave Protocol
 *
 ************************************************************************************/

UINT8	MSKAMPS_TxBuf[MSKAMPS_TXBUFSIZE];
UINT8	MSKAMPS_RxBuf[MSKAMPS_RXBUFSIZE];

UINT8	MSKAMPS_Address;
BOOLx	MSKAMPS_STXDetected;
INT16	MSKAMPS_RxBufPtr;

/* Initialize KAMP slave protocol */
void	MSKAMPS_Init(UINT8 addr)
{
	MSKAMPS_Address = addr;
	MSKAMPS_STXDetected = FALSE;
}

/*
 * KAMP slave handling, If frame was received, this function returns
 * frame size(size of data field + 2(address & OP. code)), otherwise returns 0.
 */
int	MSKAMPS_Handle(void)
{
	UINT8 rx_data,bcs1,bcs2;
	INT16 decode_num;

	/* Sending frame ? */
	if(!MSKAMPS_IsSenderReady()) return 0;

	while(MSKAMPS_ReceiveByte(&rx_data))
	{
	   /* Check STX --> Frame started ? */
	   if(!MSKAMPS_STXDetected) {
	      if(rx_data == MSKAMPS_STX) {
	         MSKAMPS_STXDetected = TRUE;
	         MSKAMPS_RxBufPtr = 0;
	      }
	      continue;
	   }

	   /* Check ETX --> Frame ended ? */
	   if(rx_data == MSKAMPS_ETX) {
	      MSKAMPS_STXDetected = FALSE;

	      /* Check address */
	      if(MSKAMPS_RxBuf[0] == MSKAMPS_Address || MSKAMPS_RxBuf[0] == MSKAMPS_GLBADDRESS)
	      {
	      	 /* Decode data & BCS */
	         decode_num = MSKAMPS_Decode(&MSKAMPS_RxBuf[2],MSKAMPS_RxBufPtr-2);

	      	 /* Calculate & check BCS */
	      	 if(decode_num > 1) {
	      	    MSKAMPS_GetBCS(&MSKAMPS_RxBuf[0],decode_num,&bcs1,&bcs2);
	      	    if(bcs1 == MSKAMPS_RxBuf[decode_num] && bcs2 == MSKAMPS_RxBuf[decode_num+1]) {
	      	       /* Finally, frame is accepted !!!! */
	      	       MSKAMPS_ProcessRequest(MSKAMPS_RxBuf[1],&MSKAMPS_RxBuf[2],decode_num-2);
	      	       return(decode_num); /* The size of data field + 2(Address & OP. code) */
	      	    }
	         }
	      }

	      return 0;
	   }

	   /* Buffering & check frame size */
	   if(MSKAMPS_RxBufPtr < MSKAMPS_RXBUFSIZE) MSKAMPS_RxBuf[MSKAMPS_RxBufPtr++] = rx_data;
	   else MSKAMPS_STXDetected = FALSE;
	}

	return 0;
}

/* For processing request from master station */
void	MSKAMPS_ProcessRequest(UINT8 op,UINT8 *rx_buf,INT16 length)
{
	INT16 data_num = -1,encode_num;
	UINT8 bcs1,bcs2;

	/* Process request frame by OP. code */
	switch(op)
	{

/*
 * <<<<< User Process Addition >>>>>
 * Add your processes in this protocol
 */

/* User process addition start mark <-- Don't modify this string */

	  case MSKAMPS_OP01 : data_num = MSKAMPS_ProcessOP01Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP02 : data_num = MSKAMPS_ProcessOP02Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP03 : data_num = MSKAMPS_ProcessOP03Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP04 : data_num = MSKAMPS_ProcessOP04Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP05 : data_num = MSKAMPS_ProcessOP05Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP06 : data_num = MSKAMPS_ProcessOP06Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP07 : data_num = MSKAMPS_ProcessOP07Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;
	  case MSKAMPS_OP08 : data_num = MSKAMPS_ProcessOP08Data(rx_buf,length,&MSKAMPS_TxBuf[3]);break;

/* User process addition end mark  <-- Don't modify this string */

	}

	/* Don't need to response ? */
	if(data_num == -1) return;

	/* Fill header */
	MSKAMPS_TxBuf[0] = MSKAMPS_STX;
	MSKAMPS_TxBuf[1] = MSKAMPS_Address;
	MSKAMPS_TxBuf[2] = op;

	/* Calculate & fill BCS */
	MSKAMPS_GetBCS(&MSKAMPS_TxBuf[1],data_num+2,&bcs1,&bcs2);
	MSKAMPS_TxBuf[3 + data_num] = bcs1;
	MSKAMPS_TxBuf[3 + data_num + 1] = bcs2;

	/* Encode data & BCS */
	encode_num = MSKAMPS_Encode(&MSKAMPS_TxBuf[3],data_num+2);

	/* Fill tail */
	MSKAMPS_TxBuf[3 + encode_num] = MSKAMPS_ETX;

	/* Send data */
	MSKAMPS_SendFrame(&MSKAMPS_TxBuf[0],encode_num+4);
}

/* Get binary check sum of byte array */
void	MSKAMPS_GetBCS(UINT8 *buf,INT16 length,UINT8 *bcs1,UINT8 *bcs2)
{
        INT16 i;

        *bcs1 = 0, *bcs2 = 0;
        for(i=0;i<length;i=i+2) *bcs1 = *bcs1 + buf[i];
        for(i=1;i<length;i=i+2) *bcs2 = *bcs2 + buf[i];

        *bcs1 = *bcs1 & 0xff;
        *bcs2 = *bcs2 & 0xff;
}

/* Perform 7th-bit-collect encoding */
INT16	MSKAMPS_Encode(UINT8 *buf,INT16 length)
{
	INT16 i,j,add_byte_ptr = length;
	UINT8 collect_byte,mask_bit;

	/* Collect 7th bits and append newly generated byte(s) to byte array */
	j = 0, collect_byte = 0, mask_bit = 0x40;
	for(i=0;i<length;i++)
	{
	    if(buf[i] & 0x80) collect_byte = collect_byte | mask_bit;
	    mask_bit = mask_bit >> 1;

	    /* 1 byte(7 bits) collected ? */
	    if(++j >= 7) {
	       buf[add_byte_ptr++] = collect_byte;
	       j = 0, collect_byte = 0, mask_bit = 0x40;
	    }
	}
	if(j != 0) buf[add_byte_ptr++] = collect_byte;

	/* Mask all 7th bits of buffer data */
	for(i=0;i<add_byte_ptr;i++) buf[i] = buf[i] | 0x80;

	/* Return size of encoded data & BCS */
	return add_byte_ptr;
}

/*
 * Perform 7th-bit-collect decoding.
 * If "length" is  2 ~  8, add byte number is 1.
 * If "length" is 10 ~ 16, add byte number is 2.
 * If "length" is 18 ~ 24, add byte number is 3.
 * If "length" is 26 ~ 32, add byte number is 4.
 * ......
 *
 * "length" can't be 0, 1, 9, 17, 25, ....
 */
INT16	MSKAMPS_Decode(UINT8 *buf,INT16 length)
{
	INT16 i,j;
	INT16 add_byte_num,add_byte_ptr;
	UINT8 mask_bit;

	/* Illegal length ? */
	if(length <= 0 || (length-1)%8 == 0) return 0;

	add_byte_num = (length+7)/8;
	add_byte_ptr = length - add_byte_num;

	/* Recover all 7th bits of data & BCS */
	j = 0, mask_bit = 0x40;
	for(i=0;i<add_byte_ptr;i++) {
	    if(!(buf[add_byte_ptr] & mask_bit)) buf[i] = buf[i] & 0x7f;
	    mask_bit = mask_bit >> 1;

	    if(++j >= 7) {
	       add_byte_ptr++;
	       j = 0, mask_bit = 0x40;
	    }
	}

	/* Return size of decoded data & BCS */
	return(length-add_byte_num);
}

