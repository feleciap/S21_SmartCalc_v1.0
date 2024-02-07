#include "calc.h"

int calculate(Node **polish, double *result) {
  int status = 0;
  Node *stek = NULL;
  while (*polish != NULL && status == 0) {
    if ((*polish)->type == NUM) {
      push(&stek, pop(polish), NUM);
    } else if ((*polish)->type == SUM) {
      status = sum(polish, &stek);
    } else if ((*polish)->type == SUB) {
      status = sub(polish, &stek);
    } else if ((*polish)->type == MULT) {
      status = mult(polish, &stek);
    } else if ((*polish)->type == DIV) {
      status = division(polish, &stek);
    } else if ((*polish)->type == POWER) {
      status = power(polish, &stek);
    } else if ((*polish)->type == MOD) {
      status = mod(polish, &stek);
    } else if ((*polish)->type == UNAR_PLUS) {
      pop(polish);
    } else if ((*polish)->type == UNAR_MINUS) {
      status = unar_minus(polish, &stek);
    } else if ((*polish)->type == COS) {
      status = cosinus(polish, &stek);
    } else if ((*polish)->type == SIN) {
      status = sinus(polish, &stek);
    } else if ((*polish)->type == TAN) {
      status = tangens(polish, &stek);
    } else if ((*polish)->type == ACOS) {
      status = arccosinus(polish, &stek);
    } else if ((*polish)->type == ASIN) {
      status = arcsinus(polish, &stek);
    } else if ((*polish)->type == ATAN) {
      status = arctangens(polish, &stek);
    } else if ((*polish)->type == SQRT) {
      status = sqrt_func(polish, &stek);
    } else if ((*polish)->type == LN) {
      status = ln_func(polish, &stek);
    } else if ((*polish)->type == LOG)
      status = log_func(polish, &stek);
  }
  if (!status) *result = pop(&stek);
  return status;
}

int sum(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0, b = 0, c = 0;
  a = pop(stek);
  b = pop(stek);
  c = a + b;
  if (c == INFINITY || c == NAN) {
    status = 2;
  } else
    status = push(stek, c, NUM);
  return status;
}

int sub(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0, b = 0, c = 0;
  a = pop(stek);
  b = pop(stek);
  c = b - a;
  if (c == INFINITY || c == NAN) {
    status = 2;
  } else
    status = push(stek, c, NUM);
  return status;
}

int mult(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0, b = 0, c = 0;
  a = pop(stek);
  b = pop(stek);
  c = b * a;
  if (c == INFINITY || c == NAN) {
    status = 2;
  } else
    status = push(stek, c, NUM);
  return status;
}

int division(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0, b = 0, c = 0;
  a = pop(stek);
  b = pop(stek);
  if (c < 0.0000001) {
    c = b / a;
    if (c == INFINITY || c == NAN) {
      status = 1;
    } else
      status = push(stek, c, NUM);
  } else
    status = 1;
  return status;
}

int log_func(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, log10(a), NUM);
}

int ln_func(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, log(a), NUM);
}

int sqrt_func(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0;
  a = pop(stek);
  if (a < 0) {
    status = 1;
  } else
    status = push(stek, sqrt(a), NUM);
  return status;
}

int arctangens(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, atan(a), NUM);
}

int arcsinus(Node **polish, Node **stek) {
  int status = 0;
  pop(polish);
  double a = 0, c = 0;
  a = pop(stek);
  c = asin(a);
  if (c == INFINITY || c == NAN) {
    status = 1;
  } else
    status = push(stek, c, NUM);
  return status;
}

int arccosinus(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, acos(a), NUM);
}

int tangens(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, tan(a), NUM);
}

int sinus(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, sin(a), NUM);
}

int cosinus(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, cos(a), NUM);
}

int unar_minus(Node **polish, Node **stek) {
  pop(polish);
  double a = 0;
  a = pop(stek);
  return push(stek, (0 - a), NUM);
}

int mod(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0, b = 0;
  a = pop(stek);
  b = pop(stek);
  if (a == 0) {
    status = 1;
  } else
    status = push(stek, fmod(b, a), NUM);
  return status;
}

int power(Node **polish, Node **stek) {
  pop(polish);
  int status = 0;
  double a = 0, b = 0, c = 0;
  a = pop(stek);
  b = pop(stek);
  c = pow(b, a);
  if (c == INFINITY || c == NAN) {
    status = 2;
  } else
    status = push(stek, c, NUM);
  return status;
}