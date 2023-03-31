#include <stdio.h>
#include <stdlib.h>

#include "tests/unit.h"

void run_test_case(Suite *testcase);
void run_all_tests();

int main() {
  run_all_tests();
  return 0;
}

void run_test_case(Suite *testcase) {
  static int count = 1;
  printf("TEST CASE №%d\n", count++);

  SRunner *sr;
  sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  printf("\n");
}

void run_all_tests() {
  Suite *list_cases[] = {
      suite_s21_from_int_to_decimal(),
      suite_s21_from_decimal_to_int(),
      suite_s21_from_float_to_decimal(),
      suite_s21_from_decimal_to_float(),
      suite_s21_add(),
      suite_s21_sub(),
      suite_s21_mul(),
      suite_s21_div(),
      suite_s21_mod(),
      suite_s21_is_less(),
      suite_s21_is_greater(),
      suite_s21_is_equal(),
      suite_s21_is_not_equal(),
      suite_s21_is_greater_or_equal(),
      suite_s21_is_less_or_equal(),
      suite_s21_floor(),
      suite_s21_round(),
      suite_s21_truncate(),
      suite_s21_negate(),
  };
  for (int i = 0; i < (int)(sizeof(list_cases) / sizeof(Suite *)); i++)
    run_test_case(list_cases[i]);
}