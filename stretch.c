#include "stretch.h"

static sint16_t **the_image = NULL;
static sint16_t **out_image = NULL;

sint32_t main(sint16_t argc, char_t **argv)
{
  char_t in_name[80] = {0}, out_name[80] = {0};
  float    x_stretch, y_stretch;
  sint16_t bilinear    = 0; 

  sint32_t tmp_length  = 0, 
           tmp_width   = 0,
           length      = 0, 
           width       = 0,
           error       = ERR_NONE;
   
  bmpfileheader      bmp_file_header;
  bitmapheader       bmheader;
  bitmapheader       bmheader2;
  tiff_header_struct tiff_file_header;
  tiff_header_struct tiff_file_header2;

  /* Interpret the command line parameters. */
  if(argc < REQUIRED_PARAMETERS || argc > REQUIRED_PARAMETERS){
    (void)printf("\nn usage: stretch in-file out-file x-stretch "
           "y-stretch bilinear (1 or 0)\n");

    error = ERR_INVALID_NO_OF_ARGS;
  }

  if(error == ERR_NONE) {
    strcpy(in_name,  argv[1]);
    strcpy(out_name, argv[2]);
    x_stretch = (float) atof(argv[3]);
    y_stretch = (float) atof(argv[4]);
    bilinear  = (float) atoi(argv[5]);

    if(does_not_exist(in_name) != 0){
      (void)printf("\nERROR input file %s does not exist", in_name);
      error = ERR_NO_INPUT_FILE;
    } 
  }

  if(error == ERR_NONE) {
    /* Create an output file different in size */
    get_image_size(in_name, &length, &width);
    tmp_length = ((float)(length) * y_stretch);
    tmp_width  = ((float)(width) * x_stretch);
    create_resized_image_file(in_name, out_name, tmp_length, tmp_width);

    the_image = allocate_image_array(length, width);
    out_image = allocate_image_array(tmp_length, tmp_width);

    read_image_array(in_name, the_image);
    stretch(the_image, out_image,
            x_stretch, y_stretch,
            bilinear,
            tmp_length,
            tmp_width,
            length,
            width);

    write_image_array(out_name, out_image);
    free_image_array(out_image, tmp_length);
    free_image_array(the_image, length);
  }

  return error;
}

void stretch(sint16_t **the_image, 
             sint16_t **out_image,
             float x_stretch, 
             float y_stretch,
             sint16_t bilinear,
             sint32_t out_rows, 
             sint32_t out_cols,
             sint32_t in_rows,
             sint32_t in_cols)
{
  double tmpx = 0.0d, tmpy = 0.0d;
  float  fi = 0.0f, fj = 0.0f;
  sint16_t i = 0, j = 0, new_i = 0, new_j = 0;

  /* Loop over image array */
  (void)printf("\n");

  for(i = 0; i < out_rows; i++) {
    if((i % 10) == 0) {
      (void)printf("%d ", i);
    }
      
    for(j = 0; j < out_cols; j++) {
      fi = i;
      fj = j;

      tmpx = fj/x_stretch;
      tmpy = fi/y_stretch;

      new_i = tmpy;
      new_j = tmpx;

      if(bilinear == 0) {
        if(new_j < 0 || new_j >= in_cols || new_i < 0 || new_i >= in_rows) {
            out_image[i][j] = FILL;
        }
        else {
          out_image[i][j] = the_image[new_i][new_j];
        }
      }
      else{
        out_image[i][j] = bilinear_interpolate(the_image, tmpx, 
                              tmpy, in_rows, in_cols);
      }
    }
  }
}

