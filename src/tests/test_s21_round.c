#include "unit.h"

START_TEST(round_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{7, 7, 7, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  s21_set_exp(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{25, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  s21_set_exp(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_9) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_exp(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

Suite *suite_s21_round() {
  Suite *s = suite_create("s21_round");
  TCase *temp = tcase_create("test_s21_round");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, round_0);
  tcase_add_test(temp, round_1);
  tcase_add_test(temp, round_2);
  tcase_add_test(temp, round_3);
  tcase_add_test(temp, round_4);
  tcase_add_test(temp, round_5);
  tcase_add_test(temp, round_6);
  tcase_add_test(temp, round_7);
  tcase_add_test(temp, round_8);
  tcase_add_test(temp, round_9);
  return s;
}
