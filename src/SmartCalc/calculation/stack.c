#include "stack.h"

#include <stdlib.h>

struct node* push(struct node* top, double value, enum enum_type type) {
  struct node* next_top = (struct node*)malloc(sizeof(struct node));
  next_top->value = value;
  next_top->type = type;
  next_top->next = top;
  return next_top;
}

struct node* add_to_list(struct node* head, double value, enum enum_type type) {
  struct node* next_node = (struct node*)malloc(sizeof(struct node));
  next_node->value = value;
  next_node->type = type;
  next_node->next = NULL;
  if (empty(head)) {
    head = next_node;
  } else {
    struct node* temp = head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = next_node;
  }
  return head;
}

struct node* pop(struct node* top) {
  struct node* next_top = top->next;
  free(top);
  return next_top;
}

double top(struct node* stack) { return stack->value; }
enum enum_type top_type(struct node* stack) { return stack->type; }

int empty(const struct node* stack) { return stack == NULL; }

void destroy(struct node* top) {
  while (top) {
    struct node* next_top = top->next;
    free(top);
    top = next_top;
  }
}

int priority_of_type(enum enum_type type) {
  int priority = 0;
  if (type == add_type || type == sub_type) {
    priority = 1;
  } else if (type == mul_type || type == div_type || type == mod_type) {
    priority = 2;
  } else if (type == pow_type) {
    priority = 3;
  }
  return priority;
}