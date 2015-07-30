#include "maincp.h"

sint32_t main(sint32_t argc, char_t **argv)
{
  sint16_t **the_image = NULL, 
           **out_image = NULL;

  char_t name1[80] = {0}, 
         name2[80] = {0};

  sint16_t i    = 0, is_ok  = 0, il1  = 0, 
           ie1  = 0, ll1    = 0, le1  = 0,
           il2  = 0, ie2    = 0, ll2  = 0, le2 = 0;

  sint32_t length1  = 0, 
           length2  = 0, 
           width1   = 0, 
           width2   = 0,
           error    = ERR_NONE;

  /* Interpret the command line parameters. */
  if(argc != REQUIRED_PARAMETERS) {
    (void)printf(
    "\n"
    "\n usage: maincp in-file out_file "
    "in-il in-ie in-ll in-le out-il out-ie"
    "\n"
    "\n The image portion is pasted from the "
    "\n in-file into the out-file"
    "\n");

    error = ERR_INVALID_NO_OF_ARGS;
  }

  strcpy(name1, argv[1]);
  strcpy(name2, argv[2]);

  if(does_not_exist(name1) != 0) {
    (void)printf("\nERROR input file %s does not exist", name1);
    error = ERR_NO_INPUT_FILE;
  }

  if(does_not_exist(name2) != 0) {
    (void)printf("\nERROR input file %s does not exist", name2);
    error = ERR_NO_INPUT_FILE;
  }

  if(error == ERR_NONE) {
      il1 = (sint16_t) atoi(argv[3]);
      ie1 = (sint16_t) atoi(argv[4]);
      ll1 = (sint16_t) atoi(argv[5]);
      le1 = (sint16_t) atoi(argv[6]);
      il2 = (sint16_t) atoi(argv[7]);
      ie2 = (sint16_t) atoi(argv[8]);

    /* Read the input image sizes, allocate the image array and read 
       the image for both images. */
    get_image_size(name1, &length1, &width1);
    get_image_size(name2, &length2, &width2);

    the_image = allocate_image_array(length1, width1);
    out_image = allocate_image_array(length2, width2);

    read_image_array(name1, the_image);
    read_image_array(name2, out_image);

    /* Paste */
    check_cut_and_paste_limits(il1, ie1, ll1, le1, il2, ie2, 
                  length1, width1, length2, width2, &is_ok);

    (void)printf("\nMAIN> is_ok=%d", is_ok);

    if(is_ok) {
        paste_image_piece(the_image, out_image, il1, ie1, ll1, le1, il2, ie2);
    }

    write_image_array(name2, out_image);
    free_image_array(out_image, length2);
    free_image_array(the_image, length1);
  }

  return error;
}
