/***************************************************************************************************
 * File Name     : macro.h
 * Version       : 1.00b
 * Device        : TMS320F28388D
 * Tool-Chain    : Code Composer Studio v10.1.1.
 * H/W Platform  :
 * Description   :
 * History       :
 *                                                                              PGM by A414999
 **************************************************************************************************/
#ifndef SOURCE_L1_MACRO_H_
#define SOURCE_L1_MACRO_H_

/***************************************************************************************************
 * Define
 **************************************************************************************************/
#define MAX(X,Y)            ((X>Y) ? X : Y)
#define MIN(X,Y)            ((X<Y) ? X : Y)

#define DELTA(X,Y)          ((X>Y) ? (X-Y) : (Y-X))
#define SIGN(X)             ((X>=0) ? 1 : 0)
#define ABS(X)              ((X>=0) ? X : -X)
#define LIMIT(X,LO,HI)      ((X>=HI)? HI : ((X<=LO) ? LO : X))
#define BOUND(X,LO,HI)      ((X>HI)? (X -= HI) : ((X<LO) ? (X +=HI) : X))

#define TOGGLE(data)        data = ((data==1U) ? 0U : 1U)

#endif /* SOURCE_L1_MACRO_H_ */
/* EOF */
