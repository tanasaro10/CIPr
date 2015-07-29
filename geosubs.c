
    /********************************************
    *
    *    file geosubs.c
    *
    *    Functions: This file contains
    *       geometry
    *       arotate
    *       bilinear_interpolate
    *
    *    Purpose:
    *       These functions performs different
    *       geometric operations.
    *
    *    External Calls:
    *       none
    *
    *    Modifications:
    *       20 October 1993- created
    *       27 August 1998 - modified to work on 
    *            entire images at once.
    *       28 July 2015 - refactored
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    ********************************************/

#include "cips.h"
#include "imageio.h"
#include "mtypes.h"
#include "geosubs.h"

 /*******************************************
     *
     *   geometry(..
     *
     *   This routine performs geometric
     *   transformations on the pixels in an
     *   image array.  It performs basic
     *   displacement, stretching, and rotation.
     *
     *   The basic equations are:
     *
     *   new x = x.cos(a) + y.sin(a) + x_displace
     *           + x.x_stretch +x.y.x_cross
     *
     *   new y = y.cos(a) - x.sin(a) + y_displace
     *           + y.y_stretch +x.y.y_cross
     *
     *******************************************/

void geometry(int16_t **the_image, int16_t **out_image,
        geometry_options image, int32_t rows, int32_t cols) {

  double32_t cosa, sina, radian_angle, tmpx, tmpy;
  float32_t  x_div, y_div, x_num, y_num;
  int16_t    i, j, new_i, new_j;

    /******************************
    *
    *   Load the terms array with
    *   the correct parameters.
    *
    *******************************/

  radian_angle = (double32_t) image.x_angle / MAGIC_NUMBER;
  cosa  = cos(radian_angle);
  sina  = sin(radian_angle);

    /************************************
    *
    *   NOTE: You divide by the
    *   stretching factors. Therefore, if
    *   they are zero, you divide by 1.
    *   You do this with the x_div y_div
    *   variables. You also need a
    *   numerator term to create a zero
    *   product.  You do this with the
    *   x_num and y_num variables.
    *
    *************************************/

  if (image.x_stretch < 0.00001) {
    x_div = 1.0;
    x_num = 0.0;
  }
  else {
    x_div = image.x_stretch;
    x_num = 1.0;
  }

  if (image.y_stretch < 0.00001) {
    y_div = 1.0;
    y_num = 0.0;
  }
  else {
    y_div = image.y_stretch;
    y_num = 1.0;
  }

  /**************************
  *
  *   Loop over image array
  *
  **************************/
  for (i = 0; i < rows; i++) {
    if ((i % 10) == 0) {
      printf("%d ", i);
    }
    for (j = 0; j < cols; j++) {

      tmpx = j * cosa + i * sina + image.x_displace +
            (double32_t) x_num * j / x_div +
            (double32_t) image.x_cross * i * j;

      tmpy = i * cosa - j * sina + image.y_displace +
            (double32_t) y_num * i / y_div +
            (double32_t) image.y_cross * i * j;

      if (image.x_stretch != 0.0) {
        tmpx = tmpx - j * cosa + i * sina;
      }
      if (image.y_stretch != 0.0) {
        tmpy = tmpy - i * cosa - j * sina;
      }

      new_j = (int16_t) tmpx;
      new_i = (int16_t) tmpy;

      if (image.bilinear == 0) {
        if ((new_j < 0) || (new_j >= cols) || (new_i < 0) || (new_i >= rows)) {
          out_image[i][j] = FILL;
        }
        else { 
          out_image[i][j] = the_image[new_i][new_j];
        }
      }  /* ends if bilinear */
      else {
        out_image[i][j] = bilinear_interpolate(the_image, tmpx, tmpy, 
                                                rows, cols);
      }  /* ends bilinear if */
    }  /* ends loop over j */
  }  /* ends loop over i */

}  /* ends geometry */



     /*******************************************
     *
     *   arotate(..
     *
     *   This routine performs rotation about
     *   any point m,n.
     *
     *   The basic equations are:
     *
     *   new x = x.cos(a) - y.sin(a)
     *           -m.cos(a) + m + n.sin(a)
     *
     *   new y = y.cos(a) + x.sin(a)
     *           -m.sin(a) - n.cos(a) + n
     *
     *******************************************/

void arotate(int16_t **the_image, int16_t **out_image,
            rotate_options image, int32_t rows, int32_t cols) {

  double32_t cosa, sina, radian_angle, tmpx, tmpy;
  int16_t    i, j, new_i, new_j;

  radian_angle = image.angle / MAGIC_NUMBER;
  cosa  = cos(radian_angle);
  sina  = sin(radian_angle);

      /**************************
      *
      *   Loop over image array
      *
      **************************/

  printf("\n");
  for (i = 0; i < rows; i++) {
    if ((i % 10) == 0) {
      printf("%d ", i);
    }
    for (j = 0; j < cols; j++) {

     /******************************************
     *
     *   new x = x.cos(a) - y.sin(a)
     *           -m.cos(a) + m + n.sin(a)
     *
     *   new y = y.cos(a) + x.sin(a)
     *           -m.sin(a) - n.cos(a) + n
     *
     *******************************************/

      tmpx = j * cosa - i * sina - image.m * cosa + image.m + image.n * sina;
      tmpy = i * cosa + j * sina - image.m * sina - image.n * cosa + image.n;

      new_j = (int16_t) tmpx;
      new_i = (int16_t) tmpy;

      if (image.bilinear == 0) {
        if ((new_j < 0) || (new_j >= cols) || (new_i < 0) || (new_i >= rows)) {
          out_image[i][j] = FILL;
        }
        else {
          out_image[i][j] = the_image[new_i][new_j];
        }   
      }  /* ends if bilinear */
      else {
        out_image[i][j] = bilinear_interpolate(the_image, tmpx, tmpy,
                                                 rows, cols);
      }  /* ends bilinear if */

    }  /* ends loop over j */
  }  /* ends loop over i */

}  /* ends arotate */


     /*******************************************
     *
     *   bilinear_interpolate(..
     *
     *   This routine performs bi-linear
     *   interpolation.
     *
     *   If x or y is out of range, i.e. less
     *   than zero or greater than rows or cols,
     *   this routine returns a zero.
     *
     *   If x and y are both in range, this
     *   routine interpolates in the horizontal
     *   and vertical directions and returns
     *   the proper gray level.
     *
     *******************************************/
