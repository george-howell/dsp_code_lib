/**
 * @file    mat_matrix_structure.c
 *
 * @brief   Basic matrix structure creation and operations
 *  
 * @par
 * Created On: 30/12/21
 * Created By: G. Howell
 */

/*------------------- INCLUDES -----------------------------------*/

#include "mat_matrix_structure.h"

/*------------------- EXTERN VARIABLES ---------------------------*/
/*------------------- PRIVATE MACROS AND DEFINES -----------------*/
/*------------------- PRIVATE TYPEDEFS ---------------------------*/
/*------------------- STATIC VARIABLES ---------------------------*/
/*------------------- GLOBAL VARIABLES ---------------------------*/
/*------------------- STATIC FUNCTION PROTOTYPES -----------------*/
/*------------------- STATIC FUNCTIONS ---------------------------*/
/*------------------- GLOBAL FUNCTIONS ---------------------------*/

/**
 * @brief   Creates a matrix of the form [noRows x noCols]
 *
 * @param   noRows  number of rows in the matrix
 * @param   noCols  number of columns in the matrix
 *
 * @return  Pointer to matrix typedef
 */
MAT_MatrixStructDef *MAT_CreateMatrix(uint32_t noRows, uint32_t noCols)
{
    // create matrix structure
    MAT_MatrixStructDef *mat = calloc(1, sizeof(*mat));
    
    // assign rows and columns
    mat->noRows = noRows;
    mat->noCols = noCols;

    // initialise matrix rows
    mat->mData = calloc(mat->noRows, sizeof(*mat->mData));

    // initialise column for each row
    for(uint32_t rowIdx = 0; rowIdx<mat->noRows; rowIdx++) 
    {
        mat->mData[rowIdx] = calloc(mat->noCols, sizeof(**mat->mData));
    }

    return mat;
}

/**
 * @brief   Free's the matrix data and structure
 *
 * @param   inputMat    matrix typedef structure
 *
 * @return
 */
void MAT_FreeMatrix(MAT_MatrixStructDef *inputMat)
{
    // clear matrix columns data
    for(uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++) 
    {
        free(inputMat->mData[rowIdx]);
    }

    // free matrix rows
    free(inputMat->mData);

    // free matrix typedef structure
    free(inputMat);
}

/**
 * @brief   Free's the matrix data and structure
 *
 * @param   inputMat    matrix typedef structure
 */
float *MAT_ExtractVector(MAT_MatrixStructDef *inputMat)
{
    uint32_t len;
    if (inputMat->noRows>inputMat->noCols)
    {
        len = inputMat->noRows;
    }
    else
    {
        len = inputMat->noCols;
    }

    float *vector = (float*)malloc(len*sizeof(float));

    uint32_t vecIdx = 0;
    for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {
             vector[vecIdx++] = inputMat->mData[rowIdx][colIdx];
        }
    }

    return vector;
}
