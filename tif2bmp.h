/******************************************************************************
*
*     file tif2bmp.c
*
*     Functions: This file contains
*         main
*
*     Purpose:
*        This program creates a bmp file
*        that is just like the input tiff file.
*
*     External Calls:
*        imageio.c
*           does_not_exist
*           get_image_size
*           read_image_array
*           write_image_array
*           free_image_array
*           create_allocate_bmp_file
*
*     Modifications:
*         27 September 1998 - created
*         30 July 2015 - Refactored
*           Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015
*
******************************************************************************/
#ifndef TIF2BMP_H
#define TIF2BMP_H

#include "cips.h"
#include "mtypes.h"
#include "imageio.h"

#define ERR_NONE                0
#define ERR_INVALID_NO_OF_ARGS -1
#define ERR_NO_INPUT_FILE      -2
#define ERR_INPUT_NOT_TIF      -3
#define ERR_OUTPUT_NOT_BMP     -4
#define ERR_NO_IMAGE_LOADED    -5

#endif