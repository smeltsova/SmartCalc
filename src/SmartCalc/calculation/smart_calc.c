#include "smart_calc.h"

#include <string.h>

int calculator(char* expression, double* result, char* x_str) {
  int error = OK;
  struct node* expression_list = NULL;
  if ((error = parse_expression(expression, &expression_list)) == OK) {
    *result = 0;
    double x_value = 0;
    if (find_x(expression_list)) {
      x_value = atof(x_str);
    }
    struct node* rpn = NULL;
    if ((error = translate_to_RPN(expression_list, &rpn)) == OK) {
      error = calculate(rpn, x_value, result);
    }
    destroy(rpn);
  }
  return error;
}

int parse_expression(char* str, struct node** expression_list) {
  int correct = OK;
  if (!str) {
    correct = INCORRECT_EXPRESSION;
  } else {
    int isUnar = 1;
    for (int i = 0; correct == OK && str[i]; i++) {
      if (str[i] == '(') {
        *expression_list = add_to_list(*expression_list, 0, open_bracket);
        isUnar = 1;
      } else if (str[i] == ')') {
        *expression_list = add_to_list(*expression_list, 0, close_bracket);
        isUnar = 0;
      } else if (str[i] == 'x') {
        *expression_list = add_to_list(*expression_list, 0, x);
        isUnar = 0;
      } else if (isdigit(str[i])) {
        char num[256] = {0};
        int j = 0;
        int past_digit_point = 0;
        while (str[i] && (isdigit(str[i]) || str[i] == '.') && j < 256) {
          if (str[i] == '.') {
            if (past_digit_point) correct = INCORRECT_EXPRESSION;
            past_digit_point = 1;
          }
          num[j++] = str[i++];
        }
        i--;
        if (correct == OK) {
          double value = atof(num);
          *expression_list = add_to_list(*expression_list, value, number);
        }
        isUnar = 0;
      } else if (strchr("+-*/^mcstal", str[i])) {
        correct = check_operator(str, &i, expression_list, isUnar);
        isUnar = 0;
      } else if (str[i] != ' ') {
        correct = INCORRECT_EXPRESSION;
      }
    }
    if (correct != OK) destroy(*expression_list);
  }
  return correct;
}

int check_operator(char* str, int* i, struct node** expression_list,
                   int isUnar) {
  int correct = OK;
  if ((str[*i] == '+' || str[*i] == '-') && (isUnar)) {
    *expression_list = add_to_list(*expression_list, 0, number);
    *expression_list =
        add_to_list(*expression_list, 0, operation_type(str[*i]));
  } else if (strchr("+-*^/", str[*i])) {
    *expression_list =
        add_to_list(*expression_list, 0, operation_type(str[*i]));
  } else {
    char temp[5] = {0};
    int j = 0;
    while (j < 5 && str[*i] && strchr("modcossintansqrtlnlog", str[*i])) {
      temp[j++] = str[(*i)++];
    }
    (*i)--;
    enum enum_type type;
    correct = compare_to_ops(temp, &type);
    if (correct == OK) {
      *expression_list = add_to_list(*expression_list, 0, type);
    }
  }
  return correct;
}

enum enum_type operation_type(char s) {
  enum enum_type type = number;
  if (s == '+') {
    type = add_type;
  } else if (s == '-') {
    type = sub_type;
  } else if (s == '*') {
    type = mul_type;
  } else if (s == '/') {
    type = div_type;
  } else if (s == '^') {
    type = pow_type;
  }
  return type;
}

int compare_to_ops(char* s, enum enum_type* type) {
  int correct = OK;
  if (strcmp(s, "mod") == 0) {
    *type = mod_type;
  } else if (strcmp(s, "cos") == 0) {
    *type = cos_type;
  } else if (strcmp(s, "sin") == 0) {
    *type = sin_type;
  } else if (strcmp(s, "tan") == 0) {
    *type = tan_type;
  } else if (strcmp(s, "acos") == 0) {
    *type = acos_type;
  } else if (strcmp(s, "asin") == 0) {
    *type = asin_type;
  } else if (strcmp(s, "atan") == 0) {
    *type = atan_type;
  } else if (strcmp(s, "sqrt") == 0) {
    *type = sqrt_type;
  } else if (strcmp(s, "ln") == 0) {
    *type = ln_type;
  } else if (strcmp(s, "log") == 0) {
    *type = log_type;
  } else {
    correct = INCORRECT_EXPRESSION;
  }
  return correct;
}

int find_x(struct node* expression_list) {
  int found = 0;
  while (expression_list && !found) {
    if (top_type(expression_list) == x) found = 1;
    struct node* next_expression_list = expression_list->next;
    expression_list = next_expression_list;
  }
  return found;
}

