
#include "s21_decimal.h"
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int degree = _G_D_(value);
  int return_result = 0;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (degree > 28) {
    return_result = 1;
  } else {
    while (degree > 0) {
      s21_right_shift(value, 1, TRUE, &value);
      degree--;
    }
    /*	degree=_G_D_(value);
            while(degree>0){
             s21_left_shift(value, 1, TRUE, &value);
             degree--;
            }
    */

    _S_D_((value), 0);
    *result = value;
  }
  return return_result;
}