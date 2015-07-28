#include "imageio.h"

void read_tiff_header(char_t file_name[], tiff_header_struct *image_header)
{
  FILE *image_file = NULL;
  char_t  buffer[12] = {0};

  sint16_t not_finished = 0, lsb = 0;

  sint32_t bits_per_pixel = 0, 
          offset_to_ifd = 0, 
          strip_offset = 0, 
          image_length = 0, 
          image_width = 0, 
          subfile = 0;

  uint16_t  length_of_field = 0,
            s_bits_per_pixel = 0,
            s_strip_offset = 0,
            s_image_length = 0,
            s_image_width = 0,
            entry_count = 0,
            field_type = 0,
            tag_type = 0;

  image_file = fopen(file_name, "rb");
  if(image_file == NULL) {
    printf("\n\nTIFF.C> ERROR - could not open tiff file");
  } else {
    // Determine if the file uses MSB first or LSB first
    fread((char_t*)buffer, 1, 8, image_file);

    if(buffer[0] == 0x49) {
      lsb = 1;
    } else {
      lsb = 0;
    }

    // Read the offset to the IFD
    extract_long_from_buffer(buffer, lsb, 4, &offset_to_ifd);
    not_finished = 1;

    while(not_finished) 
    {
      // Seek to the IFD and read the entry_count, 
      // i.e. the number of entries in the IFD.
      fseek(image_file, offset_to_ifd, SEEK_SET);
      fread((char_t*)buffer, 1, 2, image_file);
      extract_ushort_from_buffer(buffer, lsb, 0, &entry_count);

      // Now loop over the directory entries.
      // Look only for the tags we need.  
      // These are:
      //    - ImageLength
      //    - ImageWidth
      //    - BitsPerPixel(BitsPerSample)
      //    - StripOffset

      for(sint32_t i = 0; i < entry_count; i++) {
        fread((char_t*)buffer, 1, 12, image_file);
        extract_ushort_from_buffer(buffer, lsb, 0, &tag_type);

        switch(tag_type) {
          // Subfile Type
          case 255u: {
            extract_ushort_from_buffer(buffer, lsb, 2, &field_type);
            extract_ushort_from_buffer(buffer, lsb, 4, &length_of_field);
            extract_long_from_buffer(buffer, lsb, 8, &subfile);

            break;
          }

          // ImageWidth 
          case 256u: {
            extract_ushort_from_buffer(buffer, lsb, 2, &field_type);
            extract_ushort_from_buffer(buffer, lsb, 4, &length_of_field);
             
            if(field_type == 3u) {
              extract_ushort_from_buffer(buffer, lsb, 8, &s_image_width);
              image_width = s_image_width;
            } else {
              extract_long_from_buffer(buffer, lsb, 8, &image_width);
            }

            break;
          }

          // ImageLength
          case 257u: {
            extract_ushort_from_buffer(buffer, lsb, 2, &field_type);
            extract_ushort_from_buffer(buffer, lsb, 4, &length_of_field);
             
            if(field_type == 3u) {
              extract_ushort_from_buffer(buffer, lsb, 8, &s_image_length);
              image_length = s_image_length;
            }
            else {
              extract_long_from_buffer(buffer, lsb, 8, &image_length);
            }

            break;
          }

          // BitsPerSample
          case 258u: {
            extract_ushort_from_buffer(buffer, lsb, 2, &field_type);
            extract_ushort_from_buffer(buffer, lsb, 4, &length_of_field);
             
            if(field_type == 3) {
              extract_ushort_from_buffer(buffer, lsb, 8, &s_bits_per_pixel);
              bits_per_pixel = s_bits_per_pixel;
            }
            else {
              extract_long_from_buffer(buffer, lsb, 8, &bits_per_pixel);
            }

            break;
          }

          // StripOffset
          case 273u: {
            extract_ushort_from_buffer(buffer, lsb, 2, &field_type);
            extract_ushort_from_buffer(buffer, lsb, 4, &length_of_field);
            
            if(field_type == 3u) {
              extract_ushort_from_buffer(buffer, lsb, 8, &s_strip_offset);
              strip_offset = s_strip_offset;
            }
            else {
              extract_long_from_buffer(buffer, lsb, 8, &strip_offset);
            }
            
            break;
          }

          default: {
            break;
          }
        }
      }

      fread(buffer, 1, 4, image_file);
      extract_long_from_buffer(buffer, lsb, 0, &offset_to_ifd);
      
      if(offset_to_ifd == 0) 
        not_finished = 0;
    }

    image_header->lsb             = lsb;
    image_header->bits_per_pixel  = bits_per_pixel;
    image_header->image_length    = image_length;
    image_header->image_width     = image_width;
    image_header->strip_offset    = strip_offset;

    fclose(image_file);
  } 
}

void extract_long_from_buffer(char_t buffer[], 
                              sint16_t lsb, 
                              sint16_t start, 
                              sint32_t *number)
{
  long_char_union lcu;

  if(lsb == 1) {
    lcu.l_alpha[0] = buffer[start+0];
    lcu.l_alpha[1] = buffer[start+1];
    lcu.l_alpha[2] = buffer[start+2];
    lcu.l_alpha[3] = buffer[start+3];
  } else if(lsb == 0) {
    lcu.l_alpha[0] = buffer[start+3];
    lcu.l_alpha[1] = buffer[start+2];
    lcu.l_alpha[2] = buffer[start+1];
    lcu.l_alpha[3] = buffer[start+0];
  }

  *number = lcu.l_num;
}

