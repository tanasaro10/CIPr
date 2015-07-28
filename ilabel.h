
    /************************************************
    *
    *   file ilabel.h
    *
    *   Functions: This file contains
    *       main
    *
    *   Purpose:
    *      This program writes simple block letters
    *      the an image file.  You can use these
    *      as labels for other images.
    *
    *   External Calls:
    *      imageio.c - create_image_file
    *                  read_image_array
    *                  write_image_array
    *                  get_image_size
    *                  allocate_image_array
    *                  free_image_array
    *
    *   Modifications:
    *      21 May 1993 - created
    *      22 August 1998 - modified to work on entire
    *           images at once.
    *      19 September 1998 - modified to work with 
    *            all I O routines in imageio.c.
    *	   Modified Date: 27 Iuly 2015 
    *	   Author: Mihu Andrei Cristian
    *	   Scoala de vara Thales
    *
    *************************************************/


#include "cips.h"
#include "imageio.h"
#include "mtypes.h"

#define R             9u
#define C             7u
#define COUNTER_LIMIT 8u
#define IE_START      7u
#define VAL         200u

enum eTag{

	eReturnOK=0,
	eNotSuffArg=1,
	eNotExist=2,
	eImageNULL=3

}error;

enum eTag errFlag;



