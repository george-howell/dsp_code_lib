/*
 * toeplitz.c
 *
 *  Created on: 29 Dec 2021
 *      Author: ghowell
 */

#include "toeplitz.h"

/************************************************************************
 * @fn              - toeplitz
 *
 * @brief           - Creates a toeplitz matrix from a row and column 
 *                    data array of size [len x len];
 *
 * @param[in]       - pRowData: pointer to array for row entries
 * @param[in]       - pColData: pointer to array for column entries
 * @param[in]       - len: length of data, hence results size of matrix
 *
 * @return          - Two dimensional toeplitz matrix
 *
 * @notes           - Arrays must be of the same length and the inital 
 *                    value must be the same, i.e. pRowData[0]==pColData[0]
 */
float **toeplitz(float *pRowData, float *pColData, uint32_t len)
{
    // create and initialise matrix
    float **toeplitzMat = malloc(sizeof(float*) * len);
    for(uint32_t ni = 0; ni < len; ni++) {
        toeplitzMat[ni] = malloc(sizeof(float*) * len);
    }

    int32_t rowIdx, colIdx;

    // create upper triangular matrix from row data
    for (rowIdx=0; rowIdx<len; rowIdx++)
    {
        for (colIdx=rowIdx; colIdx<len; colIdx++)
        {
            toeplitzMat[rowIdx][colIdx]= *(pRowData+colIdx-rowIdx);  
        }
    }

    // create lower triangular matrix for column data
    for (rowIdx=1; rowIdx<len; rowIdx++)
    {
        for (colIdx=0; colIdx<rowIdx; colIdx++)
        {
            toeplitzMat[rowIdx][colIdx]= *(pColData-(colIdx-rowIdx));  
        }
    }
    
    return toeplitzMat;
}
