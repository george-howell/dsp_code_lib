/**
 * @file    stat_lag_statistics.c
 *
 * @brief   Basic lag statistics
 *  
 * @par
 * Created On: 24/12/22
 * Created By: G. Howell
 */

/*------------------- INCLUDES -----------------------------------*/

#include "stat_lag_statistics.h"

/*------------------- EXTERN VARIABLES ---------------------------*/
/*------------------- PRIVATE MACROS AND DEFINES -----------------*/
/*------------------- PRIVATE TYPEDEFS ---------------------------*/
/*------------------- STATIC VARIABLES ---------------------------*/
/*------------------- GLOBAL VARIABLES ---------------------------*/
/*------------------- STATIC FUNCTION PROTOTYPES -----------------*/
/*------------------- STATIC FUNCTIONS ---------------------------*/
/*------------------- GLOBAL FUNCTIONS ---------------------------*/

/**
 * @brief   Determines the covariance vector which is of the
 *          length of the specified order.
 *
 * @param   data1   pointer to array of data
 * @param   data2   pointer to array of data
 * @param   order   order of matrix
 *
 * @return  pointer to covariance vector
 *
 * @notes   The order must not exceed the length of data.
 */
MAT_MatrixStructDef *STAT_CovarianceVector(MAT_MatrixStructDef *data1, MAT_MatrixStructDef *data2, uint32_t order)
{
    // find mean of signals
    float mean1, mean2;
    mean1 = STAT_Mean(data1);
    mean2 = STAT_Mean(data2);

    // subtract mean of signals
    MAT_MatrixStructDef *data1Tmp = LAL_ScalerAddition(data1, -mean1);
    MAT_MatrixStructDef *data2Tmp = LAL_ScalerAddition(data2, -mean2);

    MAT_MatrixStructDef *covarVec = MAT_CreateMatrix(1, order);
    float macVal;
    for (uint32_t orderIdx=0; orderIdx<order; orderIdx++)
    {
        MAT_MatrixStructDef *shiftVec = LAL_ShiftVector(data2Tmp, orderIdx);
        macVal = LAL_MACVectors(data1Tmp, shiftVec);
        MAT_FreeMatrix(shiftVec);

        covarVec->mData[0][orderIdx] = macVal/((float)data1->noCols-1);
    }

    MAT_FreeMatrix(data1Tmp);
    MAT_FreeMatrix(data2Tmp);

    return covarVec;
}

/**
 * @brief   Determines the covariance matrix given two signals.
 *          The size of the resulting matrix is determined by
 *          the order.
 *
 * @param   data1   pointer to row array of data
 * @param   data2   pointer to row array of data
 * @param   order   order of matrix
 *
 * @return  Pointer to the covariance matrix
 *
 * @notes   The data arrays must be the same length.
 */
MAT_MatrixStructDef *STAT_CovarianceMatrix(MAT_MatrixStructDef *data1, MAT_MatrixStructDef *data2, uint32_t order)
{
    // determine covariance row and column vector
    MAT_MatrixStructDef *covarRow = STAT_CovarianceVector(data1, data2, order);
    MAT_MatrixStructDef *covarColTmp = STAT_CovarianceVector(data2, data1, order);
    MAT_MatrixStructDef *covarCol = LAL_Transpose(covarColTmp);
    MAT_FreeMatrix(covarColTmp);

    // create toeplitz covariance matrix
    MAT_MatrixStructDef *covarMat = LAL_Toeplitz(covarRow, covarCol, order);

    MAT_FreeMatrix(covarRow);
    MAT_FreeMatrix(covarCol);

    return covarMat;
}
