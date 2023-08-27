#include "s21_tests.h"

int assert_node_eq(struct node **got, struct node **expected) {
  int eq = 1;
  while (!empty(*got) && !empty(*expected)) {
    if ((top_type(*expected) != top_type(*got)) ||
        ((top_type(*got) == number) &&
         (fabs(top(*got) - top(*expected)) > PRECISION))) {
      eq = 0;
    }
    *expected = pop(*expected);
    *got = pop(*got);
  }
  if (!empty(*got) || !empty(*expected)) {
    eq = 0;
  }
  destroy(*got);
  destroy(*expected);
  return eq;
}