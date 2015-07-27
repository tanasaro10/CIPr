#include "imageio.h"

int main()
{

  return 0;
}

void read_tiff_header(char_t file_name[], tiff_header_struct *image_header)
{
  FILE *image_file = NULL;

  char_t  buffer[12] = {0};

  int16_t not_finished = 0, lsb = 0;

  int32_t bits_per_pixel = 0, 
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

      for(uint16_t i = 0; i < entry_count; i++) {
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
                              int16_t lsb, 
                              int16_t start, 
                              int32_t *number)
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
                                int16_t lsb, 
                                int16_t start, 
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
                                int16_t lsb,
                                int16_t start,
                                int16_t *number)
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
                                int16_t lsb,
                                int16_t start,
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

int16_t **allocate_image_array(int32_t length, int32_t width)
{
  int16_t **the_array = malloc(length * sizeof(int16_t*));

  for(int i = 0; i < length; i++) {
    the_array[i] = malloc(width * sizeof(int16_t));

    if(the_array[i] == '\0') {
       printf("\n\tmalloc of the_image[%d] failed", i);
    }
  }

  return the_array; 
}

int16_t free_image_array(int16_t **the_array, int32_t length)
{

}

void read_tiff_image(char_t image_file_name, int16_t **the_image)
{

}

void read_line(FILE *image_file, 
                int16_t **the_image,
                int16_t line_number,
                tiff_header_struct *image_header,
                int16_t ie,
                int16_t le)
{

}

void seek_to_first_line(FILE *image_file,
                        tiff_header_struct *image_header,
                        int16_t il)
{

}

void seek_to_end_of_line(FILE *image_file,
                          int16_t le,
                          tiff_header_struct *image_header)
{

}

void create_tiff_file_if_needed(char_t in_name[],
                                char_t out_name[],
                                int16_t **out_image)
{

}

void create_allocate_tiff_file(char_t file_name[], 
                                tiff_header_struct *image_header)
{

}

void write_tiff_image(char_t image_file_name[], int16_t **array)
{

}

void write_line(FILE *image_file,
                int16_t **array,
                int16_t line_number,
                tiff_header_struct *image_header,
                int16_t ie,
                int16_t le)
{

}

void insert_short_into_buffer(char_t buffer[], int16_t start, int16_t number)
{

}

void insert_ushort_into_buffer(char_t buffer[], int16_t start, uint16_t number)
{

}

void insert_long_into_buffer(char_t buffer[], int16_t start, int32_t number)
{

}

void insert_ulong_into_buffer(char_t buffer[], int16_t start, uint32_t number)
{

}

/******************************************************************************
*
*   round_off_image_size(...
*
*   This takes the image header and rounds it off to a multiple of ROWS and 
*   COLS.
*   e.g. if width=123 it returns 1.
*
******************************************************************************/
void round_off_image_size(tiff_header_struct *image_header,
                          int16_t length, 
                          int16_t width);

/******************************************************************************
*
*   does_not_exist(...
*
*   This function checks the disk to see if  a file exists.  If the file is 
*   there this function returns a 0, if it does not exist this function 
*   returns a 1.
*
******************************************************************************/
uint16_t does_not_exist(char_t file_name[]);

/******************************************************************************
*
*   read_bmp_file_header(...
*
*   This function reads the bmpfileheader structure from the top of a bmp
*   image file.
*
******************************************************************************/
void read_bmp_file_header(char_t file_name[],
                          bmpfileheader *file_header);

/******************************************************************************
*
*   print_bmp_file_header(...
*
*   This function prints parts of the bmpfileheader structure.
*
******************************************************************************/
void print_bmp_file_header(bmpfileheader *file_header);

/******************************************************************************
*
*   read_bm_header(...
*
*   This function reads the bitmapheader structure from the top of a bmp
*   image file.
*
******************************************************************************/
void read_bm_header(char_t file_name[], bitmapheader *bmheader);

/******************************************************************************
*
*   print_bm_header(...
*
*   This function reads the bitmapheader structure from the top of a bmp
*   image file.
*
******************************************************************************/
void print_bm_header(bitmapheader *bmheader);

/******************************************************************************
*
*   read_color_table(...
*
*   This function reads the color table from a bmp image file.
*
******************************************************************************/
void read_color_table(char_t file_name[], ctstruct *rgb, int16_t size);

/******************************************************************************
*
*   print_color_table(...
*
*   This function prints the color table from a bmp file.
*
******************************************************************************/
void print_color_table(ctstruct *rgb, int16_t size);

/******************************************************************************
*
*   flip_image_array(...
*
*   This function flips an image array about its horizontal mid-point.
*
******************************************************************************/
void flip_image_array(int16_t **the_image, int32_t cols, int32_t rows);

