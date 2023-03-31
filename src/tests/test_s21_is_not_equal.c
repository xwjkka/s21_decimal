#include "unit.h"

START_TEST(is_not_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_DeleteBit(&val2, 127);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val2, 127);
  s21_SetBit(&val1, 33);
  s21_SetBit(&val2, 33);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 3);
  s21_SetBit(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 3);
  s21_SetBit(&val2, 4);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 3);
  s21_SetBit(&val2, 4);
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

Suite *suite_s21_is_not_equal() {
  Suite *s = suite_create("s21_is_not_equal");
  TCase *temp = tcase_create("test_s21_is_not_equal");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, is_not_equal_0);
  tcase_add_test(temp, is_not_equal_1);
  tcase_add_test(temp, is_not_equal_2);
  tcase_add_test(temp, is_not_equal_3);
  tcase_add_test(temp, is_not_equal_4);
  tcase_add_test(temp, is_not_equal_5);
  tcase_add_test(temp, is_not_equal_6);
  tcase_add_test(temp, is_not_equal_7);
  tcase_add_test(temp, is_not_equal_8);

  return s;
}
