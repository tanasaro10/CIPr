
       /*********************************************
       *
       *   file boolean.c
       *
       *   Functions: This file contains
       *      main
       *
       *   Purpose:
       *      This file contains the main calling
       *      routine that calls the Boolean 
       *      operations.
       *
       *   External Calls:
       *      imageio.c - create_image_file
       *                  read_image_array
       *                  write_image_array
       *                  get_image_size
       *                  allocate_image_array
       *                  free_image_array
       *      boole.c - and_image
       *                or_image
       *                xor_image
       *                nand_image
       *                nor_image
       *                not_image
       *
       *   Modifications:
       *      3 March 1993 - created
       *      22 August 1998 - modified to work on 
       *           entire images at once.
       *      19 September 1998 - modified to work with 
       *           all I O routines in imageio.c.
       *      27 July 2015 - refactored
       *      28 July 2015 - refactored
       *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
       *
       *********************************************/

#include "cips.h"
#include "mtypes.h"
#include "boole.h"
#include "imageio.h"
#include "boolean.h"

int main(int32_t argc, char_t *argv[]) {

  char_t    name1[NAME_LENGTH], name2[NAME_LENGTH], name3[NAME_LENGTH], 
            type[NAME_LENGTH];
  sint32_t  length, width;
  sint16_t  value;
  sint16_t  **the_image, **out_image;
  errors    error_flag = NO_ERROR;

       /****************************************
       *
       *   Interpret the command line parameters.
       *
       *****************************************/

  if (argc < PARAM_NUMBER) {
    printf(
    "\n\nNot enough parameters:"
    "\n"
    "\n usage: boolean in-file1 in-file2 out-file "
    "type [value]"
    "\n           or "
    "\n        boolean in-file1 out-file not value"
    "\n"
    "\n recall type: and or xor nand nor not"
    "\n              You must specify a value for "
    "nand & nor"
    "\n");
    error_flag = WRONG_NUMBER_OF_PARAMETERS;
  }
  else {
     /****************************************
         *
         *  Process the NOT case (1 input file,
         *  1 output file).
         *
         *  Else process the other cases.
         *
         *****************************************/

         /*  NOT CASE */
    if(strcmp("not", argv[3]) == 0) {
      strcpy(name1, argv[1]); 
      strcpy(name2, argv[2]);
      strcpy(type,  argv[3]);
      value = atoi(argv[4]);

      if(does_not_exist(name1)) {
        printf("\nERROR input file %s does not exist\n", name1);
        error_flag = IN_FILE_DOES_NOT_EXIST;
      }
      else {
        if (get_image_size(name1, &length, &width) != 1) {
          error_flag = GET_IMAGE_SIZE_ERROR;
        }

        the_image = allocate_image_array(length, width);
        out_image = allocate_image_array(length, width);
        if ((the_image == NULL) || (out_image == NULL)) {
          error_flag = ALLOCATE_IMAGE_ARRAY_ERROR;
        }
        else {
          create_image_file(name1, name2);
          read_image_array(name1, the_image);
          not_image(the_image, out_image, length, width, value);
          write_image_array(name2, out_image);
        }  
      }
    }  /* ends if not  case*/

      /* NOW ALL OTHER CASES */
    else {
      strcpy(name1, argv[1]);
      strcpy(name2, argv[2]);
      strcpy(name3, argv[3]);
      strcpy(type,  argv[4]);
      value = atoi(argv[5]);

      if (does_not_exist(name1)) {
        printf("\nERROR input file %s does not exist\n", name1);
        error_flag = IN_FILE_DOES_NOT_EXIST;
      }
      if (does_not_exist(name2)) {
        printf("\nERROR input file %s does not exist\n", name2);
        error_flag = IN_FILE_DOES_NOT_EXIST;
      }
      if ((error_flag == NO_ERROR) && (!are_not_same_size(name1, name2))) {
        if (get_image_size(name1, &length, &width) != 1) {
          error_flag = GET_IMAGE_SIZE_ERROR;
        }
        
        the_image = allocate_image_array(length, width);
        out_image = allocate_image_array(length, width);
        if ((the_image == NULL) || (out_image == NULL)) {
          error_flag = ALLOCATE_IMAGE_ARRAY_ERROR;
        }
        create_image_file(name1, name3);
        read_image_array(name1, the_image);
        read_image_array(name2, out_image);

        /* AND */
        if (strcmp("and", type) == 0) {
          and_image(the_image, out_image, length, width);
        }  /* ends AND operation */

        /* OR */
        if (strcmp("or", type) == 0) {
          or_image(the_image, out_image, length, width);
        }  /* ends OR operation */

        /* XOR */
        if (strcmp("xor", type) == 0) {
          xor_image(the_image, out_image, length, width);
        }  /* ends XOR operation */

        /* NAND */
        if (strcmp("nand", type) == 0) {
          nand_image(the_image, out_image, length, width, value);
        }  /* ends NAND operation */

        /* NOR */
        if (strcmp("nor", type) == 0) {
          nor_image(the_image, out_image, length, width, value);
        }  /* ends NOR operation */

        write_image_array(name3, out_image);
      }
      else {
        printf("\n Images %s and %s are not the same size\n", name1, name2);
        error_flag = IMAGES_ARE_NOT_THE_SAME_SIZE;
      }  /* ends */
    }
  }

  free_image_array(out_image, length);
  free_image_array(the_image, length);

  return error_flag;
}  /* ends main  */
