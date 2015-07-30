#include "tif2bmp.h"

sint32_t main(sint32_t argc, char_t **argv)
{
  sint32_t l = 0, w = 0, error = ERR_NONE;
  sint16_t **the_image = NULL;
  char_t *cc = NULL;
   
  bmpfileheader      bmp_file_header;
  bitmapheader       bmheader;
   
  if(argc < 3 || argc > 3){
    printf("\nusage: tif2bmp tif-file-name bmp-file-name\n");
    error = ERR_INVALID_NO_OF_ARGS;
  }

  if(does_not_exist(argv[1])){
    printf("\nERROR input file %s does not exist", argv[1]);
    error = ERR_NO_INPUT_FILE;
  }

  cc = strstr(argv[1], ".tif");
  if(cc == NULL){  
    printf("\nERROR %s must be a tiff file", argv[1]);
    error = ERR_INPUT_NOT_TIF;
  }

  cc = strstr(argv[2], ".bmp");
  if(cc == NULL){  /* create a bmp */
    printf("\nERROR %s must be a bmp file name", argv[2]);
    error = ERR_OUTPUT_NOT_BMP;
  }

  if(error == ERR_NONE) {
    get_image_size(argv[1], &l, &w);
    the_image = allocate_image_array(l, w);
  }

  if(the_image == NULL) {
    error = ERR_NO_IMAGE_LOADED;
  }

  if(error == ERR_NONE) { 
    bmheader.height = l;
    bmheader.width  = w;
    create_allocate_bmp_file(argv[2], &bmp_file_header, &bmheader);
    read_image_array(argv[1], the_image);
    write_image_array(argv[2], the_image);
    free_image_array(the_image, l);
  }

  return error;
}
