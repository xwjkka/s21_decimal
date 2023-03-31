#include "unit.h"

START_TEST(from_float_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = -1234.567993;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = 1234.567993;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(float_to_decimal_2) {
  float a = 15112345678;
  float res = 0;
  s21_decimal number = {0};
  s21_from_float_to_decimal(a, &number);
  s21_from_decimal_to_float(number, &res);
  ck_assert_float_eq(a, res);
}
END_TEST

START_TEST(float_to_decimal_3) {
  float a = -151.4214;

  s21_decimal res = {0};
  res.bits[0] = 1514214;
  res.bits[1] = 0;
  res.bits[2] = 0;
  s21_set_exp(&res, 4);
  s21_SetBit(&res, 127);

  s21_decimal number = {0};
  s21_from_float_to_decimal(a, &number);
  ck_assert_float_eq(1, s21_is_equal(number, res));
}
END_TEST

START_TEST(float_to_decimal_error_0) {
  float a = FLT_MAX;
  s21_decimal number = {0};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &number), 1);
}

END_TEST
Suite *suite_s21_from_float_to_decimal() {
  Suite *s = suite_create("s21_from_float_to_decimal");
  TCase *temp = tcase_create("test_s21_from_float_to_decimal");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, from_float_to_decimal_0);
  tcase_add_test(temp, from_float_to_decimal_1);
  tcase_add_test(temp, float_to_decimal_2);
  tcase_add_test(temp, float_to_decimal_3);
  tcase_add_test(temp, float_to_decimal_error_0);
  return s;
}
