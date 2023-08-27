#include "s21_tests.h"

START_TEST(test_1) {
  char expression[] = "1+6+3";
  double got = 0, expected = 10;
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_2) {
  char expression[] = "x*x - 3/2";
  char x_str[] = "5";
  double got = 0, expected = 23.5;
  ck_assert_int_eq(calculator(expression, &got, x_str), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_3) {
  char expression[] =
      "-(7*cos(-sin(2*6 - 15) + ln(10)))/ (tan(tan(8* 3.6 / 1.5 /sqrt(2))))";
  double got = 0;
  double expected = -(7 * cos(-sin(2 * 6 - 15) + log(10))) /
                    (tan(tan(8 * 3.6 / 1.5 / sqrt(2))));  //-0.11635635904853295
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_4) {
  char expression[] = "x^x*0.004 / 0.02/5*sqrt(x+9)-1.3 + acos(0.9)/asin(0.9)";
  double got = 0, expected = 1042.356930502;
  char x_str[] = "5.3";
  ck_assert_int_eq(calculator(expression, &got, x_str), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_5) {
  char expression[] = "1+atan(10)/8 - (-5)";
  double got = 0, expected = 1 + atan(10) / 8 - (-5);
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_6) {
  char expression[] = "-1/x";
  double got = 0, expected = -2;
  char x_str[] = "0.5";
  ck_assert_int_eq(calculator(expression, &got, x_str), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_7) {
  char expression[] = "-1/(x";
  double got = 0;
  char x_str[] = "0.5";
  ck_assert_int_eq(calculator(expression, &got, x_str), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_8) {
  char expression[] = "-1/x+";
  double got = 0;
  char x_str[] = "0.5";
  ck_assert_int_eq(calculator(expression, &got, x_str), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_9) {
  char expression[] = "-1/x+son(x)";
  double got = 0;
  char x_str[] = "0.5";
  ck_assert_int_eq(calculator(expression, &got, x_str), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_10) {
  char expression[] = "1/x";
  double got = 0;
  char x_str[] = "0.0";
  ck_assert_int_eq(calculator(expression, &got, x_str), UNDEFINED);
}
END_TEST

START_TEST(test_11) {
  char expression[] = "1 + sqrt(x - 10.001)";
  double got = 0;
  char x_str[] = "10";
  ck_assert_int_eq(calculator(expression, &got, x_str), UNDEFINED);
}
END_TEST

START_TEST(test_12) {
  char expression[] = "-2^2";
  double got = 0, expected = -4;
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_13) {
  char expression[] = "3*2^2";
  double got = 0, expected = 12;
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_14) {
  char expression[] = "0.5 + 2.1 mod 1 /10 + log(1000)";
  double got = 0, expected = 3.51;
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_15) {
  char expression[] = "1-+";
  double got = 0;
  ck_assert_int_eq(calculator(expression, &got, NULL), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_16) {
  char expression[] = "value * 3";
  double got = 0;
  ck_assert_int_eq(calculator(expression, &got, NULL), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_17) {
  char expression[] = "sin";
  double got = 0;
  ck_assert_int_eq(calculator(expression, &got, NULL), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_18) {
  char expression[] = "+*";
  double got = 0;
  ck_assert_int_eq(calculator(expression, &got, NULL), INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(test_19) {
  char expression[] = "2^3^2";
  double got = 0, expected = 512;
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

START_TEST(test_20) {
  char expression[] =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  double got = 0, expected = 256 / 2;
  ck_assert_int_eq(calculator(expression, &got, NULL), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
}
END_TEST

Suite *suite_calculator() {
  Suite *s = suite_create("suite_calculator");
  TCase *tc = tcase_create("calculator_tc");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);

  suite_add_tcase(s, tc);
  return s;
}