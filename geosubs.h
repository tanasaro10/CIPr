
    /********************************************
    *
    *    file geosubs.h
    *
    *    Modifications:
    *       28 July 2015 - created
    *           Alexandra Bodirlau, Scoala de Vara - Thales - 2015
    *
    ********************************************/

#ifndef GEOSUBS_H
#define GEOSUBS_H

#define FILL 150
#define MAGIC_NUMBER 57.29577951 /* the magic number is from
       								180 degrees divided by pi */
#define EPSILON 0.00001
    
typedef struct {
    float x_angle;
    float x_stretch;
    float y_stretch;
    float x_cross;
    float y_cross;
    int16_t x_displace;
    int16_t y_displace;
    int16_t bilinear;
} geometry_options;

typedef struct {
    float angle;
    int16_t m;
    int16_t n;
    int16_t bilinear;
} rotate_options;

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
        geometry_options image, int32_t rows, int32_t cols);

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
        rotate_options image, int32_t rows, int32_t cols);

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
int16_t bilinear_interpolate(int16_t **the_image, double x, double y,
                          int32_t rows, int32_t cols);


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
                    rotate_options *image_rotate);

#endif /* GEOSUBS_H */