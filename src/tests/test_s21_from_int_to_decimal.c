#include "unit.h"

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_long_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  long int tmp = 987654321234;
  int n = (int)tmp;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, n);
}
END_TEST

Suite *suite_s21_from_int_to_decimal() {
  Suite *s = suite_create("s21_from_int_to_decimal");
  TCase *temp = tcase_create("test_s21_from_int_to_decimal");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, from_int_to_decimal_0);
  tcase_add_test(temp, from_int_to_decimal_1);
  tcase_add_test(temp, from_int_to_decimal_long_1);

  return s;
}
