
    /********************************************
    *
    *    file geometry.h
    *
    *    Modifications:
    *       28 July 2015 - created
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    ********************************************/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#define FILE_NAME_LENGTH 80
#define PARAM_NUMBER 7

typedef enum {
	NO_ERROR = 0, 
	WRONG_NUMBER_OF_PARAMETERS = -1,
	IN_FILE_DOES_NOT_EXIST = -2,
	ARG1_IS_NOT_BMP_FILE = -3,
	ARG2_IS_NOT_TIF_FILE = -4,
	GET_IMAGE_SIZE_ERROR = 1,
	ALLOCATE_IMAGE_ARRAY_ERROR = 2
} errors;

#endif /* GEOMETRY_H */