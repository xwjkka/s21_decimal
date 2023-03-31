#include "s21_decimal.h"

////////// ниже вспомогательные функции

// нужен для s21_printf_decimal
// int call_of_me(int row) {
//   int col = 0;
//   if (row == 0) {
//     col = 31;
//   } else if (row == 1) {
//     col = 63;
//   } else if (row == 2) {
//     col = 95;
//   } else if (row == 3) {
//     col = 127;
//   }
//   return col;
// }

// // нужен для s21_printf_decimal
// int call_of_me_stop_me(int row) {
//   int col = 0;
//   if (row == 0) {
//     col = 0;
//   } else if (row == 1) {
//     col = 32;
//   } else if (row == 2) {
//     col = 64;
//   } else if (row == 3) {
//     col = 96;
//   }
//   return col;
// }

// // выводит вид decimal
// void s21_printf_decimal(s21_decimal value) {
//   int row = 0;
//   int col = 31;
//   int MANTISA[96] = {0};
//   for (; row <= 3; row++) {
//     for (col = call_of_me(row); col >= call_of_me_stop_me(row); col--) {
//       printf("%2d ", col);
//       if (col == call_of_me_stop_me(row)) {
//         printf("\n");
//       }
//     }
//     for (col = call_of_me(row); col >= call_of_me_stop_me(row); col--) {
//       if (col >= 100) {
//         if (col == 127) {
//           printf("(");
//           printf("%d", getbit(value, col));
//           printf(")");
//         } else if (col == 119) {
//           printf(" (");
//           printf("%d", getbit(value, col));
//         } else if (col < 119 && col > 112) {
//           printf(" %3d", getbit(value, col));
//         } else if (col == 112) {
//           printf(" %3d", getbit(value, col));
//           printf(")");
//         } else {
//           printf("%3d ", getbit(value, col));
//         }
//       } else {
//         printf("%2d ", getbit(value, col));
//       }
//       if (col == call_of_me_stop_me(row)) {
//         printf("\n");
//       }
//     }
//     printf("\n");
//   }
//   printf("MANTISA: ");
//   for (int bit = 95; bit >= 0; bit--) {
//     MANTISA[bit] = getbit(value, bit);
//     printf("%d", MANTISA[bit]);
//   }
//   s21_from_decimal_to_int_mantisa(value);
//   printf("\nHEX:\t");
//   char* exp = (char*)calloc(10, sizeof(char));
//   for (int bit = 119, j = 0; bit >= 112; bit--, j++) {
//     // printf("%d", getbit(value, bit));
//     exp[j] = getbit(value, bit) + 48;
//   }
//   int int_exp = hex_to_int(exp, 8);
//   printf("%s\tEXP:%d\t", exp, int_exp);
//   printf("\nSIGN:\t%d\t%c\n", getbit(value, 127),
//          getbit(value, 127) > 0 ? '-' : '+');
// }

// ---------------------------- from decimal.c ----------------------------

// получение нужного бита от 0  до 128
int getbit(s21_decimal value, int bit) {
  int res = 0;
  res = value.bits[bit / 32];
  int ostat = bit % 32;
  res = res & (1 << ostat);
  res = (res != 0);
  return res;
}
int getbit_bd(big_d value, int bit) {
  int res = 0;
  res = value.bits[bit / 32];
  int ostat = bit % 32;
  res = res & (1 << ostat);
  res = (res != 0);
  return res;
}

// //  обнуление decimal но нужного значения
// void s21_DeleteBitUnder(s21_decimal* value, int bit) {
//   while (bit >= 0) {
//     des_set_bit(value, bit, 0);
//     bit--;
//   }
// }

// // перписывает 0 и 1 из dec1 в dec2 до нужного бита
// int Perepis(s21_decimal dec1, s21_decimal* dec2, int bit) {
//   int errors = 0;
//   for (; bit >= 0; bit--) des_set_bit(dec2, bit, getbit(dec1, bit));
//   return errors;
// }

// // инверсия - меняет 1 -> 0 и 0 -> 1 в нужном бите
// void s21_inverse(s21_decimal* value, int bit) {
//   int row = bit / 32;
//   int col = bit % 32;
//   value->bits[bit / 32] = (value->bits[row]) ^ (1 << col);
// }
// bits 0-3 = chislo, bits 4 - exp + sign

void s21_SetBit(s21_decimal* value, int bit) {
  value->bits[bit / 32] = value->bits[bit / 32] | (1 << (bit % 32));
}

void s21_DeleteBit(s21_decimal* value, int bit) {
  value->bits[bit / 32] = value->bits[bit / 32] & ~(1 << (bit % 32));
}

void s21_set_exp(s21_decimal* src, int exp) {
  for (int i = 119, j = 7; j >= 0; i--, j--) {
    if ((exp & (1 << j))) {
      s21_SetBit(src, i);
    }
  }
}

