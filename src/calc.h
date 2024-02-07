#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum value_type {
  NUM,  // 0123456789
  VAR,  // x

  BRACKET_OPEN,   // (
  BRACKET_CLOSE,  // )

  SUM,  // +
  SUB,  // -

  MULT,  // *
  DIV,   // /
  MOD,   // m

  UNAR_PLUS,   // p
  UNAR_MINUS,  // u

  POWER,  // ^
  COS,    // c
  SIN,    // s
  TAN,    // t
  ACOS,   // C
  ASIN,   // S
  ATAN,   // T
  SQRT,   // k
  LN,     // l
  LOG,    // g

} type_t;

typedef struct Node {
  double value;
  type_t type;
  struct Node *next;
} Node;

typedef struct Node_Dif {
  double overpayment;
  double monthly_payment;
  double temp_amount;
  int month;
  struct Node_Dif *next;
} Node_Dif;

typedef struct Node_up_down {
  double sum;
  int date;
  int up_down;
  struct Node_up_down *next;
} Node_up_down;

typedef struct Node_table {
  int date;
  double add_percent;
  double balance_change;
  double payment;
  double temp_amount;
  struct Node_table *next;
} Node_table;

typedef struct Node_date {
  int date;
  struct Node_date *next;
} Node_date;

/* ------------ CALCULATIONS ------------ */

int calculate(Node **polish, double *result);
int sum(Node **polish, Node **stek);
int sub(Node **polish, Node **stek);
int mult(Node **polish, Node **stek);
int division(Node **polish, Node **stek);
int log_func(Node **polish, Node **stek);
int ln_func(Node **polish, Node **stek);
int sqrt_func(Node **polish, Node **stek);
int arctangens(Node **polish, Node **stek);
int arcsinus(Node **polish, Node **stek);
int arccosinus(Node **polish, Node **stek);
int tangens(Node **polish, Node **stek);
int sinus(Node **polish, Node **stek);
int cosinus(Node **polish, Node **stek);
int unar_minus(Node **polish, Node **stek);
int mod(Node **polish, Node **stek);
int power(Node **polish, Node **stek);

/* ------------ credit ------------ */

int differential_credit_calc(double amount, double percent, double period,
                             Node_Dif **difer_monthly_payment,
                             double *overpayment, double *total_payment);
int annuitant_credit_calc(Node_Dif **difer_monthly_payment, double amount,
                          double percent, double period,
                          double *monthly_payment, double *overpayment,
                          double *total_payment);
void pop_dif_monthly_payment(Node_Dif **head);
int push_dif(Node_Dif **head, double overpayment, double monthly_payment,
             double temp_amount, int month);
void dmp(Node_Dif **difer_monthly_payment, double *overpayment,
         double *monthly_payment, double *temp_amount, int *month);

/* ------------ PARSER ------------ */

int parcer(char *str, Node **infix, double x);
int write_float(const char *str, double *res);
int operation(Node **infix, char c, int *unar, double x);

/* ------------ helpfunc ------------ */

int verification(char *str);
int basic_calc(char *str_in, double x, double *result);
int graf_calc(char *str_in, double x, double *result);
int rpn(Node **infix, Node **polish);
type_t pop_type(Node **head);
int operand_out(Node **operand, Node **polish, type_t p);
int push_back(Node **head, double data, type_t type);
int sinus_itd(char *str, int *ind);
void shift(char *str, int *i, int len, int n);
int push(Node **head, double data, type_t type);
double pop(Node **head);

/* ------------ deposit ------------ */

int deposit_calc(double *deposit_amount, double percent, int period,
                 double tax_rate, int capitalization, Node_up_down **up_down,
                 Node_up_down **withdrawal, double *accured_interest,
                 double *tax_amount, Node_table **table,
                 Node_date **N_payment_date);
int push_date(Node_date **head, int date);
int pop_date(Node_date **head);
void up_top(Node_up_down **up_down, double *balance_change, double *payment,
            int date, double temp_amount);
int push_table(Node_table **head, int date, double add_percent,
               double balance_change, double payment, double temp_amount);
void pop_table(Node_table **head);
int push_up_down(Node_up_down **head, double sum, int date, int up_down);
void pop_up_down(Node_up_down **head);
void print_table(Node_table **table, int *date, double *add_percent,
                 double *balance_change, double *payment, double *temp_amount);

#endif  // SRC_CALC_H