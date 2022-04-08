/*
 * toeplitz_matrix.h
 *
 *  Created on: 29 Dec 2021
 *      Author: ghowell
 */

#ifndef _TOEPLITZ_MATRIX_H_
#define _TOEPLITZ_MATRIX_H_

#include <stdint.h>
#include <stdlib.h>

/*
 * API's
 */

float **toeplitz(float *pRowData, float *pColData, uint32_t len);

#endif /* _TOEPLITZ_MATRIX_H_ */