int s21_show_exp(s21_decimal src) {
  int exp = 0;
  for (int i = 112; i <= 119; i++) {
    exp += (getbit(src, i) ? pow(2, i - 112) : 0);
  }

  return exp;
}

int s21_GetBinExp(float src) {
  unsigned int fbits = *((unsigned int*)&src);
  int exp = 0;
  int k = 0;
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    if (k > 0 && k < 9) {
      exp += !!(fbits & mask) ? pow(2, 8 - k) : 0;
    }
    k++;
  }

  return exp - 127;
}

void des_set_bit(s21_decimal* dec, int bit, int status) {
  if (status == 1)
    dec->bits[bit / 32] |= (1 << (bit % 32));
  else if (status == 0)
    dec->bits[bit / 32] &= ~(1 << (bit % 32));
}
void des_set_bit_bd(big_d* dec, int bit, int status) {
  if (status == 1)
    dec->bits[bit / 32] |= (1 << (bit % 32));
  else if (status == 0)
    dec->bits[bit / 32] &= ~(1 << (bit % 32));
}

int des_get_exp(s21_decimal dec) { return (int)dec.bits[3] >> 16 & 255; }

void des_set_exp(s21_decimal* dec, int exp) {
  dec->bits[3] = getbit(*dec, 127) << 31 | exp << 16;
}

int des_shift_left(s21_decimal* dec, int shift) {
  int flag = 0;
  for (int i = 95; 95 - shift < i; i--)
    if (getbit(*dec, i)) flag = 1;
  if (!flag)
    for (int i = 95; i > -1; i--)
      des_set_bit(dec, i, shift <= i ? getbit(*dec, i - shift) : 0);
  return flag;
}
int des_shift_left_bd(big_d* dec, int shift) {
  int flag = 0;
  for (int i = 191; 191 - shift < i; i--)
    if (getbit_bd(*dec, i)) flag = 1;
  if (!flag)
    for (int i = 191; i > -1; i--)
      des_set_bit_bd(dec, i, shift <= i ? getbit_bd(*dec, i - shift) : 0);
  return flag;
}

void des_shift_right(s21_decimal* dec, int shift) {
  for (int i = 0; i < 96 && 0 < shift; i++) {
    if (i < 96 - shift) des_set_bit(dec, i, getbit(*dec, i + shift));
    if (95 - shift < i) des_set_bit(dec, i, 0);
  }
}
void des_shift_right_bd(big_d* dec, int shift) {
  for (int i = 0; i < 192 && 0 < shift; i++) {
    if (i < 192 - shift) des_set_bit_bd(dec, i, getbit_bd(*dec, i + shift));
    if (191 - shift < i) des_set_bit_bd(dec, i, 0);
  }
}

void s21_dec_null(s21_decimal* dec) {
  for (int i = 0; i < 4; i++) dec->bits[i] = 0;
}
void s21_dec_null_bd(big_d* dec) {
  for (int i = 0; i < 6; i++) dec->bits[i] = 0;
}

void exp_round_left(s21_decimal* a, s21_decimal* b, int* exp) {
  s21_decimal fiv = {{5, 0, 0, 0}}, one = {{1, 0, 0, 0}}, tmp = {{0, 0, 0, 0}},
              ten = {{10, 0, 0, 0}}, tmp2 = {{0, 0, 0, 0}};
  int signa = getbit(*a, 127), signb = getbit(*b, 127);
  des_div_mantissa(*a, ten, a, &tmp, NO_ROUND);
  if (des_comparison_mantissa(tmp, fiv) != LESS /*  && getbit(*a, 0) */)
    des_add_mantissa(one, *a, a);
  des_div_mantissa(*b, ten, b, &tmp, NO_ROUND);
  if (des_comparison_mantissa(tmp2, fiv) != LESS /*  && getbit(*b, 0) */)
    des_add_mantissa(one, *b, b);
  *exp -= 1;
  des_set_bit(a, 127, signa);
  des_set_bit(b, 127, signb);
}

int des_add_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal* res) {
  s21_decimal a = dec1, b = dec2;
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  int tmp = 0, overflow = RES_OK;
  for (int i = 0; i < 96; i++) {
    int sum_bits = getbit(a, i) + getbit(b, i) + tmp;
    if (sum_bits == 0) {
      des_set_bit(res, i, 0);
      tmp = 0;
    } else if (sum_bits == 1) {
      des_set_bit(res, i, 1);
      tmp = 0;
    } else if (sum_bits == 2) {
      des_set_bit(res, i, 0);
      tmp = 1;
    } else if (sum_bits == 3) {
      des_set_bit(res, i, 1);
      tmp = 1;
    }
    if (i == 95 && tmp != 0) overflow = RES_OVERFLOW;
  }
  // res->bits[3] &= ~33023;  // маска для очистки bits[3]
  return overflow;
}

