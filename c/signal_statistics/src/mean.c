/*
 * mean.c
 *
 *  Created on: 28 Dec 2021
 *      Author: ghowell
 */

#include "mean.h"

/************************************************************************
 * @fn              - mean
 *
 * @brief           - finds the mean value of a data array
 *
 * @param[in]       - *data: pointer to data
 * @param[in]       - len: length of data
 *
 * @return          - mean value
 *
 * @notes           - none
 */
float mean(float *data, uint32_t len)
{
    float acc = 0;

    // sums the data
    for(uint32_t ni=0; ni<len; ni++)
    {
        acc = acc + *(data+ni);
    }

    // normalisation by length
    acc = acc/(float)len;

    return acc;
}
