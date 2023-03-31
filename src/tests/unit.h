#ifndef SRC_TESTS_UNIT_H
#define SRC_TESTS_UNIT_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define SIGN 0x80000000
#define MAX_INT_SHIFT 31
#define BUF 1024
#define MAX_DECIMAL 79228162514264337593543950335.0
#define MIN_DECIMAL -79228162514264337593543950335.0

#define MAX_DECIMAL_STR "79228162514264337593543950335"
#define MIN_DECIMAL_STR "-79228162514264337593543950335"

#define SUCCESS 0
#define FAILURE 1
#define LARGE 1
#define SMALL 2
#define BIG 3
#define POSITIVE 0
#define NEGATIVE 1

enum bits { LOW, MID, HIGH, SCALE };

Suite *suite_s21_from_int_to_decimal();
Suite *suite_s21_from_decimal_to_int();
Suite *suite_s21_from_float_to_decimal();
Suite *suite_s21_from_decimal_to_float();

Suite *suite_s21_add();
Suite *suite_s21_sub();
Suite *suite_s21_mul();
Suite *suite_s21_div();
Suite *suite_s21_mod();

Suite *suite_s21_is_less();
Suite *suite_s21_is_greater();
Suite *suite_s21_is_equal();
Suite *suite_s21_is_not_equal();
Suite *suite_s21_is_greater_or_equal();
Suite *suite_s21_is_less_or_equal();

Suite *suite_s21_floor();
Suite *suite_s21_round();
Suite *suite_s21_truncate();
Suite *suite_s21_negate();
#endif  //  SRC_TESTS_UNIT_H