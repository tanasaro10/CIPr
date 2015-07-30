
    /***********************************************
    *
    *    file maincp.h
    *
    *    Functions: This file contains
    *       main
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
    *            all I O routines in imageio.c.
    *	   Modified Date: 30 Iuly 2015 
    *		 Author: Mihu Andrei Cristian
    *		 Scoala de vara Thales
    *
    *************************************************/

#include "cips.h"
#include "mtypes.h"
#include "imageio.h"
#include "cutp.h" 

enum eTag {
	eReturnOK=0,
	eNotSuffArg=1,
	eNotExistName1=2,
	eNotExistName2=3

};

enum eTag errFlag;
