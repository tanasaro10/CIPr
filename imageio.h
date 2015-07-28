/******************************************************************************
*   imageio.h
*       
*   Purpose:
*     To declare the subrutines that read and write tiff and bmp image files.
*
*   External calls:
*     None
*
*   Modifications:
*     23 June 1990 - created
*     28 March 1993 - using fopen, fread, fseek instead of my_open, 
*           my_read, lseek.
*     25 June 1990 - created
*     27 March 1993 - use fopen, fread, fseek instead of the earlier 
*           open, read, seek, etc.
*     21 April 1998 - modified to work with an entire image at one time.
*     18 September 1998 - imagio.c was created by combining tiff.c 
*           brwtiff.c and functions written for bmp file io
*     27 July 2015 - refactored
*           Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015  
*
******************************************************************************/

#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "cips.h"
#include "mtypes.h"

/******************************************************************************
*
*   read_tiff_header(...
*
*   This function reads the header of a TIFF file and places the needed 
*   information into the struct tiff_header_struct.
*
******************************************************************************/
void read_tiff_header(char_t file_name[], tiff_header_struct *image_header);

/******************************************************************************
*
*   extract_long_from_buffer(...
*
*   This takes a four byte long out of a buffer of characters.
*   It is important to know the byte order LSB or MSB.
*
******************************************************************************/
void extract_long_from_buffer(char_t buffer[], 
                              sint16_t lsb, 
                              sint16_t start, 
                              sint32_t *number);

/******************************************************************************
*
*   extract_ulong_from_buffer(...
*
*   This takes a four byte unsigned long out of a buffer of characters.
*   It is important to know the byte order LSB or MSB.
*
******************************************************************************/
void extract_ulong_from_buffer(char_t buffer[], 
                                sint16_t lsb, 
                                sint16_t start, 
                                uint32_t *number);

/******************************************************************************
*
*   extract_short_from_buffer(...
*
*   This takes a two byte short out of a buffer of characters.
*   It is important to know the byte order LSB or MSB.
*
******************************************************************************/
void extract_short_from_buffer(char_t buffer[],
                                sint16_t lsb,
                                sint16_t start,
                                sint16_t *number);

/******************************************************************************
*
*   extract_ushort_from_buffer(...
*
*   This takes a two byte unsiged short out of a buffer of characters.
*   It is important to know the byte order LSB or MSB.
*
******************************************************************************/
void extract_ushort_from_buffer(char_t buffer[],
                                sint16_t lsb,
                                sint16_t start,
                                uint16_t *number);

/******************************************************************************
*
*   allocate_image_array(...
*
*   This function allocates memory for a two-dimensional image array.
*
******************************************************************************/
sint16_t **allocate_image_array(sint32_t length, sint32_t width);

/******************************************************************************
*
*   free_image_array(...
*
*   This function frees up the memory used by a two-dimensional imaage array.
*
******************************************************************************/
sint16_t free_image_array(sint16_t **the_array, sint32_t length);

/******************************************************************************
*
*   read_tiff_image(...
*
*   This function reads the image data from a tiff image file.  
*   It only works for 8-bit gray scale images.
*
******************************************************************************/
void read_tiff_image(char_t image_file_name[], sint16_t **the_image);

/******************************************************************************
*
*   read_line(...
*
*   This function reads bytes from the TIFF file into a buffer, extracts the 
*   numbers from that buffer, and puts them into a ROWSxCOLS array of shorts.
*   The process depends on the number of bits per pixel used in the file 
*   (4 or 8).
*
******************************************************************************/
sint16_t read_line(FILE *image_file, 
                  sint16_t **the_image,
                  sint16_t line_number,
                  tiff_header_struct *image_header,
                  sint16_t ie,
                  sint16_t le);

/******************************************************************************
*
*   seek_to_first_line(...
*
*   This function seeks past the header information in a tiff image file to 
*   the first line of image data.
*
******************************************************************************/
sint16_t seek_to_first_line(FILE *image_file,
                            tiff_header_struct *image_header,
                            sint16_t il);

/******************************************************************************
*
*   seek_to_end_of_line(...
*
*   This function seeks to the end of the current line in a tiff image.
*
******************************************************************************/
sint16_t seek_to_end_of_line(FILE *image_file,
                            sint16_t le,
                            tiff_header_struct *image_header);

/******************************************************************************
*
*   create_tiff_file_if_needed(...
*
*   This function seeks to the end of the current line in a tiff image.
*
******************************************************************************/
void create_tiff_file_if_needed(char_t in_name[],
                                char_t out_name[],
                                sint16_t **out_image);

/******************************************************************************
*
*   create_alllocate_tiff_file(...
*
*   This function creates a file on disk that will be large enough to hold a 
*   tiff image.  The input tiff_header_struct describes the desired tiff file.
*   This function writes the tiff header and then writes a blank image array
*   out to disk the proper number of times.  This has the effect of allocating
*   the correct number of bytes on the disk. There will be 18 entries in 
*   the IFD.
*
*   The image data will begin at byte 296.
*   I will use LSB first data.
*   I will have one strip for the entire image.
*   Black is zero.
*   The component values for the image are CHUNKY (Planer configuration = 1).
*
******************************************************************************/
void create_allocate_tiff_file(char_t file_name[], 
                                tiff_header_struct *image_header);