int translate_to_RPN(struct node* expression_list, struct node** rpn) {
  int error = OK;
  struct node* stack = NULL;
  while (!empty(expression_list)) {
    if (top_type(expression_list) == number) {
      *rpn = add_to_list(*rpn, top(expression_list), number);
    } else if (top_type(expression_list) == x) {
      *rpn = add_to_list(*rpn, 0, x);
    } else if ((top_type(expression_list) == open_bracket) ||
               (is_function(top_type(expression_list)))) {
      stack = push(stack, 0, top_type(expression_list));
    } else if (is_operator(top_type(expression_list))) {
      while ((!empty(stack)) &&
             (priority_of_type(top_type(stack)) >
                  priority_of_type(top_type(expression_list)) ||
              (priority_of_type(top_type(stack)) ==
                   priority_of_type(top_type(expression_list)) &&
               (top_type(expression_list) != pow_type)))) {
        *rpn = add_to_list(*rpn, top(stack), top_type(stack));
        stack = pop(stack);
      }
      stack = push(stack, 0, top_type(expression_list));
    } else if (top_type(expression_list) == close_bracket) {
      while (!empty(stack) && top_type(stack) != open_bracket) {
        *rpn = add_to_list(*rpn, top(stack), top_type(stack));
        stack = pop(stack);
      }
      if (!empty(stack)) {
        stack = pop(stack);
      } else {
        error = INCORRECT_EXPRESSION;
      }
      if (!empty(stack) && is_function(top_type(stack))) {
        *rpn = add_to_list(*rpn, top(stack), top_type(stack));
        stack = pop(stack);
      }
    }
    expression_list = pop(expression_list);
  }
  while (!empty(stack)) {
    if (top_type(stack) == open_bracket) {
      error = INCORRECT_EXPRESSION;
    }
    *rpn = add_to_list(*rpn, top(stack), top_type(stack));
    stack = pop(stack);
  }
  return error;
}

int is_function(enum enum_type type) { return type >= cos_type; }
int is_operator(enum enum_type type) {
  return add_type <= type && type <= mod_type;
}

int calculate(struct node* rpn, double x_value, double* result) {
  int error = OK;
  struct node* stack = NULL;
  while (!empty(rpn) && error != INCORRECT_EXPRESSION) {
    if (top_type(rpn) == number) {
      stack = push(stack, top(rpn), number);
    } else if (top_type(rpn) == x) {
      stack = push(stack, x_value, number);
    } else if (is_function(top_type(rpn))) {
      error = calculate_function(&stack, top_type(rpn));
    } else {
      error = calculate_operation(&stack, top_type(rpn));
    }
    rpn = rpn->next;
  }
  if (!empty(stack)) {
    *result = top(stack);
    stack = pop(stack);
    if (!empty(stack)) {
      error = INCORRECT_EXPRESSION;
    }
  } else {
    error = INCORRECT_EXPRESSION;
  }
  return error;
}

int calculate_function(struct node** stack, enum enum_type function) {
  int error = OK;
  if (!stack || !*stack || empty(*stack)) {
    error = INCORRECT_EXPRESSION;
  } else {
    double value = top(*stack);
    *stack = pop(*stack);
    double new_value = 0;
    if (function == cos_type) {
      new_value = cos(value);
    } else if (function == sin_type) {
      new_value = sin(value);
    } else if (function == tan_type) {
      new_value = tan(value);
      if (fabs(new_value) > 1e5) {
        error = CLOSE_TO_UNDEFINED;
      }
    } else if (function == acos_type) {
      new_value = acos(value);
    } else if (function == asin_type) {
      new_value = asin(value);
    } else if (function == atan_type) {
      new_value = atan(value);
    } else if (function == sqrt_type) {
      new_value = sqrt(value);
    } else if (function == ln_type) {
      new_value = log(value);
    } else if (function == log_type) {
      new_value = log10(value);
    } else {
      error = INCORRECT_EXPRESSION;
    }
    *stack = push(*stack, new_value, number);
    if (!isfinite(new_value)) {
      error = UNDEFINED;
    }
  }
  return error;
}

int calculate_operation(struct node** stack, enum enum_type operation) {
  int error = OK;
  if (!stack || !*stack || empty(*stack)) {
    error = INCORRECT_EXPRESSION;
  } else {
    double value1 = top(*stack);
    *stack = pop(*stack);
    if (empty(*stack)) {
      error = INCORRECT_EXPRESSION;
    } else {
      double value2 = top(*stack);
      *stack = pop(*stack);
      double new_value = 0;
      if (operation == add_type) {
        new_value = value2 + value1;
      } else if (operation == sub_type) {
        new_value = value2 - value1;
      } else if (operation == mul_type) {
        new_value = value2 * value1;
      } else if (operation == div_type) {
        new_value = value2 / value1;
        if (fabs(value1) < 1e-7) {
          error = CLOSE_TO_UNDEFINED;
        }
      } else if (operation == mod_type) {
        new_value = fmod(value2, value1);
      } else if (operation == pow_type) {
        new_value = pow(value2, value1);
      } else {
        error = INCORRECT_EXPRESSION;
      }
      *stack = push(*stack, new_value, number);
      if (!isfinite(new_value)) {
        error = UNDEFINED;
      }
    }
  }
  return error;
}
