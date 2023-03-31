#include "unit.h"

START_TEST(is_less_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exp(&val1, 11);
  s21_set_exp(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exp(&val1, 10);
  s21_set_exp(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_SetBit(&val1, 127);
  s21_SetBit(&val2, 127);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_SetBit(&val2, 127);
  s21_SetBit(&val1, 83);
  s21_set_exp(&val1, 12);
  s21_set_exp(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_SetBit(&val2, 127);
  s21_SetBit(&val1, 83);
  s21_SetBit(&val2, 83);
  s21_set_exp(&val1, 10);
  s21_set_exp(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_SetBit(&val2, 127);
  s21_SetBit(&val1, 83);
  s21_set_exp(&val1, 10);
  s21_set_exp(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_DeleteBit(&val2, 127);
  s21_SetBit(&val1, 83);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_DeleteBit(&val2, 127);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

Suite *suite_s21_is_less() {
  Suite *s = suite_create("s21_is_less");
  TCase *temp = tcase_create("test_s21_is_less");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, is_less_0);
  tcase_add_test(temp, is_less_1);
  tcase_add_test(temp, is_less_2);
  tcase_add_test(temp, is_less_3);
  tcase_add_test(temp, is_less_4);
  tcase_add_test(temp, is_less_5);
  tcase_add_test(temp, is_less_6);
  tcase_add_test(temp, is_less_7);
  tcase_add_test(temp, is_less_8);
  tcase_add_test(temp, is_less_9);
  tcase_add_test(temp, is_less_10);
  tcase_add_test(temp, is_less_11);
  tcase_add_test(temp, is_less_12);

  return s;
}