/******************************************************************************
*
*   write_tiff_image(...
*
*   This function takes an array of shorts and writes them into an 
*   existing tiff image file.
*
******************************************************************************/
void write_tiff_image(char_t image_file_name[], sint16_t **array);

/******************************************************************************
*
*   write_line(...
*
*   This function takes an array of shorts, extracts the numbers and puts them 
*   into a buffer, then writes this buffer into a tiff file on disk. 
*   The process depends on the number of bits per pixel used in the file 
*   (4 or 8).
*
******************************************************************************/
sint16_t write_line(FILE *image_file,
                    sint16_t **array,
                    sint16_t line_number,
                    tiff_header_struct *image_header,
                    sint16_t ie,
                    sint16_t le);

/******************************************************************************
*
*   insert_short_into_buffer(...
*
*   This inserts a two byte short into a buffer of characters.  
*   It does this in LSB order.
*
******************************************************************************/
void insert_short_into_buffer(char_t buffer[], sint16_t start, sint16_t number);

/******************************************************************************
*
*   insert_ushort_into_buffer(...
*
*   This inserts a two byte unsigned short into a buffer of characters.  
*   It does this in LSB order.
*
******************************************************************************/
void insert_ushort_into_buffer(char_t buffer[], sint16_t start, uint16_t number);

/******************************************************************************
*
*   insert_long_into_buffer(...
*
*   This inserts a four byte long into a buffer of characters. 
*   It does this in LSB order.
*
******************************************************************************/
void insert_long_into_buffer(char_t buffer[], sint16_t start, sint32_t number);

/******************************************************************************
*
*   insert_ulong_into_buffer(...
*
*   This inserts a four byte unsigned long into a buffer of characters. 
*   It does this in LSB order.
*
******************************************************************************/
void insert_ulong_into_buffer(char_t buffer[], sint16_t start, uint32_t number);

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
                          sint16_t *length, 
                          sint16_t *width);

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
void read_color_table(char_t file_name[], ctstruct rgb[], sint16_t size);

/******************************************************************************
*
*   print_color_table(...
*
*   This function prints the color table from a bmp file.
*
******************************************************************************/
void print_color_table(ctstruct *rgb, sint16_t size);

/******************************************************************************
*
*   flip_image_array(...
*
*   This function flips an image array about its horizontal mid-point.
*
******************************************************************************/
void flip_image_array(sint16_t **the_image, int32_t cols, int32_t rows);

/******************************************************************************
*
*   read_bmp_image(...
*
*   This function reads the image array from a bmp file.
*   It only works for 8-bit images.
*
******************************************************************************/
void read_bmp_image(char_t file_name[], sint16_t **array);

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
                                sint16_t **out_image);

/******************************************************************************
*
*   write_bmp_image(...
*
*   This function writes an image array to a bmp image file.
*
******************************************************************************/
void write_bmp_image(char_t file_name[], sint16_t **array);

/******************************************************************************
*
*   calculate_pad(...
*
*   This function calculates the pad needed at the end of each row of
*   pixels in a bmp image.
*
******************************************************************************/
int32_t calculate_pad(int32_t width);

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
sint16_t get_image_size(char_t file_name[], int32_t *rows, int32_t *cols);

/******************************************************************************
*
*   get_bitsperpixel(...
*
*   This function reads the bits per pixel from either a tiff or bmp 
*   image file.
*
******************************************************************************/
sint16_t get_bitsperpixel(char_t file_name[], int32_t *bitsperpixel);

/******************************************************************************
*
*   get_lsb(...
*
*   This function reads the lsb flag from a tiff image file.
*
******************************************************************************/
sint16_t get_lsb(char_t name[]);

/******************************************************************************
*
*   is_a_bmp(...
*
*   This function looks at a file to see if it is a bmp file. First look at 
*   the file extension.  Next look at the filetype to ensure it is 0x4d42.
*
******************************************************************************/
sint16_t is_a_bmp(char_t file_name[]);

/******************************************************************************
*
*   is_a_tiff(...
*
*   This function looks at a file to see if it is a tiff file. First look at 
*   the file extension.  Next look at the first four bytes of the header.
*
******************************************************************************/
sint16_t is_a_tiff(char_t file_name[]);

/******************************************************************************
*
*   read_image_array(...
*
*   This routine reads the image data from either a tiff or bmp image.
*
******************************************************************************/
void read_image_array(char_t file_name[], sint16_t **array);

/******************************************************************************
*
*   write_image_array(...
*
*   This routine writes the image data to either a tiff or bmp image.
*
******************************************************************************/
void write_image_array(char_t file_name[], sint16_t **array);

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
sint16_t are_not_same_size(char_t file1[], char_t file2[]);

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
                            sint16_t **array);

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

#endif
