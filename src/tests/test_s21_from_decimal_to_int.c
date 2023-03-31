#include "unit.h"

START_TEST(from_decimal_to_int_0) {
  int res = (int)3.14;
  int s21_int = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 0;
  number.bits[2] = 0;
  s21_set_exp(&number, 2);
  s21_from_decimal_to_int(number, &s21_int);
  ck_assert_int_eq(res, s21_int);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  int res = 123456789;
  int s21_int = 0;
  s21_decimal number = {0};
  number.bits[0] = 123456789;
  number.bits[1] = 0;
  number.bits[2] = 0;
  s21_from_decimal_to_int(number, &s21_int);
  ck_assert_int_eq(res, s21_int);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  int res = (int)-4294;
  int s21_int = 0;
  s21_decimal number = {0};
  number.bits[0] = 4294;
  number.bits[1] = 0;
  number.bits[2] = 0;
  s21_SetBit(&number, 127);
  s21_from_decimal_to_int(number, &s21_int);
  ck_assert_int_eq(res, s21_int);
}
END_TEST

START_TEST(from_decimal_to_int_error_0) {
  int s21_int = 0;
  s21_decimal number = {0};
  number.bits[0] = 123456789;
  number.bits[1] = 123456789;
  number.bits[2] = 123456789;
  ck_assert_int_eq(1, s21_from_decimal_to_int(number, &s21_int));
}
END_TEST

Suite *suite_s21_from_decimal_to_int() {
  Suite *s = suite_create("s21_from_decimal_to_int");
  TCase *temp = tcase_create("test_s21_from_decimal_to_int");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, from_decimal_to_int_0);
  tcase_add_test(temp, from_decimal_to_int_1);
  tcase_add_test(temp, from_decimal_to_int_2);
  tcase_add_test(temp, from_decimal_to_int_error_0);

  return s;
}
