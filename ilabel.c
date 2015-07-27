
    /************************************************
    *
    *   file ilabel.c
    *
    *   Functions: This file contains
    *       main
    *
    *   Purpose:
    *      This program writes simple block letters
    *      the an image file.  You can use these
    *      as labels for other images.
    *
    *   External Calls:
    *      imageio.c - create_image_file
    *                  read_image_array
    *                  write_image_array
    *                  get_image_size
    *                  allocate_image_array
    *                  free_image_array
    *
    *   Modifications:
    *      21 May 1993 - created
    *      22 August 1998 - modified to work on entire
    *           images at once.
    *      19 September 1998 - modified to work with 
    *            all I O routines in imageio.c.
    *
    *************************************************/


#include "cips.h"

#define R             9
#define C             7
#define COUNTER_LIMIT 8
#define IE_START      7
#define VAL         200

short **image;

         /******************************
         *
         *   Define all the 9x7 arrays
         *   that contain the characters.
         *
         *******************************/

short aperiod[R][C] = {
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,  0,  0,  0},
                   {  0,  0,VAL,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short acomma[R][C] = {
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,  0,  0,  0},
                   {  0,  0,VAL,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0}};

short aexclam[R][C] = {
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short xx[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short aa[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ab[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ac[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ad[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ae[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short af[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ag[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ah[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ai[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short aj[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ak[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,VAL,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,VAL,VAL,  0,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,VAL,  0,  0,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short al[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short am[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,  0,VAL,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short an[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,  0,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,  0,VAL,VAL,  0},
                   {  0,VAL,  0,  0,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ao[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ap[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short aq[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,  0,VAL,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ar[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};
short as[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short at[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short au[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short av[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short aw[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ax[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short ay[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,  0,VAL,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short az[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,VAL,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a1[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,VAL,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a2[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,VAL,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a3[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a4[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,VAL,  0,VAL,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a5[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a6[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a7[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,VAL,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,VAL,  0,  0},
                   {  0,  0,  0,VAL,  0,  0,  0},
                   {  0,  0,VAL,  0,  0,  0,  0},
                   {  0,VAL,  0,  0,  0,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a8[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a9[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,VAL,  0,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,VAL,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};

short a0[R][C] = { {  0,  0,  0,  0,  0,  0,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,VAL,  0,  0,VAL,VAL,  0},
                   {  0,VAL,  0,  0,VAL,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,  0,VAL,  0,VAL,  0},
                   {  0,VAL,VAL,  0,  0,VAL,  0},
                   {  0,  0,VAL,VAL,VAL,  0,  0},
                   {  0,  0,  0,  0,  0,  0,  0}};



main(argc, argv)
   int  argc;
   char *argv[];
{
   int    l=1, w=1;
   int    counter=0, i, j, il, ie=7, ll, le;
   long   length, width;

   if(argc < 5){
      printf("\n usage: ilabel file-name il ie text"
      "\n  the file-name image must already exist");
      exit(0);
   }

      /****************************************
      *
      *   Ensure the file exists.
      *   Allocate an image array and read 
      *   the image.
      *
      ****************************************/

   if(does_not_exist(argv[1])){
      printf("\nFile %s does not exist \nCreate it", argv[1]);
      exit(0);
   }  /* ends if does not exist */
   else{  /* else it does exist */
      get_image_size(argv[1], &length, &width);
      image = allocate_image_array(length, width);
      read_image_array(argv[1], image);
   }  /* ends else it does exist */

   il = atoi(argv[2]);
   ie = atoi(argv[3]);

         /******************************
         *
         *   Loop through the text
         *   arguments and place the
         *   letter arrays into the
         *   image.
         *
         *******************************/

   printf("\n");
   for(i=4; i<argc; i++){
      for(j=0; j<(strlen(argv[i])); j++){

         argv[i][j] = tolower(argv[i][j]);

         printf("%c", argv[i][j]);
         printf("%d %d\n",il, ie);
         if(argv[i][j] == 'a')
            copy_array_into_image(aa, image, il, ie);
         if(argv[i][j] == 'b')
            copy_array_into_image(ab, image, il, ie);
         if(argv[i][j] == 'c')
            copy_array_into_image(ac, image, il, ie);
         if(argv[i][j] == 'd')
            copy_array_into_image(ad, image, il, ie);
         if(argv[i][j] == 'e')
            copy_array_into_image(ae, image, il, ie);
         if(argv[i][j] == 'f')
            copy_array_into_image(af, image, il, ie);
         if(argv[i][j] == 'g')
            copy_array_into_image(ag, image, il, ie);
         if(argv[i][j] == 'h')
            copy_array_into_image(ah, image, il, ie);
         if(argv[i][j] == 'i')
            copy_array_into_image(ai, image, il, ie);
         if(argv[i][j] == 'j')
            copy_array_into_image(aj, image, il, ie);
         if(argv[i][j] == 'k')
            copy_array_into_image(ak, image, il, ie);
         if(argv[i][j] == 'l')
            copy_array_into_image(al, image, il, ie);
         if(argv[i][j] == 'm')
            copy_array_into_image(am, image, il, ie);
         if(argv[i][j] == 'n')
            copy_array_into_image(an, image, il, ie);
         if(argv[i][j] == 'o')
            copy_array_into_image(ao, image, il, ie);
         if(argv[i][j] == 'p')
            copy_array_into_image(ap, image, il, ie);
         if(argv[i][j] == 'q')
            copy_array_into_image(aq, image, il, ie);
         if(argv[i][j] == 'r')
            copy_array_into_image(ar, image, il, ie);
         if(argv[i][j] == 's')
            copy_array_into_image(as, image, il, ie);
         if(argv[i][j] == 't')
            copy_array_into_image(at, image, il, ie);
         if(argv[i][j] == 'u')
            copy_array_into_image(au, image, il, ie);
         if(argv[i][j] == 'v')
            copy_array_into_image(av, image, il, ie);
         if(argv[i][j] == 'w')
            copy_array_into_image(aw, image, il, ie);
         if(argv[i][j] == 'x')
            copy_array_into_image(ax, image, il, ie);
         if(argv[i][j] == 'y')
            copy_array_into_image(ay, image, il, ie);
         if(argv[i][j] == 'z')
            copy_array_into_image(az, image, il, ie);
         if(argv[i][j] == '1')
            copy_array_into_image(a1, image, il, ie);
         if(argv[i][j] == '2')
            copy_array_into_image(a2, image, il, ie);
         if(argv[i][j] == '3')
            copy_array_into_image(a3, image, il, ie);
         if(argv[i][j] == '4')
            copy_array_into_image(a4, image, il, ie);
         if(argv[i][j] == '5')
            copy_array_into_image(a5, image, il, ie);
         if(argv[i][j] == '6')
            copy_array_into_image(a6, image, il, ie);
         if(argv[i][j] == '7')
            copy_array_into_image(a7, image, il, ie);
         if(argv[i][j] == '8')
            copy_array_into_image(a8, image, il, ie);
         if(argv[i][j] == '9')
            copy_array_into_image(a9, image, il, ie);
         if(argv[i][j] == '0')
            copy_array_into_image(a0, image, il, ie);
         if(argv[i][j] == '.')
            copy_array_into_image(aperiod, image,
                                  il, ie);
         if(argv[i][j] == ',')
            copy_array_into_image(acomma, image,
                                  il, ie);
         if(argv[i][j] == '!')
            copy_array_into_image(aexclam, image,
                                  il, ie);


         ie = ie + C;

      }  /* ends loop over j letters in argument */

            /* Put a space between words */
         copy_array_into_image(xx, image, il, ie);
         ie = ie + C;

   }  /* ends loop over i arguments */

   write_image_array(argv[1], image);
   free_image_array(image, length);
   
}  /* ends main */







copy_array_into_image(a, the_image, il, ie)
   short a[R][C], **the_image;
   int   il, ie;
{
   int i, j;
   for(i=0; i<R; i++)
      for(j=0; j<C; j++)
         the_image[il+i][ie+j] = a[i][j];

}  /* ends copy_array_into_image */
