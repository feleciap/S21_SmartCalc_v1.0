#include "calc.h"

int deposit_calc(double* deposit_amount, double percent, int period,
                 double tax_rate, int capitalization, Node_up_down** up_down,
                 Node_up_down** withdrawal, double* accured_interest,
                 double* tax_amount, Node_table** table,
                 Node_date** N_payment_date) {
  int status = 0;
  double temp_amount = *deposit_amount;
  double day_percent = percent / 36500;
  double balance_change = 0;
  double payment = 0;
  double sum_percent = 0;
  int payment_date = pop_date(N_payment_date);
  for (int date = 1; date <= period; date++) {
    double add_percent = day_percent * temp_amount;
    *accured_interest += add_percent;
    up_top(up_down, &balance_change, &payment, date, temp_amount);
    up_top(withdrawal, &balance_change, &payment, date, temp_amount);
    if ((temp_amount + balance_change < 0)) temp_amount += balance_change;
    if (capitalization) {
      balance_change += add_percent;
    } else {
      payment += add_percent;
    }
    sum_percent += add_percent;
    if (payment_date == date) {
      temp_amount += balance_change;
      status = push_table(table, date, sum_percent, balance_change, payment,
                          temp_amount);
      balance_change = 0;
      payment = 0;
      sum_percent = 0;
      if ((*N_payment_date) != NULL) {
        payment_date = pop_date(N_payment_date);
      }
    }
  }
  *tax_amount = *accured_interest * tax_rate / 100;
  *deposit_amount = temp_amount;
  return status;
}

int push_date(Node_date** head, int date) {
  int status = 0;
  Node_date* tmp = (Node_date*)calloc(1, sizeof(Node_date));
  if (tmp != NULL) {
    tmp->date = date;
    tmp->next = NULL;
    if (*head == NULL) {
      (*head) = tmp;
    } else {
      Node_date* p = (*head);
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = tmp;
    }
  } else
    status = 1;
  return status;
}

int pop_date(Node_date** head) {
  int date = (*head)->date;
  Node_date* prev = NULL;
  prev = (*head);
  *head = (*head)->next;
  free(prev);
  return date;
}

void up_top(Node_up_down** up_down, double* balance_change, double* payment,
            int date, double temp_amount) {
  if ((*up_down) != NULL) {
    if ((*up_down)->date == date) {
      if ((*up_down)->up_down) {
        *balance_change += (*up_down)->sum;
      } else {
        double temp_sum = (*up_down)->sum;
        if (temp_amount - temp_sum >= 0) {
          *balance_change -= temp_sum;
          *payment += temp_sum;
        }
      }
      pop_up_down(up_down);
    }
  }
}

int push_table(Node_table** head, int date, double add_percent,
               double balance_change, double payment, double temp_amount) {
  int status = 0;
  Node_table* tmp = (Node_table*)calloc(1, sizeof(Node_table));
  if (tmp != NULL) {
    tmp->date = date;
    tmp->add_percent = add_percent;
    tmp->balance_change = balance_change;
    tmp->payment = payment;
    tmp->temp_amount = temp_amount;
    tmp->next = NULL;
    if (*head == NULL) {
      (*head) = tmp;
    } else {
      Node_table* p = (*head);
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = tmp;
    }
  } else
    status = 1;
  return status;
}

void pop_table(Node_table** head) {
  Node_table* prev = NULL;
  prev = (*head);
  *head = (*head)->next;
  free(prev);
}

int push_up_down(Node_up_down** head, double sum, int date, int up_down) {
  int status = 0;
  Node_up_down* tmp = (Node_up_down*)calloc(1, sizeof(Node_up_down));
  if (tmp != NULL) {
    tmp->sum = sum;
    tmp->date = date;
    tmp->up_down = up_down;
    tmp->next = NULL;
    if (*head == NULL) {
      (*head) = tmp;
    } else {
      Node_up_down* p = (*head);
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = tmp;
    }
  } else
    status = 1;
  return status;
}

void pop_up_down(Node_up_down** head) {
  Node_up_down* prev = NULL;
  prev = (*head);
  *head = (*head)->next;
  free(prev);
}

void print_table(Node_table** table, int* date, double* add_percent,
                 double* balance_change, double* payment, double* temp_amount) {
  *date = (*table)->date;
  *add_percent = (*table)->add_percent;
  *balance_change = (*table)->balance_change;
  *payment = (*table)->payment;
  *temp_amount = (*table)->temp_amount;
  pop_table(table);
}