void extract_ulong_from_buffer(char_t buffer[], 
                                sint16_t lsb, 
                                sint16_t start, 
                                uint32_t *number)
{
  ulong_char_union lcu;

  if(lsb == 1) {
    lcu.l_alpha[0] = buffer[start+0];
    lcu.l_alpha[1] = buffer[start+1];
    lcu.l_alpha[2] = buffer[start+2];
    lcu.l_alpha[3] = buffer[start+3];
  } else if(lsb == 0) {
    lcu.l_alpha[0] = buffer[start+3];
    lcu.l_alpha[1] = buffer[start+2];
    lcu.l_alpha[2] = buffer[start+1];
    lcu.l_alpha[3] = buffer[start+0];
  }

  *number = lcu.l_num;
}

void extract_short_from_buffer(char_t buffer[],
                                sint16_t lsb,
                                sint16_t start,
                                sint16_t *number)
{
  short_char_union lcu;

  if(lsb == 1) {
    lcu.s_alpha[0] = buffer[start+0];
    lcu.s_alpha[1] = buffer[start+1];
  } else if(lsb == 0) {
    lcu.s_alpha[0] = buffer[start+1];
    lcu.s_alpha[1] = buffer[start+0];
  }

  *number = lcu.s_num;
}

void extract_ushort_from_buffer(char_t buffer[],
                                sint16_t lsb,
                                sint16_t start,
                                uint16_t *number)
{
  ushort_char_union lcu;

  if(lsb == 1) {
    lcu.s_alpha[0] = buffer[start+0];
    lcu.s_alpha[1] = buffer[start+1];
  } else if(lsb == 0) {
    lcu.s_alpha[0] = buffer[start+1];
    lcu.s_alpha[1] = buffer[start+0];
  }

  *number = lcu.s_num;
}

sint16_t **allocate_image_array(sint32_t length, sint32_t width)
{
  sint16_t **the_array = malloc(length * sizeof(sint16_t*));

  for(sint32_t i = 0; i < length; i++) {
    the_array[i] = malloc(width * sizeof(sint16_t));

    if(the_array[i] == '\0') {
      printf("\n\tmalloc of the_image[%d] failed", i);
    }
  }

  return the_array; 
}

sint16_t free_image_array(sint16_t **the_array, sint32_t length)
{
  for(sint32_t i = 0; i < length; i++)
    free(the_array[i]);
  
  return 1;
}

void read_tiff_image(char_t image_file_name[], sint16_t **the_image)
{
  FILE *image_file = NULL;
  tiff_header_struct image_header;
  read_tiff_header(image_file_name, &image_header);

  /***********************************************
  *
  *   Procedure:
  *   Seek to the strip offset where the data begins.
  *   Seek to the first line you want.
  *   Loop over the lines you want to read:
  *      Seek to the first element of the line.
  *      Read the line.
  *      Seek to the end of the data in that line.
  *
  ************************************************/

  image_file = fopen(image_file_name, "rb");
  if(image_file == NULL) {
    printf("\nRTIFF.C> ERROR - cannot open "
           "tiff file");
  } else {
    fseek(image_file, image_header.strip_offset, SEEK_SET);

    for(sint32_t i = 0; i < image_header.image_length; i++) {
      read_line(image_file, the_image, i, &image_header, 
                0, image_header.image_width);
    }

    fclose(image_file);
  }

}

sint16_t read_line(FILE *image_file, 
                sint16_t **the_image,
                sint16_t line_number,
                tiff_header_struct *image_header,
                sint16_t ie,
                sint16_t le)
{
  char_t  *buffer = NULL, first = 0, second = 0;
  sint16_t bytes_read = 0;
  uint16_t bytes_to_read = 0;
  short_char_union scu;

  buffer = (char_t*)malloc(image_header->image_width * sizeof(char_t));
  for(sint32_t i = 0; i < image_header->image_width; i++) {
    buffer[i] = '\0';
  }

  // Use the number of bits per pixel to calculate how many bytes to read.
  bytes_to_read = (le - ie) / (8u / image_header->bits_per_pixel);
  bytes_read = fread(buffer, 1, bytes_to_read, image_file);

  for(sint32_t i = 0; i < bytes_read; i++) {
    // Use unions defined in cips.h to stuff bytes into shorts.
    if(image_header->bits_per_pixel == 8) {
     scu.s_num                  = 0;
     scu.s_alpha[0]             = buffer[i];
     the_image[line_number][i]  = scu.s_num;
    } 

    if(image_header->bits_per_pixel == 4){
     scu.s_num             = 0;
     second                = buffer[i] & 0X000F;
     scu.s_alpha[0]        = second;
     the_image[line_number][i * 2 + 1] = scu.s_num;

     scu.s_num             = 0;
     first                 = buffer[i] >> 4;
     first                 = first & 0x000F;
     scu.s_alpha[0]        = first;
     the_image[line_number][i*2] = scu.s_num;
    } 
  }

  free(buffer);
  return bytes_read;
}

sint16_t seek_to_first_line(FILE *image_file,
                        tiff_header_struct *image_header,
                        sint16_t il)
{
  sint32_t offset = (il - 1) * image_header->image_width;
  offset /= (8 / image_header->bits_per_pixel);
  
  // seek from current position
  return fseek(image_file, offset, SEEK_CUR);
}

sint16_t seek_to_end_of_line(FILE *image_file,
                          sint16_t le,
                          tiff_header_struct *image_header)
{
  sint32_t offset = (image_header->image_width - le);
  offset /= (8 / image_header->bits_per_pixel);
  
  return fseek(image_file, offset, SEEK_CUR);
}

