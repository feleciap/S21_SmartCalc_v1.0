#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

START_TEST(calc_1) {
  double result = 0;
  char str[256] = "2051+311.22";
  double x = 0;
  int status = basic_calc(str, x, &result);
  double correct = 2051 + 311.22;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_2) {
  double result = 0;
  int status = 0;
  char str[256] = "1.32-1.8+0.036";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 1.32 - 1.8 + 0.036;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_3) {
  double result = 0;
  int status = 0;
  char str[256] = "1/((1/3)+1)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 0.75;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_4) {
  double result = 0;
  int status = 0;
  char str[256] = "1/sin(3)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 1 / sin(3);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_5) {
  double result = 0;
  int status = 0;
  char str[256] = "2^3";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = pow(2, 3);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_6) {
  double result = 0;
  int status = 0;
  char str[256] = "1.4-asin(1)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 1.4 - asin(1);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_7) {
  double result = 0;
  int status = 0;
  char str[256] = "(tan(2)/(2.5+3))";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = (tan(2) / (2.5 + 3));
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_8) {
  double result = 0;
  int status = 0;
  char str[256] = "1.4*cos(1/4)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 1.356477;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_9) {
  double result = 0;
  int status = 0;
  char str[256] = "-sin(0.732)*2";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = -1.336717;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_10) {
  double result = 0;
  int status = 0;
  char str[256] = "acos(1)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = acos(1);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_11) {
  double result = 0;
  int status = 0;
  char str[256] = "atan(-0.98)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = atan(-0.98);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_12) {
  double result = 0;
  int status = 0;
  char str[256] = "sqrt(27)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = sqrt(27);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_13) {
  double result = 0;
  int status = 0;
  char str[256] = "sqrt(-2)";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_14) {
  double result = 0;
  int status = 0;
  char str[256] = "acos(0.43)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = acos(0.43);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_15) {
  double result = 0;
  int status = 0;
  char str[256] = "-2*ln(13)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = -2 * log(13);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_16) {
  double result = 0;
  int status = 0;
  char str[256] = "log(200.5)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = log10(200.5);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_17) {
  double result = 0;
  int status = 0;
  char str[256] = "5mod2+16mod2.5";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 2;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_18) {
  double result = 0;
  int status = 0;
  char str[256] = "-(-5)";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = 5;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_19) {
  double result = 0;
  int status = 0;
  char str[256] = "-25-(-2)+(-(+3))";
  double x = 0;
  status = basic_calc(str, x, &result);
  double correct = -25 - (-2) + (-(+3));
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_20) {
  double result = 0;
  int status = 0;
  char str[256] = "sin(x)-2*(-2)";
  double x = 3;
  status = basic_calc(str, x, &result);
  double correct = sin(3) - 2 * (-2);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_21) {
  double result = 0;
  int status = 0;
  char str[256] = "(-x)^2";
  double x = 3.52;
  status = basic_calc(str, x, &result);
  double correct = pow((-3.52), 2);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_22) {
  double result = 0;
  int status = 0;
  char str[256] = "()";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_23) {
  double result = 0;
  int status = 0;
  char str[256] = "()";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_24) {
  double result = 0;
  int status = 0;
  char str[256] = "12+(3+2)-2*5)";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_25) {
  double result = 0;
  int status = 0;
  char str[256] = "1.2+3-3.69.0";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_26) {
  double result = 0;
  int status = 0;
  char str[256] = "2/3++2";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_27) {
  double result = 0;
  int status = 0;
  char str[256] = "*2/2+1";
  double x = 0;
  status = basic_calc(str, x, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calc_28) {
  double result = 0;
  int status = 0;
  char str[256] = "x*x";
  double x = 5.5;
  status = graf_calc(str, x, &result);
  double correct = 5.5 * 5.5;
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result, correct, 1e-6);
}
END_TEST