int des_add_mant_big(big_d dec1, big_d dec2, big_d* res) {
  // for (int i = 0; i < 6; i++) res->bits[i] = 0;
  big_d a = dec1, b = dec2;
  int tmp = 0, overflow = RES_OK;
  for (int i = 0; i < 192; i++) {
    int sum_bits = getbit_bd(a, i) + getbit_bd(b, i) + tmp;
    if (sum_bits == 0) {
      des_set_bit_bd(res, i, 0);
      tmp = 0;
    } else if (sum_bits == 1) {
      des_set_bit_bd(res, i, 1);
      tmp = 0;
    } else if (sum_bits == 2) {
      des_set_bit_bd(res, i, 0);
      tmp = 1;
    } else if (sum_bits == 3) {
      des_set_bit_bd(res, i, 1);
      tmp = 1;
    }
    if (i == 192 && tmp != 0) overflow = RES_OVERFLOW;
  }
  // res->bits[3] &= ~33023;  // маска для очистки bits[3]
  return overflow;
}

void des_sub_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal* res) {
  s21_decimal tmp = dec1, a = dec2;
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  for (int i = 0; i < 96; i++) {
    int sum_bits = getbit(tmp, i) - getbit(a, i);
    if (sum_bits == 0)
      des_set_bit(res, i, 0);
    else if (sum_bits == 1)
      des_set_bit(res, i, 1);
    else if (sum_bits == -1) {
      des_set_bit(res, i, 1);
      int j = i;
      for (; !getbit(tmp, j); j++) des_set_bit(&tmp, j, 1);
      des_set_bit(&tmp, j, 0);
    }
  }
}
void des_sub_mantissa_bd(big_d dec1, big_d dec2, big_d* res) {
  // for (int i = 0; i < 6; i++) res->bits[i] = 0;
  big_d tmp = dec1;
  for (int i = 0; i < 192; i++) {
    int sum_bits = getbit_bd(tmp, i) - getbit_bd(dec2, i);
    if (sum_bits == 0)
      des_set_bit_bd(res, i, 0);
    else if (sum_bits == 1)
      des_set_bit_bd(res, i, 1);
    else if (sum_bits == -1) {
      des_set_bit_bd(res, i, 1);
      int j = i;
      for (; !getbit_bd(tmp, j); j++) des_set_bit_bd(&tmp, j, 1);
      des_set_bit_bd(&tmp, j, 0);
    }
  }
}

int des_comparison_mantissa(s21_decimal dec1, s21_decimal dec2) {
  int tmp = 0;
  int res = EQUAL;
  for (int i = 0; i < 3; i++) tmp |= dec1.bits[i] ^ dec2.bits[i];
  if (tmp)
    for (int j = 2; j > -1; j--) {
      if (dec1.bits[j] > dec2.bits[j]) {
        res = MORE;
        j = -1;
      } else if (dec1.bits[j] < dec2.bits[j]) {
        res = LESS;
        j = -1;
      }
    }
  return res;
}
int des_comparison_mantissa_bd(big_d dec1, big_d dec2) {
  int tmp = 0;
  int res = EQUAL;
  for (int i = 0; i < 6; i++) tmp |= dec1.bits[i] ^ dec2.bits[i];
  if (tmp)
    for (int j = 5; j > -1; j--) {
      if (dec1.bits[j] > dec2.bits[j]) {
        res = MORE;
        j = -1;
      } else if (dec1.bits[j] < dec2.bits[j]) {
        res = LESS;
        j = -1;
      }
    }
  return res;
}

int des_div_mantissa_exp(s21_decimal a, s21_decimal b, s21_decimal* res) {
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  int bits1 = 95, bits2 = 95;
  for (; !getbit(a, bits1) && 0 < bits1;) bits1--;
  for (; !getbit(b, bits2) && 0 < bits2;) bits2--;
  s21_decimal tmp = b;
  des_shift_left(&tmp, bits1 - bits2);
  if (des_comparison_mantissa(tmp, b) == MORE) {
    des_shift_right(&tmp, 1);
    bits1--;
  }
  *res = tmp;
  return bits1 - bits2;
}
int des_div_mantissa_exp_bd(big_d a, big_d b, big_d* res) {
  // for (int i = 0; i < 6; i++) res->bits[i] = 0;
  int bits1 = 191, bits2 = 191;
  for (; !getbit_bd(a, bits1) && 0 < bits1;) bits1--;
  for (; !getbit_bd(b, bits2) && 0 < bits2;) bits2--;
  big_d tmp = b;
  des_shift_left_bd(&tmp, bits1 - bits2);
  if (des_comparison_mantissa_bd(tmp, b) == MORE) {
    des_shift_right_bd(&tmp, 1);
    bits1--;
  }
  *res = tmp;
  return bits1 - bits2;
}

