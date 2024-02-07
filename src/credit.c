#include "calc.h"

int annuitant_credit_calc(Node_Dif** difer_monthly_payment, double amount,
                          double percent, double period,
                          double* monthly_payment, double* overpayment,
                          double* total_payment) {
  int status = 0;
  double monthly_percent = percent / 1200;
  *monthly_payment =
      amount * (monthly_percent * (pow((1 + monthly_percent), period)) /
                (pow((1 + monthly_percent), period) - 1));
  double temp_amount = amount;
  for (int i = 0; i < period && !status; i++) {
    double temp_over = temp_amount * monthly_percent;
    double base_payment = *monthly_payment - temp_over;
    temp_amount -= base_payment;
    status = push_dif(difer_monthly_payment, temp_over, base_payment,
                      temp_amount, i + 1);
    *overpayment += temp_over;
  }
  *total_payment = *overpayment + amount;
  return status;
}

int differential_credit_calc(double amount, double percent, double period,
                             Node_Dif** difer_monthly_payment,
                             double* overpayment, double* total_payment) {
  int status = 0;
  double monthly_percent = percent / 1200;
  double base_monthly_payment = amount / period;
  double temp_amount = amount;
  for (int i = 0; i < period && !status; i++) {
    double temp_over = temp_amount * monthly_percent;
    temp_amount -= base_monthly_payment;
    status = push_dif(difer_monthly_payment, temp_over, base_monthly_payment,
                      temp_amount, i + 1);
    *overpayment += temp_over;
  }
  *total_payment = amount + *overpayment;
  return status;
}

int push_dif(Node_Dif** head, double overpayment, double monthly_payment,
             double temp_amount, int month) {
  int status = 0;
  Node_Dif* tmp = (Node_Dif*)calloc(1, sizeof(Node_Dif));
  if (tmp != NULL) {
    tmp->overpayment = overpayment;
    tmp->monthly_payment = monthly_payment;
    tmp->month = month;
    tmp->temp_amount = temp_amount;
    tmp->next = NULL;
    if (*head == NULL) {
      (*head) = tmp;
    } else {
      Node_Dif* p = (*head);
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = tmp;
    }
  } else
    status = 1;
  return status;
}

void pop_dif_monthly_payment(Node_Dif** head) {
  Node_Dif* prev = NULL;
  prev = (*head);
  *head = (*head)->next;
  free(prev);
}

void dmp(Node_Dif** difer_monthly_payment, double* overpayment,
         double* monthly_payment, double* temp_amount, int* month) {
  *overpayment = (*difer_monthly_payment)->overpayment;
  *monthly_payment = (*difer_monthly_payment)->monthly_payment;
  *temp_amount = (*difer_monthly_payment)->temp_amount;
  *month = (*difer_monthly_payment)->month;
  pop_dif_monthly_payment(difer_monthly_payment);
}
