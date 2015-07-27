

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
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#include "cips.h"
#include "mtypes.h"

#define LSB 1
#define PARAM_NUMBERS 3
#define BITS_PER_PIXEL 8
#define STRIP_OFFSET 1000
#define NO_ERROR 2

int main(int32_t argc, char_t *argv[]) {
  char_t   *check_extension;
  char_t   error_flag = NO_ERROR;
  int32_t  rows_number, columns_number;
  int16_t  **the_image;
  struct tiff_header_struct image_header;
  struct bmpfileheader      bmp_file_header;
  struct bitmapheader       bmheader;

  if(argc < PARAM_NUMBERS || argc > PARAM_NUMBERS){
    printf("\nusage: bmp2tif bmp-file-name tif-file-name\n");
    error_flag = -1;
  }
  else {
    if(does_not_exist(argv[1])){
      printf("\nERROR input file %s does not exist", argv[1]);
      error_flag = 0;
    }

    if (error_flag > 0) {
      check_extension = strstr(argv[1], ".bmp");
      if(check_extension == NULL){  
        printf("\nERROR %s must be a bmp file", argv[1]);
        error_flag = 0;
      }  /* ends tif */

      check_extension = strstr(argv[2], ".tif");
      if(check_extension == NULL){  /* create a bmp */
        printf("\nERROR %s must be a tiff file name", argv[2]);
        error_flag = 0;
      }
    }

    if (error_flag > 0) {
      get_image_size(argv[1], &rows_number, &columns_number);
      the_image = (int16_t  **)allocate_image_array(rows_number, columns_number);
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
  return error_flag;
}  /* ends main */