s21_decimal des_round_div_mantissa(s21_decimal a, s21_decimal b,
                                   s21_decimal* res, int round) {
  s21_decimal ost_c = a, res_r = {{0, 0, 0, 0}}, ost = {{2, 0, 0, 0}},
              nul = {{0, 0, 0, 0}}, mod = {{0, 0, 0, 0}};
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  des_shift_left(&ost_c, 1);
  if (round == ROUND) {
    des_div_mantissa(ost_c, b, &res_r, &mod, NO_ROUND);
    des_add_mantissa(*res, res_r, res);
  } else if (round == ROUND_B) {
    des_div_mantissa(ost_c, ost, &res_r, &ost, NO_ROUND);
    if (des_comparison_mantissa(nul, ost) != EQUAL) {
      des_div_mantissa(ost_c, b, &res_r, &mod, NO_ROUND);
      des_add_mantissa(*res, res_r, res);
    }
  }
  return nul;
}
big_d des_round_div_mantissa_bd(big_d a, big_d b, big_d* res, int round) {
  big_d ost_c = a, res_r = {{0, 0, 0, 0, 0, 0}}, ost = {{2, 0, 0, 0, 0, 0}},
        nul = {{0, 0, 0, 0, 0, 0}}, mod = {{0, 0, 0, 0, 0, 0}};
  des_shift_left_bd(&ost_c, 1);
  if (round == ROUND) {
    des_div_mantissa_bd(ost_c, b, &res_r, &mod, NO_ROUND);
    des_add_mant_big(*res, res_r, res);
  } else if (round == ROUND_B) {
    des_div_mantissa_bd(ost_c, ost, &res_r, &ost, NO_ROUND);
    if (des_comparison_mantissa_bd(nul, ost) != EQUAL) {
      des_div_mantissa_bd(ost_c, b, &res_r, &mod, NO_ROUND);
      des_add_mant_big(*res, res_r, res);
    }
  }
  return nul;
}

int des_r_div_mant(s21_decimal ost, s21_decimal b, s21_decimal* result) {
  s21_decimal ost_c = ost, res_r = {{0, 0, 0, 0}}, tmp = {{0, 0, 0, 0}};
  s21_decimal b2 = b;
  // for (int i = 0; i < 4; i++) result->bits[i] = 0;
  int err = ten_func(*result, &tmp), i = 0, even = !getbit(*result, 0);
  int exp = des_get_exp(*result);
  while (!err && des_m_nul(ost_c))
    if (!(err = ten_func(*result, &tmp))) {
      ten_func(*result, result);
      i++;
      ten_func(ost_c, &ost_c);
      des_div_mantissa(ost_c, b2, &res_r, &ost_c, NO_ROUND);
      des_add_mantissa(*result, res_r, result);
      even = !getbit(*result, 0);
    }
  s21_decimal fiv = {{5, 0, 0, 0}}, one = {{1, 0, 0, 0}};
  if (des_comparison_mantissa(res_r, fiv) != 2 && !even)
    des_add_mantissa(one, *result, result);
  if (!exp) des_set_exp(result, exp + i);
  return err;
}
int des_r_div_mant_bd(big_d ost, big_d b, big_d* result) {
  big_d ost_c = ost, res_r = {{0, 0, 0, 0, 0, 0}}, tmp = {{0, 0, 0, 0, 0, 0}};
  big_d b2 = b;
  // for (int i = 0; i < 6; i++) result->bits[i] = 0;
  int err = ten_func_bd(*result, &tmp), i = 0, even = !getbit_bd(*result, 0);
  while (!err && des_m_nul_bd(ost_c))
    if (!(err = ten_func_bd(*result, &tmp))) {
      ten_func_bd(*result, result);
      i++;
      ten_func_bd(ost_c, &ost_c);
      des_div_mantissa_bd(ost_c, b2, &res_r, &ost_c, NO_ROUND);
      des_add_mant_big(*result, res_r, result);
      even = !getbit_bd(*result, 0);
    }
  big_d fiv = {{5, 0, 0, 0, 0, 0}}, one = {{1, 0, 0, 0, 0, 0}};
  if (des_comparison_mantissa_bd(res_r, fiv) != 2 && !even)
    des_add_mant_big(one, *result, result);
  return err;
}

