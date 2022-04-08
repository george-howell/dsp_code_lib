/*
 * lal_matrix_operations.c
 *
 *  Created on: 30 Dec 2021
 *      Author: ghowell
 */

#include "lal_matrix_operations.h"

/************************************************************************
 * @fn              - LAL_CreateMatrix
 *
 * @brief           - Creates a matrix of the form [noRows x noCols]
 *
 * @param[in]       - noRows: number of rows in the matrix
 * @param[in]       - noCols: number of columns in the matrix
 *
 * @return          - Pointer to matrix typedef
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_CreateMatrix(uint32_t noRows, uint32_t noCols)
{
    // create matrix structure
    LAL_MatrixDef *mat = calloc(1, sizeof(*mat));
    
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

/************************************************************************
 * @fn              - LAL_FreeMatrix
 *
 * @brief           - Free's the matrix data and structure
 *
 * @param[in]       - inputMat: matrix typedef structure
 *
 * @return          - 
 *
 * @notes           - none
 */
void LAL_FreeMatrix(LAL_MatrixDef *inputMat)
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

/************************************************************************
 * @fn              - LAL_ExtractVector
 *
 * @brief           - Free's the matrix data and structure
 *
 * @param[in]       - inputMat: matrix typedef structure
 *
 * @return          - 
 *
 * @notes           - none
 */
float *LAL_ExtractVector(LAL_MatrixDef *inputMat)
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

/************************************************************************
 * @fn              - LAL_ExtractMatrix
 *
 * @brief           - Free's the matrix data and structure
 *
 * @param[in]       - inputMat: matrix typedef structure
 *
 * @return          - 
 *
 * @notes           - none
 */
float **LAL_ExtractMatrix(LAL_MatrixDef *inputMat)
{
    // create matrix
    // float **pMat;

    // pMat = inputMat->mData;

    return inputMat->mData;

    // // initialise matrix rows
    // pMat = calloc(inputMat->noRows, sizeof(*inputMat->mData));

    // // initialise column for each row
    // for(uint32_t rowIdx = 0; rowIdx<mat->noRows; rowIdx++) 
    // {
    //     mat->mData[rowIdx] = calloc(mat->noCols, sizeof(**mat->mData));
    // }  


    // float *vector = (float*)malloc(len*sizeof(float));

    // uint32_t vecIdx = 0;
    // for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    // {
    //     for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
    //     {
    //          vector[vecIdx++] = inputMat->mData[rowIdx][colIdx];
    //     }
    // }


}

/************************************************************************
 * @fn              - LAL_Determinate2x2
 *
 * @brief           - Finds the determinate of a 2x2 square matrix
 *
 * @param[in]       - inputMat: matrix typedef structure
 *
 * @return          - determinate result
 *
 * @notes           - none
 */
float LAL_Determinate2x2(LAL_MatrixDef *inputMat)
{
    return (inputMat->mData[0][0] * inputMat->mData[1][1]) - (inputMat->mData[1][0] * inputMat->mData[0][1]);
}


/************************************************************************
 * @fn              - LAL_Determinate
 *
 * @brief           - Finds the determinate of a square matrix
 *
 * @param[in]       - 
 * @param[in]       - 
 *
 * @return          - 
 *
 * @notes           - none
 */
float LAL_Determinate(LAL_MatrixDef *inputMat)
{
    if (inputMat->noRows == 1)
    {
        return (inputMat->mData[0][0]);
    }
    else if (inputMat->noRows == 2)
    {
        return (LAL_Determinate2x2(inputMat));
    }
    else 
    {
        // create minor matrix
        LAL_MatrixDef *minor;

        uint32_t firstrow_columnindex;
        float sum = 0;

        // exclude first row and current column
        for(firstrow_columnindex = 0; firstrow_columnindex < inputMat->noRows; firstrow_columnindex++)
        {
            minor = LAL_Minor(inputMat, 0, firstrow_columnindex);

            if (firstrow_columnindex % 2 == 0)
            {
                sum += inputMat->mData[0][firstrow_columnindex] * LAL_Determinate(minor);
            }
            else
            {
                sum -= inputMat->mData[0][firstrow_columnindex] * LAL_Determinate(minor);
            }


            LAL_FreeMatrix(minor);

        }

        return sum;
    }
}

