/******************************************************************************
*
*   file stretch.h
*
*   Purpose:
*      This file contains the main calling
*      routine and the needed subroutines
*      for a program which stretches
*      an image by any factor.  It can either
*      roundoff the numbers or use
*      bi-linear interpolation.
*
*   External Calls:
*      imageio.c - create_resized_image_file
*                  read_image_array
*                  write_image_array
*                  get_image_size
*                  allocate_image_array
*                  free_image_array
*
*   Modifications:
*      4 December 1993 - created
*     16 September 1998 - modified to work on entire
*         images at one time.
*     22 September 1998 - modified to work with 
*         all I O routines in imageio.c.
*     30 July 2015 - Refactored
*         Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015
*
******************************************************************************/
#ifndef STRETCH_H
#define STRETCH_H

#include "mtypes.h"
#include "imageio.h"
#include "cips.h"
#include "geosubs.h"

#define FILL 150
#define REQUIRED_PARAMETERS     6

#define ERR_NONE                0
#define ERR_INVALID_NO_OF_ARGS -1
#define ERR_NO_INPUT_FILE      -2
#define ERR_INPUT_NOT_TIF      -3
#define ERR_OUTPUT_NOT_BMP     -4
#define ERR_NO_IMAGE_LOADED    -5

/******************************************************************************
*
*   stretch(..
*
*   This routine performs the image stretching. If bilinear == 0, it uses 
*   the roundoff approach for enlarging an area. If bilinear == 1, it 
*   calls the bilinear_interpolate routine to get the value of a pixel that 
*   lies between pixels.
*
******************************************************************************/
void stretch(sint16_t **the_image, 
             sint16_t **out_image,
             float x_stretch, 
             float y_stretch,
             sint16_t bilinear,
             sint32_t out_rows, 
             sint32_t out_cols,
             sint32_t in_rows,
             sint32_t in_cols);
#endif