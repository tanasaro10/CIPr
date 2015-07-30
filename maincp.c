
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


#include "maincp.h"



uint16_t main(uint16_t  argc, char_t *argv[])
{

   char_t     name1[80], name2[80];
   uint16_t      i, is_ok, il1, ie1, ll1, le1,
            il2, ie2, ll2, le2;
   uint32_t     length1, length2, width1, width2;
   sint16_t    **the_image, **out_image;
   errFlag = eReturnOK;

       /******************************************
       *
       *  Interpret the command line parameters.
       *
       *******************************************/

   if(argc != 9){
    (void)printf(
     "\n"
     "\n usage: maincp in-file out_file "
     "in-il in-ie in-ll in-le out-il out-ie"
     "\n"
     "\n The image portion is pasted from the "
     "\n in-file into the out-file"
     "\n");
    errFlag = eNotSuffArg;
   }

  if(errFlag == eReturnOK){	

   strcpy(name1, argv[1]);
   strcpy(name2, argv[2]);

   if(does_not_exist(name1)){
    (void)printf("\nERROR input file %s does not exist",
             name1);
    errFlag = eNotExistName1;
   }

  if(errFlag == eReturnOK){

   if(does_not_exist(name2)){
    (void)printf("\nERROR input file %s does not exist",
             name2);
    errFlag = eNotExistName2;
   }
  if(errFlag == eReturnOK){


   il1 = atoi(argv[3]);
   ie1 = atoi(argv[4]);
   ll1 = atoi(argv[5]);
   le1 = atoi(argv[6]);
   il2 = atoi(argv[7]);
   ie2 = atoi(argv[8]);

      /******************************************
      *
      *   Read the input image sizes, allocate
      *   the image array and read the image
      *   for both images.
      *
      ******************************************/

   get_image_size(name1, &length1, &width1);
   get_image_size(name2, &length2, &width2);

   the_image = allocate_image_array(length1, width1);
   out_image = allocate_image_array(length2, width2);

   read_image_array(name1, the_image);
   read_image_array(name2, out_image);


       /*************************
       *
       *   Paste
       *
       **************************/

   check_cut_and_paste_limits(
      il1, ie1, 
      ll1, le1, 
      il2, ie2, 
      length1, width1,
      length2, width2,
      &is_ok);

(void)printf("\nMAIN> is_ok=%d", is_ok);

   if(is_ok){
      paste_image_piece(the_image, out_image, 
                        il1, ie1, ll1, le1,
                        il2, ie2);
   }

   write_image_array(name2, out_image);
   free_image_array(out_image, length2);
   free_image_array(the_image, length1);
}//eNotExistName2
}//eNotExistName1
}//eNotSuffArg
}  /* ends main */
