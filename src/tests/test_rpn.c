#include "s21_tests.h"

START_TEST(test_1) {
  //"2+3*1 / 9.12"
  struct node *got = NULL;
  struct node *expression_list = NULL;
  expression_list = add_to_list(expression_list, 2, number);
  expression_list = add_to_list(expression_list, 0, add_type);
  expression_list = add_to_list(expression_list, 3, number);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 1, number);
  expression_list = add_to_list(expression_list, 0, div_type);
  expression_list = add_to_list(expression_list, 9.12, number);
  struct node *expected = NULL;  // "2 3 1 * 9.12 / +"
  expected = add_to_list(expected, 2, number);
  expected = add_to_list(expected, 3, number);
  expected = add_to_list(expected, 1, number);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 9.12, number);
  expected = add_to_list(expected, 0, div_type);
  expected = add_to_list(expected, 0, add_type);

  ck_assert_int_eq(translate_to_RPN(expression_list, &got), OK);
  ck_assert_int_eq(assert_node_eq(&got, &expected), 1);
}
END_TEST

START_TEST(test_2) {
  //"-x*5   + (1/23)*(-0.98)^2  "
  struct node *got = NULL;
  struct node *expression_list = NULL;
  expression_list = add_to_list(expression_list, 0, number);
  expression_list = add_to_list(expression_list, 0, sub_type);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 5, number);
  expression_list = add_to_list(expression_list, 0, add_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 1, number);
  expression_list = add_to_list(expression_list, 0, div_type);
  expression_list = add_to_list(expression_list, 23, number);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, number);
  expression_list = add_to_list(expression_list, 0, sub_type);
  expression_list = add_to_list(expression_list, 0.98, number);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, pow_type);
  expression_list = add_to_list(expression_list, 2, number);
  struct node *expected = NULL;  // "0 x 5 * - 1 23 / 0 0.98 - 2 ^ * +"
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 5, number);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 1, number);
  expected = add_to_list(expected, 23, number);
  expected = add_to_list(expected, 0, div_type);
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0.98, number);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 2, number);
  expected = add_to_list(expected, 0, pow_type);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, add_type);
  ck_assert_int_eq(translate_to_RPN(expression_list, &got), OK);
  ck_assert_int_eq(assert_node_eq(&got, &expected), 1);
}
END_TEST

START_TEST(test_3) {
  //"-0.8*cos(x)/tan(x)*sin(x)+cos(x)-tan(x)*(sin(x))*(-ln(x))+log(x)^sqrt(x)";
  struct node *got = NULL;
  struct node *expression_list = NULL;
  expression_list = add_to_list(expression_list, 0, number);
  expression_list = add_to_list(expression_list, 0, sub_type);
  expression_list = add_to_list(expression_list, 0.8, number);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 0, cos_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, div_type);
  expression_list = add_to_list(expression_list, 0, tan_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 0, sin_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, add_type);
  expression_list = add_to_list(expression_list, 0, cos_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, sub_type);
  expression_list = add_to_list(expression_list, 0, tan_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, sin_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, mul_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, number);
  expression_list = add_to_list(expression_list, 0, sub_type);
  expression_list = add_to_list(expression_list, 0, ln_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, add_type);
  expression_list = add_to_list(expression_list, 0, log_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);
  expression_list = add_to_list(expression_list, 0, pow_type);
  expression_list = add_to_list(expression_list, 0, sqrt_type);
  expression_list = add_to_list(expression_list, 0, open_bracket);
  expression_list = add_to_list(expression_list, 0, x);
  expression_list = add_to_list(expression_list, 0, close_bracket);

  struct node *expected = NULL;  //"0 0.8 x cos * x tan / x sin * - x cos + x
                                 // tan x sin * 0 x ln - * - x log x sqrt ^ +"
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0.8, number);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, cos_type);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, tan_type);
  expected = add_to_list(expected, 0, div_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, sin_type);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, cos_type);
  expected = add_to_list(expected, 0, add_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, tan_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, sin_type);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, ln_type);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, log_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, sqrt_type);
  expected = add_to_list(expected, 0, pow_type);
  expected = add_to_list(expected, 0, add_type);
  ck_assert_int_eq(translate_to_RPN(expression_list, &got), OK);
  ck_assert_int_eq(assert_node_eq(&got, &expected), 1);
}
END_TEST

Suite *suite_translate_to_RPN() {
  Suite *s = suite_create("suite_translate_to_RPN");
  TCase *tc = tcase_create("translate_to_RPN_tc");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}