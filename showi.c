#include "showi.h"
#include <ctype.h>

sint32_t main(sint32_t argc, char_t **argv)
{
   char_t   in_name[MAX_NAME_LENGTH] = {0},
            response[MAX_NAME_LENGTH] = {0};

   sint16_t ie = 0, il = 0, not_done = 0, temp_ie = 0, temp_il = 0;
   sint32_t  height = 0, width = 0, error = ERR_NONE;
   sint16_t **the_image = NULL;
   
   // Ensure the command line is correct.
   if(argc != 4) {
    (void)printf("\nusage: showi input-image il ie\n");
    error = ERR_INVALID_NO_OF_ARGS;
   } else {
      strcpy(in_name,  argv[1]);
      il = (sint16_t)atoi(argv[2]);
      ie = (sint16_t)atoi(argv[3]);
      
      // Ensure the input image exists.
      // Allocate an image array.
      // Read the image and show it on the screen.
      if(does_not_exist(in_name) != 0) {
         printf("\nERROR input file %s does not exist", in_name);
         error = ERR_NO_INPUT_FILE;
      }
   }

   if(error == ERR_NONE) {
      get_image_size(in_name, &height, &width);
      the_image = allocate_image_array(height, width);
      read_image_array(in_name, the_image);

      temp_il  = il;
      temp_ie  = ie;
      not_done = 1;

      while(not_done) {
         if(is_in_image(temp_il, temp_ie, height, width)) {
            il = temp_il;
            ie = temp_ie;
            show_screen(the_image, il, ie);
         }

         printf("\n\n x=quit j=down k=up h=left l=right"
                "\nEnter choice and press Enter:  ");
         fgets(response, MAX_NAME_LENGTH, stdin);

         sint32_t responseLower = tolower(response[0]);

         if(responseLower == 'x') {
            not_done = 0;
         } else if(responseLower == 'j') {
            temp_il = temp_il + ((3*SHEIGHT)/4);
         } else if(responseLower == 'k') {
            temp_il = temp_il - ((3*SHEIGHT)/4);
         } else if(responseLower == 'h') {
            temp_ie = temp_ie - ((3*SWIDTH)/4);
         } else if(responseLower == 'l') {
            temp_ie = temp_ie + ((3*SWIDTH)/4);
         } else {
            // Does nothing
         }
      }

      free_image_array(the_image, height);
   }

   return error;
}

sint16_t is_in_image(sint16_t il, sint16_t ie, sint32_t height, sint32_t width)
{
   sint16_t result = 1;

   if(il < 0) {
      printf("\nil=%d tool small", il);
      result = 0;
   }

   if(ie < 0) {
      printf("\nie=%d tool small", ie);
      result = 0;
   }

   if((sint32_t)(il + SHEIGHT) > height) {
      printf("\nll=%d tool big", il+SHEIGHT);
      result = 0;
   }

   if((sint32_t)(ie + SWIDTH) > width) {
      printf("\nle=%d tool big", ie+SWIDTH);
      result = 0;
   }

   return result;
}

void show_screen(sint16_t **the_image, sint16_t il, sint16_t ie)
{
   sint32_t i = 0, j = 0;

   printf("\n     ");
   for(i = ie - 1; i < ie - 1 + SWIDTH; i++) {
      printf("-%3d", i);
   }

   for(i = il - 1; i < il - 1 + SHEIGHT; i++) {
      printf("\n%4d>", i);
      
      for(j = ie - 1; j < ie - 1 + SWIDTH; j++) {
         printf("-%3d", the_image[i][j]);
      }
   }
}
