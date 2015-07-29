
   /***********************************************
   *
   *   file dumpi.c
   *
   *   Functions: This file contains
   *      main
   *
   *   Purpose:
   *      This file contains a program that 
   *      dumps the number values of an image
   *      to an ascii text file.
   *
   *   External Calls:
   *      imageio.c - get_image_size
   *                  read_image_array
   *                  allocate_image_array
   *                  free_image_array
   *
   *   Modifications:
   *      1 October 1998 - created to work with 
   *           all I O routines in imageio.c.
   *      27 July 2015 - refactored
   *      28 July 2015 - refactored
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#include "cips.h"
#include "imageio.h"
#include "mtypes.h"
#include "dumpi.h"

int main(int32_t argc, char_t *argv[]) {
   char_t    in_name[MAX_NAME_LENGTH];
   char_t    out_name[MAX_NAME_LENGTH];
   char_t    *line, buffer[10];
   sint16_t   i, j;
   sint32_t   height, width;
   sint16_t   **the_image;
   errors    error_flag = NO_ERROR; 
   FILE      *out_file;

   
      /******************************************
      *
      *   Ensure the command line is correct.
      *
      ******************************************/

   if (argc != PARAM_NUMBER){
      printf("\nusage: dumpi input-image output-file");
      error_flag = WRONG_NUMBER_OF_PARAMETERS;
   }
   else {
      strcpy(in_name,  argv[1]);
      strcpy(out_name, argv[2]);
      
         /******************************************
         *
         *   Ensure the input image exists.
         *   Create the output text file.
         *   Allocate an image array.
         *   Read the image and dump the nubmers
         *   to a text file.
         *
         ******************************************/

      if (does_not_exist(in_name)) {
         printf("\nERROR input file %s does not exist", in_name);
         error_flag = IN_FILE_DOES_NOT_EXIST;
      }  /* ends if does_not_exist */

      if ((out_file = fopen(out_name, "wt")) == NULL) {
         printf("\nERROR Could not open file %s", out_name);
         error_flag = COULD_NOT_OPEN_OUT_FILE;
      }

      if (error_flag == NO_ERROR) {
         if (get_image_size(in_name, &height, &width) != 1) {
            error_flag = GET_IMAGE_SIZE_ERROR;
         }
         else {
            the_image = allocate_image_array(height, width);
            read_image_array(in_name, the_image);
            line = (char_t *) malloc(((width * SIZE_CONST1) + SIZE_CONST2) * sizeof(char_t *));

            if ((line == NULL) || (the_image == NULL)) {
               error_flag = ALLOCATE_IMAGE_ARRAY_ERROR;
            }
            else {
               sprintf(line, "      ");
               for (i = 0; i < width; i++) {
                  sprintf(buffer, "%4d", i);
                  strcat(line, buffer);
               }
               strcat(line, "\n");
               fputs(line, out_file);

               for (i = 0; i < height; i++) {
                  sprintf(line, "%5d>", i);
                  for (j = 0; j < width; j++) {
                     sprintf(buffer, "-%3d", the_image[i][j]); 
                     strcat(line, buffer);
                  }
                  strcat(line, "\n");
                  fputs(line, out_file);
               }
            }
         }
      }

      free_image_array(the_image, height);
      fclose(out_file);
   }

   return error_flag;
}  /* ends main */
