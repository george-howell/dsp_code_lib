/**
 * @file    fir_filter.h
 *
 * @brief   Basic FIR filters
 *  
 * @par
 * Created On: 24/12/22
 * Created By: G. Howell
 */

#ifndef __FIR_FILTER_H__
#define __FIR_FILTER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- INCLUDES -----------------------------------*/

#include <stdint.h>

/*------------------- MACROS AND DEFINES -------------------------*/

#define NUM_TAPS                2

/*------------------- TYPEDEFS -----------------------------------*/
/*------------------- EXPORTED VARIABLES -------------------------*/
/*------------------- GLOBAL FUNCTION PROTOTYPES -----------------*/

float FIR_Filter_Float(float sampleData, float *bCoeffs);

#ifdef __cplusplus
}
#endif

#endif /* __FIR_FILTER_H__ */