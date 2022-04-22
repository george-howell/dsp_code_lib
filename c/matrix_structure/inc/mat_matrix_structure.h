/**
 * @file    mat_matrix_structure.h
 *
 * @brief   Basic matrix structure creation and operations
 *  
 * @par
 * Created On: 30/12/21
 * Created By: G. Howell
 */

#ifndef _MAT_MATRIX_STRUCTURE_H_
#define _MAT_MATRIX_STRUCTURE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- INCLUDES -----------------------------------*/

#include <stdint.h>
#include <stdlib.h>

/*------------------- MACROS AND DEFINES -------------------------*/
/*------------------- TYPEDEFS -----------------------------------*/

typedef struct 
{
    uint32_t noRows;
    uint32_t noCols;
    float **mData;
} MAT_MatrixStructDef;

/*------------------- EXPORTED VARIABLES -------------------------*/
/*------------------- GLOBAL FUNCTION PROTOTYPES -----------------*/

MAT_MatrixStructDef *MAT_CreateMatrix(uint32_t noRows, uint32_t noCols);
void MAT_FreeMatrix(MAT_MatrixStructDef *inputMat);
void MAT_LoadMultidimensionalArray(MAT_MatrixStructDef *matStruct, float *multidimArray);
void MAT_LoadRowVector(MAT_MatrixStructDef *matStruct, float *rowVec);
void MAT_LoadColumnVector(MAT_MatrixStructDef *matStruct, float *colVec);
float *MAT_ExtractVector(MAT_MatrixStructDef *inputMat);
void MAT_PrintMatrix(MAT_MatrixStructDef *inputMat, char fmtType[]);

#ifdef __cplusplus
}
#endif

#endif /* _MAT_MATRIX_STRUCTURE_H_ */
