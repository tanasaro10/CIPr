/******************************************************************************
*
*   file showi.c
*
*   Purpose:
*      This file contains the program
*      that shows image numbers on the screen.
*
*   External Calls:
*      imageio.c - get_image_size
*                  read_image_array
*                  allocate_image_array
*                  free_image_array
*
*   Modifications:
*      1 October 1998 - created to work with 
*           all I O routines in imageio.c.
*      28 July 2015 - Refactored
*           Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015
*
******************************************************************************/
#ifndef SHOWI_H
#define SHOWI_H

#include "cips.h"
#include "mtypes.h"
#include "imageio.h"

#define  SHEIGHT 20
#define  SWIDTH  15

#define ERR_NONE                 0
#define ERR_INVALID_NO_OF_ARGS  -1
#define ERR_NO_INPUT_FILE       -2

/******************************************************************************
*
*   is_in_image(...
*
*   This routine verifies if an image's size fits into another's
*
******************************************************************************/
static sint16_t is_in_image(sint16_t il, 
                           sint16_t ie, 
                           sint32_t height, 
                           sint32_t width);

/******************************************************************************
*
*   show_screen(...
*
*   This routine prints to the screen the instructions on how to use
*   the application.
*
******************************************************************************/
static void show_screen(sint16_t **the_image, sint16_t il, sint16_t ie);

#endif