/**
 * @file    stat_basic.h
 *
 * @brief   Basic lag statistics
 *  
 * @par
 * Created On: 24/12/22
 * Created By: G. Howell
 */

#ifndef __STAT_BASIC_H__
#define __STAT_BASIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- INCLUDES -----------------------------------*/

#include "mat_matrix_structure.h"

/*------------------- MACROS AND DEFINES -------------------------*/
/*------------------- TYPEDEFS -----------------------------------*/
/*------------------- EXPORTED VARIABLES -------------------------*/
/*------------------- GLOBAL FUNCTION PROTOTYPES -----------------*/

float STAT_Mean(MAT_MatrixStructDef *inputMat);

#ifdef __cplusplus
}
#endif

#endif /* __STAT_BASIC_H__ */