
   /***********************************************
   *
   *   file halftone.c
   *
   *   Functions: This file contains
   *      main
   *
   *   Purpose:
   *      This file contains the main calling
   *      routine in an image addition and subtraction
   *      program.
   *
   *
   *   Modifications:
   *      1 April 1992 - created
   *     10 August 1998 - modified to work on entire
   *         images at one time.
   *     18 September 1998 - modified to work with 
   *           all I O routines in imageio.c.
   *	   Modified Date: 27 Iuly 2015 
	 *		 Author: Mihu Andrei Cristian
   *		 Scoala de vara Thales
   *************************************************/

#include "mainas.h"


void add_image_array(sint16_t **the_image, sint16_t **out_image,
                     uint32_t rows, uint32_t cols, uint16_t max);

void subtract_image_array(sint16_t **the_image, sint16_t **out_image, 
                          uint32_t rows, uint32_t cols);


uint16_t main(uint16_t argc, char_t *argv[])
{

   char_t     name1[80], name2[80], name3[80];
   uint32_t     bits_per_pixel, width, length;	
   sint16_t    **image1, **image2;
   uint16_t    max;
   errFlag = eReturnOK;

       /******************************************
       *
       *  Interpret the command line parameters.
       *
       *******************************************/

if(image1 == NULL) {
	errFlag = eImage1Null;
}

if(image2 == NULL) {
	errFlag = eImage2Null;
}

   if(argc != 5){
    (void)printf(
     "\n"
     "\n usage: mainas in1-file in2-file "
     "out_file add-subtract"
     "\n"
     "\n   recall add-subtract a=add s=subtract\n");
    errFlag = eNotStuffArg;
   }

if(errFlag == eReturnOK) {

   strcpy(name1, argv[1]);
   strcpy(name2, argv[2]);
   strcpy(name3, argv[3]);

   if(does_not_exist(name1)){
    (void)printf("\nERROR input file %s does not exist",
             name1);
    errFlag = eNotExistName1;
   }

if(errFlag == eReturnOK) {

   if(does_not_exist(name2)){
    (void)printf("\nERROR input file %s does not exist",
             name2);
    errFlag = eNotExistName2;
   }

if(errFlag == eReturnOK) {

       /******************************************
       *
       *  Ensure the two input images have the 
       *  same sizes.
       *
       *******************************************/

   if(are_not_same_size(name1, name2)){
      (void)printf(
      "\nERROR Image files %s and %s are not same size", 
      name1, name2);
      errFlag = eNotSameSize;
   }

if(errFlag == eReturnOK) {

       /******************************************
       *
       *  Allocate the two image arrays
       *
       *******************************************/

   get_image_size(name1, &length, &width);
   get_bitsperpixel(name1, &bits_per_pixel);
   image1 = allocate_image_array(length, width);
   image2 = allocate_image_array(length, width);
   
       /******************************************
       *
       *  Create the output file and read the
       *  two input images.
       *
       *******************************************/

   create_image_file(name1, name3);
   read_image_array(name1, image1);
   read_image_array(name2, image2);

       /********************************************
       *
       *   Add or subtract the input images and 
       *   write the result to the output image.
       *
       ********************************************/

   if(argv[4][0] == 'a' || argv[4][0] == 'A'){
      if(bits_per_pixel == 4)
         max = 16;
      else
         max = 255;
      add_image_array(image1, image2,
         length, width, max);
   }  /* ends if add */

   if(argv[4][0] == 's' || argv[4][0] == 'S')
      subtract_image_array(image1, image2,
         length, width);

   write_image_array(name3, image2);

   free_image_array(image1, length);
   free_image_array(image2, length);

}//eNotSameSize
}//eNotExistName
}//eNotExistName1
}/*eNotStuffArg*/
		return errFlag;
}  /* ends main  */
