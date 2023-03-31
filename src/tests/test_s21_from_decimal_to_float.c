#include "unit.h"

START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_exp(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_SetBit(&val, 127);
  s21_set_exp(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(decimal_to_float_2) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -3.14;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 0;
  number.bits[2] = 0;
  number.bits[3] |= SIGN;
  s21_set_exp(&number, 2);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.7f", float_result);
  sprintf(s21_result, "%.7f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_3) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -5792277640.493418938682;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 314;
  number.bits[2] = 314;
  number.bits[3] |= SIGN;
  s21_set_exp(&number, 12);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_4) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = 5792277640.493418938682;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 314;
  number.bits[2] = 314;
  s21_set_exp(&number, 12);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_5) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = 1980704062.8566084398385987584;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 0;
  number.bits[1] = 0;
  number.bits[2] = 1073741824;
  s21_set_exp(&number, 19);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_6) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -1980704062.8566084398385987584;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 0;
  number.bits[1] = 0;
  number.bits[2] = 1073741824;
  number.bits[3] |= SIGN;
  s21_set_exp(&number, 19);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_7) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -1980704063.3177770417887117312;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 1073741824;
  number.bits[1] = 1073741824;
  number.bits[2] = 1073741824;
  number.bits[3] |= SIGN;
  s21_set_exp(&number, 19);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST
Suite *suite_s21_from_decimal_to_float() {
  Suite *s = suite_create("s21_from_decimal_to_float");
  TCase *temp = tcase_create("test_s21_from_decimal_to_float");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, from_decimal_to_float_0);
  tcase_add_test(temp, from_decimal_to_float_1);
  tcase_add_test(temp, decimal_to_float_2);
  tcase_add_test(temp, decimal_to_float_3);
  tcase_add_test(temp, decimal_to_float_4);
  tcase_add_test(temp, decimal_to_float_5);
  tcase_add_test(temp, decimal_to_float_6);
  tcase_add_test(temp, decimal_to_float_7);
  return s;
}
