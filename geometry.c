
    /********************************************
    *
    *    file d:\cips\geometry.c
    *
    *    Functions: This file contains
    *       main
    *
    *    Purpose:
    *       This file contains the main calling
    *       routine for geometric subroutines.
    *
    *    External Calls:
    *      imageio.c - create_image_file
    *                  read_image_array
    *                  write_image_array
    *                  get_image_size
    *                  allocate_image_array
    *                  free_image_array
    *       geosubs.c - geometry
    *                   arotate
    *
    *    Modifications:
    *       26 October 1993 - created
    *       27 August 1998 - modified to work on 
    *            entire images at once.
    *       19 September 1998 - modified to work with 
    *           all I O routines in imageio.c.
    *       28 July 2015 - refactored
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    ********************************************/

#include "cips.h"
#include "geometry.h"
#include "imageio.h"
#include "mtypes.h"
#include "geosubs.h"

int main(int32_t argc, char_t *argv[]) {

  char_t           name1[FILE_NAME_LENGTH], name2[FILE_NAME_LENGTH], 
                   type[FILE_NAME_LENGTH];
  int32_t          length, width;
  int16_t          **the_image, **out_image;
  errors           error_flag = NO_ERROR;
  geometry_options image_geometry;
  rotate_options   image_rotate; 

      /*************************************
      *
      *   This program will use a different
      *   command line for each type of
      *   call.
      *
      *   Print a usage statement that
      *   gives an example of each type
      *   of call.
      *
      *************************************/

  if (argc < PARAM_NUMBER) {
    printf("\n\nNot enough parameters:");
    printf("\n");
    printf("\n   Two Operations: ");
    printf("\n      geometry  rotate");
    printf("\n\n   Examples:");
    printf("\n");
    printf("\n   geometry in out geometry angle");
    printf(" x-displace y-displace");
    printf("\n            x-stretch y-stretch");
    printf(" x-cross y-cross bilinear (1 or 0)");
    printf("\n");
    printf("\n   geometry in out rotate angle m n");
    printf(" bilinear (1 or 0)");
    printf("\n");
    error_flag = WRONG_NUMBER_OF_PARAMETERS;
  }

      /*************************************
      *
      *   Interpret the command line
      *   depending on the type of call.
      *
      *************************************/
  else {
    if (strncmp(argv[3], "geometry", 3) == 0) {
      strcpy(name1,  argv[1]);
      strcpy(name2, argv[2]);
      strcpy(type,  argv[3]);
      image_geometry.x_angle    = atof(argv[4]);
      image_geometry.x_displace = atoi(argv[5]);
      image_geometry.y_displace = atoi(argv[6]);
      image_geometry.x_stretch  = atof(argv[7]);
      image_geometry.y_stretch  = atof(argv[8]);
      image_geometry.x_cross    = atof(argv[9]);
      image_geometry.y_cross    = atof(argv[10]);
      image_geometry.bilinear   = atoi(argv[11]);
    }

    if (strncmp(argv[3], "rotate", 3) == 0) {
      strcpy(name1,  argv[1]);
      strcpy(name2, argv[2]);
      strcpy(type,  argv[3]);
      image_rotate.angle    = atof(argv[4]);
      image_rotate.m        = atoi(argv[5]);
      image_rotate.n        = atoi(argv[6]);
      image_rotate.bilinear = atoi(argv[7]);
    }

    if (does_not_exist(name1)) {
      printf("\nERROR input file %s does not exist", name1);
      error_flag = IN_FILE_DOES_NOT_EXIST;
    }

    if (error_flag == NO_ERROR) {
      if (get_image_size(name1, &length, &width) != 1) {
        error_flag = GET_IMAGE_SIZE_ERROR;
      }

      the_image = allocate_image_array(length, width);
      out_image = allocate_image_array(length, width);
      if ((the_image == NULL) || (out_image == NULL)) {
        error_flag = ALLOCATE_IMAGE_ARRAY_ERROR;
      }

      if (error_flag == NO_ERROR) {
        create_image_file(name1, name2);
        read_image_array(name1, the_image);

        /*************************************
        *
        *   Call the routines
        *
        *************************************/

        if (strncmp(type, "geometry", 3) == 0) {
          printf("Here %d %d\n", length, width);
          geometry(the_image, out_image, image_geometry, length, width);
        }  /* ends if */

        if (strncmp(type, "rotate", 3) == 0) {
          arotate(the_image, out_image, image_rotate, length, width);
        }  /* ends if */

        write_image_array(name2, out_image);
        free_image_array(out_image, length);
        free_image_array(the_image, length);
      }
    }
  }
  return 0;
}  /* ends main  */
