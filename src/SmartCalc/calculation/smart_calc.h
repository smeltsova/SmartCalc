#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

enum { OK, INCORRECT_EXPRESSION, UNDEFINED, CLOSE_TO_UNDEFINED };

int calculator(char* expression, double* result, char* x_str);
int parse_expression(char* str, struct node** stack);
int check_operator(char* str, int* i, struct node** stack, int isUnar);
enum enum_type operation_type(char s);
int compare_to_ops(char* s, enum enum_type* type);
int find_x(struct node* stack);
int is_function(enum enum_type type);
int is_operator(enum enum_type type);

int translate_to_RPN(struct node* stack, struct node** rpn);
int calculate(struct node* rpn, double x_value, double* result);
int calculate_function(struct node** stack, enum enum_type function);
int calculate_operation(struct node** stack, enum enum_type operation);
