/**
 * @file    stat_basic.c
 *
 * @brief   Basic lag statistics
 *  
 * @par
 * Created On: 24/12/22
 * Created By: G. Howell
 */

/*------------------- INCLUDES -----------------------------------*/

#include "stat_basic.h"

/*------------------- EXTERN VARIABLES ---------------------------*/
/*------------------- PRIVATE MACROS AND DEFINES -----------------*/
/*------------------- PRIVATE TYPEDEFS ---------------------------*/
/*------------------- STATIC VARIABLES ---------------------------*/
/*------------------- GLOBAL VARIABLES ---------------------------*/
/*------------------- STATIC FUNCTION PROTOTYPES -----------------*/
/*------------------- STATIC FUNCTIONS ---------------------------*/
/*------------------- GLOBAL FUNCTIONS ---------------------------*/

/**
 * @brief   Finds the mean value of all data
 *
 * @param   inputMat    pointer to input data struct
 *
 * @return  Mean value
 */
float STAT_Mean(MAT_MatrixStructDef *inputMat)
{
    uint32_t rowIdx, colIdx;
    float acc = 0;

    for(rowIdx=0; rowIdx<inputMat->noRows; rowIdx++)
    {
        for(colIdx=0; colIdx<inputMat->noCols; colIdx++)
        {   
            acc = acc + inputMat->mData[rowIdx][colIdx];
        }
    }

    acc = acc/((float)(inputMat->noRows*inputMat->noCols));

    return acc;
}