int des_div_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal* res,
                     s21_decimal* mod, int round) {
  s21_decimal a = dec1, mod2 = {{0, 0, 0, 0}}, b = dec2;
  // for (int i = 0; i < 4; i++) res->bits[i] = mod->bits[i] = 0;
  s21_dec_null(res);
  int i = 0, err = RES_OK, nulll = !des_comparison_mantissa(dec2, mod2);
  if (nulll) err = RES_NULL;
  if (!err && des_comparison_mantissa(b, a) == 1)
    *mod = a;
  else {
    while (des_comparison_mantissa(a, b) != LESS && !err) {
      s21_decimal c = {{0, 0, 0, 0}}, tmp = {{1, 0, 0, 0}};
      i = des_div_mantissa_exp(a, b, &c);
      err = des_shift_left(&tmp, i);
      err = des_add_mantissa(*res, tmp, res);
      des_sub_mantissa(a, c, mod);
      a = *mod;
    }
    if (round != ROUND_MOD && !err)
      a = des_round_div_mantissa(a, b, res, round);
    if (round == ROUND_MOD && !err) des_r_div_mant(a, b, res);
  }
  if (err) s21_dec_null(res);
  return err;
}
int des_div_mantissa_bd(big_d dec1, big_d dec2, big_d* res, big_d* mod,
                        int round) {
  // for (int i = 0; i < 6; i++) res->bits[i] = mod->bits[i] = 0;
  big_d a = dec1, mod2 = {{0, 0, 0, 0, 0, 0}}, b = dec2;
  s21_dec_null_bd(res);
  int i = 0, err = RES_OK, nulll = !des_comparison_mantissa_bd(dec2, mod2);
  if (nulll) err = RES_NULL;
  if (!err && des_comparison_mantissa_bd(b, a) == 1)
    *mod = a;
  else {
    while (des_comparison_mantissa_bd(a, b) != LESS && !err) {
      big_d c = {{0, 0, 0, 0, 0, 0}}, tmp = {{1, 0, 0, 0, 0, 0}};
      i = des_div_mantissa_exp_bd(a, b, &c);
      err = des_shift_left_bd(&tmp, i);
      err = des_add_mant_big(*res, tmp, res);
      des_sub_mantissa_bd(a, c, mod);
      a = *mod;
    }
    if (round != ROUND_MOD && !err)
      a = des_round_div_mantissa_bd(a, b, res, round);
    if (round == ROUND_MOD && !err) des_r_div_mant_bd(a, b, res);
  }
  if (err) s21_dec_null_bd(res);
  return err;
}

int des_sign_mant(s21_decimal dec1, s21_decimal dec2) {
  int sign_a = getbit(dec1, 127), sign_b = getbit(dec2, 127);
  int sign = sign_a + sign_b;
  return sign == 2 ? 0 : sign;
}

int des_mul_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal* res) {
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  s21_decimal a = dec1, b = dec2, tmp = {{0, 0, 0, 0}};
  int err = RES_OK;
  for (int i = 0; i < 96; i++)
    if (getbit(a, i)) {
      b = dec2;
      if (des_shift_left(&b, i))
        err = RES_OVERFLOW;
      else if (des_add_mantissa(b, tmp, &tmp))
        err = RES_OVERFLOW;
    }
  *res = tmp;
  return err;
}

