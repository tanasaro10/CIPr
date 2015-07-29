       /*********************************************
       *
       *   file boolean.h
       *
       *   Modifications:
       *      28 July 2015 - created
       *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
       *
       *********************************************/

#ifndef BOOLEAN_H
#define BOOLEAN_H

#define PARAM_NUMBERS 5
#define NAME_LENGTH 80

typedef enum {NO_ERROR = 0, 
		WRONG_NUMBER_OF_PARAMETERS = -1,
		IN_FILE_DOES_NOT_EXIST = -2,
		IMAGES_ARE_NOT_THE_SAME_SIZE = -3,
		GET_IMAGE_SIZE_ERROR = 1,
		ALLOCATE_IMAGE_ARRAY_ERROR = 2,
} errors;

#endif /*  BOOLEAN_H */
