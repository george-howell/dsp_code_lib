/**
 * @file    lal_basic_operations.c
 *
 * @brief   Basic linear algebra operations
 *  
 * @par
 * Created On: 30/12/21
 * Created By: G. Howell
 */

/*------------------- INCLUDES -----------------------------------*/

#include "lal_basic_operations.h"

/*------------------- EXTERN VARIABLES ---------------------------*/
/*------------------- PRIVATE MACROS AND DEFINES -----------------*/
/*------------------- PRIVATE TYPEDEFS ---------------------------*/
/*------------------- STATIC VARIABLES ---------------------------*/
/*------------------- GLOBAL VARIABLES ---------------------------*/
/*------------------- STATIC FUNCTION PROTOTYPES -----------------*/
/*------------------- STATIC FUNCTIONS ---------------------------*/
/*------------------- GLOBAL FUNCTIONS ---------------------------*/

/**
 * @brief   Finds the determinate of a 2x2 square matrix
 *
 * @param   inputMat    matrix structure definition
 *
 * @return  determinate result
 */
float LAL_Determinate2x2(MAT_MatrixStructDef *inputMat)
{
    return (inputMat->mData[0][0] * inputMat->mData[1][1]) - (inputMat->mData[1][0] * inputMat->mData[0][1]);
}

/**
 * @brief   Finds the determinate of a square matrix
 *
 * @param   inputMat    matrix structure definition
 * 
 * @return
 */
float LAL_Determinate(MAT_MatrixStructDef *inputMat)
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
        MAT_MatrixStructDef *minor;

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

            MAT_FreeMatrix(minor);

        }

        return sum;
    }
}

/**
 * @brief   Creates a minor matrix of the specified element
 *
 * @param   inputMat    matrix structure definition
 *
 * @return  Pointer to minor matrix definition
 */
MAT_MatrixStructDef *LAL_Minor(MAT_MatrixStructDef *inputMat, uint32_t rowPos, uint32_t colPos)
{
    // create minor matrix
    MAT_MatrixStructDef *minorMat;
    minorMat = MAT_CreateMatrix(inputMat->noRows-1, inputMat->noCols-1);

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

/**
 * @brief   Creates a matrix of cofactors of the input matrix
 *
 * @param   inputMat    matrix structure definition
 *
 * @return  Pointer to cofactor matrix definition
 */
MAT_MatrixStructDef *LAL_Cofactors(MAT_MatrixStructDef *inputMat)
{
    // create matrix of cofactors
    MAT_MatrixStructDef *cofactMat;
    cofactMat = MAT_CreateMatrix(inputMat->noRows, inputMat->noCols);

    // create determinate matrix
    MAT_MatrixStructDef *minorMat;
    minorMat = MAT_CreateMatrix(inputMat->noRows-1, inputMat->noCols-1);

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
            MAT_MatrixStructDef *minorMat;
            minorMat = LAL_Minor(inputMat, rowIdx, colIdx);
            
            // calculate determinate
            cofactMat->mData[rowIdx][colIdx] = sign*LAL_Determinate(minorMat);
            // free minor matrix
            MAT_FreeMatrix(minorMat);

            sign *= -1;
        }
    }

    return cofactMat;
}

/**
 * @brief   Performs element wise division of two matrices of the 
 *          same order.
 *
 * @param   numMat  numerator matrix definition structure
 * @param   denMat  denominator matrix definition structure
 *
 * @return  Pointer to Hadarmard division matrix definition
 */
MAT_MatrixStructDef *LAL_HadarmardDivison(MAT_MatrixStructDef *numMat, MAT_MatrixStructDef *denMat)
{
    // create divison matrix
    MAT_MatrixStructDef *divMat;
    divMat = MAT_CreateMatrix(numMat->noRows, numMat->noCols);

    for (uint32_t rowIdx=0; rowIdx<numMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<numMat->noCols; colIdx++)
        {
             divMat->mData[rowIdx][colIdx] = numMat->mData[rowIdx][colIdx]/denMat->mData[rowIdx][colIdx];
        }
    }

    return divMat;
}

/**
 * @brief   Transpose a NxM matrix
 *
 * @param   inputMat    matrix structure definition
 *
 * @return  Pointer to transpose matrix definition
 */