/************************************************************************
 * @fn              - LAL_Minor
 *
 * @brief           - Creates a minor matrix of the specified element
 *
 * @param[in]       - inputMat: matrix typedef structure
 *
 * @return          - Pointer to minor matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_Minor(LAL_MatrixDef *inputMat, uint32_t rowPos, uint32_t colPos)
{
    // create minor matrix
    LAL_MatrixDef *minorMat;
    minorMat = LAL_CreateMatrix(inputMat->noRows-1, inputMat->noCols-1);

    register uint32_t rowIdxMinor = 0;
    register uint32_t colIdxMinor = 0;

    for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++) 
    {
        if (rowIdx!=rowPos) 
        {
            for(uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++) 
            {
                if (colIdx!=colPos)
                {
                    minorMat->mData[rowIdxMinor][colIdxMinor] = inputMat->mData[rowIdx][colIdx];
                    colIdxMinor++;
                }
            }
            colIdxMinor = 0;
            rowIdxMinor++;   
        }
    }

    return minorMat;
}

/************************************************************************
 * @fn              - LAL_Cofactors
 *
 * @brief           - Creates a matrix of cofactors of the input matrix
 *
 * @param[in]       - inputMat: matrix typedef structure
 *
 * @return          - Pointer to cofactor matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_Cofactors(LAL_MatrixDef *inputMat)
{
    // create matrix of cofactors
    LAL_MatrixDef *cofactMat;
    cofactMat = LAL_CreateMatrix(inputMat->noRows, inputMat->noCols);

    // create determinate matrix
    LAL_MatrixDef *minorMat;
    minorMat = LAL_CreateMatrix(inputMat->noRows-1, inputMat->noCols-1);

    float sign;
    for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        //TODO - do better
        if ((rowIdx%2)==0)
        {
            sign = 1;
        }
        else
        {
            sign = -1;
        }
        for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {
            // get minor matrix
            LAL_MatrixDef *minorMat;
            minorMat = LAL_Minor(inputMat, rowIdx, colIdx);
            
            // calculate determinate
            cofactMat->mData[rowIdx][colIdx] = sign*LAL_Determinate(minorMat);
            // free minor matrix
            LAL_FreeMatrix(minorMat);

            sign *= -1;
        }
    }

    return cofactMat;
}

/************************************************************************
 * @fn              - LAL_HadarmardDivison
 *
 * @brief           - Performs element wise division of two matrices of 
 *                    the same order.
 *
 * @param[in]       - numMat: numerator matrix definition structure
 * @param[in]       - denMat: denominator matrix definition structure
 *
 * @return          - Pointer to Hadarmard division matrix definition
 *
 * @notes           - Matrices must be of the same order
 */
LAL_MatrixDef *LAL_HadarmardDivison(LAL_MatrixDef *numMat, LAL_MatrixDef *denMat)
{
    // create divison matrix
    LAL_MatrixDef *divMat;
    divMat = LAL_CreateMatrix(numMat->noRows, numMat->noCols);

    for (uint32_t rowIdx=0; rowIdx<numMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<numMat->noCols; colIdx++)
        {
             divMat->mData[rowIdx][colIdx] = numMat->mData[rowIdx][colIdx]/denMat->mData[rowIdx][colIdx];
        }
    }

    return divMat;
}

