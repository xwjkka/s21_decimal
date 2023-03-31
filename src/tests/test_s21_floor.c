#include "unit.h"

START_TEST(floor_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  s21_set_exp(&val, 5);
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 5);
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

Suite *suite_s21_floor() {
  Suite *s = suite_create("s21_floor");
  TCase *temp = tcase_create("test_s21_floor");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, floor_0);
  tcase_add_test(temp, floor_1);
  tcase_add_test(temp, floor_2);
  tcase_add_test(temp, floor_3);

  return s;
}
