#include "unit.h"

START_TEST(simple) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  int result_int = 0;
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (2 % 100));
}
END_TEST

START_TEST(simple2) {
  s21_decimal val1 = {{234, 0, 0, 0}};
  s21_set_exp(&val1, 3);
  s21_decimal val2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(0.234, 100));
}
END_TEST

START_TEST(simple3) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal result_dec = {0};

  char *s = "0.234";
  char *b = "0.100";

  char_str_to_decimal(s, &dec1);
  char_str_to_decimal(b, &dec2);

  s21_mod(dec1, dec2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(0.234, 0.100));
}
END_TEST

START_TEST(simple4) {
  s21_decimal val1 = {{120234, 0, 0, 0}};
  s21_set_exp(&val1, 3);
  s21_decimal val2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(120.234, 100));
}
END_TEST

START_TEST(simple5) {
  s21_decimal val1 = {{120234, 0, 0, 0}};
  s21_set_exp(&val1, 3);
  s21_decimal val2 = {{100200, 0, 0, 0}};
  s21_set_exp(&val2, 3);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(120.234, 100.200));
}
END_TEST

START_TEST(simple6) {
  s21_decimal val1 = {{120234, 0, 0, 0}};
  s21_decimal val2 = {{100200, 0, 0, 0}};
  s21_set_exp(&val2, 3);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(120234, 100.200));
}
END_TEST

START_TEST(simple7) {
  s21_decimal val1 = {{120234, 0, 0, 0}};
  s21_decimal val2 = {{100200, 0, 0, 0}};
  s21_set_exp(&val1, 5);
  s21_set_exp(&val2, 3);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(1.20234, 100.200));
}
END_TEST

START_TEST(simple8) {
  s21_decimal val1 = {{120234, 0, 0, 0}};
  s21_decimal val2 = {{100200, 0, 0, 0}};
  s21_set_exp(&val1, 3);
  s21_set_exp(&val2, 5);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mod(val1, val2, &result_dec);
  float result_int = 0;
  s21_from_decimal_to_float(result_dec, &result_int);
  ck_assert_float_eq(result_int, fmod(120.234, 1.00200));
}
END_TEST

START_TEST(test_s21_mol_int) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(100000, &test_value_1);
  s21_from_int_to_decimal(1000, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (100000 % 1000));

  result_dec.bits[LOW] = 0;
  result_dec.bits[MID] = 0;
  result_dec.bits[HIGH] = 0;
  result_dec.bits[SCALE] = 0;
  test_value_1.bits[SCALE] = 0;
  test_value_2.bits[SCALE] = 0;
  s21_from_int_to_decimal(1, &test_value_1);
  s21_from_int_to_decimal(3, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, (1 % 3));
}
END_TEST

START_TEST(mod_1) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "1";
  char *result = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(mod_2) {
  char *a = "79228162514264337593543950334";
  char *b = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  ck_assert_int_eq(exit_code, 3);
}
END_TEST

START_TEST(mod_3) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "79228162514264337593543950334";
  char *result = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(mod_4) {
  char *a = "7922816251426";
  char *b = "0.001";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(mod_5) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "1";
  char *result = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(mod_6) {
  char *a = "79228162514264337593543950334";
  char *b = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  ck_assert_int_eq(exit_code, 3);
}
END_TEST

START_TEST(mod_7) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "79228162514264337593543950334";
  char *result = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(mod_8) {
  char *a = "7922816251426";
  char *b = "0.001";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_mod(number1, number2, &dec_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

Suite *suite_s21_mod() {
  Suite *s = suite_create("s21_mod");
  TCase *temp = tcase_create("test_s21_mod");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, simple);
  tcase_add_test(temp, simple2);
  tcase_add_test(temp, simple3);
  tcase_add_test(temp, simple4);
  tcase_add_test(temp, simple5);
  tcase_add_test(temp, simple6);
  tcase_add_test(temp, simple7);
  tcase_add_test(temp, simple8);
  tcase_add_test(temp, test_s21_mol_int);
  tcase_add_test(temp, mod_1);
  tcase_add_test(temp, mod_2);
  tcase_add_test(temp, mod_3);
  tcase_add_test(temp, mod_4);
  tcase_add_test(temp, mod_5);
  tcase_add_test(temp, mod_6);
  tcase_add_test(temp, mod_7);
  tcase_add_test(temp, mod_8);
  return s;
}
