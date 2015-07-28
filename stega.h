/******************************************************************************
*
*  file stega.c
*
*  Purpose:
*     This file contains the main calling  routine and other routines that
*     use steganography to hide one image inside another and then recover the
*     hidden image.
*
*  External Calls:
*      imageio.c - create_image_file
*                  read_image_array
*                  write_image_array
*                  get_image_size
*                  allocate_image_array
*                  free_image_array
*
*  Modifications:
*     5 April 1998 - created
*     22 September 1998 - modified to work with 
*           all I O routines in imageio.c.
*     28 July 2015 - Refactored
*           Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015
*
*******************************************************************************/

#ifndef STEGA_H
#define STEGA_H

#include "cips.h"
#include "mtypes.h"
#include "imageio.h"

#define EIGHT 8

/******************************************************************************
*
*   hide_image(...
*
*   This routine hides the message image in the cover image.  Loop through 
*   the pixels in the message image and call hide_pixels for every pixel 
*   in the message image.
*
******************************************************************************/
sint16_t hide_image(sint16_t **cover_image,
                    sint16_t **message_image,
                    sint32_t mlength,
                    sint32_t mwidth,
                    sint32_t clength,
                    sint32_t cwidth,
                    sint16_t lsb,
                    sint16_t n);

/******************************************************************************
*
*   hide_pixels(...
*
*   This routine hides the bits in a pixel from the message image into the 
*   least significant bit of eight pixels in the cover image.
*
*   Do this one operation for every row of  pixels in the message and 
*   cover images.
*
******************************************************************************/
sint16_t hide_pixels(sint16_t **cover_image,
                      sint16_t **message_image,
                      sint16_t mie,
                      sint16_t cie,
                      sint16_t lsb,
                      sint16_t n,
                      sint32_t mlength);

/******************************************************************************
*
*   uncover_image(...
*
*   This routine pulls the message image out f the cover image (the opposite
*   of the cover_image routine).
*
******************************************************************************/
sint16_t uncover_image(sint16_t **cover_image,
                    sint16_t **message_image,
                    sint32_t mlength,
                    sint32_t mwidth,
                    sint32_t clength,
                    sint32_t cwidth,
                    sint16_t lsb,
                    sint16_t n);

/******************************************************************************
*
*   uncover_pixels(...
*
*   This routine pulls the eight bits that  make up a pixel in the message 
*   image out of the LSB of eight pixels in the cover image.  It is the 
*   opposite of the cover_pixels routine.
*
******************************************************************************/
sint16_t uncover_pixels(sint16_t **cover_image,
                      sint16_t **message_image,
                      sint16_t mie,
                      sint16_t cie,
                      sint16_t lsb,
                      sint16_t n,
                      sint32_t mlength);

/******************************************************************************
*
*   is_odd(...
*
*   This routine determines if a short is  an odd number.  If it is, this 
*   routine returns a 1, else it returns a 0.
*
******************************************************************************/
sint16_t is_odd(int16_t number);

/******************************************************************************
*
*   stega_show_usage(...
*
*   This routine prints the instructions on how to use the application
*
******************************************************************************/
void stega_show_usage(void);

#endif