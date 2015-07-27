/******************************************************************************
*   cips.h
*
*   Functions: This file contains no functions. It
*   contains declarations of the data structures used
*   by the C Image Processing Systems CIPS.
*
*   Purpose:
*     To declare data structures.
*
*   Modifications:
*     June 1990 = created
*     27 July 2015 - refactored
*           Iulian-Razvan Matesica, Scoala de Vara - Thales - 2015  
*
******************************************************************************/

#ifndef CIPS_H
#define CIPS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <fcntl.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mtypes.h"

#define MAX_NAME_LENGTH     80
#define ROWS                100
#define COLS                100
#define GRAY_LEVELS         255
#define PREWITT             1
#define PEAK_SPACE          50
#define PEAKS               30
#define KIRSCH              2
#define SOBEL               3
#define STACK_SIZE          40000
#define STACK_FILE_LENGTH   500
#define FORGET_IT           -50
#define STACK_FILE     "c:stack"

/******************************************************************************
*
*   N O T E
*   P O R T A B I L I T Y   I S S U E
*
*   The next two statements help port the system to non-Microsoft C compilers.
*   
*   If you use Microsoft C, then you should
*   #define MSC 1     and
*   #undef  OTHERC
*   
*   If you are using another C compiler or are porting this to another type of 
*   machine, then you should 
*   #undef  MSC
*   #define OTHERC 1
*   
*   Now you need to make changes in mymsc.c
*
******************************************************************************/

#define OTHERC 1
#undef MSC

/******************************************************************************
*
*   N O T E
*   P O R T A B I L I T Y   I S S U E
*
*   Define the Microsoft contants.  If you
*   are using OTHERC, then just put numbers
*   there to hold a place.
*
******************************************************************************/

#ifdef MSC
#define VRES16COLOR   _VRES16COLOR
#define ERESCOLOR     _ERESCOLOR
#define MAXCOLORMODE  _MAXCOLORMODE
#define HRESBW        _HRESBW
#define MRES4COLOR    _MRES4COLOR
#define TEXTC80       _TEXTC80
#define GCLEARSCREEN  _GCLEARSCREEN
#endif

#ifdef OTHERC
#define VRES16COLOR   1u
#define ERESCOLOR     1u
#define MAXCOLORMODE  1u
#define HRESBW        1u
#define MRES4COLOR    1u
#define TEXTC80       1u
#define GCLEARSCREEN  1u
#endif

/******************************************************************************
*
*   The following struct defines the information you need to read 
*   from the tiff file header.
*
*   TODO: Ordonare variabile in structura pentru aliniere
*
******************************************************************************/
typedef struct {
    int16_t lsb;
    int32_t bits_per_pixel;
    int32_t image_length;
    int32_t image_width;
    int32_t strip_offset;
} tiff_header_struct;

/******************************************************************************
*
*   The following struct defines the information you need to read 
*   from the bmp file header.
*
*   TODO: Ordonare variabile in structura pentru aliniere
*
******************************************************************************/
typedef struct {
  uint16_t filetype;
  uint32_t filesize;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t bitmapoffset;
} bmpfileheader;

typedef struct {
  uint32_t size;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bitsperpixel;
  uint32_t compression;
  uint32_t sizeofbitmap;
  uint32_t horzres;
  uint32_t vertres;
  uint32_t colorsused;
  uint32_t colorsimp;
} bitmapheader;

typedef struct {
  uint8_t blue;
  uint8_t green;
  uint8_t red;
} ctstruct;

/******************************************************************************
*
*   The following four unions are used to put the bytes from the header
*   into either an integer or a floating point number.
*
*   TODO: Ordonare variabile in structura pentru aliniere
*
******************************************************************************/
typedef union {
  int16_t s_num;
  char_t  s_alpha[2];
} short_char_union;

typedef union {
  int16_t  i_num;
  char_t i_alpha[2];
} int_char_union;

typedef union {
  int32_t  l_num;
  char_t  l_alpha[4];
} long_char_union;

typedef union {
  float f_num;
  char_t  f_alpha[4];
} float_char_union;

typedef union {
  int16_t s_num;
  char_t  s_alpha[2];
} ushort_char_union;

typedef union {
  int16_t  i_num;
  char_t i_alpha[2];
} uint_char_union;

typedef union {
  int32_t  l_num;
  char_t  l_alpha[4];
} ulong_char_union;

#endif
