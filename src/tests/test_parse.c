#include "s21_tests.h"

START_TEST(test_1) {
  char expression[] = "2+3*1 / 9.12";
  struct node *got = NULL;
  struct node *expected = NULL;
  expected = add_to_list(expected, 2, number);
  expected = add_to_list(expected, 0, add_type);
  expected = add_to_list(expected, 3, number);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 1, number);
  expected = add_to_list(expected, 0, div_type);
  expected = add_to_list(expected, 9.12, number);
  ck_assert_int_eq(parse_expression(expression, &got), OK);
  ck_assert_int_eq(assert_node_eq(&got, &expected), 1);
}
END_TEST

START_TEST(test_2) {
  char expression[] = "-x*5   + (1/23)*(-0.98)^2  ";
  struct node *got = NULL;
  struct node *expected = NULL;
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 5, number);
  expected = add_to_list(expected, 0, add_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 1, number);
  expected = add_to_list(expected, 0, div_type);
  expected = add_to_list(expected, 23, number);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0.98, number);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, pow_type);
  expected = add_to_list(expected, 2, number);
  ck_assert_int_eq(parse_expression(expression, &got), OK);
  ck_assert_int_eq(assert_node_eq(&got, &expected), 1);
}
END_TEST

START_TEST(test_3) {
  char expression[] =
      "-0.8*cos(x)/"
      "tan(x)*sin(x)+ acos(x)-atan(x)* (asin(x))*(-ln(x))+  log(x)^ sqrt(x)";
  struct node *got = NULL;
  struct node *expected = NULL;
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0.8, number);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, cos_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, div_type);
  expected = add_to_list(expected, 0, tan_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, sin_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, add_type);
  expected = add_to_list(expected, 0, acos_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0, atan_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, asin_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, mul_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, number);
  expected = add_to_list(expected, 0, sub_type);
  expected = add_to_list(expected, 0, ln_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, add_type);
  expected = add_to_list(expected, 0, log_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);
  expected = add_to_list(expected, 0, pow_type);
  expected = add_to_list(expected, 0, sqrt_type);
  expected = add_to_list(expected, 0, open_bracket);
  expected = add_to_list(expected, 0, x);
  expected = add_to_list(expected, 0, close_bracket);

  ck_assert_int_eq(parse_expression(expression, &got), OK);
  ck_assert_int_eq(assert_node_eq(&got, &expected), 1);
}
END_TEST

START_TEST(test_4) {
  char expression[] = "-1/x+son(x)";
  struct node *got = NULL;
  ck_assert_int_eq(parse_expression(expression, &got), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_5) {
  char expression[] = "1*si";
  struct node *got = NULL;
  ck_assert_int_eq(parse_expression(expression, &got), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_6) {
  char expression[] = "2^pqrt(x)";
  struct node *got = NULL;
  ck_assert_int_eq(parse_expression(expression, &got), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_7) {
  char expression[] = "value * 3";
  struct node *got = NULL;
  ck_assert_int_eq(parse_expression(expression, &got), INCORRECT_EXPRESSION);
}
END_TEST

Suite *suite_parse_expression() {
  Suite *s = suite_create("suite_parse_expression");
  TCase *tc = tcase_create("parse_expression_tc");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  suite_add_tcase(s, tc);
  return s;
}