/*
 * data_io.c
 *
 *  Created on: 22 Dec 2021
 *      Author: ghowell
 */

#include "data_io.h"

/*
 * readRawFile
 */
Data_IO_Status readRawFile(char *filename, fmtType *data, uint32_t len)
{
    FILE *fid;

    // open the file
    if((fid = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"Error opening file %s\n",filename);
        return DATA_IO_ERR;
    }

    // read data from file and close
    fread(data, sizeof(fmtType), len, fid);
    fclose(fid);

    return DATA_IO_OK;
}

/*
 * writeRawFile
 */
Data_IO_Status writeRawFile(char *filename, fmtType *data, uint32_t len)
{
    FILE *fid;

    // open the file
    if((fid = fopen(filename,"w")) == NULL)
    {
        fprintf(stderr,"Error opening file %s\n",filename);
        return DATA_IO_ERR;
    }

    // write data to file and close
    fwrite(data, sizeof(fmtType), len, fid);
    fclose(fid);

    return DATA_IO_OK;
}
