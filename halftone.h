
    /***********************************************
   *
   *   file halftone.h
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
#include "mtypes.h"
#include "cips.h"
#include "imageio.h"


enum eTag{
	eReturnOK=0,
	eNotSuffArg=1,
	eNoName=2
}error;
enum eTag errFlag;

extern uint16_t main(uint16_t argc, char_t *argv[]);
