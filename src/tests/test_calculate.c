#include "s21_tests.h"

START_TEST(test_1) {
  // "2+3*1/9.12"
  double x_value = 15;
  double got = 0, expected = 2 + 3 * 1 / 9.12;
  struct node *rpn = NULL;  // "2 3 1 * 9.12 / +"
  rpn = add_to_list(rpn, 2, number);
  rpn = add_to_list(rpn, 3, number);
  rpn = add_to_list(rpn, 1, number);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 9.12, number);
  rpn = add_to_list(rpn, 0, div_type);
  rpn = add_to_list(rpn, 0, add_type);

  ck_assert_int_eq(calculate(rpn, x_value, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  destroy(rpn);
}
END_TEST

START_TEST(test_2) {
  // "-x*5+(1/23)*(-0.98)^2";
  double x_value = 4.834;
  double got = 0, expected = -4.834 * 5 + (1. / 23) * pow(-0.98, 2);
  struct node *rpn = NULL;  // "0 x 5 * - 1 23 / 0 0.98 - 2 ^ * +"
  rpn = add_to_list(rpn, 0, number);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 5, number);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 0, sub_type);
  rpn = add_to_list(rpn, 1, number);
  rpn = add_to_list(rpn, 23, number);
  rpn = add_to_list(rpn, 0, div_type);
  rpn = add_to_list(rpn, 0, number);
  rpn = add_to_list(rpn, 0.98, number);
  rpn = add_to_list(rpn, 0, sub_type);
  rpn = add_to_list(rpn, 2, number);
  rpn = add_to_list(rpn, 0, pow_type);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 0, add_type);
  ck_assert_int_eq(calculate(rpn, x_value, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  destroy(rpn);
}
END_TEST

START_TEST(test_3) {
  //"-0.8*cos(x)/tan(x)*sin(x)+ cos(x)-atan(x)* (sin(x))*(-ln(x))+  log(x)^
  // sqrt(x)";

  double x_value = 1;
  double got = 0;
  double expected = -0.8 * cos(1) / tan(1) * sin(1) + cos(1) -
                    atan(1) * (sin(1)) * (-log(1)) + pow(log10(1), sqrt(1));
  struct node *rpn = NULL;  //"0 0.8 x cos * x tan / x sin * - x cos + x
                            // atan x sin * 0 x ln - * - x log x sqrt ^ +"

  rpn = add_to_list(rpn, 0, number);
  rpn = add_to_list(rpn, 0.8, number);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, cos_type);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, tan_type);
  rpn = add_to_list(rpn, 0, div_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, sin_type);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 0, sub_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, cos_type);
  rpn = add_to_list(rpn, 0, add_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, atan_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, sin_type);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 0, number);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, ln_type);
  rpn = add_to_list(rpn, 0, sub_type);
  rpn = add_to_list(rpn, 0, mul_type);
  rpn = add_to_list(rpn, 0, sub_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, log_type);
  rpn = add_to_list(rpn, 0, x);
  rpn = add_to_list(rpn, 0, sqrt_type);
  rpn = add_to_list(rpn, 0, pow_type);
  rpn = add_to_list(rpn, 0, add_type);
  ck_assert_int_eq(calculate(rpn, x_value, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  destroy(rpn);
}
END_TEST

Suite *suite_calculate() {
  Suite *s = suite_create("suite_calculate");
  TCase *tc = tcase_create("calculate_tc");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}