int des_mul_mant_big(s21_decimal dec1, s21_decimal dec2, s21_decimal* res) {
  // for (int i = 0; i < 6; i++) res->bits[i] = 0;
  s21_decimal a = dec1, b = dec2;
  big_d tmp2 = {{0, 0, 0, 0, 0, 0}}, a2 = {{0, 0, 0, 0, 0, 0}},
        b2 = {{0, 0, 0, 0, 0, 0}}, b3 = {{0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) a2.bits[i] = a.bits[i];
  for (int i = 0; i < 3; i++) b2.bits[i] = b3.bits[i] = b.bits[i];
  int expa = des_get_exp(a), expb = des_get_exp(b), err = RES_OK;
  int exp = expa + expb;
  for (int i = 0; i < 192; i++)
    if (getbit_bd(a2, i)) {
      b2 = b3;
      if (des_shift_left_bd(&b2, i))
        err = RES_OVERFLOW;
      else if (des_add_mant_big(b2, tmp2, &tmp2))
        err = RES_OVERFLOW;
    }
  while (exp > 28) {
    exp -= 1;
    big_d ten = {{10, 0, 0, 0, 0, 0}}, fiv = {{5, 0, 0, 0, 0, 0}},
          one = {{1, 0, 0, 0, 0, 0}}, ost = {{0, 0, 0, 0, 0, 0}};
    des_div_mantissa_bd(tmp2, ten, &tmp2, &ost, NO_ROUND);
    if (des_comparison_mantissa_bd(ost, fiv) != LESS && getbit_bd(tmp2, 0))
      des_add_mant_big(one, tmp2, &tmp2);
  }
  des_set_exp(res, exp);
  return err;
}

int ten_func(s21_decimal ten, s21_decimal* ten_res) {
  s21_decimal tmp1 = ten, tmp2 = ten;
  // for (int i = 0; i < 4; i++) ten_res->bits[i] = 0;
  int err = des_shift_left(&tmp1, 3);
  err |= des_shift_left(&tmp2, 1);
  err |= des_add_mantissa(tmp1, tmp2, ten_res);
  if (err) *ten_res = ten;
  return err;
}
int ten_func_bd(big_d ten, big_d* ten_res) {
  big_d tmp1 = ten, tmp2 = ten;
  // for (int i = 0; i < 6; i++) ten_res->bits[i] = 0;
  int err = des_shift_left_bd(&tmp1, 3);
  err |= des_shift_left_bd(&tmp2, 1);
  err |= des_add_mant_big(tmp1, tmp2, ten_res);
  if (err) *ten_res = ten;
  return err;
}

void des_denomenator(s21_decimal* dec1, s21_decimal* dec2) {
  s21_decimal a = *dec1, b = *dec2, ten = {{10, 0, 0, 0}}, res = {{0, 0, 0, 0}},
              mod = {{0, 0, 0, 0}};
  a = des_is_minus_null(a);
  b = des_is_minus_null(b);
  int exp_r = 0, bits1 = 95, s1 = getbit(a, 127), s2 = getbit(b, 127);
  int exp_a = des_get_exp(*dec1), exp_b = des_get_exp(*dec2);
  for (; !getbit(a, bits1) && 0 < bits1;) bits1--;
  if (exp_a < exp_b) {
    if (1 < (exp_r = exp_b - exp_a))
      for (int i = 0; i < exp_r - 1; i++) ten_func(ten, &ten);
    if (!des_mul_mantissa(a, ten, &res)) {
      des_set_exp(&res, exp_a + exp_r);
      a = res;
    } else {
      des_div_mantissa(b, ten, &b, &mod, ROUND);
      des_set_exp(&b, exp_b - exp_r);
    }
    *dec1 = a;
    *dec2 = b;
    des_set_bit(dec1, 127, s1);
    des_set_bit(dec2, 127, s2);
  } else if (exp_a > exp_b)
    des_denomenator(dec2, dec1);
}

s21_decimal des_is_minus_null(s21_decimal dec) {
  s21_decimal nul = {{0, 0, 0, des_get_exp(dec) << 16}}, tmp = dec;
  return des_comparison_mantissa(tmp, nul) == 0 && getbit(tmp, 127) ? nul : tmp;
}

int des_add_sign_mant(s21_decimal dec1, s21_decimal dec2, s21_decimal* res) {
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  s21_decimal a = dec1, b = dec2;
  int sign_a = getbit(a, 127), sign_b = getbit(b, 127);
  int err = RES_OK, comp = des_comparison_mantissa(a, b);
  if (!sign_a && !sign_b) {
    if (des_add_mantissa(a, b, res)) err = RES_OVERFLOW;
  } else if (sign_a && sign_b) {
    if (!des_add_mantissa(a, b, res))
      des_set_bit(res, 127, 1);
    else
      err = RES_OVERFLOW;
  } else if (sign_a != sign_b) {
    if (comp == LESS) {
      des_sub_mantissa(b, a, res);
      if (sign_b) des_set_bit(res, 127, 1);
    } else if (comp == MORE)
      des_sub_mantissa(a, b, res);
  }
  return err;
}

int des_sub_sign_mant(s21_decimal dec1, s21_decimal dec2, s21_decimal* res,
                      int* exp) {
  // for (int i = 0; i < 4; i++) res->bits[i] = 0;
  s21_decimal a = dec1, b = dec2, tmp = {{0, 0, 0, 0}};
  int sign_a = getbit(a, 127), sign_b = getbit(b, 127), err = 0;
  int comp = des_comparison_mantissa(a, b);
  if (!sign_a && !sign_b)
    if (comp == LESS) {
      des_sub_mantissa(b, a, res);
      des_set_bit(res, 127, 1);
    } else
      des_sub_mantissa(a, b, res);
  else if (sign_a && sign_b) {
    if (comp == LESS)
      des_sub_mantissa(b, a, res);
    else
      des_sub_mantissa(a, b, res);
    if (des_comparison_mantissa(a, b) == 1) des_set_bit(res, 127, 1);
  } else {
    while (des_add_mantissa(a, b, &tmp) && *exp)  //*result = tmp;
      exp_round_left(&a, &b, exp);
    err = des_add_mantissa(a, b, res);
    if (sign_a && !sign_b) des_set_bit(res, 127, 1);
    if (!des_m_nul(a) && !sign_a && !sign_b) des_set_bit(res, 127, 1);
  }
  if (!des_m_nul(*res)) s21_dec_null(res);
  return err;
}

int des_m_nul(s21_decimal dec) {
  return (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) ? 0 : 1;
}
int des_m_nul_bd(big_d dec) {
  return (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0 &&
          dec.bits[3] == 0 && dec.bits[4] == 0 && dec.bits[5] == 0)
             ? 0
             : 1;
}

void des_end_func(s21_decimal* dec, int exp, int err) {
  if (des_m_nul(*dec)) des_set_exp(dec, exp);
  if (err) s21_dec_null(dec);
}

// int des_less_one(s21_decimal dec) {
//   int exp = des_get_exp(dec), tmp = 0;
//   while (exp) {
//     exp--;
//     des_shift_right(&dec, 3);
//     des_shift_right(&dec, 1);
//   }
//   for (int i = 0; i < 2; i++) tmp |= dec.bits[i] ^ dec.bits[i + 1];
//   return tmp < 1;
// }

// int des_equal(s21_decimal a, s21_decimal b) {
//   return !des_comparison_mantissa(a, b) && des_get_exp(a) == des_get_exp(b);
// }

void des_del_nul(s21_decimal* res, int* exp) {
  s21_decimal tmp = {{0, 0, 0, 0}}, ten = {{10, 0, 0, 0}}, ost = {{0, 0, 0, 0}};
  des_div_mantissa(*res, ten, &tmp, &ost, NO_ROUND);
  while (*exp && ost.bits[0] == 0) {
    des_div_mantissa(*res, ten, res, &tmp, NO_ROUND);
    des_div_mantissa(*res, ten, &tmp, &ost, NO_ROUND);
    *exp -= 1;
  }
}

void des_dec_to_str(s21_decimal* dec, char* res) {
  des_mantisa_dec_to_str(dec, res, DECIMAL);
  int exp = des_get_exp(*dec);
  int len = strlen(res);
  if (len == exp) {
    des_rev_str(res);
    res[len] = '.';
    res[len + 1] = '0';
    res[len + 2] = 0;
    len = strlen(res);
    des_rev_str(res);
  } else if (exp > 0) {
    res[len] = '0';
    res[len + 1] = 0;
    len = strlen(res);
    int start = len - exp - 1;
    char nul[100] = {0};
    if (start < 0) {
      start *= -1;
      start++;
      for (int i = 0; i < start; i++) nul[i] = '0';
      strcat(nul, res);
      strcpy(res, nul);
      len = strlen(res);
      start = len - exp - 1;
    }
    for (int i = len; i > start; i--) res[i] = res[i - 1];
    if (res[0] == '0')
      res[1] = '.';
    else
      res[start] = '.';
    if (getbit(*dec, 127)) {
      for (int i = len; i > 0; i--) res[i] = res[i - 1];
      res[0] = '-';
    } else
      res[len] = 0;
  } else {
    if (getbit(*dec, 127)) {
      for (int i = strlen(res); i > 0; i--) res[i] = res[i - 1];
      res[0] = '-';
    }
  }
}

void char_str_to_decimal(char* buf, s21_decimal* dec) {
  s21_dec_null(dec);
  int tchk = strcspn(buf, ".");
  if (tchk == (int)strlen(buf)) tchk = 0;
  des_set_bit(dec, 127, buf[0] == '-' ? 1 : 0);
  if (tchk != 0) tchk = strlen(buf) - tchk - 1;
  char* exp = calloc(20, sizeof(char));
  if (exp != NULL) {
    itoa(tchk, exp, 2);
    int len = strlen(exp);
    des_rev_str(exp);
    if (len < 8) {
      for (int i = len; i != 8; i++) exp[i] = '0';
      exp[8] = 0;
    }
    des_rev_str(exp);
    for (int i = 7, j = 112; i > -1; j++, i--) {
      if (strlen(exp) == 7 && i == 7) j--;
      des_set_bit(dec, j, exp[i] == '1' ? 1 : 0);
    }
    free(exp);
  }
  char* mantis = calloc(100, sizeof(char));
  if (mantis != NULL) {
    for (int i = 0, j = 0; buf[i] > 0;) {
      if (buf[i] == '-' || buf[i] == '.')
        i++;
      else if (j == 0 && buf[i] == '0')
        i++;
      else
        mantis[j++] = buf[i++];
    }
    char_manstis_to_dec(mantis, dec);
    free(mantis);
  }
}

////////// Далее идут вспомогательные функции для ввода и вывода в/из децимал

void des_mantisa_dec_to_str(s21_decimal* dec, char* str1, int d_enum) {
  char* str2 = calloc(100, sizeof(char));
  char* res = calloc(100, sizeof(char));
  str1[0] = '0';
  d_int max = 0, min = 0;
  if (d_enum == STEPEN) {
    max = 120;  // биты степени
    min = 112;  // биты степени
    // s21_printf_decimal(*dec);
  } else if (d_enum == DECIMAL) {
    max = 96;  // биты децимал
    min = 0;   // биты децимал
  }
  for (d_int i = min; i < max; i++)
    if (getbit(*dec, i)) {
      d_int x = i;
      if (d_enum == STEPEN) x -= 112;
      des_2_v_pow(str2, x);
      des_str1_plus_str2(str1, str2, res);
      strcpy(str1, res);
    }
  des_rev_str(str1);
  free(res);
  free(str2);
}

void des_str_x2(char* str, char* res) {
  int len = strlen(str);
  int tmp = 0, i = 0, ra3 = 0;
  for (; i < len; i++) {
    tmp = (str[i] - 48) * 2 + ra3;
    if (tmp > 9) ra3 = 1;
    res[i] = tmp % 10 + 48;
    if (tmp < 10) ra3 = 0;
  }
  if (ra3 > 0) res[i] = ra3 + 48;
}

void des_2_v_pow(char* str, int step) {
  size_t len = strlen(str);
  for (size_t i = 0; i < len; i++) str[i] = 0;
  str[0] = '2';
  if (step == 0)
    str[0] = '1';
  else if (step == 1)
    str[0] = '2';
  else
    for (int i = 0; i < step - 1; i++) des_str_x2(str, str);
}

void des_str1_plus_str2(char* str1, char* str2, char* res) {
  int len = strlen(str1);
  int len2 = strlen(str2);
  int tmp = 0, i = 0, j = 0, ra3 = 0;
  for (; i < len && j < len2; i++, j++) {
    tmp = (str1[i] - 48) + (str2[j] - 48) + ra3;
    if (tmp > 9) ra3 = 1;
    res[i] = tmp % 10 + 48;
    if (tmp < 10) ra3 = 0;
  }
  if (ra3 > 0 && len == len2) res[i] = ra3-- + 48;
  if (len < len2) {
    for (int i = len; i < len2; i++) {
      tmp = (str2[i] - 48) + ra3;
      if (tmp > 9) ra3 = 1;
      res[i] = tmp % 10 + 48;
      if (tmp < 10) ra3 = 0;
    }
  } else if (len > len2) {
    for (int i = len2; i < len; i++) {
      tmp = (str1[i] - 48) + ra3;
      if (tmp > 9) ra3 = 1;
      res[i] = tmp % 10 + 48;
      if (tmp < 10) ra3 = 0;
    }
  }
  if (ra3 > 0 && len != len2) {
    res[strlen(res)] = ra3-- + 48;
  }
}

char* itoa(int value, char* result, int base) {
  int error = 0;
  // check that the base if valid
  if (base < 2 || base > 36) {
    *result = '\0';
    error = 1;
  }
  if (!error) {
    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;
    do {
      tmp_value = value;
      value /= base;
      *ptr++ =
          "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstu"
          "vw"
          "xyz"[35 + (tmp_value - value * base)];
    } while (value);
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr-- = *ptr1;
      *ptr1++ = tmp_char;
    }
  }
  return result;
}

