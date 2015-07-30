#include "cutp.h"

void paste_image_piece(sint16_t **the_image,
                      sint16_t **out_image,
                      sint32_t il1,
                      sint32_t ie1,
                      sint32_t ll1,
                      sint32_t le1,
                      sint32_t il2,
                      sint32_t ie2) 
{ 
  sint32_t i = 0, j = 0, limit1 = 0, limit2 = 0;

  limit1 = ll1 - il1;
  limit2 = le1 - ie1;

  for(i = 0; i < limit1; i++) {
    for(j = 0; j < limit2; j++) {
      out_image[il2 + i][ie2 + j] = the_image[il1 + i][ie1 + j];
    }
  }
}

void check_cut_and_paste_limits(sint32_t il1, 
                                sint32_t ie1, 
                                sint32_t ll1, 
                                sint32_t le1, 
                                sint32_t il2, 
                                sint32_t ie2, 
                                sint32_t image1_length, 
                                sint32_t image1_width,
                                sint32_t image2_length, 
                                sint32_t image2_width,
                                sint16_t *is_ok)
{
  sint16_t result = 1;

  if(il1 < 0 || ie1 < 0) {
    (void)printf("\nCheck> il1=%d ie1=%d", il1, ie1);
    result = 0;
  }

  if(il2 < 0 || ie2 < 0) {
    (void)printf("\nCheck> il2=%d ie2=%d", il2, ie2);
    result = 0;
  }

  if(ll1 > image1_length) {
    (void)printf("\nCheck> ll1=%d length=%d", ll1, image1_length);
    result = 0;
  }

  if(le1 > image1_width) {
    (void)printf("\nCheck> le1=%d width=%d", le1, image1_width);
    result = 0;
  }

  if((il2 + (ll1 - il1)) > image2_length) {
    (void)printf("\nCheck> il2=%d length=%d", il2 + (ll1 - il1), image2_length);
    result = 0;
  }

  if((ie2 + (le1 - ie1)) > image2_width) {
    printf("\nCheck> ie2=%d width=%d", ie2 + (le1 - ie1), image2_width);
    result = 0;
  }

  *is_ok = result;
}
