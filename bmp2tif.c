

   /************************************************
   *
   *       file bmp2tif.c
   *
   *       Functions: This file contains
   *           main
   *
   *       Purpose:
   *          This program creates a tiff file
   *          that is just like the input bmp file.
   *
   *       External Calls:
   *          imageio.c
   *             does_not_exist
   *             get_image_size
   *             read_image_array
   *             write_image_array
   *             free_image_array
   *             create_allocate_tif_file
   *
   *       Modifications:
   *         27 September 1998 - created
   *         27 July 2015 - refactored
   *         28 July 2015 - refactored
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#include "cips.h"
#include "imageio.h"
#include "mtypes.h"
#include "bmp2tif.h"

int main(int32_t argc, char_t *argv[]) {
  char_t             *check_extension;
  sint32_t           rows_number, columns_number;
  sint16_t           **the_image;
  tiff_header_struct image_header;
  bmpfileheader      bmp_file_header;
  bitmapheader       bmheader;
  errors             error_flag = NO_ERROR;

  if(argc < PARAM_NUMBERS || argc > PARAM_NUMBERS){
    printf("\nusage: bmp2tif bmp-file-name tif-file-name\n");
    error_flag = WRONG_NUMBER_OF_PARAMETERS;
  }
  else {
    if(does_not_exist(argv[1])){
      printf("\nERROR input file %s does not exist\n", argv[1]);
      error_flag = IN_FILE_DOES_NOT_EXIST;
    }

    if (error_flag == NO_ERROR) {
      check_extension = strstr(argv[1], ".bmp");
      if(check_extension == NULL){  
        printf("\nERROR %s must be a bmp file\n", argv[1]);
        error_flag = ARG1_IS_NOT_BMP_FILE;
      }  

      check_extension = strstr(argv[2], ".tif");
      if(check_extension == NULL){  /* create a bmp */
        printf("\nERROR %s must be a tiff file name\n", argv[2]);
        error_flag = ARG2_IS_NOT_TIF_FILE;
      }
    }

    if (error_flag == NO_ERROR) {
      if (get_image_size(argv[1], &rows_number, &columns_number) != 1) {
        error_flag = GET_IMAGE_SIZE_ERROR;
      }

      the_image = allocate_image_array(rows_number, columns_number);
      if (the_image == NULL) {
        error_flag = ALLOCATE_IMAGE_ARRAY_ERROR;
      }
      else {
        image_header.lsb            = LSB;
        image_header.bits_per_pixel = BITS_PER_PIXEL;
        image_header.image_length   = rows_number;
        image_header.image_width    = columns_number;
        image_header.strip_offset   = STRIP_OFFSET;
        create_allocate_tiff_file(argv[2], &image_header);
        read_image_array(argv[1], the_image);
        write_image_array(argv[2], the_image);
        free_image_array(the_image, rows_number);
      }
    }
  }

  return error_flag;
}  /* ends main */
