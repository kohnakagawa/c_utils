#include "stack.h"
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>

// instantiate functions and struct
DEFINE_STACK_TYPE(double)
DECL_STACK_METHODS(double)
DEFINE_STACK_METHODS(double)

// test functions
void test_stack_push_pop(void);

int main() {
  CU_pSuite stack_suite;
  CU_initialize_registry();
  stack_suite = CU_add_suite("stack", NULL, NULL);
  CU_add_test(stack_suite, "stack", test_stack_push_pop);
  CU_console_run_tests();
  CU_cleanup_registry();
  return 0;
}

void test_stack_push_pop(void) {
  stack_double* ptr_sd = stack_double_new();

  stack_double_push(ptr_sd, 10.0);
  CU_ASSERT(stack_double_size(ptr_sd) == 1);

  const double val = stack_double_pop(ptr_sd);
  CU_ASSERT(val == 10.0);
  CU_ASSERT(stack_double_size(ptr_sd) == 0);

  for (int i = 0; i < 10; i++) {
    stack_double_push(ptr_sd, i);
  }
  CU_ASSERT(stack_double_size(ptr_sd) == 10);

  for (int i = 9; i >= 2; i--) {
    const double val = stack_double_pop(ptr_sd);
    CU_ASSERT(val == (double)i);
  }

  CU_ASSERT(stack_double_size(ptr_sd) == 2);

  stack_double_delete(ptr_sd);
}
