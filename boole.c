
    /***********************************************
    *
    *       file boole.c
    *
    *       Functions: This file contains
    *          and_image
    *          or_image
    *          xor_image
    *          nand_image
    *          nor_image
    *          not_image
    *
    *       Purpose:
    *          These functions implement the basic
    *          Boolean algebra functions AND, OR,
    *          XOR, NAND, NOR, and NOT.
    *
    *       External Calls:
    *          none
    *
    *       Modifications:
    *          3 March 1993 - created
    *         22 August 1998 - modified to work on 
    *              entire images at once.
    *         27 July 2015 - refactored
    *         28 July 2015 - refactored
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    ***********************************************/


#include "cips.h"
#include "mtypes.h"
#include "boole.h"

   /************************************************
   *
   *   and_image(...
   *
   *   This function performs the Boolean AND 
   *   operation.  The output image = in1 AND in2.
   *   This works for 0 non-zero images.  If both
   *   in1 and in2 are non-zero, the output = in1.
   *
   *************************************************/

void and_image(sint16_t **the_image, sint16_t **out_image,
          sint32_t rows, sint32_t cols) {
  sint32_t  i, j;

  for (i = 0; i < rows; i++) {
    if ((i % 10) == 0) {
      printf(" %d", i);
    }
    for (j = 0; j < cols; j++) {
      if ((the_image[i][j] != 0) && (out_image[i][j] != 0)) {
        out_image[i][j] = the_image[i][j];
      }
      else {
        out_image[i][j] = 0;
      }
    }  /* ends loop over j */
  }  /* ends loop over i */
} /* ends and_image */





   /************************************************
   *
   *   or_image(...
   *
   *   This function performs the Boolean OR 
   *   operation.  The output image = in1 OR in2.
   *   This works for 0 non-zero images.  If both
   *   in1 and in2 are non-zero, the output = in1.
   *   If in1 is non-zero, the output = in1.
   *   If in1 is zero and in2 is non-zero, the
   *   output = in2.
   *
   *************************************************/

void or_image(sint16_t **the_image, sint16_t **out_image,
         sint32_t rows, sint32_t cols) {
  sint32_t  i, j;

  for (i = 0; i < rows; i++) {
    if ((i%10) == 0) {
      printf(" %d", i);
    }
    for (j = 0; j < cols; j++) {
      if ((the_image[i][j] != 0) || (out_image[i][j] != 0)) {
        if (the_image[i][j] != 0) {
          out_image[i][j] = the_image[i][j];
        }
        else {
          out_image[i][j] = out_image[i][j];
        }
      }
      else {
        out_image[i][j] = 0;
      }
    }  /* ends loop over j */
  }  /* ends loop over i */

} /* ends or_image */





   /************************************************
   *
   *   xor_image(...
   *
   *   This function performs the Boolean XOR 
   *   operation.  The output image = in1 XOR in2.
   *   This works for 0 non-zero images.  If 
   *   in1 is non-zero and in2 is 0, output = in1. If
   *   in2 is non-zero and in1 is 0, output = in2.
   *   If both in1 and in2 are non-zero, output = 0.
   *   If both in1 and in2 are zero, output = 0.
   *
   *************************************************/

void xor_image(sint16_t **the_image, sint16_t **out_image,
         sint32_t rows, sint32_t cols) {
  sint32_t  i, j;
  sint16_t  answer;

  for (i = 0; i < rows; i++) {
    if ((i%10) == 0) {
      printf(" %d", i);
    }
    for (j = 0; j < cols; j++) {
      if ((the_image[i][j] != 0) && (out_image[i][j] == 0)) {
        answer = the_image[i][j];
      }
      if ((the_image[i][j] == 0) && (out_image[i][j] != 0)) {
        answer = out_image[i][j];
      }
      if ((the_image[i][j] == 0) && (out_image[i][j] == 0)) {
        answer = 0;
      }
      if ((the_image[i][j] != 0) && (out_image[i][j] != 0)) {
        answer = 0;
      }
      out_image[i][j] = answer;
    }  /* ends loop over j */
  }  /* ends loop over i */

} /* ends xor_image */





   /***********************************************
   *
   *   nand_image(...
   *
   *   This function performs the Boolean NAND 
   *   operation.  The output image = in1 NAND in2.
   *   This works for 0 non-zero images.  If both
   *   in1 and in2 are non-zero, the output = 0.
   *   Otherwise, the output = value.
   *
   ************************************************/

void nand_image(sint16_t **the_image, sint16_t **out_image,
         sint32_t rows, sint32_t cols, sint16_t value) {
  sint32_t  i, j;

  for (i = 0; i < rows; i++) {
    if ((i%10) == 0) {
      printf(" %d", i);
    }
    for (j = 0; j < cols; j++) {
      if ((the_image[i][j] != 0) && (out_image[i][j] != 0)) {
        out_image[i][j] = 0;
      }
      else {
        out_image[i][j] = value;
      }
    }  /* ends loop over j */
  }  /* ends loop over i */
} /* ends nand_image */






   /***********************************************
   *
   *   nor_image(...
   *
   *   This function performs the Boolean NOR 
   *   operation.  The output image = in1 NOR in2.
   *   This works for 0 non-zero images.  If niether
   *   in1 nor in2 are non-zero, the output = value.
   *   That is, if both in1 and in2 are zero, the
   *   output = value.
   *
   ************************************************/

void nor_image(sint16_t **the_image, sint16_t **out_image,
         sint32_t rows, sint32_t cols, sint16_t value) {
  sint32_t  i, j;

  for (i = 0; i < rows; i++){
    if ((i % 10) == 0) {
      printf(" %d", i);
    }
    for (j = 0; j < cols; j++){
      if ((the_image[i][j] == 0) && (out_image[i][j] == 0)) {
        out_image[i][j] = value;
      }
      else {
        out_image[i][j] = 0;
      }
    }  /* ends loop over j */
  }  /* ends loop over i */

} /* ends nor_image */


   /***********************************************
   *
   *   not_image(...
   *
   *   This function will complement the values 
   *   of the input image and put them into the 
   *   output image. It will complement using a 
   *   0-value scheme where value is one of the 
   *   input parameters.
   *
   ************************************************/

void not_image(sint16_t **the_image, sint16_t **out_image,
         sint32_t rows, sint32_t cols, sint16_t value) {
  sint32_t  i, j;

  for (i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      out_image[i][j] = value;
    }
  }

  for (i = 0; i < rows; i++) {
    if ((i % 10) == 0) {
      printf(" %d", i);
    }
    for (j = 0; j < cols; j++) {
      if (the_image[i][j] == value) {
        out_image[i][j] = 0;
      }
    }  /* ends loop over j */
  }  /* ends loop over i */

} /* ends not_image */

