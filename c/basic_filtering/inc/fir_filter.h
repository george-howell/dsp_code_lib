/*
 * fir_filter.h
 *
 *  Created on: 24 Dec 2021
 *      Author: ghowell
 */

#ifndef _FIR_FILTER_H_
#define _FIR_FILTER_H_

#include <stdint.h>

#define NO_TAPS         2

static float shiftReg[NO_TAPS];

/*
 * API's
 */

float FIR_Filter_Float(float sampleData, float *bCoeffs);

#endif /* _FIR_FILTER_H_ */