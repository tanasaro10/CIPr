 /************************************************
   *
   *       file bmp2tif.h
   *
   *       Modifications:
   *         28 July 2015 - refactored
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#ifndef BMP2TIF_H
#define BMP2TIF_H

#define LSB 1
#define PARAM_NUMBER 3
#define BITS_PER_PIXEL 8
#define STRIP_OFFSET 1000

typedef enum {
   NO_ERROR = 0, 
	WRONG_NUMBER_OF_PARAMETERS = -1,
	IN_FILE_DOES_NOT_EXIST = -2,
	ARG1_IS_NOT_BMP_FILE = -3,
	ARG2_IS_NOT_TIF_FILE = -4,
	GET_IMAGE_SIZE_ERROR = 1,
	ALLOCATE_IMAGE_ARRAY_ERROR = 2
} errors;

#endif /* BMP2TIF_H */