
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

#include "halftone.h"

uint16_t main(uint16_t argc, char_t *argv[]) {

	char_t  in_name[MAX_NAME_LENGTH];
	char_t  out_name[MAX_NAME_LENGTH];
	uint16_t i;
	uint32_t height, width;
	uint8_t **the_image, **out_image;
	uint8_t threshold;
	errFlag = eReturnOK;

   
      /******************************************
      *
      *   Ensure the command line is correct.
      *
      ******************************************/

	if(argc != 4) {

		printf("\nusage: halftone input-image output-image threshold");
		errFlag = eNotSuffArg;
	}
	
	if(errFlag == eReturnOK) {

		strcpy(in_name,  argv[1]);
		strcpy(out_name, argv[2]);
		threshold = atoi(argv[3]);
   
      /******************************************
      *
      *   Ensure the input image exists.
      *   Create the output image file.
      *   Allocate an image array, read the input 
      *   image, half_tone it, and write
      *   the result.
      *
      ******************************************/

		if(does_not_exist(in_name)) { 

			printf("\nERROR input file %s does not exist",in_name);
			printf("\n      ");
			printf("usage: histeq input-image output-image");
			errFlag = eNoName;
		}  /* ends if does_not_exist */

		if(errFlag == eReturnOK) {

			create_image_file(in_name, out_name);
			get_image_size(in_name, &height, &width);
			the_image = allocate_image_array(height, width);
			out_image = allocate_image_array(height, width);
			read_image_array(in_name, the_image);
			half_tone(the_image, out_image,threshold, 200, 0, height, width);
			write_image_array(out_name, out_image);
			free_image_array(the_image, height);
			free_image_array(out_image, height);
		}
	}
	return errFlag;
		}  /* ends main */