int is_less_mod(s21_decimal val1, s21_decimal val2) {
  int result = 0;
  s21_DeleteBit(&val1, 127);
  s21_DeleteBit(&val2, 127);
  result = s21_is_less(val1, val2);
  return (result);
}

void char_manstis_to_dec(char* str, s21_decimal* dec) {
  char* str1 = str;
  for (int bit = 0, bits1 = 0, bits2 = 0, int_to = 0; bits1 < 3;) {
    int len = strlen(str1) - 1;
    if (len == -1) {
      dec->bits[bits1] = int_to;
      break;
    }
    char* str2 = str1 + len;
    if ((((int)str1[len]) % 2) == 0) {
      bit = 0;
    } else {
      bit = 1;
      str1[len] = ((str1[len] - '0') - 1 + '0');
    }
    while (str1 - 1 != str2) {
      int tmp = *str2 - '0';
      if (str1 != str2)
        if ((*(str2 - 1) - '0') % 2 == 1) {
          *(str2 - 1) = (*(str2 - 1) - '0') - 1 + '0';
          tmp += 10;
        }
      *str2 = tmp / 2 + '0';
      if (str1 == str2) {
        if (*str1 - '0' == 0) {
          str1++;
        }
        break;
      }
      str2--;
    }
    bit = bit << bits2;
    int_to = int_to | bit;
    bits2++;
    if (bits2 == 32) {
      bits2 = 0;
      dec->bits[bits1] = int_to;
      bits1++;
      int_to = 0;
    }
  }
}

// int hex_to_int(char* buf, int size) {
//   int sum = 0;
//   for (int i = size - 1, j = 0; i > -1; i--, j++)
//     if (buf[i] == '1') sum += pow(2, j);
//   return sum;
// }

void des_rev_str(char* str) {
  d_int len = strlen(str) - 1;
  for (d_int i = 0, j = len; i <= len / 2; i++, j--) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

// void s21_from_decimal_to_int_mantisa(s21_decimal value) {
//   char* mantis = calloc(100, sizeof(char));
//   des_mantisa_dec_to_str(&value, mantis, DECIMAL);
//   printf("\nDESET MANTISA: %s", mantis);
//   free(mantis);
// }

int s21_isnull_dec(s21_decimal value) {
  int flag = 1;
  for (int i = 0; i < 4; i++) {
    if (value.bits[i] != 0) {
      flag = 0;
    }
  }
  return (flag);
}