MAT_MatrixStructDef *LAL_Transpose(MAT_MatrixStructDef *inputMat)
{
    // create transpose matrix
    MAT_MatrixStructDef *transposeMat;
    transposeMat = MAT_CreateMatrix(inputMat->noCols, inputMat->noRows);

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

/**
 * @brief   Computes the adjoint of a square matrix
 *
 * @param   inputMat    matrix structure definition
 *
 * @return  Pointer to adjoint matrix definition
 */
MAT_MatrixStructDef *LAL_Adjoint(MAT_MatrixStructDef *inputMat)
{
    // determine cofactor matrix
    MAT_MatrixStructDef *cofactMat;
    cofactMat = LAL_Cofactors(inputMat); 

    // transpose cofactor matrix
    MAT_MatrixStructDef *adjointMat;
    adjointMat = LAL_Transpose(cofactMat);

    // free cofactor matrix
    MAT_FreeMatrix(cofactMat);

    return adjointMat;
}

/**
 * @brief   Calculates an inverse square matrix
 *
 * @param   inputMat    matrix definition structure
 *
 * @return  Pointer to inverse matrix definition
 */
MAT_MatrixStructDef *LAL_Inverse(MAT_MatrixStructDef *inputMat)
{

    // determine adjoint matrix
    MAT_MatrixStructDef *adjointMat;
    adjointMat = LAL_Adjoint(inputMat);

    // calculate determinate
    float det = LAL_Determinate(inputMat);

    // find inverse
    MAT_MatrixStructDef *inverseMat;
    inverseMat = LAL_ScalarDivison(adjointMat, det);

    // free adjoint matrix
    MAT_FreeMatrix(adjointMat);

    return inverseMat;
}

/**
 * @brief   Adds a scalar factor to the matrix elements
 *
 * @param   inputMat    matrix definition structure
 * @param   scalFactor  scalar factor
 *
 * @return  Pointer to sum matrix definition
 */
MAT_MatrixStructDef *LAL_ScalerAddition(MAT_MatrixStructDef *inputMat, float scalFactor)
{
    // create scaler mulitple matrix
    MAT_MatrixStructDef *sumMat = MAT_CreateMatrix(inputMat->noRows, inputMat->noCols);

    // mulitple matrix by scalar value
    for (uint32_t rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {
             sumMat->mData[rowIdx][colIdx] = scalFactor + inputMat->mData[rowIdx][colIdx];
        }
    }

    return sumMat;  
}

/**
 * @brief   Multiplies a matrix by a scalar value
 *
 * @param   inputMat    matrix definition structure
 * @param   scalFactor  scalar factor
 *
 * @return  Pointer to scalar matrix definition
 */
MAT_MatrixStructDef *LAL_ScalerMultiply(MAT_MatrixStructDef *inputMat, float scalFactor)
{
    // create scaler mulitple matrix
    MAT_MatrixStructDef *scalMat;
    scalMat = MAT_CreateMatrix(inputMat->noRows, inputMat->noCols);

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

/**
 * @brief   Performs element wise scaler division of two matrices.
 *
 * @param   numMat  numerator matrix definition structure
 * @param   den     scalar denominator value
 *
 * @return  Pointer to scalar divison matrix definition
 */
MAT_MatrixStructDef *LAL_ScalarDivison(MAT_MatrixStructDef *numMat, float den)
{
    // create divison matrix
    MAT_MatrixStructDef *divMat;
    divMat = MAT_CreateMatrix(numMat->noRows, numMat->noCols);

    for (uint32_t rowIdx=0; rowIdx<numMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<numMat->noCols; colIdx++)
        {
             divMat->mData[rowIdx][colIdx] = numMat->mData[rowIdx][colIdx]/den;
        }
    }

    return divMat;
}

/**
 * @brief   Multiplies a matrix by a vector or matrix
 *
 * @param   inputMat    matrix definition structure
 * @param   inputVec    input vector or matrix
 *
 * @return  Pointer to multiplication matrix definition
 */
MAT_MatrixStructDef *LAL_Multiply(MAT_MatrixStructDef *inputMat, MAT_MatrixStructDef *inputVec)
{
    // create scaler mulitple matrix
    MAT_MatrixStructDef *multiMat;
    multiMat = MAT_CreateMatrix(inputMat->noRows, inputVec->noCols);

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

/*
 * @brief   Creates a toeplitz matrix from a row and column 
 *          data array of size [len x len];
 *
 * @param   pRowData    pointer to array for row entries
 * @param   pColData    pointer to array for column entries
 * @param   size        size of matrix
 *
 * @return  Two dimensional toeplitz matrix
 *
 * @notes   Arrays must be of the same length and the inital 
 *          value must be the same, i.e. pRowData[0]==pColData[0]
 */
MAT_MatrixStructDef *LAL_Toeplitz(MAT_MatrixStructDef *pRowData, MAT_MatrixStructDef *pColData, uint32_t size)
{
    MAT_MatrixStructDef *toeplitzMat = MAT_CreateMatrix(size, size);

    int32_t rowIdx, colIdx;

    // create upper triangular matrix from row data
    for (rowIdx=0; rowIdx<size; rowIdx++)
    {
        for (colIdx=rowIdx; colIdx<size; colIdx++)
        {
            toeplitzMat->mData[rowIdx][colIdx] = pRowData->mData[0][colIdx-rowIdx];
        }
    }

    // create lower triangular matrix for column data
    for (rowIdx=1; rowIdx<size; rowIdx++)
    {
        for (colIdx=0; colIdx<rowIdx; colIdx++)
        {
            toeplitzMat->mData[rowIdx][colIdx] = pColData->mData[-colIdx+rowIdx][0];
        }
    }
    
    return toeplitzMat;
}

/**
 * @brief   Takes a row or column vector and shifts the data by the
 *          +/- shift value
 *
 * @param   inputVec    matrix definition structure
 * @param   shiftVal    shift value
 *
 * @return  Pointer to shifted data
 */
MAT_MatrixStructDef *LAL_ShiftVector(MAT_MatrixStructDef *inputVec, int32_t shiftVal)
{
    MAT_MatrixStructDef *shiftVec = MAT_CreateMatrix(inputVec->noRows, inputVec->noCols);

    if (inputVec->noCols>1)
    {
        if (shiftVal>0)
        {
            uint32_t colIdx;
            for (colIdx=shiftVal; colIdx<inputVec->noCols; colIdx++)
            {
                shiftVec->mData[0][colIdx] = inputVec->mData[0][colIdx-shiftVal];
            }
        }
        else
        {
            uint32_t colIdx;
            for (colIdx=(-shiftVal); colIdx<inputVec->noCols; colIdx++)
            {
                shiftVec->mData[0][colIdx+shiftVal] = inputVec->mData[0][colIdx];
            } 
        }
    }
    else
    {
        if (shiftVal>0)
        {
            uint32_t rowIdx;
            for (rowIdx=shiftVal; rowIdx<inputVec->noRows; rowIdx++)
            {
                shiftVec->mData[rowIdx][0] = inputVec->mData[rowIdx-shiftVal][0];
            }
        }
        else
        {
            uint32_t rowIdx;
            for (rowIdx=(-shiftVal); rowIdx<inputVec->noRows; rowIdx++)
            {
                shiftVec->mData[rowIdx+shiftVal][0] = inputVec->mData[rowIdx][0];
            } 
        }
    }

    return shiftVec;
}

/**
 * @brief   Multiplies and accumulates either two row or column vectors
 *          of the same length
 *
 * @param   inputVec1   input vector 1
 * @param   inputVec2   input vector 2
 *
 * @return  MAC value
 */

float LAL_MACVectors(MAT_MatrixStructDef *inputVec1, MAT_MatrixStructDef *inputVec2)
{
	float acc = 0;

    if (inputVec1->noCols>1)
    {
        uint32_t colIdx;
        for (colIdx=0; colIdx<inputVec1->noCols; colIdx++)
        {
            acc = acc + (inputVec1->mData[0][colIdx]*inputVec2->mData[0][colIdx]);
        }
    }
    else
    {
        uint32_t rowIdx;
        for (rowIdx=0; rowIdx<inputVec1->noRows; rowIdx++)
        {
            acc = acc + (inputVec1->mData[rowIdx][0]*inputVec2->mData[rowIdx][0]);
        }   
    }

    return acc;
}