/******************************************************************************
*
*   read_bmp_image(...
*
*   This function reads the image array from a bmp file.
*   It only works for 8-bit images.
*
******************************************************************************/
void read_bmp_image(char_t file_name[], int16_t **array);

/******************************************************************************
*
*   create_allocate_bmp_file(...
*
*   The calling routine must set the height and width. This routine will set
*   everything else.
*
******************************************************************************/
void create_allocate_bmp_file(char_t file_name[], 
                              bmpfileheader *file_header,
                              bitmapheader *bmheader);

/******************************************************************************
*
*   create_bmp_file_if_needed(...
*
*   This function allocates a bmp image file it it does not exist.  It uses
*   the header information from the input  image name.
*
******************************************************************************/
void create_bmp_file_if_needed(char_t in_name[],
                                char_t out_name[],
                                int16_t **out_image);

/******************************************************************************
*
*   write_bmp_image(...
*
*   This function writes an image array to a bmp image file.
*
******************************************************************************/
void write_bmp_image(char_t file_name[], int16_t **array);

/******************************************************************************
*
*   calculate_pad(...
*
*   This function calculates the pad needed at the end of each row of
*   pixels in a bmp image.
*
******************************************************************************/
int16_t calculate_pad(int32_t width);

/******************************************************************************
*
*   get_image_size(...
*
*   This function reads the rows and cols from the header of either a tiff 
*   or bmp image file.
*
*   IF IT CANNOT FIND THIS INFORMATION,
*   it returns a ZERO.
*
******************************************************************************/
int16_t get_image_size(char_t file_name[], int32_t *rows, int32_t *cols);

/******************************************************************************
*
*   get_bitsperpixel(...
*
*   This function reads the bits per pixel from either a tiff or bmp 
*   image file.
*
******************************************************************************/
int16_t get_bitsperpixel(char_t file_name[], int32_t *bitsperpixel);

/******************************************************************************
*
*   get_lsb(...
*
*   This function reads the lsb flag from a tiff image file.
*
******************************************************************************/
int16_t get_lsb(char_t name[]);

/******************************************************************************
*
*   is_a_bmp(...
*
*   This function looks at a file to see if it is a bmp file. First look at 
*   the file extension.  Next look at the filetype to ensure it is 0x4d42.
*
******************************************************************************/
int16_t is_a_bmp(char_t file_name[]);

/******************************************************************************
*
*   is_a_tiff(...
*
*   This function looks at a file to see if it is a tiff file. First look at 
*   the file extension.  Next look at the first four bytes of the header.
*
******************************************************************************/
int16_t is_a_tiff(char_t file_name[]);

/******************************************************************************
*
*   read_image_array(...
*
*   This routine reads the image data from either a tiff or bmp image.
*
******************************************************************************/
void read_image_array(char_t file_name[], int16_t **array);

/******************************************************************************
*
*   write_image_array(...
*
*   This routine writes the image data to either a tiff or bmp image.
*
******************************************************************************/
void write_image_array(char_t file_name[], int16_t **array);

/******************************************************************************
*
*   equate_tiff_headers(...
*
*   This function sets the elements of the destination header to the 
*   values of the source header.
*
******************************************************************************/
void equate_tiff_headers(tiff_header_struct *src, tiff_header_struct *dest);

/******************************************************************************
*
*   equate_bmpfileheaders(...
*
*   This function sets the elements of the destination header to the 
*   values of the source header.
*
******************************************************************************/
void equate_bmpfileheaders(bmpfileheader *src, bmpfileheader *dest);

/******************************************************************************
*
*   equate_bitmapheaders(...
*
*   This function sets the elements of the destination header to the 
*   values of the source header.
*
******************************************************************************/
void equate_bitmapheaders(bitmapheader *src, bitmapheader *dest);

/******************************************************************************
*
*   are_not_same_size(...
*
*   This function checks the rows and cols of two images whose names 
*   are passed.
*   It returns a 1 if the images are not the same size.
*
******************************************************************************/
int16_t are_not_same_size(char_t file1[], char_t file2[]);

/******************************************************************************
*
*   create_file_if_needed(...
*
*   This function creates an output file if it does not exist.  It can create
*   the output file as a tiff or a bmp based on the input file type.
*
******************************************************************************/
void create_file_if_needed(char_t in_name[], 
                            char_t out_name[],
                            int16_t **array);

/******************************************************************************
*
*   create_image_file(...
*
*   This function creates an output image file. 
*   It uses the input image file as a pattern.
*
******************************************************************************/
void create_image_file(char_t in_name[], char_t out_name[]);

/******************************************************************************
*
*   create_resized_image_file(...
*
*   This function creates an output image file.
*   It uses the input image file as a pattern.
*
******************************************************************************/
void create_resized_image_file(char_t in_name[],
                                char_t out_name[],
                                int32_t length,
                                int32_t width);
