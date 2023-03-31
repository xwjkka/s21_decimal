#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal a = value_1, b = value_2;
  a = des_is_minus_null(a);
  b = des_is_minus_null(b);
  int res = 0, sign_a = getbit(a, 127), sign_b = getbit(b, 127);
  des_denomenator(&a, &b);
  int comp = des_comparison_mantissa(a, b);
  if (sign_a && !sign_b)
    res = 1;
  else if (sign_a == sign_b) {
    if (comp == MORE && sign_a && sign_b)
      res = 1;
    else if (comp == LESS && !sign_a && !sign_b)
      res = 1;
  }
  return res;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0, sign_a = getbit(value_1, 127), sign_b = getbit(value_2, 127);
  s21_decimal nul = {{0, 0, 0, 0}};
  des_denomenator(&value_1, &value_2);
  int comp = des_comparison_mantissa(value_1, value_2);
  if (comp == EQUAL && des_comparison_mantissa(value_1, nul) == EQUAL)
    res = 1;
  else if (sign_a == sign_b)
    if (comp == EQUAL) res = 1;
  return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal a = value_1, b = value_2;
  a = des_is_minus_null(a);
  b = des_is_minus_null(b);
  int res = 0, sign_a = getbit(a, 127), sign_b = getbit(b, 127);
  des_denomenator(&a, &b);
  int comp = des_comparison_mantissa(a, b);
  if (!sign_a && sign_b)
    res = 1;
  else if (sign_a == sign_b) {
    if (comp == MORE && !sign_a && !sign_b)
      res = 1;
    else if (comp == LESS && sign_a && sign_b)
      res = 1;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_decimal a = value_1, b = value_2, tmp = {{0, 0, 0, 0}};
  des_denomenator(&a, &b);
  int err = RES_OK, exp = des_get_exp(a);
  while (des_add_mantissa(a, b, &tmp) && exp)  //*result = tmp;
    exp_round_left(&a, &b, &exp);
  err = des_add_sign_mant(a, b, result);
  if (getbit(value_1, 127) && getbit(value_2, 127) && err) err = 2;
  des_end_func(result, exp, err);
  return err;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_decimal a = value_1, b = value_2, nul = {{0, 0, 0, 0}},
              one = {{1, 0, 0, 0}};
  int bank1 = des_comparison_mantissa(b, nul);
  des_denomenator(&a, &b);
  int bank2 = des_comparison_mantissa(b, nul) == 0 && bank1;
  int err = RES_OK, exp = des_get_exp(a);
  int sign = getbit(a, 127) & getbit(b, 127);
  err = des_sub_sign_mant(a, b, result, &exp);
  if (bank2 && !sign && getbit(value_1, 0))
    des_sub_mantissa(*result, one, result);
  if (getbit(*result, 127) && err) err = 2;
  des_end_func(result, exp, err);
  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal a = value_1, b = value_2;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  a = des_is_minus_null(a);
  b = des_is_minus_null(b);
  int exp = 0, err = 0;
  // des_denomenator(&a, &b);
  exp = des_get_exp(a) + des_get_exp(b);
  err = des_mul_mantissa(a, b, result);
  if (err) {
    err = 0;
    des_denomenator(&a, &b);
    exp = des_get_exp(a) + des_get_exp(b);
    if (exp > 28) {
      s21_dec_null(result);
      err = des_mul_mant_big(a, b, result);
    } else
      err = des_mul_mantissa(a, b, result);
  }
  // while (28 < exp) {
  //   des_div_mantissa(*result, ten, result, &tmp, NO_ROUND);
  //   s21_decimal fiv = {{5,0,0,0}}, one = {{1,0,0,0}};
  //   if (des_comparison_mantissa(tmp, fiv) != LESS && getbit(*result, 0))
  //     des_add_mantissa(one, *result, result);
  //   exp--;
  // }
  des_set_bit(result, 127, des_sign_mant(a, b));
  if (!des_m_nul(*result)) des_set_bit(result, 127, 0);
  if (getbit(*result, 127) && err) err = 2;
  des_end_func(result, exp, err);
  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_decimal a = value_1, b = value_2, ost = {{0, 0, 0, 0}},
              mod = {{0, 0, 0, 0}};
  int exp = 0, err = !des_comparison_mantissa(b, ost) ? RES_NULL : RES_OK;
  if (!err) {
    exp = des_get_exp(a) - des_get_exp(b);
    des_denomenator(&a, &b);
    err = des_div_mantissa(a, b, result, &mod, ROUND_MOD);
    exp = des_get_exp(*result);
  }
  des_del_nul(result, &exp);
  des_set_bit(result, 127, des_sign_mant(value_1, value_2));
  des_end_func(result, exp, err);
  return err;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (dst == NULL || abs(src) == INFINITY) {
    res = 1;
  } else {
    for (int i = 0; i < 4; i++) dst->bits[i] = 0;
    if (src < 0) {
      s21_SetBit(dst, 127);
      src *= -1;
    }
    dst->bits[0] = src;
  }

  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  *dst = 0;
  int sign = 0;
  if (getbit(src, 127)) {
    sign = 1;
  }
  s21_truncate(src, &src);
  if (src.bits[1] || src.bits[2]) {
    res = 1;
  } else {
    *dst = src.bits[0];
    if (sign) {
      *dst = -*dst;
    }
  }
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if ((dst == NULL) || (isnan(src) != 0) || (fabs(src) == INFINITY)) {
    res = 1;
  } else {
    for (int i = 0; i < 4; i++) dst->bits[i] = 0;
    int binExp = s21_GetBinExp(src);
    if (src < 0) {
      s21_SetBit(dst, 127);
      src *= -1;
    }
    if (binExp > 95 || binExp < -95) {
      res = 1;
    } else {
      int scale = 0;
      for (; !((int)src); src *= 10, scale++) {
      }

      for (; scale < 28 && ((int)src / (int)(pow(2, 20)) == 0);
           src *= 10, scale++) {
      }
      src = round(src);
      while ((int)src % 10 == 0) {
        src /= 10;
        scale--;
      }
      binExp = s21_GetBinExp(src);
      s21_SetBit(dst, binExp);
      if (binExp < -94 || scale > 28) {
        res = 1;
      } else {
        unsigned int fbits = *((unsigned int *)&src);
        for (int i = binExp - 1, j = 22; j >= 0; i--, j--) {
          if ((fbits & (1 << j))) {
            s21_SetBit(dst, i);
          }
        }
        s21_set_exp(dst, scale);
      }
    }
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  *dst = 0;
  if (!dst) {
    res = 1;
  } else {
    *dst = 0.0;
    for (int i = 0; i < 96; i++) {
      if (getbit(src, i)) {
        *dst += pow(2, i);
      }
    }

    *dst /= pow(10, s21_show_exp(src));

    if (getbit(src, 127)) {
      *dst *= -1;
    }
  }
  return res;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal ten = {{10, 0, 0, 0}}, mod = {{0, 0, 0, 0}};
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int err = 0;
  int sign = getbit(value, 127);
  for (int i = des_get_exp(value); 0 < i; i--)
    err = des_div_mantissa(value, ten, &value, &mod, NO_ROUND);
  *result = value;
  if (sign) des_set_bit(result, 127, 1);
  return err;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int flag = 0;
  if (s21_isnull_dec(value)) {
    flag = 1;
  } else {
    *result = value;
    if (getbit(*result, 127)) {
      s21_DeleteBit(result, 127);
    } else {
      s21_SetBit(result, 127);
    }
  }
  return (flag);
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  s21_decimal ostatok = {{0, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal edinica = {{1, 0, 0, 0}};
  int exp = s21_show_exp(value);
  if (getbit(value, 127)) {
    s21_DeleteBit(&value, 127);
    if (exp != 0) {
      while (exp > 1) {
        des_div_mantissa(value, ten, &value, &ostatok, ROUND_B);
        if (ostatok.bits[0] > 0) {
          des_add_mantissa(value, edinica, &value);
        }
        exp--;
      }
      des_div_mantissa(value, ten, &value, &ostatok, ROUND_B);
      des_add_mantissa(value, edinica, &value);
      *result = value;
      s21_SetBit(result, 127);
    } else {
      *result = value;
      s21_SetBit(result, 127);
    }
  } else {
    if (exp != 0) {
      while (exp > 0) {
        des_div_mantissa(value, ten, &value, &ostatok, ROUND_B);
        exp--;
      }
      *result = value;
    } else {
      *result = value;
    }
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  s21_decimal ostatok = {{0, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  int sign = getbit(value, 127);
  int exp = s21_show_exp(value);
  s21_DeleteBit(&value, 127);
  if (exp != 0) {
    while (exp > 1) {
      des_div_mantissa(value, ten, &value, &ostatok, ROUND);
      exp--;
    }
    des_div_mantissa(value, ten, &value, &ostatok, ROUND);
    *result = value;
  } else {
    *result = value;
  }
  if (sign) {
    s21_SetBit(result, 127);
  }
  return 0;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int flag = 0;
  s21_decimal null = {{0, 0, 0, 0}};
  s21_decimal buf = {{0, 0, 0, 0}};
  int exp_1 = s21_show_exp(value_1);
  int exp_2 = s21_show_exp(value_2);
  int sign_1 = getbit(value_1, 127);
  int sign_2 = getbit(value_2, 127);

  if (s21_is_equal(value_1, null)) {
    *result = null;
  } else if (s21_is_equal(value_2, null)) {
    flag = 3;
  } else if (is_less_mod(value_1, value_2)) {
    *result = value_1;
  } else {
    des_div_mantissa(value_1, value_2, &null, result, NO_ROUND);
    s21_div(value_1, value_2, &buf);
    s21_truncate(buf, &buf);
    if (exp_1 > 0 || exp_2 > 0) {
      s21_mul(buf, value_2, result);
      s21_sub(value_1, *result, result);
      if (exp_2 > exp_1) {
        s21_set_exp(result, exp_2);
      } else {
        s21_set_exp(result, exp_1);
      }
    }
  }
  if (sign_1 != sign_2) {
    s21_SetBit(result, 127);
  }
  return flag;
}

// fmod(10.324, 9.234) == делит мантиссы, остаток - 10.324 - 9.234, * результат
// деления 0.234 mod 100 = 234 / 100 == 2 .  234 - 100 * 2 = 34.