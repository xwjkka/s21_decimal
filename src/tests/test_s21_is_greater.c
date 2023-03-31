#include "unit.h"

START_TEST(is_greater_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_SetBit(&val1, 127);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exp(&val1, 11);
  s21_set_exp(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_exp(&val1, 10);
  s21_set_exp(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_SetBit(&val1, 127);
  s21_SetBit(&val2, 127);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  s21_SetBit(&val1, 127);
  s21_DeleteBit(&val2, 127);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(greater_9) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 3782;
  d.bits[1] = 1512;
  d.bits[2] = 123;
  s21_set_exp(&d, 12);
  d1.bits[0] = 3782;
  d1.bits[1] = 1512;
  d1.bits[2] = 123;
  s21_set_exp(&d1, 10);
  ck_assert_int_eq(s21_is_greater(d, d1), 0);
}
END_TEST

START_TEST(greater_10) {
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
  ck_assert_int_eq(s21_is_greater(d, d1), 0);
}
END_TEST

START_TEST(greater_11) {
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
  ck_assert_int_eq(s21_is_greater(d, d1), 0);
}
END_TEST

START_TEST(greater_12) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 0;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 0;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  ck_assert_int_eq(s21_is_greater(d, d1), 0);
}
END_TEST

START_TEST(greater_13) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2000;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 20;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  ck_assert_int_eq(s21_is_greater(d, d1), 1);
}
END_TEST

START_TEST(greater_14) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2001;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 20;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  ck_assert_int_eq(s21_is_greater(d, d1), 1);
}
END_TEST

START_TEST(greater_15) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2001;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 2001;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  d1.bits[3] |= SIGN;
  ck_assert_int_eq(s21_is_greater(d, d1), 1);
}
END_TEST

START_TEST(greater_16) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2000;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 2001;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  d1.bits[3] |= SIGN;
  ck_assert_int_eq(s21_is_greater(d, d1), 1);
}
END_TEST

START_TEST(greater_17) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 20;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d.bits[3] |= SIGN;
  d1.bits[0] = 2000;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  d1.bits[3] |= SIGN;
  ck_assert_int_eq(s21_is_greater(d, d1), 1);
}
END_TEST

START_TEST(greater_18) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 2000;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d1.bits[0] = 2001;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  ck_assert_int_eq(s21_is_greater(d, d1), 0);
}
END_TEST

START_TEST(greater_19) {
  s21_decimal d = {0};
  s21_decimal d1 = {0};
  d.bits[0] = 20;
  d.bits[1] = 0;
  d.bits[2] = 0;
  d.bits[3] |= SIGN;
  d1.bits[0] = 2001;
  d1.bits[1] = 0;
  d1.bits[2] = 0;
  d1.bits[3] |= SIGN;
  ck_assert_int_eq(s21_is_greater(d, d1), 1);
}
END_TEST

START_TEST(greater_20) {
  char *a = "79228162514264337593543950335";
  char *b = "79228162514264337593543950335";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 0);
}
END_TEST

START_TEST(greater_21) {
  char *a = "79228162514264337593543950334";
  char *b = "79228162514264337593543950.334";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 1);
}
END_TEST

START_TEST(greater_22) {
  char *a = "0";
  char *b = "-0";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 0);
}
END_TEST

START_TEST(greater_23) {
  char *a = "79228162514264337593543950334";
  char *b = "-79228162514264337593543950.334";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 1);
}
END_TEST

START_TEST(greater_24) {
  char *a = "-79228162514264337593543950334";
  char *b = "79228162514264337593543950.334";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 0);
}
END_TEST

START_TEST(greater_25) {
  char *a = "792";
  char *b = "792";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 0);
}
END_TEST

START_TEST(greater_26) {
  char *a = "792";
  char *b = "-792";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 1);
}
END_TEST

START_TEST(greater_27) {
  char *a = "-792";
  char *b = "792";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 0);
}
END_TEST

START_TEST(greater_28) {
  char *a = "-791";
  char *b = "-792";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 1);
}
END_TEST

START_TEST(greater_29) {
  char *a = "-792";
  char *b = "-792.01";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 1);
}
END_TEST

START_TEST(greater_30) {
  char *a = "-792.0100";
  char *b = "-7921.010";
  s21_decimal src = {0};
  s21_decimal dst = {0};
  char_str_to_decimal(a, &src);
  char_str_to_decimal(b, &dst);
  ck_assert_int_eq(s21_is_greater(src, dst), 1);
}
END_TEST

Suite *suite_s21_is_greater() {
  Suite *s = suite_create("s21_is_greater");
  TCase *temp = tcase_create("test_s21_is_greater");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, is_greater_0);
  tcase_add_test(temp, is_greater_1);
  tcase_add_test(temp, is_greater_2);
  tcase_add_test(temp, is_greater_3);
  tcase_add_test(temp, is_greater_4);
  tcase_add_test(temp, is_greater_5);
  tcase_add_test(temp, is_greater_6);
  tcase_add_test(temp, is_greater_7);
  tcase_add_test(temp, is_greater_8);
  tcase_add_test(temp, greater_9);
  tcase_add_test(temp, greater_10);
  tcase_add_test(temp, greater_11);
  tcase_add_test(temp, greater_12);
  tcase_add_test(temp, greater_13);
  tcase_add_test(temp, greater_14);
  tcase_add_test(temp, greater_15);
  tcase_add_test(temp, greater_16);
  tcase_add_test(temp, greater_17);
  tcase_add_test(temp, greater_18);
  tcase_add_test(temp, greater_19);

  tcase_add_test(temp, greater_20);
  tcase_add_test(temp, greater_21);
  tcase_add_test(temp, greater_22);
  tcase_add_test(temp, greater_23);
  tcase_add_test(temp, greater_24);
  tcase_add_test(temp, greater_25);
  tcase_add_test(temp, greater_26);
  tcase_add_test(temp, greater_27);
  tcase_add_test(temp, greater_28);
  tcase_add_test(temp, greater_29);
  tcase_add_test(temp, greater_30);
  return s;
}
