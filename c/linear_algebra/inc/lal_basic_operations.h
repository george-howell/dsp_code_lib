/**
 * @file    lal_basic_operations.h
 *
 * @brief   Basic linear algebra operations
 *  
 * @par
 * Created On: 30/12/21
 * Created By: G. Howell
 */

#ifndef _LAL_BASIC_OPERATIONS_H_
#define _LAL_BASIC_OPERATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- INCLUDES -----------------------------------*/

#include <stdint.h>
#include <stdlib.h>
#include "mat_matrix_structure.h"

/*------------------- MACROS AND DEFINES -------------------------*/
/*------------------- TYPEDEFS -----------------------------------*/
/*------------------- EXPORTED VARIABLES -------------------------*/
/*------------------- GLOBAL FUNCTION PROTOTYPES -----------------*/

float LAL_Determinate(MAT_MatrixStructDef *matDef);
float LAL_Determinate2x2(MAT_MatrixStructDef *matDef);
MAT_MatrixStructDef *LAL_Minor(MAT_MatrixStructDef *inputMat, uint32_t rowPos, uint32_t colPos);
MAT_MatrixStructDef *LAL_Cofactors(MAT_MatrixStructDef *inputMat);
MAT_MatrixStructDef *LAL_HadarmardDivison(MAT_MatrixStructDef *numMat, MAT_MatrixStructDef *denMat);
MAT_MatrixStructDef *LAL_Transpose(MAT_MatrixStructDef *inputMat);
MAT_MatrixStructDef *LAL_Adjoint(MAT_MatrixStructDef *inputMat);
MAT_MatrixStructDef *LAL_Inverse(MAT_MatrixStructDef *inputMat);
MAT_MatrixStructDef *LAL_ScalerAddition(MAT_MatrixStructDef *inputMat, float scalFactor);
MAT_MatrixStructDef *LAL_ScalerMultiply(MAT_MatrixStructDef *inputMat, float scalFactor);
MAT_MatrixStructDef *LAL_ScalarDivison(MAT_MatrixStructDef *numMat, float den);
MAT_MatrixStructDef *LAL_Multiply(MAT_MatrixStructDef *inputMat, MAT_MatrixStructDef *inputVec);
MAT_MatrixStructDef *LAL_Toeplitz(MAT_MatrixStructDef *pRowData, MAT_MatrixStructDef *pColData, uint32_t size);
MAT_MatrixStructDef *LAL_ShiftVector(MAT_MatrixStructDef *inputVec, int32_t shiftVal);

#ifdef __cplusplus
}
#endif

#endif /* _LAL_BASIC_OPERATIONS_H_ */
