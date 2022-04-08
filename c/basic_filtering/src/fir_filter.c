/*
 * fir_filter.c
 *
 *  Created on: 24 Dec 2021
 *      Author: ghowell
 */

#include "fir_filter.h"

float FIR_Filter_Float(float sampleData, float *bCoeffs)
{
    // shift register
    for (uint32_t ni=(NO_TAPS-1); ni>0; ni--)
    {
        shiftReg[ni] = shiftReg[ni-1];
    }
    shiftReg[0] = sampleData;

    // perform MAC operation
    float acc = 0;
    for (uint32_t ni=0; ni<NO_TAPS; ni++)
    {
        acc = acc + (*(bCoeffs+ni) * shiftReg[ni]);  
    }
    
    return acc;
}
