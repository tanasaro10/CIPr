    /***********************************************
    *
    *       file boole.h
    *
    *       Modifications:
    *         27 July 2015 - refactored
    *		      28 July 2015 - refactored		
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    ***********************************************/

#ifndef BOOLE_H
#define BOOLE_H

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
          sint32_t rows, sint32_t cols);

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
         sint32_t rows, sint32_t cols); 

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
         sint32_t rows, sint32_t cols);


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
         sint32_t rows, sint32_t cols, sint16_t value);

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
         sint32_t rows, sint32_t cols, sint16_t value);


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
         sint32_t rows, sint32_t cols, sint16_t value);

#endif /* BOOLE_H */