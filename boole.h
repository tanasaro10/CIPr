#ifndef BOOLE_H
#define BOOLE_H

void and_image(int16_t **the_image, int16_t **out_image,
          int32_t rows, int32_t cols);

void or_image(int16_t **the_image, int16_t **out_image,
         int32_t rows, int32_t cols); 

void xor_image(int16_t **the_image, int16_t **out_image,
         int32_t rows, int32_t cols);

void nand_image(int16_t **the_image, int16_t **out_image,
         int32_t rows, int32_t cols, int16_t value);

void nor_image(int16_t **the_image, int16_t **out_image,
         int32_t rows, int32_t cols, int16_t value);

void not_image(int16_t **the_image, int16_t **out_image,
         int32_t rows, int32_t cols, int16_t value);

#endif /* BOOLE_H */