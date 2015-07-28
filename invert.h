
   /***********************************************
   *
   *   file invert.h
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

#include "cips.h"
#include "mtypes.h"

enum eTag{

	eReturnOK=0,
	eImageNULL=1,
	eNotStuffArg=2,
	eOKisNotValab=3
	
}error;
enum eTag errFlag;

