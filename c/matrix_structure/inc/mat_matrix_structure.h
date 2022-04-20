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
float *MAT_ExtractVector(MAT_MatrixStructDef *inputMat);

#ifdef __cplusplus
}
#endif

#endif /* _MAT_MATRIX_STRUCTURE_H_ */