#include "s21_smartcalc_v1.h"

Stack* stack_init_elem(Stack* new_elem) {
  Stack* tmp = malloc(sizeof(Stack));
  tmp->next = NULL;
  tmp->value = new_elem->value;
  tmp->type = new_elem->type;
  tmp->oper = new_elem->oper;
  return tmp;
}

Stack* stack_init_value(int type, double value, Stack* stack) {
  stack->type = type;

  if (stack->type == 2)
    stack->oper = value;
  else
    stack->oper = 0;

  if (stack->type == 3)
    stack->value = value;
  else
    stack->value = 0;
  return stack;
}

Stack* stack_push(Stack* new_elem, Stack* stack) {
  Stack* tmp = stack_init_elem(new_elem);
  if (stack) {
    tmp->next = stack;
  }
  return tmp;
}

Stack* stack_pop(Stack* stack) {
  Stack* tmp = stack->next;
  free(stack);
  return tmp;
}

Stack* stack_reverse(Stack* stack) {
  Stack* tmp = NULL;
  do {
    tmp = stack_push(stack, tmp);
    stack = stack_pop(stack);
  } while (stack);
  return tmp;
}

void stack_free(Stack* stack) {
  while (stack->next) {
    stack = stack_pop(stack);
  }
  free(stack);
}

Stack* unary_sign(Stack* top) {
  Stack tmp;
  tmp.value = 0;
  tmp.oper = 0;
  tmp.type = 3;
  if (top->oper == 16) {
    top = stack_push(&tmp, top);
  }
  return top;
}

double get_number(char* str, int* pos) {
  char digits[50] = {0};
  int j = 0;
  int i = *pos;
  while ((str[i] >= 48 && str[i] <= 57) || str[i] == '.') {
    digits[j] = str[i];
    j++;
    i++;
  }
  double tmp = atof(digits);
  *pos += j - 1;
  return tmp;
}

int get_priority(int i, int j) {
  int p[17][18];
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 18; j++) {
      p[i][j] = 2;
      if (j == 16 || i == 0 || i == 16) p[i][j] = 1;
      if (1 <= i && i <= 2 && 3 <= j && j <= 15) p[i][j] = 1;
      if (3 <= i && i <= 5 && 6 <= j && j <= 15) p[i][j] = 1;
      if (i == 6 && 7 <= j && j <= 15) p[i][j] = 1;
    }
  }
  p[0][0] = 4, p[0][17] = 3, p[16][0] = 3, p[16][17] = 3;
  return p[i][j];
}

int check_oper(char* str, int rigth, int left) {
  int err = 0;
  for (; str[rigth] != -1; rigth--) {
    if (str[rigth - 1] == ' ') {
      continue;
    } else if (strchr("nsgt()0123456789.x", str[rigth - 1])) {
      break;
    } else if ((strchr("+-*/^d", str[rigth])) && rigth == 0) {
      err = 8;
      break;
    } else {
      err = 8;
      break;
    }
  }
  int flag = 0;
  for (; str[left] != '\0'; left++) {
    if (str[left + 1] == ' ') {
      continue;
    } else if (str[left + 1] == '(') {
      flag = 1;
      continue;
    } else if (strchr("+-*/^m", str[left + 1]) && flag) {
      continue;
    } else if (strchr("sctla0123456789.x", str[left + 1])) {
      break;
    } else {
      err = 8;
      break;
    }
  }
  return err;
}

int check_func(char* str, int* pos) {
  int err = 0;
  if (!strncmp(str + *pos, "sin(", 4)) {
    *pos += 2;
  } else if (!strncmp(str + *pos, "sqrt(", 5)) {
    *pos += 3;
  } else if (!strncmp(str + *pos, "cos(", 4)) {
    *pos += 2;
  } else if (!strncmp(str + *pos, "tan(", 4)) {
    *pos += 2;
  } else if (!strncmp(str + *pos, "ln(", 3)) {
    *pos += 1;
  } else if (!strncmp(str + *pos, "log(", 4)) {
    *pos += 2;
  } else if (!strncmp(str + *pos, "asin(", 5)) {
    *pos += 3;
  } else if (!strncmp(str + *pos, "acos(", 5)) {
    *pos += 3;
  } else if (!strncmp(str + *pos, "atan(", 5)) {
    *pos += 3;
  } else if (!strncmp(str + *pos, "mod", 3)) {
    err = check_oper(str, *pos, *pos + 2);
    *pos += 2;
  } else {
    err = 7;
  }
  return err;
}

