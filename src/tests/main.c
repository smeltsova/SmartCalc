#include "s21_tests.h"

int main() {
  srand(time(0));
  run_tests();
  return 0;
}

void run_tests() {
  Suite *list_cases[] = {suite_parse_expression(), suite_translate_to_RPN(),
                         suite_calculate(), suite_calculator(), NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;
  printf("CURRENT TEST: %d\n", counter_testcase++);
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

/*
double randd(double min, double max) {
  return min + (max - min) * ((double)rand() / RAND_MAX);
}
*/
