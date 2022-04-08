/*
 * data_io.h
 *
 *  Created on: 23 Dec 2021
 *      Author: ghowell
 */

#include <stdio.h>
#include <stdint.h>

#ifndef DATA_IO_H_
#define DATA_IO_H_

typedef float fmtType;

typedef enum
{
    DATA_IO_OK,
    DATA_IO_ERR
} Data_IO_Status;

Data_IO_Status readRawFile(char *filename, fmtType *data, uint32_t len);
Data_IO_Status writeRawFile(char *filename, fmtType *data, uint32_t len);

#endif /* DATA_IO_H_ */
