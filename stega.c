#include "stega.h"

void main(sint16_t argc, char_t **argv)
{
  char_t cover_image_name[80] = {0}, message_image_name[80] = {0};
  sint16_t hide    = 0,
           lsb     = 0,
           n       = 0,
           uncover = 0;

  sint32_t clength = 0, 
           mlength = 0, 
           cwidth  = 0,
           mwidth  = 0;

  sint16_t **the_image = NULL, **out_image = NULL;

  // Ensure the command line is correct.
  if(argc < 5) {
    stega_show_usage();
    exit(0);
  }

  if(strcmp(argv[1], "-h") == 0) {
    hide    = 1;
    uncover = 0;
  } else if(strcmp(argv[1], "-u") == 0) {
    hide    = 0;
    uncover = 1;
  } else if(hide == 0 && uncover == 0) {
    printf("\nNiether hiding nor uncovering");
    printf("\nSo, quitting\n");
    exit(1);
  }

  strcpy(cover_image_name, argv[2]);
  strcpy(message_image_name, argv[3]);
  n = atoi(argv[4]);

  // Hide the cover image in the message image.
  if(hide) {
    if(does_not_exist(cover_image_name)) {
      printf("\n%s does not exist, quitting", 
      cover_image_name);
    } else  if(does_not_exist(message_image_name)) {
      printf("\n%s does not exist, quitting", 
      message_image_name);
    }

    // Ensure both images have the same height and the cover image is 
    // eight times as wide as the message image. Also determine if the 
    // bit order is lsb first or not.
    get_image_size(cover_image_name, &clength, &cwidth);
    get_image_size(message_image_name, &mlength, &mwidth);

    if(mlength != clength) {
      printf("\n\nmlength NOT EQUAL TO clength");
      printf("\nQUITING");
      exit(2);
    }

    if(cwidth != (n*mwidth)) {
      printf("\nCover image not wide enough");
      printf("\nQUITING");
      exit(3);
    }

    lsb = get_lsb(cover_image_name);

    // Allocate the two image arrays. Read the cover and message 
    // images and hide the message image.
    the_image = allocate_image_array(clength, cwidth);
    out_image = allocate_image_array(mlength, mwidth);
    read_image_array(cover_image_name, the_image);
    read_image_array(message_image_name, out_image);
    hide_image(the_image, out_image,
                mlength, mwidth,
                clength, cwidth,
                lsb, n);
    write_image_array(cover_image_name, the_image);
  }

  // Uncover the cover image from the  message image.
  if(uncover) {
    printf("\nMAIN> Uncover");

    if(does_not_exist(cover_image_name)){
       printf("\n%s does not exist, quitting", 
       cover_image_name);
    }

    // Create the message image to be the correct size.
    get_image_size(cover_image_name, &clength, &cwidth);
    mlength = clength;
    mwidth  = cwidth/n;
    create_resized_image_file(cover_image_name,
                              message_image_name, 
                              mlength, mwidth); 
    lsb = get_lsb(cover_image_name);

    // Allocate the two image arrays. Read the cover image 
    // and uncover the message image.
    the_image = allocate_image_array(clength, cwidth);
    out_image = allocate_image_array(mlength, mwidth);
    read_image_array(cover_image_name, the_image);
    uncover_image(the_image, out_image,
                  mlength, mwidth,
                  clength, cwidth,
                  lsb, n);
    write_image_array(message_image_name, out_image);
  }

  free_image_array(the_image, clength);
  free_image_array(out_image, mlength);
}

sint16_t hide_image(sint16_t **cover_image,
                    sint16_t **message_image,
                    sint32_t mlength,
                    sint32_t mwidth,
                    sint32_t clength,
                    sint32_t cwidth,
                    sint16_t lsb,
                    sint16_t n)
{
  char_t response[80] = {0};

  for(sint32_t h_counter = 0; h_counter < mwidth; h_counter++) {
    hide_pixels(cover_image, message_image, h_counter, 
                h_counter * n, lsb, n, mlength);
  }
}

