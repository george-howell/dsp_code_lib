/*
 * lal_matrix_operations.h
 *
 *  Created on: 30 Dec 2021
 *      Author: ghowell
 */

#ifndef _LAL_MATRIX_OPERATIONS_H_
#define _LAL_MATRIX_OPERATIONS_H_

#include <stdint.h>
#include <stdlib.h>

/*
 * Matrix Type Definition
 */

typedef struct 
{
    uint32_t noRows;
    uint32_t noCols;
    float **mData;
} LAL_MatrixDef;

/*
 * API's
 */

LAL_MatrixDef *LAL_CreateMatrix(uint32_t noRows, uint32_t noCols);
void LAL_FreeMatrix(LAL_MatrixDef *matDef);
float *LAL_ExtractVector(LAL_MatrixDef *inputMat);
float **LAL_ExtractMatrix(LAL_MatrixDef *inputMat);

float LAL_Determinate(LAL_MatrixDef *matDef);
float LAL_Determinate2x2(LAL_MatrixDef *matDef);
LAL_MatrixDef *LAL_Minor(LAL_MatrixDef *inputMat, uint32_t rowPos, uint32_t colPos);
LAL_MatrixDef *LAL_Cofactors(LAL_MatrixDef *inputMat);
LAL_MatrixDef *LAL_HadarmardDivison(LAL_MatrixDef *numMat, LAL_MatrixDef *denMat);
LAL_MatrixDef *LAL_ScalarDivison(LAL_MatrixDef *numMat, float den);
LAL_MatrixDef *LAL_Transpose(LAL_MatrixDef *inputMat);
LAL_MatrixDef *LAL_Adjoint(LAL_MatrixDef *inputMat);
LAL_MatrixDef *LAL_Inverse(LAL_MatrixDef *inputMat);
LAL_MatrixDef *LAL_ScalerMultiply(LAL_MatrixDef *inputMat, float scalFactor);
LAL_MatrixDef *LAL_Multiply(LAL_MatrixDef *inputMat, LAL_MatrixDef *inputVec);

#endif /* _MATRIX_OPERATIONS_H_ */