int validate_str(char* str) {
  int err = 0;
  int brackets = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ',') str[i] = '.';
    if (str[i] == '(' && str[i + 1] == ')') {
      brackets = 0;
      err = 6;
      break;
    };
    if (str[i] == '(') {
      brackets++;
    } else if (str[i] == ')') {
      brackets--;
    } else if (strchr("+-*/^", str[i])) {
      err = check_oper(str, i, i);
      if (err) break;
    } else if (strchr("mcstal", str[i])) {
      err = check_func(str, &i);
      if (err) break;
    }
  }
  if (brackets != 0 && !err) {
    err = 9;
  }
  return err;
}

Stack* parser(char* str, double* argum) {
  Stack* top = NULL;
  Stack tmp;
  for (int i = 0; str[i] != 0; i++) {
    if (str[i] == '\n' || str[i] == ' ') {
      continue;
    } else if (str[i] == '+') {
      top = unary_sign(top);
      top = stack_push(stack_init_value(2, 1, &tmp), top);
    } else if (str[i] == '-') {
      top = unary_sign(top);
      top = stack_push(stack_init_value(2, 2, &tmp), top);
    } else if (str[i] == '*') {
      top = stack_push(stack_init_value(2, 3, &tmp), top);
    } else if (str[i] == '/') {
      top = stack_push(stack_init_value(2, 4, &tmp), top);
    } else if (!strncmp(str + i, "mod", 3)) {
      top = stack_push(stack_init_value(2, 5, &tmp), top);
      i += 2;
    } else if (str[i] == '^') {
      top = stack_push(stack_init_value(2, 6, &tmp), top);
    } else if (48 <= str[i] && str[i] <= 57) {
      double x = get_number(str, &i);
      top = stack_push(stack_init_value(3, x, &tmp), top);
    } else if (!strncmp(str + i, "sin", 3)) {
      top = stack_push(stack_init_value(2, 7, &tmp), top);
      i += 2;
    } else if (!strncmp(str + i, "cos", 3)) {
      top = stack_push(stack_init_value(2, 8, &tmp), top);
      i += 2;
    } else if (!strncmp(str + i, "tan", 3)) {
      top = stack_push(stack_init_value(2, 9, &tmp), top);
      i += 2;
    } else if (!strncmp(str + i, "asin", 4)) {
      top = stack_push(stack_init_value(2, 10, &tmp), top);
      i += 3;
    } else if (!strncmp(str + i, "acos", 4)) {
      top = stack_push(stack_init_value(2, 11, &tmp), top);
      i += 3;
    } else if (!strncmp(str + i, "atan", 4)) {
      top = stack_push(stack_init_value(2, 12, &tmp), top);
      i += 3;
    } else if (!strncmp(str + i, "sqrt", 4)) {
      top = stack_push(stack_init_value(2, 13, &tmp), top);
      i += 3;
    } else if (!strncmp(str + i, "ln", 2)) {
      top = stack_push(stack_init_value(2, 14, &tmp), top);
      i += 1;
    } else if (!strncmp(str + i, "log", 3)) {
      top = stack_push(stack_init_value(2, 15, &tmp), top);
      i += 2;
    } else if (str[i] == '(') {
      top = stack_push(stack_init_value(2, 16, &tmp), top);
    } else if (str[i] == ')') {
      top = stack_push(stack_init_value(2, 17, &tmp), top);
    } else if (str[i] == 'x') {
      top = stack_push(stack_init_value(3, *argum, &tmp), top);
    }
  }
  tmp.value = 0, tmp.oper = 0, tmp.type = 2, tmp.next = 0;
  top = stack_push(&tmp, top);
  return top;
}