sint16_t hide_pixels(sint16_t **cover_image,
                      sint16_t **message_image,
                      sint16_t mie,
                      sint16_t cie,
                      sint16_t lsb,
                      sint16_t n,
                      sint32_t mlength)
{
  char_t result = 0, new_message = 0, sample = 0;
  sint16_t c_counter = 0;

  char_t mask1[EIGHT] =  {
    0x01,  /* 0000 0001 */
    0x02,  /* 0000 0010 */
    0x04,  /* 0000 0100 */
    0x08,  /* 0000 1000 */
    0x10,  /* 0001 0000 */
    0x20,  /* 0010 0000 */
    0x40,  /* 0100 0000 */
    0x80   /* 1000 0000 */
  };

  char_t mask2[EIGHT] = {
    0xFE,  /* 1111 1110 */
    0xFD,  /* 1111 1101 */
    0xFB,  /* 1111 1011 */
    0xF7,  /* 1111 0111 */
    0xEF,  /* 1110 1111 */
    0xDF,  /* 1101 1111 */
    0xBF,  /* 1011 1111 */
    0x7F   /* 0111 1111 */
  };

  printf("\nHP> mie=%d   cie=%d   lsb=%d", mie, cie, lsb);

  for(sint32_t i = 0; i < mlength; i++) {
    c_counter = 0;
    sample = message_image[i][mie];

    for(sint32_t j = n - 1; j > -1; j--) {

      // Find out if the jth bit is a 1 or 0.  If it is non-zero, set
      // the LSB of the message image's pixel.  Else, clear that LSB.
      new_message = cover_image[i][cie+c_counter];
      result      = sample & mask1[j];

      /* set lsb */
      if(result != 0x00) { 
        if(lsb) {
          new_message = new_message | mask1[0];
        } else {
          new_message = new_message | mask1[EIGHT];
        }
      /* clear lsb */
      } else { 
        if(lsb) {
          new_message = new_message & mask2[0];
        }
        else {
          new_message = new_message & mask2[EIGHT];
        }
      }

      cover_image[i][cie+c_counter] = new_message;
      c_counter++;
    }
  }
}

sint16_t uncover_image(sint16_t **cover_image,
                    sint16_t **message_image,
                    sint32_t mlength,
                    sint32_t mwidth,
                    sint32_t clength,
                    sint32_t cwidth,
                    sint16_t lsb,
                    sint16_t n)
{
  for(sint32_t h_counter = 0; h_counter < mwidth; h_counter++) {
    uncover_pixels(cover_image, 
                    message_image,
                    h_counter,
                    h_counter*n,
                    lsb,
                    n,
                    mlength);
  }
}

sint16_t uncover_pixels(sint16_t **cover_image,
                      sint16_t **message_image,
                      sint16_t mie,
                      sint16_t cie,
                      sint16_t lsb,
                      sint16_t n,
                      sint32_t mlength)
{
  char_t result = 0, new_message = 0, sample = 0;

  char_t mask1[EIGHT] = {
    0x80,  /* 1000 0000 */
    0x40,  /* 0100 0000 */
    0x20,  /* 0010 0000 */
    0x10,  /* 0001 0000 */
    0x08,  /* 0000 1000 */
    0x04,  /* 0000 0100 */
    0x02,  /* 0000 0010 */
    0x01   /* 0000 0001 */
  };

  char_t mask2[EIGHT] = {
    0x7F,  /* 0111 1111 */
    0xBF,  /* 1011 1111 */
    0xDF,  /* 1101 1111 */
    0xEF,  /* 1110 1111 */
    0xF7,  /* 1111 0111 */
    0xFB,  /* 1111 1011 */
    0xFD,  /* 1111 1101 */
    0xFE   /* 1111 1110 */
  };

  sint16_t c = 0, c_counter = 0;
  printf("\nUP> mie=%d   cie=%d   lsb=%d", mie, cie, lsb);

  // If a pixel in the cover image is odd, its lsb has been set, so 
  // the corresponding bit in the message image should be set.
  for(sint32_t i = 0; i < mlength; i++) {
    c = n - 1;
    new_message = 0x00;
    
    for(sint32_t j = 0; j < n; j++) {
       if(is_odd(cover_image[i][cie+j])){
          /* set bit c */
          if(lsb) {
            new_message = new_message | mask1[j];
          }
          else {
            new_message = new_message | mask1[c];
          }
       }

       c--;
    }

    message_image[i][mie] = new_message;
  }
}

sint16_t is_odd(int16_t number)
{
   return number % 2;
}

void stega_show_usage(void)
{
  printf("\n\nNot enough parameters:");
  printf("\n");
  printf("   "
          "\nstega -h cover-image-name message-image-name n"
          "\n       to hide the message image in the cover image"
          "\n                 or"
          "\nstega -u cover-image-name message-image-name n"
          "\n       to uncover the cover image from the message image\n\n");
}
