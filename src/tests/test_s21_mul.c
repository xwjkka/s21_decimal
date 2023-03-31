#include "unit.h"

START_TEST(mul_01) {
  s21_decimal val1 = {{2958030960, 223845272, 0, 18 << 16}};
  s21_decimal val2 = {{2431504396, 46, 0, 11 << 16}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  // for (int i = 95; i > -1; i--) printf("%d", getbit(res, i));
  // printf("\n");
}
END_TEST

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_set_exp(&val1, 127);
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_set_exp(&val2, 127);
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_exp(&val1, 1);
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{200, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_exp(&val2, 1);
  s21_set_exp(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_14) {
  s21_decimal val2 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val1 = {{20, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_exp(&val2, 1);
  s21_set_exp(&val2, 2);
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

Suite *suite_s21_mul() {
  Suite *s = suite_create("s21_mul");
  TCase *temp = tcase_create("test_s21_mul");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, mul_01);
  tcase_add_test(temp, mul_0);
  tcase_add_test(temp, mul_1);
  tcase_add_test(temp, mul_2);
  tcase_add_test(temp, mul_3);
  tcase_add_test(temp, mul_4);
  tcase_add_test(temp, mul_5);
  tcase_add_test(temp, mul_6);
  tcase_add_test(temp, mul_7);
  tcase_add_test(temp, mul_8);
  tcase_add_test(temp, mul_9);
  tcase_add_test(temp, mul_10);
  tcase_add_test(temp, mul_11);
  tcase_add_test(temp, mul_12);
  tcase_add_test(temp, mul_13);
  tcase_add_test(temp, mul_14);

  return s;
}
