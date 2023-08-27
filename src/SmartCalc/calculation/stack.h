#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>

enum enum_type {
  number,
  x,
  open_bracket,
  close_bracket,
  add_type,
  sub_type,
  mul_type,
  div_type,
  pow_type,
  mod_type,
  cos_type,
  sin_type,
  tan_type,
  acos_type,
  asin_type,
  atan_type,
  sqrt_type,
  ln_type,
  log_type
};

struct node {
  double value;
  enum enum_type type;
  struct node* next;
};

#ifndef NULL
#define NULL (void*)0
#endif

enum enum_type top_type(struct node* stack);
struct node* pop(struct node* top);
void destroy(struct node* top);
double top(struct node* stack);
int empty(const struct node* stack);
struct node* push(struct node* top, double value, enum enum_type type);
struct node* add_to_list(struct node* head, double value, enum enum_type type);

int priority_of_type(enum enum_type type);

#endif  // SRC_STACK_H_
