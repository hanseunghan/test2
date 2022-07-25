/***************************************************************************************************
 * File Name     : datatype.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v11.0.0.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L0_DATATYPE_H_
#define SOURCE_L0_DATATYPE_H_

/***************************************************************************************************
 *  TYPE DEF.
 **************************************************************************************************/
#ifndef __BD6Tx_TYPE__
#define __BD6Tx_TYPE__

typedef signed char            sint08;
typedef unsigned char          uint08;
typedef signed int             sint16;
typedef unsigned int           uint16;
typedef signed long int        sint32;
typedef unsigned long int      uint32;
typedef signed long long int   sint64;
typedef unsigned long long int uint64;
typedef float                  float32;

typedef sint08  S08;
typedef uint08  U08;
typedef sint16  S16;
typedef uint16  U16;
typedef sint32  S32;
typedef uint32  U32;
typedef sint64  S64;
typedef uint64  U64;
typedef float32 F32;

#endif

typedef union {
    uint08  u08[8];
    uint16  u16[4];
    uint32  u32[2];
    sint08  s08[8];
    sint16  s16[4];
    sint32  s32[2];
    uint64  u64;
} DataType64;

typedef union {
    uint08  u08[4];
    uint16  u16[2];
    uint32  u32;
    sint08  s08[4];
    sint16  s16[2];
    sint32  s32;
} DataType32;

#endif /* SOURCE_L0_DATATYPE_H_ */
/* EOF */

