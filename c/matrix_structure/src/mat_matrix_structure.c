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
#include <stdio.h>

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
 * @brief   Loads the multidimensional array into the matrix 
 *          structure pointer to pointer data variable
 *
 * @param   matStruct       matrix typedef structure to load
 *                          data into
 * @param   multidimArray   multidimensional array to load
 *                          data from
 *
 * @return
 */
void MAT_LoadMultidimensionalArray(MAT_MatrixStructDef *matStruct, float *multidimArray)
{
    int32_t rowIdx, colIdx;
    for (colIdx=0; colIdx<matStruct->noCols; colIdx++)
    {
        for (rowIdx=0; rowIdx<matStruct->noRows; rowIdx++)
        {
            matStruct->mData[rowIdx][colIdx] = multidimArray[rowIdx + colIdx * matStruct->noCols];
        }
    }
}

/**
 * @brief   Loads a row vector into the matrix structure
 *
 * @param   matStruct   matrix typedef structure
 * @param   rowVec      row vector
 *
 * @return
 */
void MAT_LoadRowVector(MAT_MatrixStructDef *matStruct, float *rowVec)
{
    int32_t colIdx;
    for (colIdx=0; colIdx<matStruct->noCols; colIdx++)
    {
        matStruct->mData[0][colIdx] = rowVec[colIdx];
    }
}

/**
 * @brief   Loads a column vector into the matrix structure
 *
 * @param   matStruct   matrix typedef structure
 * @param   colVec      column vector
 *
 * @return
 */
void MAT_LoadColumnVector(MAT_MatrixStructDef *matStruct, float *colVec)
{
    int32_t rowIdx;
    for (rowIdx=0; rowIdx<matStruct->noRows; rowIdx++)
    {
        matStruct->mData[rowIdx][0] = colVec[rowIdx];
    }
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

/**
 * @brief   Prints the data in the matrix
 *
 * @param   inputMat    matrix typedef structure
 * @param   fmtType     data format type
 */
void MAT_PrintMatrix(MAT_MatrixStructDef *inputMat, char fmtType[])
{
    char strTmp[100];

    uint32_t rowIdx, colIdx;
    for (rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        for (colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {
            sprintf(strTmp, fmtType, inputMat->mData[rowIdx][colIdx]);
            printf("%s\t", strTmp);
        }
        printf("\n");
    }
}

