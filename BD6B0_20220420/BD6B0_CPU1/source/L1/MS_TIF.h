/*
 *	MS_TIF.H : Header Definitions For MS_TIF.c
 *
 */

#ifndef __MS_TIF_H__
#define __MS_TIF_H__


/*
 * <<<<< User Modification 1 >>>>>
 * Modify for your compiler data type
 */

/* User modification 1 start mark <-- Don't modify this string */

#ifndef	__KVAR_TYPE__
#define __KVAR_TYPE__
typedef	char			INT8;		/* 1 Byte  */
typedef	short int		INT16;		/* 2 Bytes */
typedef	long			INT32;		/* 4 Bytes */
typedef	unsigned char 		UINT8;		/* 1 Byte  */
typedef	unsigned short int	UINT16;		/* 2 Bytes */
typedef	unsigned long 		UINT32;		/* 4 Bytes */
typedef	char			BOOLx;
typedef float			FLOAT32;		/* 4 Bytes */
#endif

/* User modification 1 end mark  <-- Don't modify this string */


#ifndef TRUE
#define TRUE			-1
#define FALSE   		0
#endif


/* For KAMP protocol frame */
#define	MSKAMPS_MAXADDRESS	32
#define MSKAMPS_GLBADDRESS	0x00
#define	MSKAMPS_STX		0x72
#define MSKAMPS_ETX		0x73
#define MSKAMPS_OPTOTNUM	8
#define MSKAMPS_OP01		0x40
#define MSKAMPS_OP02		0x41
#define MSKAMPS_OP03		0x42
#define MSKAMPS_OP04		0x43
#define MSKAMPS_OP05		0x44
#define MSKAMPS_OP06		0x45
#define MSKAMPS_OP07		0x46
#define MSKAMPS_OP08		0x47

/* For KAMP slave protocol buffer size */
#define	MSKAMPS_TXBUFSIZE	550
#define MSKAMPS_RXBUFSIZE	50


/* Prototypes for communication driver */
BOOLx	MSKAMPS_IsSenderReady(void);
void	MSKAMPS_SendFrame(UINT8 *tx_buf,INT16 length);
BOOLx	MSKAMPS_ReceiveByte(UINT8 *rx_byte);

/* Prototypes for variable read/write */
void	MS_GetRDVValue(UINT8 *buf);
void	MS_CaptureARVValue();

/* Prototypes for processing data by each OP. code */
INT16	MSKAMPS_ProcessOP01Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP02Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP03Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP04Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP05Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP06Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP07Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);
INT16	MSKAMPS_ProcessOP08Data(UINT8 *rx_buf,INT16 length,UINT8 *tx_buf);

/* Prototypes for KAMP slave protocol */
void	MSKAMPS_Init(UINT8 addr);
int	MSKAMPS_Handle(void);
void	MSKAMPS_ProcessRequest(UINT8 op,UINT8 *rx_buf,INT16 length);
void	MSKAMPS_GetBCS(UINT8 *buf,INT16 length,UINT8 *bcs1,UINT8 *bcs2);
INT16	MSKAMPS_Encode(UINT8 *buf,INT16 length);
INT16	MSKAMPS_Decode(UINT8 *buf,INT16 length);

#endif

