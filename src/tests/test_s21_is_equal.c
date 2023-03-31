#include "unit.h"

START_TEST(is_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  s21_DeleteBit(&val2, 127);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val2, 127);
  s21_SetBit(&val1, 33);
  s21_SetBit(&val2, 33);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 3);
  s21_SetBit(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 3);
  s21_SetBit(&val2, 4);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 3);
  s21_SetBit(&val2, 4);
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(equal_9) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 3782;
  d.bits[1] = 1512;
  d.bits[2] = 123;
  s21_set_exp(&d, 12);
  d1.bits[0] = 3782;
  d1.bits[1] = 1512;
  d1.bits[2] = 123;
  s21_set_exp(&d, 10);
  ck_assert_int_eq(s21_is_equal(d, d1), 0);
}
END_TEST

START_TEST(equal_10) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 3782;
  d.bits[1] = 1512;
  d.bits[2] = 123;
  s21_set_exp(&d, 12);
  d1.bits[0] = 3782;
  d1.bits[1] = 1512;
  d1.bits[2] = 123;
  s21_set_exp(&d1, 12);
  ck_assert_int_eq(s21_is_equal(d, d1), 1);
}
END_TEST

START_TEST(equal_11) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 3782;
  d.bits[1] = 1512;
  d.bits[2] = 123;
  d.bits[3] |= SIGN;
  s21_set_exp(&d, 12);
  d1.bits[0] = 3782;
  d1.bits[1] = 1512;
  d1.bits[2] = 123;
  d1.bits[3] |= SIGN;
  s21_set_exp(&d1, 12);
  ck_assert_int_eq(s21_is_equal(d, d1), 1);
}
END_TEST

START_TEST(equal_12) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 0;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 0;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  ck_assert_int_eq(s21_is_equal(d, d1), 1);
}
END_TEST

START_TEST(equal_13) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2000;
  d.bits[1] = 0;
  d.bits[2] = 0;
  s21_set_exp(&d, 2);
  d1.bits[0] = 20;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  ck_assert_int_eq(s21_is_equal(d, d1), 1);
}
END_TEST

START_TEST(equal_14) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2020;
  d.bits[1] = 0;
  d.bits[2] = 0;
  s21_set_exp(&d, 2);
  d1.bits[0] = 201;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  s21_set_exp(&d1, 1);
  ck_assert_int_eq(s21_is_equal(d, d1), 0);
}
END_TEST

START_TEST(equal_15) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 20;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 2000;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  s21_set_exp(&d1, 2);
  ck_assert_int_eq(s21_is_equal(d, d1), 1);
}
END_TEST

Suite *suite_s21_is_equal() {
  Suite *s = suite_create("s21_is_equal");
  TCase *temp = tcase_create("test_s21_is_equal");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, is_equal_0);  // s21_is_equal
  tcase_add_test(temp, is_equal_1);
  tcase_add_test(temp, is_equal_2);
  tcase_add_test(temp, is_equal_3);
  tcase_add_test(temp, is_equal_4);
  tcase_add_test(temp, is_equal_5);
  tcase_add_test(temp, is_equal_6);
  tcase_add_test(temp, is_equal_7);
  tcase_add_test(temp, is_equal_8);
  tcase_add_test(temp, equal_9);
  tcase_add_test(temp, equal_10);
  tcase_add_test(temp, equal_11);
  tcase_add_test(temp, equal_12);
  tcase_add_test(temp, equal_13);
  tcase_add_test(temp, equal_14);
  tcase_add_test(temp, equal_15);
  return s;
}