int16_t bilinear_interpolate(int16_t **the_image, double32_t x, double32_t y,
                          int32_t rows, int32_t cols) {
   
  double32_t fraction_x, fraction_y, one_minus_x, one_minus_y;
  double32_t p1, p2;
  int16_t    ceil_x, ceil_y, floor_x, floor_y;
  int16_t    p3, result = FILL;

      /******************************
      *
      *   If x or y is out of range,
      *   return a FILL.
      *
      *******************************/

  if ((x < 0.0) || (x >= (double32_t)(cols - 1)) || 
    (y < 0.0) || (y >= (double32_t)(rows - 1))) {
    p3 = result;
  }
  else {
    floor_x    = (int16_t) floor(x);
    floor_y    = (int16_t) floor(y);
    ceil_x     = (int16_t) ceil(x);
    ceil_y     = (int16_t) ceil(y);

    fraction_x = x - floor(x);
    fraction_y = y - floor(y);

    one_minus_x = 1.0 - fraction_x;
    one_minus_y = 1.0 - fraction_y;

    p1 = one_minus_x * the_image[floor_y][floor_x] +
        fraction_x * the_image[floor_y][ceil_x];

    p2 = one_minus_x * the_image[ceil_y][floor_x] +
        fraction_x * the_image[ceil_y][ceil_x];
   
    p3 = (int16_t) (one_minus_y * p1 + fraction_y * p2);
   
  }
  
  return p3;
}  /* ends bilinear_interpolate */



#ifdef NEVER

     /*******************************************
     *
     *   get_geometry_options(..
     *
     *   This routine interacts with the user
     *   to obtain the parameters to call the
     *   geometry operations subroutines.
     *
     *******************************************/

void get_geometry_options(char_t operation[], geometry_options *image_geometry,
                          rotate_options *image_rotate) {
   
  int16_t not_finished, response;
  not_finished = 1;
  while (not_finished){

    printf("\nThe geomety options are:");
    printf("\n\t1. Operation is %s", operation);
    printf("\n\t2. Angle is %f", image_geometry->x_angle);
    printf("\n\t3. x-displace=%d y-displace=%d", image_geometry->x_displace, image_geometry->y_displace);
    printf("\n\t4. x-stretch=%f y-stretch=%f", image_geometry->x_stretch, image_geometry->y_stretch);
    printf("\n\t5. x-cross=%f y-cross=%f", image_geometry->x_cross, image_geometry->y_cross);
    printf("\n\t6. bilinear = %d", image_geometry->bilinear);
    printf("\n\t7. rotation points m=%d n=%d", image_rotate->m, image_rotate->n);
    printf("\n\nExamples:");
    printf("\ngeometry needs: angle");
    printf(" x-displace y-displace");
    printf(" x-stretch y-stretch");
    printf("\n                x-cross y-cross");
    printf(" bilinear (1 or 0)");
    printf("\nrotate needs: angle m n");
    printf(" bilinear (1 or 0)");
    printf("\n\nEnter choice (0 = no change) _\b");
    get_integer(&response);

    if (response == 0) {
      not_finished = 0;
    }

    if (response == 1) {
      printf("\nEnter operation:");
      gets(operation);
    }  /* ends if 1 */

    if (response == 2) {
      printf("\nEnter angle: ___\b\b\b");
      get_float(image_geometry->x_angle);
      get_float(image_rotate->angle);
    }  /* ends if 2 */

    if (response == 3) {
      printf("\nEnter x-displace: ___\b\b\b");
      get_integer(image_geometry->x_displace);
      printf("\nEnter y-displace: ___\b\b\b");
      get_integer(image_geometry->y_displace);
    }  /* ends if 3 */

    if (response == 4) {
      printf("\nEnter x-stretch: ___\b\b\b");
      get_float(image_geometry->x_stretch);
      printf("\nEnter y-stretch: ___\b\b\b");
      get_float(image_geometry->y_stretch);
    }  /* ends if 4 */

    if (response == 5) {
      printf("\nEnter x-cross: ___\b\b\b");
      get_float(image_geometry->x_cross);
      printf("\nEnter y-cross: ___\b\b\b");
      get_float(image_geometry->y_cross);
    }  /* ends if 5 */

    if (response == 6) {
      printf("\nEnter bilinear: _\b");
      get_integer(image_geometry->bilinear);
      get_integer(image_rotate->bilinear);
    }  /* ends if 6 */

    if (response == 7) {
      printf("\nEnter rotation point m: _\b");
      get_integer(image_rotate->m);
      printf("\nEnter rotation point n: _\b");
      get_integer(image_rotate->n);
    }  /* ends if 7 */

  }  /* ends while not_finished */

}  /* ends get_geometry_options */

#endif
