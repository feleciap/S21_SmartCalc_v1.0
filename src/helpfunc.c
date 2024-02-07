#include "calc.h"

int verification(char *str) {
  int status = 0, open = 0, point = 0;
  int len = strlen(str);
  if (len > 255 || len < 1) status = 1;
  for (int i = 0; i < (len) && !status; i++) {
    if (!strchr("0123456789.Xx()+-*/^mcstalpu", str[i])) status = 1;

    if (strchr("mcstal", str[i])) {
      status = sinus_itd(str, &i);
      len = strlen(str);
    }
  }
  if (!strchr("0123456789XxcstCSTklg+-(", str[0])) status = 1;

  for (int i = 0; i < (len - 1) && !status; i++) {
    char now = str[i], next = str[i + 1];
    if (strchr("0123456789", now)) {
      if (!strchr("0123456789.+-*/m^)", next)) status = 1;

    } else if (strchr("x", now)) {
      if (!strchr("+-*/m^)", next)) status = 1;

    } else if (strchr("+-*/m^", now)) {
      if (!strchr("0123456789XxcstCSTklg(", next)) status = 1;

      point = 0;
    } else if (strchr("cstCSTklg", now)) {
      if (!strchr("(", next)) status = 1;

    } else if (strchr("(", now)) {
      if (!strchr("0123456789XxcstCSTklg+-(", next)) status = 1;

      open++;
      point = 0;
    } else if (now == '.') {
      if (!strchr("0123456789", next) || point != 0) status = 1;
      point++;
    } else if (strchr(")", now)) {
      if (!strchr(")+-*/m^", next)) status = 1;
      if (open == 0) {
        status = 1;
      } else
        open--;
    }
  }
  if (!strchr("0123456789Xx)", str[len - 1])) status = 1;
  if (str[len - 1] == ')') {
    open--;
  }
  if (open) status = 1;
  return status;
}

int basic_calc(char *str_in, double x, double *result) {
  Node *infix = NULL;
  Node *polish = NULL;
  char str[256] = {0};
  strcpy(str, str_in);
  int status = verification(str);
  if (!status) status = parcer(str, &infix, x);
  if (!status) status = rpn(&infix, &polish);
  if (!status) status = calculate(&polish, result);
  return status;
}

int graf_calc(char *str_in, double x, double *result) {
  Node *infix = NULL;
  Node *polish = NULL;
  char str[256] = {0};
  strcpy(str, str_in);
  int status = parcer(str, &infix, x);
  if (!status) status = rpn(&infix, &polish);
  if (!status) status = calculate(&polish, result);
  return status;
}

int rpn(Node **infix, Node **polish) {
  int status = 0;
  Node *operand = NULL;
  while (*infix != NULL && status == 0) {
    type_t type = (*infix)->type;
    if (type == NUM) {
      status = push_back(polish, pop(infix), NUM);
    } else if (type == SUM || type == SUB) {
      status = operand_out(&operand, polish, 3);
      status = push(&operand, pop(infix), type);
    } else if (type == MULT || type == DIV || type == MOD) {
      status = operand_out(&operand, polish, SUB);
      status = push(&operand, pop(infix), type);
    } else if (type > UNAR_MINUS) {
      status = operand_out(&operand, polish, UNAR_MINUS);
      status = push(&operand, pop(infix), type);
    } else if (type == BRACKET_OPEN) {
      status = push(&operand, pop(infix), type);
    } else if (type == BRACKET_CLOSE) {
      status = operand_out(&operand, polish, BRACKET_OPEN);
      pop_type(infix);
      pop_type(&operand);
    } else if (type == UNAR_MINUS || type == UNAR_PLUS) {
      status = operand_out(&operand, polish, UNAR_MINUS);
      status = push(&operand, pop(infix), type);
    }
  }
  while (operand != NULL) status = push_back(polish, 0, pop_type(&operand));
  return status;
}

type_t pop_type(Node **head) {
  Node *prev = NULL;
  type_t type = 0;
  prev = (*head);
  type = prev->type;
  *head = (*head)->next;
  free(prev);
  return type;
}

int operand_out(Node **operand, Node **polish, type_t p) {
  int status = 0;
  while (*operand != NULL && (*operand)->type > p)
    status = push_back(polish, 0, pop_type(operand));
  return status;
}

int push_back(Node **head, double data, type_t type) {
  int status = 0;
  Node *tmp = (Node *)calloc(1, sizeof(Node));
  if (tmp != NULL) {
    tmp->value = data;
    tmp->type = type;
    tmp->next = NULL;
    if (*head == NULL) {
      (*head) = tmp;
    } else {
      Node *p = (*head);
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = tmp;
    }
  } else
    status = 1;
  return status;
}

int sinus_itd(char *str, int *ind) {
  int status = 0, i = *ind;
  int len = strlen(str);
  if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
    str[i] = 'c';  // cos
    shift(str, &i, len, 2);
  } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
    str[i] = 's';  // sin
    shift(str, &i, len, 2);
  } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
    str[i] = 't';  // tan
    shift(str, &i, len, 2);
  } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
             str[i + 3] == 's') {
    str[i] = 'C';  // acos
    shift(str, &i, len, 3);
  } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
             str[i + 3] == 'n') {
    str[i] = 'S';  // asin
    shift(str, &i, len, 3);
  } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
             str[i + 3] == 'n') {
    str[i] = 'T';  // atan
    shift(str, &i, len, 3);
  } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
             str[i + 3] == 't') {
    str[i] = 'k';  // sqrt
    shift(str, &i, len, 3);
  } else if (str[i] == 'l' && str[i + 1] == 'n') {
    str[i] = 'l';  // ln
    shift(str, &i, len, 1);
  } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
    str[i] = 'g';  // log
    shift(str, &i, len, 2);
  } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
    str[i] = 'm';  // mod
    shift(str, &i, len, 2);
  } else
    status = 1;
  return status;
}

void shift(char *str, int *i, int len, int n) {
  for (int j = (*i + 1); j < (len - n); j++) str[j] = str[j + n];
  str[len - n] = '\0';
}

int push(Node **head, double data, type_t type) {
  int status = 0;
  Node *tmp = (Node *)calloc(1, sizeof(Node));
  if (tmp != NULL) {
    tmp->value = data;
    tmp->type = type;
    tmp->next = (*head);
    (*head) = tmp;
  } else
    status = 1;
  return status;
}

double pop(Node **head) {
  Node *prev = NULL;
  double value;
  prev = (*head);
  value = prev->value;
  *head = (*head)->next;
  free(prev);
  return value;
}
