/**
 * @file    stat_lag_statistics.h
 *
 * @brief   Basic lag statistics
 *  
 * @par
 * Created On: 24/12/22
 * Created By: G. Howell
 */

#ifndef __STAT_LAG_STATISTICS_H__
#define __STAT_LAG_STATISTICS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- INCLUDES -----------------------------------*/

#include "mat_matrix_structure.h"
#include "stat_basic.h"
#include "lal_basic_operations.h"

/*------------------- MACROS AND DEFINES -------------------------*/
/*------------------- TYPEDEFS -----------------------------------*/
/*------------------- EXPORTED VARIABLES -------------------------*/
/*------------------- GLOBAL FUNCTION PROTOTYPES -----------------*/

MAT_MatrixStructDef *STAT_CovarianceVector(MAT_MatrixStructDef *data1, MAT_MatrixStructDef *data2, uint32_t order);
MAT_MatrixStructDef *STAT_CovarianceMatrix(MAT_MatrixStructDef *data1, MAT_MatrixStructDef *data2, uint32_t order);

#ifdef __cplusplus
}
#endif

#endif /* __STAT_LAG_STATISTICS_H__ */