/*
 * weiner_filter.h
 *
 *  Created on: 27 Dec 2021
 *      Author: ghowell
 */

#ifndef _WEINER_FILTER_H_
#define _WEINER_FILTER_H_

#include <stdint.h>
#include "covariance.h"
#include "lal_matrix_operations.h"

float *Weiner_Filter_NC(float *pInputSig, float *pNoiseSig, uint32_t len, uint32_t order);

#endif /* _WEINER_FILTER_H_ */