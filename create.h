   /************************************************
   *
   *       file create.h
   *
   *       Modifications:
   *         28 July 2015 - created
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#ifndef CREATE_H
#define CREATE_H

#define LSB 1
#define PARAM_NUMBERS 4
#define BITS_PER_PIXEL 8
#define STRIP_OFFSET 1000

typedef enum {NO_ERROR = 0, 
			WRONG_NUMBER_OF_PARAMETERS = -1,
			WRONG_TYPE_OF_INPUT_FILE = -2
} errors;

#endif /* CREATE_H */