START_TEST(calc_29) {
  double amount = 100000;
  double percent = 10;
  double period = 10;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  Node_Dif *difer_monthly_payment = NULL;
  int status = 0;
  status =
      annuitant_credit_calc(&difer_monthly_payment, amount, percent, period,
                            &monthly_payment, &overpayment, &total_payment);
  double test_monthly_payment = 10464.04;
  double test_overpayment = 4640.38;
  double test_total_payment = 104640.38;
  while (difer_monthly_payment != NULL)
    pop_dif_monthly_payment(&difer_monthly_payment);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(monthly_payment, test_monthly_payment, 1e-2);
  ck_assert_double_eq_tol(overpayment, test_overpayment, 1e-2);
  ck_assert_double_eq_tol(total_payment, test_total_payment, 1e-2);
}
END_TEST

START_TEST(calc_30) {
  double amount = 100000;
  double percent = 10;
  double period = 2;
  double overpayment = 0;
  double total_payment = 0;
  double monthly_payment = 0;
  double temp_amount = 0;
  int month = 0;
  Node_Dif *difer_monthly_payment = NULL;
  int status = 0;
  status =
      differential_credit_calc(amount, percent, period, &difer_monthly_payment,
                               &overpayment, &total_payment);
  double test_overpayment = 1250;
  double test_total_payment = 101250;

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(overpayment, test_overpayment, 1e-2);
  ck_assert_double_eq_tol(total_payment, test_total_payment, 1e-2);
  dmp(&difer_monthly_payment, &overpayment, &monthly_payment, &temp_amount,
      &month);
  ck_assert_double_eq_tol(overpayment, 833.33, 1e-2);
  ck_assert_double_eq_tol(monthly_payment, 50000, 1e-2);
  ck_assert_double_eq_tol(temp_amount, 50000, 1e-2);
  ck_assert_int_eq(month, 1);
  dmp(&difer_monthly_payment, &overpayment, &monthly_payment, &temp_amount,
      &month);
  ck_assert_double_eq_tol(overpayment, 416.67, 1e-2);
  ck_assert_double_eq_tol(monthly_payment, 50000, 1e-2);
  ck_assert_double_eq_tol(temp_amount, 0, 1e-2);
  ck_assert_int_eq(month, 2);
}
END_TEST

START_TEST(calc_31) {
  double deposit_amount = 100000;
  double percent = 10;
  double period = 2;
  double tax_rate = 13;
  int capitalization = 0;
  Node_up_down *up_down = NULL;
  Node_up_down *withdrawal = NULL;
  double accured_interest = 0;
  double tax_amount = 0;
  Node_table *table = NULL;
  Node_date *N_payment_date = NULL;
  int status = 0;
  double add_percent = 0;
  double balance_change = 0;
  double payment = 0;
  double temp_amount = 0;
  int date = 0;
  push_date(&N_payment_date, 1);
  push_date(&N_payment_date, 2);
  push_up_down(&up_down, 1000, 1, 1);
  status = deposit_calc(
      &deposit_amount, percent, period, tax_rate, capitalization, &up_down,
      &withdrawal, &accured_interest, &tax_amount, &table, &N_payment_date);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(accured_interest, 55.07, 1e-2);
  ck_assert_double_eq_tol(tax_amount, 7.16, 1e-2);
  ck_assert_double_eq_tol(deposit_amount, 101000, 1e-2);
  print_table(&table, &date, &add_percent, &balance_change, &payment,
              &temp_amount);
  ck_assert_double_eq_tol(add_percent, 27.4, 1e-2);
  ck_assert_double_eq_tol(balance_change, 1000, 1e-2);
  ck_assert_double_eq_tol(temp_amount, 101000, 1e-2);
  ck_assert_double_eq_tol(payment, 27.4, 1e-2);
  ck_assert_int_eq(date, 1);
  print_table(&table, &date, &add_percent, &balance_change, &payment,
              &temp_amount);
  ck_assert_double_eq_tol(add_percent, 27.67, 1e-2);
  ck_assert_double_eq_tol(balance_change, 0, 1e-2);
  ck_assert_double_eq_tol(temp_amount, 101000, 1e-2);
  ck_assert_double_eq_tol(payment, 27.67, 1e-2);
  ck_assert_int_eq(date, 2);
}
END_TEST

