/*
 * weiner_filter.c
 *
 *  Created on: 27 Dec 2021
 *      Author: ghowell
 */
#include <stdio.h>
#include "weiner_filter.h"

// WEINERFLT_StatusDef Weiner_Filter(void)
// {
//     // determine convariance

//     // calculate coefficients

//     // filter input signal   
// }

/************************************************************************
 * @fn              - Covariance_Matrix
 *
 * @brief           - 
 *
 * @param[in]       - 
 * @param[in]       - 
 *
 * @return          - 
 *
 * @notes           - none
 */
float *Weiner_Filter_NC(float *pInputSig, float *pNoiseSig, uint32_t len, uint32_t order)
{
    float *r_in, **R_nn;

    // create covariance vector and matrix
    r_in = covariance_vector(pNoiseSig, pInputSig, len, order); //WHY IS THIS OTHER WAY ROUND?
    R_nn = covariance_matrix(pNoiseSig, pNoiseSig, len, order);

    // TODO FREE

    // create matrix definitions
    LAL_MatrixDef *covarMat, *covarVec, *inverseMat, *wCoMat;

    // add covariance matrix and vector to LAL matrix definition
    covarMat = LAL_CreateMatrix(order, order);
    covarMat->mData = R_nn;
    covarVec = LAL_CreateMatrix(order, 1);
    uint32_t ni;
    for (ni=0; ni<order; ni++)
    {
        covarVec->mData[ni][0] = r_in[ni];  
    }

    // calculate inverse matrix
    inverseMat = LAL_Inverse(covarMat);

    printf("\nCovar Vec\n");
    for (uint32_t rowIdx=0; rowIdx<covarVec->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<covarVec->noCols; colIdx++)
        {
            printf("%.15f\t", covarVec->mData[rowIdx][colIdx]);
        }
        printf("\n");
    }

    printf("\nCovar Mat\n");
    for (uint32_t rowIdx=0; rowIdx<covarMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<covarMat->noCols; colIdx++)
        {
            printf("%.15f\t", covarMat->mData[rowIdx][colIdx]);
        }
        printf("\n");
    }

    printf("\nInverse Matrix\n");
    for (uint32_t rowIdx=0; rowIdx<inverseMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<inverseMat->noCols; colIdx++)
        {
            printf("%.15f\t", inverseMat->mData[rowIdx][colIdx]);
        }
        printf("\n");
    }

    // free covariance matrix
    LAL_FreeMatrix(covarMat);

    // multiply inverse covariance matrix by covariance vector
    wCoMat = LAL_Multiply(inverseMat, covarVec);

    printf("\nWeiner Matrix\n");
    for (uint32_t rowIdx=0; rowIdx<wCoMat->noRows; rowIdx++)
    {
        for (uint32_t colIdx=0; colIdx<wCoMat->noCols; colIdx++)
        {
            printf("%.15f\t", wCoMat->mData[rowIdx][colIdx]);
        }
        printf("\n");
    }

    // free covariance matrix
    LAL_FreeMatrix(inverseMat);
    LAL_FreeMatrix(covarVec);

    //
    float *pWCo = LAL_ExtractVector(wCoMat);
    LAL_FreeMatrix(wCoMat);

    return pWCo;
}
