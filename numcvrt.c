
    /******************************************
    *
    *  file d:\cips\numcvrt.c
    *
    *  Functions:
    *     get_integer
    *     get_short
    *     get_long
    *     get_float
    *
    *  Purpose: 
    *     These functions read numbers from
    *     the keyboard.
    *
    *  Modifications:
    *     12 May 1993 - recreated
    *     28 July 2015 - created
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    *******************************************/


#include "mtypes.h"
#include <stdio.h>
#include <stdlib.h>

#define STRING_LENGTH 80

void get_integer(sint16_t *n) {
  char_t string[STRING_LENGTH];

  gets(string);
  *n = atoi(string);
}


void get_short(sint16_t *n) {
  char_t string[STRING_LENGTH];

  gets(string);
  *n = atoi(string);
}


void get_long(sint32_t *n) {
  char_t string[STRING_LENGTH];

  gets(string);
  *n = atol(string);
}


void get_float(float *f) {
  char_t string[STRING_LENGTH];

  gets(string);
  *f = atof(string);
}