double calc_from_stack(Stack* top) {
  Stack* head = NULL;  // стек с числами и операциями
  Stack tmp;
  double result = 0;
  while (top) {
    if (top->type == 3) {
      head = stack_push(top, head);
      top = stack_pop(top);
    } else if (top->type == 2) {
      if (1 <= top->oper && top->oper <= 6) {
        double op2 = head->value;
        head = stack_pop(head);
        double op1 = head->value;
        head = stack_pop(head);
        result = calc_arithmetic(op1, op2, top->oper);
        top = stack_pop(top);
        head = stack_push(stack_init_value(3, result, &tmp), head);
      } else if (7 <= top->oper && top->oper <= 15) {
        double op1 = head->value;
        head = stack_pop(head);
        result = calc_function(op1, top->oper);
        top = stack_pop(top);
        head = stack_push(stack_init_value(3, result, &tmp), head);
      }
    }
  }
  stack_free(head);
  return result;
}

double calc_arithmetic(double op1, double op2, int oper) {
  double res = 0;
  if (oper == 1) res = op1 + op2;
  if (oper == 2) res = op1 - op2;
  if (oper == 3) res = op1 * op2;
  if (oper == 4) res = op1 / op2;
  if (oper == 5) res = fmod(op1, op2);
  if (oper == 6) res = pow(op1, op2);
  return res;
}

double calc_function(double arg, int oper) {
  double res = 0;
  if (oper == 7) res = sin(arg);
  if (oper == 8) res = cos(arg);
  if (oper == 9) res = tan(arg);
  if (oper == 10) res = asin(arg);
  if (oper == 11) res = acos(arg);
  if (oper == 12) res = atan(arg);
  if (oper == 13) res = sqrt(arg);
  if (oper == 14) res = log(arg);
  if (oper == 15) res = log10(arg);
  return res;
}

Stack* reverse_polish(Stack* top) {
  Stack* head = NULL;
  Stack* res = NULL;  // результирующий стек
  Stack tmp = {0, 0, 2, NULL};
  head = stack_push(&tmp, head);
  while (1) {
    if (top->type == 3) {
      res = stack_push(top, res);
      top = stack_pop(top);
    } else if (top->type == 2) {
      int weigth = get_priority(head->oper, top->oper);
      if (weigth == 1) {
        head = stack_push(top, head);
        top = stack_pop(top);
      } else if (weigth == 2) {
        res = stack_push(head, res);
        head = stack_pop(head);
      } else if (weigth == 3) {
        if (top) top = stack_pop(top);
        if (head) head = stack_pop(head);
      } else if (weigth == 4) {
        break;
      }
    }
  }
  res = stack_reverse(res);
  stack_free(top);
  stack_free(head);
  return res;
}

int smart_calc(char* str, double* result) {
  int err = validate_str(str);
  if (!err) {
    Stack* top = NULL;
    top = stack_reverse(parser(str, result));
    top = reverse_polish(top);
    *result = calc_from_stack(top);
  }
  return err;
}

// void stack_output(Stack* stack) {
//   Stack* tmp = stack;
//   for (; tmp != NULL;) {
//     printf("Element:");
//     printf("   value: %.2f", tmp->value);
//     printf("   oper: %d", tmp->oper);
//     printf("   type: %d", tmp->type);
//     printf("\n");
//     tmp = tmp->next;
//   }
//   free(tmp);
// }

//---------------- main -----------------
// int main() {
//   double x = 6.;
//   char str[] = "() + 6,432 + 5,666 + 10,1 - ((+5.34) + 4.54)";
//   double y = x;
//   int err = smart_calc(str, &y);
//   printf("\nmain: Ok  \n str: %s \n   y: %f \n", str, y);
//   printf(" err: %d \n", err);
//   printf("math: %f\n", (+6.432) + (5.666 + (+10.1)) + ((+5.34) + 4.54));

//   printf("\n --==:: The end ::==--\n");
//   return 0;
// }