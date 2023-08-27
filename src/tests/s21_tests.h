#ifndef SRC_TESTS_S21_TESTS_H_
#define SRC_TESTS_S21_TESTS_H_

#include <check.h>
#include <limits.h>
#include <time.h>

#include "../SmartCalc/calculation/smart_calc.h"

#define PRECISION 1e-6

#include "s21_tests.h"

int assert_node_eq(struct node **got, struct node **expected);

Suite *suite_calculator();
Suite *suite_parse_expression();
Suite *suite_translate_to_RPN();
Suite *suite_calculate();

void run_tests();
void run_testcase(Suite *testcase);
double randd(double min, double max);

#endif  // SRC_TESTS_S21_TESTS_H_