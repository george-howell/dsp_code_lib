 /*
  * covariance.h
  *
  *  Created on: 28 Dec 2021
  *      Author: ghowell
  */

#ifndef _COVARIANCE_H_
#define _COVARIANCE_H_

#include <stdint.h>
#include <stdlib.h>
#include "mean.h"
#include "toeplitz.h"

/*
 * API's
 */
float *covariance_vector(float *data1, float *data2, uint32_t len, uint32_t order);
float **covariance_matrix(float *data1, float *data2, uint32_t len, uint32_t order);

#endif /* _COVARIANCE_H_ */