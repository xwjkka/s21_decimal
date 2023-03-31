#include "unit.h"

START_TEST(is_greater_or_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exp(&val1, 11);
  s21_set_exp(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exp(&val1, 10);
  s21_set_exp(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_SetBit(&val1, 127);
  s21_SetBit(&val2, 127);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

Suite *suite_s21_is_greater_or_equal() {
  Suite *s = suite_create("s21_is_greater_or_equal");
  TCase *temp = tcase_create("test_s21_is_greater_or_equal");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, is_greater_or_equal_0);
  tcase_add_test(temp, is_greater_or_equal_1);
  tcase_add_test(temp, is_greater_or_equal_2);
  tcase_add_test(temp, is_greater_or_equal_3);
  tcase_add_test(temp, is_greater_or_equal_4);
  tcase_add_test(temp, is_greater_or_equal_5);
  tcase_add_test(temp, is_greater_or_equal_6);
  tcase_add_test(temp, is_greater_or_equal_7);

  return s;
}
