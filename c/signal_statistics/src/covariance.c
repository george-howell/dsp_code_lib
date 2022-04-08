/*
 * covariance.c
 *
 *  Created on: 28 Dec 2021
 *      Author: ghowell
 */

#include "covariance.h"

/************************************************************************
 * @fn              - covariance_vector
 *
 * @brief           - Determines the covariance vector which is of the
 *                    length of the specified order.
 *
 * @param[in]       - data1: pointer to array of data
 * @param[in]       - data2: pointer to array of data
 * @param[in]       - len: number of data samples
 * @param[in]       - order: order of matrix
 *
 * @return          - pointer to covariance vector
 *
 * @notes           - The order must not exceed the length of data.
 */
float *covariance_vector(float *data1, float *data2, uint32_t len, uint32_t order)
{
    // find mean of signals
    float mean1, mean2;
    mean1 = mean(data1, len);
    mean2 = mean(data2, len);

    // subtract mean of signals
    uint32_t sampIdx;
    for(sampIdx=0; sampIdx<len; sampIdx++)
    {
        *(data1+sampIdx) -= mean1;
        *(data2+sampIdx) -= mean2;
    }

    float acc;
    float *covarVec = (float*)malloc(sizeof(float)*order);

    for (uint32_t ni=0; ni<order; ni++)
    {
        acc = 0;
        for(sampIdx=ni; sampIdx<len; sampIdx++)
        {
            // multiple and sum data
            acc = acc + (*(data1+sampIdx-ni) * *(data2+sampIdx));
        }

        // normalise (sample variance)
        acc = acc/((float)len - 1.0);

        // assign to covariance vector
        covarVec[ni] = acc;
    }

    return covarVec;

}

/************************************************************************
 * @fn              - covariance_matrix
 *
 * @brief           - Determines the covariance matrix given two signals.
 *                    The size of the resulting matrix is determined by
 *                    the order.
 *
 * @param[in]       - data1: pointer to array of data
 * @param[in]       - data2: pointer to array of data
 * @param[in]       - len: number of data samples
 * @param[in]       - order: order of matrix
 *
 * @return          - pointer to the covariance matrix
 *
 * @notes           - The data arrays must be the same length.
 */
float **covariance_matrix(float *data1, float *data2, uint32_t len, uint32_t order)
{
    // determine covariance row and column vector
    float *covarRow, *covarCol;
    covarRow = covariance_vector(data1, data2, len, order);
    covarCol = covariance_vector(data2, data1, len, order);

    // create toeplitz covariance matrix
    float **covarMat;
    covarMat = toeplitz(covarRow, covarCol, len);

    free(covarRow);
    free(covarCol);

    return covarMat;
}
