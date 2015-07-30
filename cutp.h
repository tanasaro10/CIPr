/******************************************************************************
*
*    file cutp.h
*
*    Functions: This file contains
*        paste_image_piece
*        check_cut_and_paste_limits
*
*    Purpose:
*        These functions paste a part of one
*        image into another image.
*
*    External Calls:
*        none
*
*    Modifications:
*         3 April 1992 - created
*        12 August 1998 - modified to work with an entire image array.
*        30 July 2015 - Refactored
*              Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015
*
*******************************************************************************/
#ifndef CUTP_H
#define CUTP_H

#include "cips.h"
#include "imageio.h"

/******************************************************************************
*   
*   paste_image_piece(...
*
*   This function pastes a rectangular piece of an image into another image.
*   The rectangle to be pasted into the image is described by the il1, ie1, ll1, 
*   le1 parameters for the input image.
* 
*******************************************************************************/
void paste_image_piece(sint16_t **the_image,
                      sint16_t **out_image,
                      sint32_t il1,
                      sint32_t ie1,
                      sint32_t ll1,
                      sint32_t le1,
                      sint32_t il2,
                      sint32_t ie2);

/******************************************************************************
*   
*   check_cut_and_paste_limits(...
*
*   This function looks at the line and element parameters and ensures that 
*   they are not bigger than ROWS and COLS. If they are bigger, the last 
*   element or last line parameters are reduced.
* 
*******************************************************************************/
void check_cut_and_paste_limits(sint32_t il1, 
                                sint32_t ie1, 
                                sint32_t ll1, 
                                sint32_t le1, 
                                sint32_t il2, 
                                sint32_t ie2, 
                                sint32_t image1_length, 
                                sint32_t image1_width,
                                sint32_t image2_length, 
                                sint32_t image2_width,
                                sint16_t *is_ok);

#endif