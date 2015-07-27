
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
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#include "cips.h"

#define PARAM_NUMBER 3
#define NO_ERROR 3

int main(int32_t argc, char_t *argv[]) {
   char_t    in_name[MAX_NAME_LENGTH];
   char_t    out_name[MAX_NAME_LENGTH];
   char_t    *line, buffer[10];
   int32_t   i, j;
   int32_t   height, width;
   int16_t   **the_image;
   int16_t   error_flag = NO_ERROR; 
   FILE  *out_file;

   
      /******************************************
      *
      *   Ensure the command line is correct.
      *
      ******************************************/

   if (argc != PARAM_NUMBER){
      printf("\nusage: dumpi input-image output-file");
      error_flag = 0;
   }

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
      error_flag = 0;
   }  /* ends if does_not_exist */

   if ((out_file = fopen(out_name, "wt")) == NULL) {
      printf("\nERROR Could not open file %s", out_name);
      error_flag = 2;
   }

   get_image_size(in_name, &height, &width);
   the_image = allocate_image_array(height, width);
   read_image_array(in_name, the_image);

   line = malloc( ((width * 4) + 7) * sizeof(char  *));

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

   free_image_array(the_image, height);
   fclose(out_file);

}  /* ends main */
