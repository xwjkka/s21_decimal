#include "unit.h"

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "1";
  char *result = "79228162514264337593543950334";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_div(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(div_6) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_div(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_int_eq(exit_code, 3);
}
END_TEST

START_TEST(div_7) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162514264337593543950334";
  char *b = "79228162514264337593543950334";
  char *result = "1";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_div(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(div_8) {
  char s21_result[BUF] = {'\0'};
  char *a = "79228162.5142643";
  char *b = "0.0001";
  char *result = "792281625142.643";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_div(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

Suite *suite_s21_div() {
  Suite *s = suite_create("s21_div");
  TCase *temp = tcase_create("test_s21_div");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, div_0);
  tcase_add_test(temp, div_1);
  tcase_add_test(temp, div_2);
  tcase_add_test(temp, div_3);
  tcase_add_test(temp, div_4);
  tcase_add_test(temp, div_5);
  tcase_add_test(temp, div_6);
  tcase_add_test(temp, div_7);
  tcase_add_test(temp, div_8);
  return s;
}
