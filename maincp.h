/******************************************************************************
*
*    file maincp.h
*
*    Purpose:
*       This file contains the main calling
*       routine for a program which 
*       cuts a piece from one image and pastes
*       it into another.
*
*    External Calls:
*      imageio.c - create_image_file
*                  read_image_array
*                  write_image_array
*                  get_image_size
*                  allocate_image_array
*                  free_image_array
*      cutp.c - paste_image_piece
*               check_cut_and_paste_limits
*
*    Modifications:
*       8 April 1992 - created
*      12 August 1998 - modified to work on
*           entire image array at once.
*      18 September 1998 - modified to work with 
*           all I O routines in imageio.c.
*      30 July 2015 - Refactored
*           Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015
*
******************************************************************************/
#ifndef MAINCP_H
#define MAINCP_H

#include "cips.h"
#include "imageio.h"
#include "cutp.h"

#define REQUIRED_PARAMETERS     9

#define ERR_NONE                0
#define ERR_INVALID_NO_OF_ARGS -1
#define ERR_NO_INPUT_FILE      -2

#endif