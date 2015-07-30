   /***********************************************
   *
   *   file dumpi.h
   *
   *   Modifications:
   *      28 July 2015 - created
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#ifndef DUMPI_H
#define DUMPI_H

#define PARAM_NUMBER 3
#define SIZE_CONST1 4
#define SIZE_CONST2 7

typedef enum {
   NO_ERROR = 0, 
	WRONG_NUMBER_OF_PARAMETERS = -1,
	IN_FILE_DOES_NOT_EXIST = -2,
	COULD_NOT_OPEN_OUT_FILE = -3,
	GET_IMAGE_SIZE_ERROR = 1,
	ALLOCATE_IMAGE_ARRAY_ERROR = 2
} errors;

#endif /* DUMPI_H */