
   /***********************************************
   *
   *   file invert.c
   *
   *   Functions: This file contains
   *      main
   *
   *   Purpose:
   *      This program takes an image file and
   *      inverts it. It works with 8 bit images
   *      only.
   *
   *   External Calls:
   *          imageio.c
   *             create_allocate_tif_file
   *             create_allocate_bmp_file
   *             get_image_size
   *             allocate_image_array
   *             free_image_array
   *             read_image_array
   *             write_image_array
   *
   *   Modifications:
   *      6 March 1993 - created
   *      22 August 1998 - modified to work on entire
   *           images at once.
   *      19 September 1998 - modified to work with 
   *           all I O routines in imageio.c.
   *	   Modified Date: 27 Iuly 2015 
   *	   Author: Mihu Andrei Cristian
   *	   Scoala de vara Thales
   *
   ***********************************************/


#include "invert.h"
#include "imageio.h"

uint16_t main(sint16_t argc, char_t *argv[])
{
	char_t name1[80], name2[80];
	char_t *cc;
	sint32_t a, b, ok = 0; 
	uint32_t length, width;
	sint16_t **the_image;
	tiff_header_struct image_header;
	bmpfileheader bmp_file_header;
	bitmapheader  bmheader;
	errFlag = eReturnOK;

	if(the_image == NULL) {
	errFlag = eImageNULL;
	}

	if(argc != 3){
		printf("\nusage: invert in-file out-file\n");
		errFlag = eNotStuffArg;
	}

	strcpy(name1, argv[1]);
	strcpy(name2, argv[2]);

	get_image_size(name1, &length, &width);

	the_image = allocate_image_array(length, width);

	cc = strstr(argv[1], ".tif");
	if(cc != NULL){  /* create a tif */
		ok = 1;
		image_header.lsb            = 1;
		image_header.bits_per_pixel = 8;
		image_header.image_length   = length;
		image_header.image_width    = width;
		image_header.strip_offset   = 1000;
		create_allocate_tiff_file(argv[2], 
		                          &image_header);
	}  /* ends tif */

   cc = strstr(argv[1], ".bmp");
	if(cc != NULL){  /* create a bmp */
		ok = 1;
		bmheader.height = length;
		bmheader.width  = width;
		create_allocate_bmp_file(argv[2], 
		                         &bmp_file_header, 
		                         &bmheader);
	}  /* ends tif */

if(errFlag == eReturnOK) {

	if(ok == 0){
		printf("\nERROR input file neither tiff nor bmp");
		errFlag = eOKisNotValab;
	}

	read_image_array(name1, the_image);

	for(a=0; a<length; a++) {
		for(b=0; b<width; b++) {
		   the_image[a][b] = GRAY_LEVELS-the_image[a][b];
		}
	}
	write_image_array(name2, the_image);

	free_image_array(the_image, length);
}
	return errFlag;
}  /* ends main */