void create_tiff_file_if_needed(char_t in_name[],
                                char_t out_name[],
                                sint16_t **out_image)
{
  tiff_header_struct image_header;

  if(does_not_exist(out_name)) {
    printf("\n\n output file does not exist %s", out_name);
    read_tiff_header(in_name, &image_header);
    create_allocate_tiff_file(out_name, &image_header);
    printf("\nBFIN> Created %s", out_name);
  }
}

void create_allocate_tiff_file(char_t file_name[], 
                                tiff_header_struct *image_header)
{
  char_t  buffer[12] = {0}, *image_buffer = NULL, long_buffer[50] = {0};
  FILE  *image_file = NULL;
  sint16_t bytes_written = 0;
  sint32_t k = 0;

  // Create the image file in binary mode for both reading and writing.
  image_file = fopen(file_name, "wb");

  if(image_file == NULL) {
    printf("\n\n could not open file %s", file_name);
  } else {
    /***************************************
    *
    *   Write out the first 8 bytes of the
    *   header.  The meaning of the bytes (HEX) is:
    *      0-1 = 49 49 - LSB first
    *      2-3 = 2A 00 - version #
    *      4-7 = 08 00 00 00 - go to offset
    *           8 for the first
    *           Image File
    *           Directory
    *
    ****************************************/

    buffer[0] = 0x49;
    buffer[1] = 0x49;
    buffer[2] = 0x2A;
    buffer[3] = 0x00;
    buffer[4] = 0x08;
    buffer[5] = 0x00;
    buffer[6] = 0x00;
    buffer[7] = 0x00;

    bytes_written = fwrite(buffer, 1, 8, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /***************************************
    *
    *   Write out the first 2 bytes of the
    *   Image File Directory.  These tell
    *   the number of entries in the IFD.
    *
    ****************************************/

    buffer[0] = 0x12;
    buffer[1] = 0x00;
    bytes_written = fwrite(buffer, 1, 2, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /***************************************
    *
    *   Write out the entries into the
    *   Image File Directory.
    *
    ****************************************/

    /* New Subfile Type */
    buffer[0]  = 0xFE;
    buffer[1]  = 0x00;
    buffer[2]  = 0x03;
    buffer[3]  = 0x00;
    buffer[4]  = 0x01;
    buffer[5]  = 0x00;
    buffer[6]  = 0x00;
    buffer[7]  = 0x00;
    buffer[8]  = 0x00;
    buffer[9]  = 0x00;
    buffer[10] = 0x00;
    buffer[11] = 0x00;
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Subfile Type */
    buffer[0]  = 0xFF;
    buffer[1]  = 0x00;
    buffer[2]  = 0x03;
    buffer[3]  = 0x00;
    buffer[4]  = 0x01;
    buffer[5]  = 0x00;
    buffer[6]  = 0x00;
    buffer[7]  = 0x00;
    buffer[8]  = 0x01;
    buffer[9]  = 0x00;
    buffer[10] = 0x00;
    buffer[11] = 0x00;
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Image Width */
    insert_short_into_buffer(buffer, 0, 256);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, image_header->image_width);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Image Length */
    insert_short_into_buffer(buffer, 0, 257);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, image_header->image_length);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Bits Per Sample */
    insert_short_into_buffer(buffer, 0, 258);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, image_header->bits_per_pixel);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Compression - None */
    insert_short_into_buffer(buffer, 0, 259);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 1);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Photometric Interpretation */
    /* set to 1 because BLACK is ZERO */
    insert_short_into_buffer(buffer, 0, 262);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 1);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Strip Offset */
    /* start after software name at 296 */
    insert_short_into_buffer(buffer, 0, 273);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 296);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Samples per Pixel */
    insert_short_into_buffer(buffer, 0, 277);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 1);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* clear buffer */
    for(sint32_t i = 0; i < 12; i++) {
      buffer[i] = 0x00;
    }

    /* Rows Per Strip 1 strip for the entire image */
    /* use 2E32 - 1, which is max */
    insert_short_into_buffer(buffer, 0, 278);
    insert_short_into_buffer(buffer, 2, 4);
    insert_short_into_buffer(buffer, 4, 1);
    insert_long_into_buffer(buffer, 8, 4294967295);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Strip Byte Counts */
    /* this = image width times length */
    insert_short_into_buffer(buffer, 0, 279);
    insert_short_into_buffer(buffer, 2, 4);
    insert_short_into_buffer(buffer, 4, 1);
    insert_long_into_buffer(buffer, 8, 
          (sint32_t)(image_header->image_length * image_header->image_width));
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Min Sample Value */
    insert_short_into_buffer(buffer, 0, 280);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 0);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Max Sample Value */
    insert_short_into_buffer(buffer, 0, 281);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    if(image_header->bits_per_pixel == 8) {
      insert_short_into_buffer(buffer, 8, 255);
    } else {
      insert_short_into_buffer(buffer, 8, 15);
    }

    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* X Resolution */
    /* Store the 8 bytes for this value starting at 230 */
    insert_short_into_buffer(buffer, 0, 282);
    insert_short_into_buffer(buffer, 2, 5);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 230);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Y Resolution */
    /* Store the 8 bytes for this value starting at 238 */
    insert_short_into_buffer(buffer, 0, 283);
    insert_short_into_buffer(buffer, 2, 5);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 238);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* clear buffer */
    for(sint32_t i = 0; i < 12; i++) {
      buffer[i] = 0x00;
    }

    /* Planer Configuration */
    /* chunky */
    insert_short_into_buffer(buffer, 0, 284);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 1);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Resolution Unit */
    /* inches */
    insert_short_into_buffer(buffer, 0, 296);
    insert_short_into_buffer(buffer, 2, 3);
    insert_short_into_buffer(buffer, 4, 1);
    insert_short_into_buffer(buffer, 8, 2);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Software */
    /* Put this a 246, 50 bytes */
    insert_short_into_buffer(buffer, 0, 305);
    insert_short_into_buffer(buffer, 2, 2);
    insert_short_into_buffer(buffer, 4, 50);
    insert_short_into_buffer(buffer, 8, 246);
    bytes_written = fwrite(buffer, 1, 12, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Offset to next IFD (0 means no more IFD's) */
    for(sint32_t i = 0; i < 12; i++) {
      buffer[i] = 0x00;
    }

    bytes_written = fwrite(buffer, 1, 4, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* clear buffer */
    for(sint32_t i = 0; i < 12; i++) {
      buffer[i] = 0x00;
    }

    /* Now store the X Resolution first long 
       is numerator second long is denominator */
    insert_long_into_buffer(buffer, 0, 300L);
    insert_long_into_buffer(buffer, 4, 1L);
    bytes_written = fwrite(buffer, 1, 8, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Now store the Y Resolution first long is numerator
       second long is denominator */
    insert_long_into_buffer(buffer, 0, 300L);
    insert_long_into_buffer(buffer, 4, 1L);
    bytes_written = fwrite(buffer, 1, 8, image_file);
    printf("\n wrote %d bytes", bytes_written);

    /* Now store the software tag */
    for(sint32_t i = 0; i < 50; i++) {
      long_buffer[i] = '\0';
    }

    strcpy(long_buffer, "Dwayne Phillips C Image Processing System 1993");
    long_buffer[46] = '\0';
    long_buffer[47] = '\0';
    long_buffer[48] = '\0';
    long_buffer[49] = '\0';
    bytes_written = fwrite(long_buffer, 1, 50, image_file);
    printf("\n wrote %d bytes", bytes_written);
    printf("\n%s", long_buffer);

    // Now write the image data.
    printf("\n length is %d", image_header->image_length);
    printf("\n width is %d", image_header->image_width);
    k = image_header->image_width;

    if(image_header->bits_per_pixel == 4) {
      k = k / 2;
    }

    image_buffer = (char_t*)malloc(k * sizeof(char_t));
    for(sint32_t i = 0; i < k; i++) {
      image_buffer[i] = 0x00;
    }

    for(sint32_t i = 0; i < image_header->image_length; i++) {
      bytes_written = fwrite(image_buffer, 1, k, image_file);
      printf("\n wrote %d bytes", bytes_written);
    }

    fclose(image_file);
    free(image_buffer);
  }
}

void write_tiff_image(char_t image_file_name[], sint16_t **array)
{
  FILE  *image_file = NULL;
  tiff_header_struct image_header;

  read_tiff_header(image_file_name, &image_header);

  /***********************************************
  *
  *   Procedure:
  *   Seek to the strip offset where the data begins.
  *   Seek to the first line you want.
  *   Loop over the lines you want to write.
  *      Seek to the first element of the line.
  *      Write the line.
  *      Seek to the end of the data in that line.
  *
  ************************************************/

  image_file = fopen(image_file_name, "rb+");
  if(image_file == NULL) {
    printf("\n\n could not open file %s", image_file_name);
  } else {
    fseek(image_file, image_header.strip_offset, SEEK_SET);
    
    for(sint32_t i = 0; i < image_header.image_length; i++) {
      write_line(image_file, array, i, &image_header, 
                  0, image_header.image_width);

    } 

    fclose(image_file);
  }
}

sint16_t write_line(FILE *image_file,
                sint16_t **array,
                sint16_t line_number,
                tiff_header_struct *image_header,
                sint16_t ie,
                sint16_t le)
{
  char_t *buffer = NULL, first = 0, second = 0;
  sint16_t bytes_written = 0;
  uint16_t bytes_to_write = 0;
  short_char_union scu;

  buffer = (char_t*)malloc(image_header->image_width * sizeof(char_t));
  for(sint32_t i = 0; i < image_header->image_width; i++) {
    buffer[i] = '\0';
  }

  bytes_to_write = (le - ie) / (8 / image_header->bits_per_pixel);
  
  for(sint32_t i = 0; i < bytes_to_write; i++) {
    /**********************************************
    *
    *   Use unions defined in cips.h to stuff shorts
    *   into bytess.
    *
    **********************************************/

    if(image_header->bits_per_pixel == 8) {
     scu.s_num = 0;
     scu.s_num = array[line_number][i];
     buffer[i] = scu.s_alpha[0];
    } else if(image_header->bits_per_pixel == 4) {
     scu.s_num = 0;
     scu.s_num = array[line_number][i*2];
     first     = scu.s_alpha[0] << 4;

     scu.s_num = 0;
     scu.s_num = array[line_number][i*2];
     second    = scu.s_alpha[0] & 0X000F;

     buffer[i] = first | second;
    }
  }

  bytes_written = fwrite(buffer, 1, bytes_to_write, image_file);

  free(buffer);
  return bytes_written;
}

void insert_short_into_buffer(char_t buffer[], sint16_t start, sint16_t number)
{
  short_char_union lsu;

  lsu.s_num = number;
  buffer[start + 0] = lsu.s_alpha[0];
  buffer[start + 1] = lsu.s_alpha[1];
}

void insert_ushort_into_buffer(char_t buffer[], sint16_t start, uint16_t number)
{
  ushort_char_union lsu;

  lsu.s_num = number;
  buffer[start + 0] = lsu.s_alpha[0];
  buffer[start + 1] = lsu.s_alpha[1];
}

void insert_long_into_buffer(char_t buffer[], sint16_t start, sint32_t number)
{
  long_char_union lsu;

  lsu.l_num = number;
  buffer[start + 0] = lsu.l_alpha[0];
  buffer[start + 1] = lsu.l_alpha[1];
  buffer[start + 2] = lsu.l_alpha[2];
  buffer[start + 3] = lsu.l_alpha[3];
}

void insert_ulong_into_buffer(char_t buffer[], sint16_t start, uint32_t number)
{
  ulong_char_union lsu;

  lsu.l_num = number;
  buffer[start + 0] = lsu.l_alpha[0];
  buffer[start + 1] = lsu.l_alpha[1];
  buffer[start + 2] = lsu.l_alpha[2];
  buffer[start + 3] = lsu.l_alpha[3];
}

void round_off_image_size(tiff_header_struct *image_header,
                          sint16_t *length, 
                          sint16_t *width)
{
  *length = (ROWS - 10 + image_header->image_length) / ROWS;
  *width  = (COLS - 10 + image_header->image_width) / COLS;
}

uint16_t does_not_exist(char_t file_name[])
{
  FILE *image_file = NULL;
  sint16_t result = 1;

  image_file = fopen(file_name, "rb");
  if(image_file != NULL){
    result = 0;
    fclose(image_file);
  }

  return result;
}

void read_bmp_file_header(char_t file_name[],
                          bmpfileheader *file_header)
{
  char_t  buffer[10] = {0};
  sint16_t ss = 0;
  uint16_t uss = 0;
  uint32_t ull = 0;
  FILE *fp = NULL;

  fp = fopen(file_name, "rb");
  if(fp == NULL) {
    printf("\n\n could not open file %s\n", file_name);
    exit(1);
  } else {
    fread(buffer, 1, 2, fp);
    extract_ushort_from_buffer(buffer, 1, 0, &uss);
    file_header->filetype = uss;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    file_header->filesize = ull;

    fread(buffer, 1, 2, fp);
    extract_short_from_buffer(buffer, 1, 0, &ss);
    file_header->reserved1 = ss;

    fread(buffer, 1, 2, fp);
    extract_short_from_buffer(buffer, 1, 0, &ss);
    file_header->reserved2 = ss;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    file_header->bitmapoffset = ull;

    fclose(fp);
  }
}

void print_bmp_file_header(bmpfileheader *file_header)
{
  printf("\nfile type %x", file_header->filetype);
  printf("\nfile size %d", file_header->filesize);
  printf("\nbit map offset %d", file_header->bitmapoffset);
}

void read_bm_header(char_t file_name[], bitmapheader *bmheader)
{
  char_t buffer[10] = {0};
  uint16_t uss = 0;
  sint32_t ll = 0;
  uint32_t ull = 0;
  FILE *fp = NULL;

  fp = fopen(file_name, "rb");
  if(fp == NULL) {
    printf("\n\n could not open file %s\n", file_name);
    exit(1);
  } else {
    // Seek past the first 14 byte header.
    fseek(fp, 14, SEEK_SET);

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->size = ull;

    fread(buffer, 1, 4, fp);
    extract_long_from_buffer(buffer, 1, 0, &ll);
    bmheader->width = ll;

    fread(buffer, 1, 4, fp);
    extract_long_from_buffer(buffer, 1, 0, &ll);
    bmheader->height = ll;

    fread(buffer, 1, 2, fp);
    extract_ushort_from_buffer(buffer, 1, 0, &uss);
    bmheader->planes = uss;

    fread(buffer, 1, 2, fp);
    extract_ushort_from_buffer(buffer, 1, 0, &uss);
    bmheader->bitsperpixel = uss;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->compression = ull;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->sizeofbitmap = ull;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->horzres = ull;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->vertres = ull;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->colorsused = ull;

    fread(buffer, 1, 4, fp);
    extract_ulong_from_buffer(buffer, 1, 0, &ull);
    bmheader->colorsimp = ull;

    fclose(fp);
  }  
}

void print_bm_header(bitmapheader *bmheader)
{
  printf("\nwidth %d", bmheader->width);
  printf("\nheight %d", bmheader->height);
  printf("\nplanes %d", bmheader->planes);
  printf("\nbitsperpixel %d", bmheader->bitsperpixel);
  printf("\ncolorsused %d", bmheader->colorsused);
  printf("\ncolorsimp %d", bmheader->colorsimp);
}

void read_color_table(char_t file_name[], ctstruct rgb[], sint16_t size)
{
  char_t buffer[10] = {0};
  FILE *fp = NULL;

  fp = fopen(file_name, "rb");

  if(fp == NULL) {
    printf("\n\n could not open file %s", file_name);
    exit(1);
  } else {
    fseek(fp, 54, SEEK_SET);
    for(sint32_t i = 0; i < size; i++) {
      fread(buffer, 1, 1, fp);
      rgb[i].blue = buffer[0];
      fread(buffer, 1, 1, fp);
      rgb[i].green = buffer[0];
      fread(buffer, 1, 1, fp);
      rgb[i].red = buffer[0];
      fread(buffer, 1, 1, fp);
    }

    fclose(fp);
  }
}

void print_color_table(ctstruct *rgb, sint16_t size)
{
  for(sint32_t i = 0; i < size; i++) {
    printf("\n %d %d %d", rgb[i].blue, rgb[i].green, rgb[i].red);
  }
}

void flip_image_array(sint16_t **the_image, sint32_t cols, sint32_t rows)
{
  sint32_t rd2 = 0;
  sint16_t **temp = NULL;

  temp = allocate_image_array(rows, cols);
  rd2  = rows / 2;

  for(sint32_t i = 0; i < rd2; i++) {
    for(sint32_t j = 0; j < cols; j++) {
      temp[rows - 1 - i][j] = the_image[i][j];
    }
  }

  for(sint32_t i = rd2; i < rows; i++) {
    for(sint32_t j = 0; j < cols; j++) {
      temp[rows - 1 - i][j] = the_image[i][j];
    }
  }

  for(sint32_t i = 0; i < rows; i++) {
    for(sint32_t j = 0; j < cols; j++) {
      the_image[i][j] = temp[i][j];
    }
  }

  free_image_array(temp, rows);
}

void read_bmp_image(char_t file_name[], sint16_t **array)
{
  FILE   *fp = NULL;
  sint16_t  negative = 0,
            pad      = 0,
            place    = 0;

  sint32_t  colors   = 0,
            height   = 0,
            width    = 0;

  bmpfileheader file_header;
  bitmapheader  bmheader;
  ctstruct rgb[GRAY_LEVELS + 1];
  uint8_t uc = 0;

  read_bmp_file_header(file_name, &file_header);
  read_bm_header(file_name, &bmheader);

  if(bmheader.bitsperpixel != 8){
    printf("\nCannot read image when bits per pixel is not 8");
    exit(1);
  }

  if(bmheader.colorsused == 0) {
    colors = GRAY_LEVELS + 1;
  }
  else {
    colors = bmheader.colorsused;
  }

  read_color_table(file_name, rgb, colors);

  fp = fopen(file_name, "rb");
  if(fp == NULL) {
    printf("\n\n could not open file %s", file_name);
  } else {
    fseek(fp, file_header.bitmapoffset, SEEK_SET);
    width = bmheader.width;

    if(bmheader.height < 0){
      height = -bmheader.height;
      negative = 1;
    }
    else {
      height = bmheader.height;
    }

    pad = calculate_pad(width);

    for(sint32_t i = 0; i < height; i++) {
      for(sint32_t j = 0; j < width; j++) {
         place = fgetc(fp);
         uc = (place & 0xff);
         place = uc;
         array[i][j] = rgb[place].blue;
      }

      if(pad != 0){
         fseek(fp, pad, SEEK_CUR);
      }
    }

    if(negative == 0) {
      flip_image_array(array, width, height);
    }
  }
}

void create_allocate_bmp_file(char_t file_name[], 
                              bmpfileheader *file_header,
                              bitmapheader *bmheader)
{
  char_t buffer[100] = {0};
  sint16_t pad = 0;
  FILE *fp = NULL;

  pad = calculate_pad(bmheader->width);

  bmheader->size         =  40;
  bmheader->planes       =   1;
  bmheader->bitsperpixel =   8;
  bmheader->compression  =   0;
  bmheader->sizeofbitmap = bmheader->height * (bmheader->width + pad);
  bmheader->horzres      = 300;
  bmheader->vertres      = 300;
  bmheader->colorsused   = 256;
  bmheader->colorsimp    = 256;

  file_header->filetype     = 0x4D42;
  file_header->reserved1    =  0;
  file_header->reserved2    =  0;
  file_header->bitmapoffset = 14 + bmheader->size + bmheader->colorsused * 4;
  file_header->filesize     = file_header->bitmapoffset + bmheader->sizeofbitmap;

  if((fp = fopen(file_name, "wb")) == NULL){
    printf("\nERROR Could not create file %s", file_name);
    exit(2);
  }

  // Write the 14-byte bmp file header.
  insert_ushort_into_buffer(buffer, 0, file_header->filetype);
  fwrite(buffer, 1, 2, fp);

  insert_ulong_into_buffer(buffer, 0, file_header->filesize);
  fwrite(buffer, 1, 4, fp);

  insert_short_into_buffer(buffer, 0, file_header->reserved1);
  fwrite(buffer, 1, 2, fp);

  insert_short_into_buffer(buffer, 0, file_header->reserved2);
  fwrite(buffer, 1, 2, fp);

  insert_ulong_into_buffer(buffer, 0, file_header->bitmapoffset);
  fwrite(buffer, 1, 4, fp);


  // Write the 40-byte bit map header.
  insert_ulong_into_buffer(buffer, 0, bmheader->size);
  fwrite(buffer, 1, 4, fp);

  insert_long_into_buffer(buffer, 0, bmheader->width);
  fwrite(buffer, 1, 4, fp);

  insert_long_into_buffer(buffer, 0, bmheader->height);
  fwrite(buffer, 1, 4, fp);

  insert_ushort_into_buffer(buffer, 0, bmheader->planes);
  fwrite(buffer, 1, 2, fp);

  insert_ushort_into_buffer(buffer, 0, bmheader->bitsperpixel);
  fwrite(buffer, 1, 2, fp);

  insert_ulong_into_buffer(buffer, 0, bmheader->compression);
  fwrite(buffer, 1, 4, fp);

  insert_ulong_into_buffer(buffer, 0, bmheader->sizeofbitmap);
  fwrite(buffer, 1, 4, fp);

  insert_ulong_into_buffer(buffer, 0, bmheader->horzres);
  fwrite(buffer, 1, 4, fp);

  insert_ulong_into_buffer(buffer, 0, bmheader->vertres);
  fwrite(buffer, 1, 4, fp);

  insert_ulong_into_buffer(buffer, 0, bmheader->colorsused);
  fwrite(buffer, 1, 4, fp);

  insert_ulong_into_buffer(buffer, 0, bmheader->colorsimp);
  fwrite(buffer, 1, 4, fp);

  // Write a blank color table.
  // It has 256 entries (number of colors) that are each 4 bytes.
  buffer[0] = 0x00;

  for(sint32_t i = 0; i < (256 * 4); i++) {
    fwrite(buffer, 1, 1, fp);
  }

  // Write a zero image.  
  buffer[0] = 0x00;

  for(sint32_t i = 0; i < bmheader->sizeofbitmap; i++) {
    fwrite(buffer, 1, 1, fp);
  }

  fclose(fp);
}

void create_bmp_file_if_needed(char_t in_name[],
                                char_t out_name[],
                                sint16_t **out_image)
{
  bmpfileheader file_header;
  bitmapheader  bmheader;

  if(does_not_exist(out_name)) {
    printf("\n\n output file does not exist %s", out_name);
    read_bm_header(in_name, &bmheader);
    create_allocate_bmp_file(out_name, &file_header, &bmheader);
    printf("\nBFIN> Created %s", out_name);
  }
}

void write_bmp_image(char_t file_name[], sint16_t **array)
{
  char_t *buffer = NULL;
  FILE *image_file = NULL;
  sint32_t height = 0, width = 0, pad = 0;

  bitmapheader  bmheader;
  bmpfileheader file_header;
  ctstruct rgb[GRAY_LEVELS + 1];
  short_char_union scu;

  read_bmp_file_header(file_name, &file_header);
  read_bm_header(file_name, &bmheader);

  height = bmheader.height;
  width  = bmheader.width;
  if(height < 0)  {
    height = -height;
  }

  buffer = (char_t*)malloc(width * sizeof(char_t));
  for(sint32_t i = 0; i < width; i++) {
    buffer[i] = '\0';
  }

  image_file = fopen(file_name, "rb+");
  if(image_file == NULL) {
    printf("\n\n could not open file %s", file_name);
    exit(2);
  } else {
    // Write the color table first.
    fseek(image_file, 54, SEEK_SET);
    
    for(sint32_t i = 0; i < GRAY_LEVELS + 1; i++) {
      rgb[i].blue  = i;
      rgb[i].green = i;
      rgb[i].red   = i;
    }

    for(sint32_t i = 0; i < bmheader.colorsused; i++) {
      buffer[0] = rgb[i].blue;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = rgb[i].green;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = rgb[i].red;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = 0x00;
      fwrite(buffer , 1, 1, image_file);
    }

    fseek(image_file, file_header.bitmapoffset, SEEK_SET);
    pad = calculate_pad(width);

    for(sint32_t i = 0; i < height; i++) {
      for(sint32_t j = 0; j < width; j++) {
        if(bmheader.bitsperpixel == 8) {
          scu.s_num = 0;
          if(bmheader.height > 0) {
            scu.s_num = array[height - 1 - i][j];
          }
          else {
            scu.s_num = array[i][j];
          }

          buffer[j] = scu.s_alpha[0];
        }
        else {
          printf("\nERROR bitsperpixel is not 8");
          exit(1);
        }
      }

      fwrite(buffer, 1, width, image_file);
      if(pad != 0) {
         for(sint32_t j = 0; j < pad; j++) {
            buffer[j] = 0x00;
         }

         fwrite(buffer, 1, pad, image_file);
      }
    }

    fclose(image_file);
  }

  free(buffer);
}

sint32_t calculate_pad(sint32_t width)
{
  return ((width % 4) == 0) ? 0 : (4 - (width % 4));
}

sint16_t get_image_size(char_t file_name[], sint32_t *rows, sint32_t *cols)
{
  sint16_t is_bmp  = 0,
           is_tiff = 0,
           result  = 0;
  
  bitmapheader bmph;
  tiff_header_struct tiffh;

  if(is_a_bmp(file_name)) {
    is_bmp = 1;
    read_bm_header(file_name, &bmph);
    *rows = bmph.height;
    *cols = bmph.width;
  }

  if(is_a_tiff(file_name)){
    is_tiff = 1;
    read_tiff_header(file_name, &tiffh);
    *rows = tiffh.image_length;
    *cols = tiffh.image_width;
  }

  if(is_bmp == 1 || is_tiff == 1) {
    result = 1;
  }

  return result;
}

sint16_t get_bitsperpixel(char_t file_name[], sint32_t *bitsperpixel)
{
  sint16_t is_bmp  = 0,
           is_tiff = 0,
           result  = 0;

  sint32_t temp = 0;
  bitmapheader bmph;
  tiff_header_struct tiffh;

  if(is_a_bmp(file_name)){
    is_bmp = 1;
    read_bm_header(file_name, &bmph);
    temp = (sint32_t)bmph.bitsperpixel;
    *bitsperpixel = temp;
  }

  if(is_a_tiff(file_name)){
    is_tiff = 1;
    read_tiff_header(file_name, &tiffh);
    *bitsperpixel = tiffh.bits_per_pixel;
  }

  if(is_bmp == 1 || is_tiff == 1) {
    result = 1;
  }

  return result;
}

/******************************************************************************
*
*   get_lsb(...
*
*   This function reads the lsb flag from a tiff image file.
*
******************************************************************************/
sint16_t get_lsb(char_t name[])
{
  sint16_t result = 0;
  tiff_header_struct tiff_header;

  if(is_a_bmp(name)) {
    result = 1;
  } else  if(is_a_tiff(name)) {
    read_tiff_header(name, &tiff_header);

    if(tiff_header.lsb == 1) {
      result = 1;
    }
  }

  return result;
}

sint16_t is_a_bmp(char_t file_name[])
{
  char_t *cc = NULL;
  sint16_t result = 0;
  bmpfileheader file_header;

  cc = strstr(file_name, ".bmp");
  if(cc == NULL) {
    result = 0;
  } else {
    read_bmp_file_header(file_name, &file_header);

    if(file_header.filetype != 0x4d42) {
      result = 0;
    } else {
      result = 1;  
    }
  }
  
  return result;
}

sint16_t is_a_tiff(char_t file_name[])
{
  char_t *cc = NULL, buffer[4] = {0};
  FILE *fp = NULL;
  sint16_t  ok = 0, result = 0;

  cc = strstr(file_name, ".tif");
  if(cc == NULL) {
    result = 0;
  } else {
    fp = fopen(file_name, "rb");
    if(fp == NULL) {

    } else {
      fread(buffer, 1, 4, fp);
      fclose(fp);

      if(buffer[0] == 0x49 && buffer[1] == 0x49 &&
          buffer[2] == 0x2a && buffer[3] == 0x00) {
        ok = 1;
      }

      if(buffer[0] == 0x4d && buffer[1] == 0x4d &&
          buffer[2] == 0x00 && buffer[3] == 0x2a) {
        ok = 1;
      }

      if(ok == 0) {
        result = 0;
      } else {
        result = 1;
      }
    }
  }
  
  return result;
}

void read_image_array(char_t file_name[], sint16_t **array)
{
  sint16_t ok = 0;

  if(is_a_tiff(file_name)) {
    read_tiff_image(file_name, array);
    ok = 1;
  } else if(is_a_bmp(file_name)) {
    read_bmp_image(file_name, array);
    ok = 1;
  }

  if(ok == 0) {
    printf("\nERROR could not read file %s", file_name);
    exit(1);
  }
}

void write_image_array(char_t file_name[], sint16_t **array)
{
  sint16_t ok = 0;

  if(is_a_tiff(file_name)) {
    write_tiff_image(file_name, array);
    ok = 1;
  } else if(is_a_bmp(file_name)) {
    write_bmp_image(file_name, array);
    ok = 1;
  }

  if(ok == 0){
    printf("\nERROR could not write file %s", file_name);
    exit(1);
  }
}

void equate_tiff_headers(tiff_header_struct *src, tiff_header_struct *dest)
{
  dest->lsb            = src->lsb;
  dest->bits_per_pixel = src->bits_per_pixel;
  dest->image_length   = src->image_length;
  dest->image_width    = src->image_width;
  dest->strip_offset   = src->strip_offset;
}

void equate_bmpfileheaders(bmpfileheader *src, bmpfileheader *dest)
{
  dest->filetype     = src->filetype;
  dest->filesize     = src->filesize;
  dest->reserved1    = src->reserved1;
  dest->reserved2    = src->reserved2;
  dest->bitmapoffset = src->bitmapoffset;
}

void equate_bitmapheaders(bitmapheader *src, bitmapheader *dest)
{
  dest->size         = src->size;
  dest->width        = src->width;
  dest->height       = src->width;
  dest->planes       = src->planes;
  dest->bitsperpixel = src->bitsperpixel;
  dest->compression  = src->compression;
  dest->sizeofbitmap = src->sizeofbitmap;
  dest->horzres      = src->horzres;
  dest->vertres      = src->vertres;
  dest->colorsused   = src->colorsused;
  dest->colorsimp    = src->colorsimp;
}

sint16_t are_not_same_size(char_t file1[], char_t file2[])
{
  sint16_t result = 0;
  sint32_t cols1  = 1, cols2  = 2, rows1  = 3, rows2  = 4;

  get_image_size(file1, &rows1, &cols1);
  get_image_size(file2, &rows2, &cols2);

  if(rows1 != rows2 || cols1 != cols2) {
    result = 1;
  }

  return result;
}

void create_file_if_needed(char_t in_name[], 
                            char_t out_name[],
                            sint16_t **array)
{
  if(is_a_tiff(in_name)) {
    create_tiff_file_if_needed(in_name, out_name, array);
  } else if(is_a_bmp(in_name)) {
    create_bmp_file_if_needed(in_name, out_name, array);
  }
}

void create_image_file(char_t in_name[], char_t out_name[])
{
  bmpfileheader      bmp_file_header;
  bitmapheader       bmheader;
  tiff_header_struct tiff_file_header;

  if(is_a_tiff(in_name)) {
    read_tiff_header(in_name, &tiff_file_header);
    create_allocate_tiff_file(out_name, &tiff_file_header);
  } else if(is_a_bmp(in_name)) {
    read_bmp_file_header(in_name,  &bmp_file_header);
    read_bm_header(in_name, &bmheader);
    create_allocate_bmp_file(out_name, &bmp_file_header, &bmheader);
  }
}

void create_resized_image_file(char_t in_name[],
                                char_t out_name[],
                                sint32_t length,
                                sint32_t width)
{
  bmpfileheader      bmp_file_header;
  bitmapheader       bmheader;
  tiff_header_struct tiff_file_header;

  if(is_a_tiff(in_name)) {
    read_tiff_header(in_name, &tiff_file_header);
    tiff_file_header.image_length = length;
    tiff_file_header.image_width  = width;
    create_allocate_tiff_file(out_name, &tiff_file_header);
  } else if(is_a_bmp(in_name)) {
    read_bmp_file_header(in_name, &bmp_file_header);
    read_bm_header(in_name, &bmheader);
    bmheader.height = length;
    bmheader.width  = width;
    create_allocate_bmp_file(out_name, &bmp_file_header, &bmheader);
  }
}
