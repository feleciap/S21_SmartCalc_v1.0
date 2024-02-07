#include "calc.h"

int parcer(char *str, Node **infix, double x) {
  int len = strlen(str);
  int unar = 1, status = 0;
  for (int i = 0; i < len && !status; i++) {
    if (str[i] > 47 && str[i] < 58) {
      double num = 0;
      unar = 0;
      i += write_float(str + i, &num);
      status = push_back(infix, num, NUM);
    } else
      status = operation(infix, str[i], &unar, x);
  }
  return status;
}

int write_float(const char *str, double *res) {
  int i = 0;
  char bufer[256] = {0};
  char *numstr = "0123456789";
  while ((strchr(numstr, str[i]) || str[i] == '.') && str[i]) {
    i++;
  }
  if (str[i] == 'e' || str[i] == 'E') {
    i++;
    if (str[i] == '+' || str[i] == '-') i++;
    while (strchr(numstr, str[i]) && str[i]) i++;
  }
  int j = 0;
  for (; j < i; j++) {
    bufer[j] = str[j];
  }
  bufer[j + 1] = '\0';
  *res = atof(bufer);
  return i - 1;
}

int operation(Node **infix, char c, int *unar, double x) {
  int status = 0;
  if (c == 'x') {
    status = push_back(infix, x, NUM);
    *unar = 0;
  } else if (*unar && c == 45) {
    status = push_back(infix, 0, UNAR_MINUS);
  } else if (*unar && c == 43) {
    status = push_back(infix, 0, UNAR_PLUS);
  } else if (c == 43) {
    status = push_back(infix, 0, SUM);
  } else if (c == 45) {
    status = push_back(infix, 0, SUB);
  } else if (c == 42) {
    status = push_back(infix, 0, MULT);
  } else if (c == 47) {
    status = push_back(infix, 0, DIV);
  } else if (c == 'm') {
    status = push_back(infix, 0, MOD);
  } else if (c == 94) {
    status = push_back(infix, 0, POWER);
  } else if (c == 99) {
    status = push_back(infix, 0, COS);
  } else if (c == 115) {
    status = push_back(infix, 0, SIN);
  } else if (c == 116) {
    status = push_back(infix, 0, TAN);
  } else if (c == 67) {
    status = push_back(infix, 0, ACOS);
  } else if (c == 83) {
    status = push_back(infix, 0, ASIN);
  } else if (c == 84) {
    status = push_back(infix, 0, ATAN);
  } else if (c == 107) {
    status = push_back(infix, 0, SQRT);
  } else if (c == 108) {
    status = push_back(infix, 0, LN);
  } else if (c == 103) {
    status = push_back(infix, 0, LOG);
  } else if (c == 40) {
    status = push_back(infix, 0, BRACKET_OPEN);
    *unar = 1;
  } else if (c == 41) {
    status = push_back(infix, 0, BRACKET_CLOSE);
  }
  return status;
}
