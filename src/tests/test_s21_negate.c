#include "unit.h"

START_TEST(negate_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{0, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_negate(val, &res));
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_negate(val, &res));
}
END_TEST

Suite *suite_s21_negate() {
  Suite *s = suite_create("s21_negate");
  TCase *temp = tcase_create("test_s21_negate");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, negate_0);
  tcase_add_test(temp, negate_1);
  tcase_add_test(temp, negate_2);
  tcase_add_test(temp, negate_3);

  return s;
}
