#include "vector.h"
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>

// instantiate functions and struct
DEFINE_VECTOR_TYPE(double)
DECL_VECTOR_METHODS(double)
DEFINE_VECTOR_METHODS(double)

// test functions
void test_vector_push_back(void);
void test_vector_clear(void);
void test_vector_pop_back(void);
void test_vector_at(void);

int main() {
  CU_pSuite vector_suite;
  CU_initialize_registry();
  vector_suite = CU_add_suite("vector", NULL, NULL);
  CU_add_test(vector_suite, "clear", test_vector_clear);
  CU_add_test(vector_suite, "push_back", test_vector_push_back);
  CU_add_test(vector_suite, "pop_back", test_vector_pop_back);
  CU_console_run_tests();
  CU_cleanup_registry();
  return 0;
}

void test_vector_clear(void) {
  vector_double* ptr_vd = vector_double_new();

  vector_double_clear(ptr_vd);
  CU_ASSERT(vector_double_size(ptr_vd) == 0);

  for (int i = 0; i < 10; i++) {
    vector_double_push_back(ptr_vd, i);
  }
  vector_double_clear(ptr_vd);
  CU_ASSERT(vector_double_size(ptr_vd) == 0);

  vector_double_delete(ptr_vd);
}

void test_vector_push_back(void) {
  vector_double* ptr_vd = vector_double_new();

  // CASE 1 capacity is constant.
  const double val[] = {1, 5, 4, 6, 5};
  const size_t val_size = sizeof(val) / sizeof(double);

  for (size_t i = 0; i < val_size; i++) {
    vector_double_push_back(ptr_vd, val[i]);
  }
  for (size_t i = 0; i < val_size; i++) {
    CU_ASSERT(vector_double_at(ptr_vd, i) == val[i]);
  }

  // CASE 2 capacity changes.
  vector_double_clear(ptr_vd);
  for (int i = 0; i < 130; i++) {
    vector_double_push_back(ptr_vd, i);
  }
  for (int i = 0; i < 130; i++) {
    CU_ASSERT(vector_double_at(ptr_vd, i) == i);
  }
  CU_ASSERT(vector_double_capacity(ptr_vd) == INIT_MAX_DATA_SIZE * 2);

  // CASE 3 capacity changes.
  vector_double_clear(ptr_vd);
  for (int i = 0; i < 1000; i++) {
    vector_double_push_back(ptr_vd, i);
  }
  for (int i = 0; i < 1000; i++) {
    CU_ASSERT(vector_double_at(ptr_vd, i) == i);
  }
  CU_ASSERT(vector_double_capacity(ptr_vd) == INIT_MAX_DATA_SIZE * 8);

  vector_double_delete(ptr_vd);
}

void test_vector_pop_back(void) {
  vector_double* ptr_vd = vector_double_new();

  for (int i = 0; i < 150; i++) {
    vector_double_push_back(ptr_vd, i);
  }
  for (int i = 149; i >= 0; i--) {
    vector_double_pop_back(ptr_vd);
  }
  CU_ASSERT(vector_double_size(ptr_vd) == 0);

  vector_double_pop_back(ptr_vd);
  CU_ASSERT(vector_double_size(ptr_vd) == 0);

  vector_double_delete(ptr_vd);
}