/************************************************************************
 * @fn              - LAL_ScalarDivison
 *
 * @brief           - Performs element wise scaler division of two 
 *                    matrices.
 *
 * @param[in]       - numMat: numerator matrix definition structure
 * @param[in]       - den: scalar denominator value
 *
 * @return          - Pointer to scalar divison matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_ScalarDivison(LAL_MatrixDef *numMat, float den)
{
    // create divison matrix
    LAL_MatrixDef *divMat;
    divMat = LAL_CreateMatrix(numMat->noRows, numMat->noCols);

    for (uint32_t rowIdx=0; rowIdx<numMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<numMat->noCols; colIdx++)
        {
             divMat->mData[rowIdx][colIdx] = numMat->mData[rowIdx][colIdx]/den;
        }
    }

    return divMat;
}

/************************************************************************
 * @fn              - LAL_Transpose
 *
 * @brief           - Transpose a NxM matrix
 *
 * @param[in]       - inputMat: matrix definition structure
 *
 * @return          - Pointer to transpose matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_Transpose(LAL_MatrixDef *inputMat)
{
    // create transpose matrix
    LAL_MatrixDef *transposeMat;
    transposeMat = LAL_CreateMatrix(inputMat->noCols, inputMat->noRows);

    // transpose matrix
    for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {
             transposeMat->mData[colIdx][rowIdx] = inputMat->mData[rowIdx][colIdx];
        }
    }

    return transposeMat;
}

/************************************************************************
 * @fn              - LAL_Adjoint
 *
 * @brief           - Computes the adjoint of a square matrix
 *
 * @param[in]       - inputMat: matrix definition structure
 *
 * @return          - Pointer to adjoint matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_Adjoint(LAL_MatrixDef *inputMat)
{
    // determine cofactor matrix
    LAL_MatrixDef *cofactMat;
    cofactMat = LAL_Cofactors(inputMat); 

    // transpose cofactor matrix
    LAL_MatrixDef *adjointMat;
    adjointMat = LAL_Transpose(cofactMat);

    // free cofactor matrix
    LAL_FreeMatrix(cofactMat);

    return adjointMat;
}

/************************************************************************
 * @fn              - LAL_Inverse
 *
 * @brief           - Calculates an inverse square matrix
 *
 * @param[in]       - inputMat: matrix definition structure
 *
 * @return          - Pointer to inverse matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_Inverse(LAL_MatrixDef *inputMat)
{

    // determine adjoint matrix
    LAL_MatrixDef *adjointMat;
    adjointMat = LAL_Adjoint(inputMat);

    // calculate determinate
    float det = LAL_Determinate(inputMat);

    // find inverse
    LAL_MatrixDef *inverseMat;
    inverseMat = LAL_ScalarDivison(adjointMat, det);

    // free adjoint matrix
    LAL_FreeMatrix(adjointMat);

    return inverseMat;
}

/************************************************************************
 * @fn              - LAL_ScalerMultiply
 *
 * @brief           - Multiplies a matrix by a scalar value
 *
 * @param[in]       - inputMat: matrix definition structure
 * @param[in]       - scalFactor: scalar factor
 *
 * @return          - Pointer to scalar matrix definition
 *
 * @notes           - none
 */
LAL_MatrixDef *LAL_ScalerMultiply(LAL_MatrixDef *inputMat, float scalFactor)
{
    // create scaler mulitple matrix
    LAL_MatrixDef *scalMat;
    scalMat = LAL_CreateMatrix(inputMat->noRows, inputMat->noCols);

    // mulitple matrix by scalar value
    for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {
             scalMat->mData[colIdx][rowIdx] = scalFactor * inputMat->mData[rowIdx][colIdx];
        }
    }

    return scalMat;   
}

/************************************************************************
 * @fn              - LAL_Multiply
 *
 * @brief           - Multiplies a matrix by a vector or matrix
 *
 * @param[in]       - inputMat: matrix definition structure
 * @param[in]       - inputVec: input vector or matrix
 *
 * @return          - Pointer to multiplication matrix definition
 *
 * @notes           - Inner product must be equal
 */
LAL_MatrixDef *LAL_Multiply(LAL_MatrixDef *inputMat, LAL_MatrixDef *inputVec)
{
    // create scaler mulitple matrix
    LAL_MatrixDef *multiMat;
    multiMat = LAL_CreateMatrix(inputMat->noRows, inputVec->noCols);

    // mulitple matrix by scalar value
    float acc;
    for (uint32_t multiRowIdx=0; multiRowIdx<multiMat->noRows; multiRowIdx++)
    {
        for (uint32_t multiColIdx=0; multiColIdx<multiMat->noCols; multiColIdx++)
        {
            acc = 0;
            for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
            {
                acc = acc + (inputMat->mData[multiRowIdx][colIdx] * inputVec->mData[colIdx][multiColIdx]);
            }

            multiMat->mData[multiRowIdx][multiColIdx] = acc;
        }
    }

    return multiMat;   
}

/************************************************************************
 * @fn              - LAL_Multiply
 *
 * @brief           - Calculates an inverse square matrix
 *
 * @param[in]       - inputMat: matrix definition structure
 *
 * @return          - Pointer to inverse matrix definition
 *
 * @notes           - none
 */
// LAL_MatrixDef *LAL_Multiply(LAL_MatrixDef *inputMat1, LAL_MatrixDef *inputMat2)
// {
//     // determine if scalar, array or matrix
//     if (inputMat2->noRows==1 && inputMat2->noCols==1)
//     {

//     }
//     else if ()
//     {

//     }
// }
































