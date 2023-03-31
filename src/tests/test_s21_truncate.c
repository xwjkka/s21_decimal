#include "unit.h"

START_TEST(truncate_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  s21_set_exp(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

Suite *suite_s21_truncate() {
  Suite *s = suite_create("s21_truncate");
  TCase *temp = tcase_create("test_s21_truncate");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, truncate_0);
  tcase_add_test(temp, truncate_1);
  tcase_add_test(temp, truncate_2);
  tcase_add_test(temp, truncate_3);

  return s;
}
