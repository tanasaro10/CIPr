
   /************************************************
   *
   *       file create.c
   *
   *       Functions: This file contains
   *           main
   *
   *       Purpose:
   *          This program creates an 8 bit tiff file
   *          of size l*ROWS by w*COLS.
   *
   *       External Calls:
   *          imageio.c
   *             create_allocate_tif_file
   *             create_allocate_bmp_file
   *
   *       Modifications:
   *          7 Arpil 1992 - created
   *         15 August 1998 - modified to work with
   *              an entire image array at once.
   *         18 September 1998 - modified to work with 
   *              all I O routines in imageio.c.
   *         27 July 2015 - refactored
   *         28 July 2015 - refactored
   *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
   *
   *************************************************/

#include "cips.h"
#include "imageio.h"
#include "mtypes.h"
#include "create.h"

int main(int32_t argc, char_t *argv[]) {
   char_t             *check_ext;
   int32_t            rows_number, columns_number;
   int16_t            ok = 0; 
   tiff_header_struct image_header;
   bmpfileheader      bmp_file_header;
   bitmapheader       bmheader;
   errors             error_flag = NO_ERROR;

   if ((argc < PARAM_NUMBER) || (argc > PARAM_NUMBER)) {
      printf("\nusage: create file-name length width\n");
      error_flag = WRONG_NUMBER_OF_PARAMETERS;
   }
   else {
      rows_number = atoi(argv[2]);
      columns_number = atoi(argv[3]);

      check_ext = strstr(argv[1], ".tif");
      if (check_ext != NULL) {  /* create a tif */
         ok = 1;
         image_header.lsb            = LSB;
         image_header.bits_per_pixel = BITS_PER_PIXEL;
         image_header.image_length   = rows_number;
         image_header.image_width    = columns_number;
         image_header.strip_offset   = STRIP_OFFSET;
         create_allocate_tiff_file(argv[1], &image_header);
      }  /* ends tif */

      check_ext = strstr(argv[1], ".bmp");
      if (check_ext != NULL) {  /* create a bmp */
         ok = 1;
         bmheader.height = rows_number;
         bmheader.width  = columns_number;
         create_allocate_bmp_file(argv[1], &bmp_file_header, &bmheader);
      }  /* ends tif */

      if (ok == 0) {
         printf("\nERROR input file neither tiff nor bmp\n");
         error_flag = WRONG_TYPE_OF_INPUT_FILE;
      }
   }
   return error_flag;
}
