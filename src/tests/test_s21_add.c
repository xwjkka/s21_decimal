#include "unit.h"

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal val2 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_set_exp(&val1, 5);
  s21_set_exp(&val2, 3);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_decimal val2 = {
      {S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, ~(S21_MAX_UINT / 2)}};
  s21_set_exp(&val1, 5);
  s21_set_exp(&val2, 3);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_19) {
  // RESULT до округления 7922816251426433759.6771969004
  char s21_result[BUF] = {'\0'};
  char *a = "-3961408125713216879.6771975167";
  char *b = "-3961408125713216879.9999993837";
  char *result = "-7922816251426433759.677196900";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(add_20) {
  // RESULT до округления 7922816251426433759.6771969004
  char s21_result[BUF] = {'\0'};
  char *a = "-3960000000009.6771975167";
  char *b = "-3961408125713216879.9999993837";
  char *result = "-3961412085713216889.6771969004";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

// Тесты на очень большое число

START_TEST(add_21) {
  // RESULT  79228162514264337593543950336
  char *a = "79228162514264337593543950335";
  char *b = "1";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  ck_assert_int_eq(exit_code, 1);
}
END_TEST

START_TEST(add_22) {
  // RESULT  79228162514264337593543950331
  char *a = "79228162514264337593540000335";
  char *b = "3543950335";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  ck_assert_int_eq(exit_code, 1);
}
END_TEST

// Тесты на сложение отрицательного и положительного числа

// Тест провален. Добавил к тестам на вычитание
START_TEST(add_23) {
  // 3961404165713216870.322801867
  char s21_result[BUF] = {'\0'};
  char *a = "-3960000000009.6771975167";
  char *b = "3961408125713216879.9999993837";
  char *result = "3961404165713216870.3228018670";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(add_24) {
  // RESULT до округления -3961404165713216870.322801867
  char s21_result[BUF] = {'\0'};
  char *a = "3960000000009.6771975167";
  char *b = "-3961408125713216879.9999993837";
  char *result = "-3961404165713216870.3228018670";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(add_25) {
  // RESULT до округления -3961404165713216870.322801867
  char s21_result[BUF] = {'\0'};
  char *a = "9.6771975167";
  char *b = "-396125713216879.9999993837";
  char *result = "-396125713216870.3228018670";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

// Тест провален. Добавил к тестам для вычитания

START_TEST(add_31) {
  char s21_result[BUF] = {'\0'};
  char *a = "-1.12233445511223344552255";
  char *b = "1.12233445511223344552255";
  char *result = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

START_TEST(add_32) {
  char s21_result[BUF] = {'\0'};
  char *a = "1.12233445511223344552255";
  char *b = "-1.12233445511223344552255";
  char *result = "0";
  s21_decimal number1 = {0};
  s21_decimal number2 = {0};
  char_str_to_decimal(a, &number1);
  char_str_to_decimal(b, &number2);
  s21_decimal dec_result = {0};
  int exit_code = 0;
  exit_code = s21_add(number1, number2, &dec_result);
  des_dec_to_str(&dec_result, s21_result);
  ck_assert_str_eq(result, s21_result);
  ck_assert_int_eq(exit_code, 0);
}
END_TEST

Suite *suite_s21_add() {
  Suite *s = suite_create("s21_add");
  TCase *temp = tcase_create("test_s21_add");
  suite_add_tcase(s, temp);

  tcase_add_test(temp, add_0);
  tcase_add_test(temp, add_1);
  tcase_add_test(temp, add_2);
  tcase_add_test(temp, add_3);
  tcase_add_test(temp, add_4);
  tcase_add_test(temp, add_5);
  tcase_add_test(temp, add_6);
  tcase_add_test(temp, add_7);
  tcase_add_test(temp, add_8);
  tcase_add_test(temp, add_9);
  tcase_add_test(temp, add_10);
  tcase_add_test(temp, add_11);
  tcase_add_test(temp, add_12);
  tcase_add_test(temp, add_13);
  tcase_add_test(temp, add_14);
  tcase_add_test(temp, add_15);
  tcase_add_test(temp, add_16);
  tcase_add_test(temp, add_17);
  tcase_add_test(temp, add_18);
  tcase_add_test(temp, add_19);
  tcase_add_test(temp, add_20);
  tcase_add_test(temp, add_21);
  tcase_add_test(temp, add_22);
  tcase_add_test(temp, add_23);
  // sub_case
  tcase_add_test(temp, add_24);
  tcase_add_test(temp, add_25);
  // Coverage test
  tcase_add_test(temp, add_31);
  tcase_add_test(temp, add_32);
  return s;
}