START_TEST(calc_32) {
  double deposit_amount = 100000;
  double percent = 10;
  double period = 2;
  double tax_rate = 13;
  int capitalization = 1;
  Node_up_down *up_down = NULL;
  Node_up_down *withdrawal = NULL;
  double accured_interest = 0;
  double tax_amount = 0;
  Node_table *table = NULL;
  Node_date *N_payment_date = NULL;
  int status = 0;
  double add_percent = 0;
  double balance_change = 0;
  double payment = 0;
  double temp_amount = 0;
  int date = 0;
  push_date(&N_payment_date, 1);
  push_date(&N_payment_date, 2);
  push_up_down(&withdrawal, 1000, 1, 0);
  status = deposit_calc(
      &deposit_amount, percent, period, tax_rate, capitalization, &up_down,
      &withdrawal, &accured_interest, &tax_amount, &table, &N_payment_date);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(accured_interest, 54.53, 1e-2);
  ck_assert_double_eq_tol(tax_amount, 7.09, 1e-2);
  ck_assert_double_eq_tol(deposit_amount, 99054.53, 1e-2);
  print_table(&table, &date, &add_percent, &balance_change, &payment,
              &temp_amount);
  ck_assert_double_eq_tol(add_percent, 27.4, 1e-2);
  ck_assert_double_eq_tol(balance_change, -972.6, 1e-2);
  ck_assert_double_eq_tol(temp_amount, 99027.4, 1e-2);
  ck_assert_double_eq_tol(payment, 1000, 1e-2);
  ck_assert_int_eq(date, 1);
  print_table(&table, &date, &add_percent, &balance_change, &payment,
              &temp_amount);
  ck_assert_double_eq_tol(add_percent, 27.13, 1e-2);
  ck_assert_double_eq_tol(balance_change, 27.13, 1e-2);
  ck_assert_double_eq_tol(temp_amount, 99054.53, 1e-2);
  ck_assert_double_eq_tol(payment, 0, 1e-2);
  ck_assert_int_eq(date, 2);
}
END_TEST

Suite *s21_calculator_test(void) {
  Suite *suite = suite_create("s21_calculator");
  TCase *tCase = tcase_create("s21_calculator");

  tcase_add_test(tCase, calc_1);
  tcase_add_test(tCase, calc_2);
  tcase_add_test(tCase, calc_3);
  tcase_add_test(tCase, calc_4);
  tcase_add_test(tCase, calc_5);
  tcase_add_test(tCase, calc_6);
  tcase_add_test(tCase, calc_7);
  tcase_add_test(tCase, calc_8);
  tcase_add_test(tCase, calc_9);
  tcase_add_test(tCase, calc_10);
  tcase_add_test(tCase, calc_11);
  tcase_add_test(tCase, calc_12);
  tcase_add_test(tCase, calc_13);
  tcase_add_test(tCase, calc_14);
  tcase_add_test(tCase, calc_15);
  tcase_add_test(tCase, calc_16);
  tcase_add_test(tCase, calc_17);
  tcase_add_test(tCase, calc_18);
  tcase_add_test(tCase, calc_19);
  tcase_add_test(tCase, calc_20);
  tcase_add_test(tCase, calc_21);
  tcase_add_test(tCase, calc_22);
  tcase_add_test(tCase, calc_23);
  tcase_add_test(tCase, calc_24);
  tcase_add_test(tCase, calc_25);
  tcase_add_test(tCase, calc_26);
  tcase_add_test(tCase, calc_27);
  tcase_add_test(tCase, calc_28);
  tcase_add_test(tCase, calc_29);
  tcase_add_test(tCase, calc_30);
  tcase_add_test(tCase, calc_31);
  tcase_add_test(tCase, calc_32);

  suite_add_tcase(suite, tCase);

  return suite;
}

int main() {
  Suite *suite = s21_calculator_test();
  SRunner *sRunner = srunner_create(suite);
  srunner_set_fork_status(sRunner, CK_NOFORK);
  srunner_run_all(sRunner, CK_VERBOSE);
  int failed_tests = srunner_ntests_failed(sRunner);
  srunner_free(sRunner);

  return (failed_tests == 0) ? 0 : 1;
}