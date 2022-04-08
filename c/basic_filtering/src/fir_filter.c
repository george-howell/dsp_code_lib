/**
 * @file    fir_filter.c
 *
 * @brief   Basic FIR filters
 *  
 * @par
 * Created On: 24/12/22
 * Created By: G. Howell
 */

/*------------------- INCLUDES -----------------------------------*/

#include "fir_filter.h"

/*------------------- EXTERN VARIABLES ---------------------------*/
/*------------------- PRIVATE MACROS AND DEFINES -----------------*/
/*------------------- PRIVATE TYPEDEFS ---------------------------*/
/*------------------- STATIC VARIABLES ---------------------------*/

static float shiftReg[NUM_TAPS];

/*------------------- GLOBAL VARIABLES ---------------------------*/
/*------------------- STATIC FUNCTION PROTOTYPES -----------------*/
/*------------------- STATIC FUNCTIONS ---------------------------*/
/*------------------- GLOBAL FUNCTIONS ---------------------------*/

/**
 * @brief Basic FIR filter
 *
 * @param   sampleData    Sample data
 * @param   bCoeffs       B coefficients
 *
 * @return  Filter sample data output
 */
float FIR_Filter_Float(float sampleData, float *bCoeffs)
{
    // shift register
    for (uint32_t ni=(NUM_TAPS-1); ni>0; ni--)
    {
        shiftReg[ni] = shiftReg[ni-1];
    }
    shiftReg[0] = sampleData;

    // perform MAC operation
    float acc = 0;
    for (uint32_t ni=0; ni<NUM_TAPS; ni++)
    {
        acc = acc + (*(bCoeffs+ni) * shiftReg[ni]);  
    }
    
    return acc;
}
