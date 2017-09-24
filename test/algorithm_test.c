#include "algorithm.h"
#include <stdint.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

DEFINE_FILL(int32_t)
DEFINE_COPY(int32_t)

void test_fill() {
  int32_t a[20] = {};
  fill_int32_t(a, -1, 20);
  for (int i = 0; i < 20; i++) CU_ASSERT_EQUAL(a[i], -1);
}

void test_copy() {
  int32_t a[20] = {};
  int32_t b[20] = {};
  for (int i = 0; i < 20; i++) b[i] = i;
  copy_int32_t(a, b, 20);
  for (int i = 0; i < 20; i++) CU_ASSERT_EQUAL(a[i], b[i]);
}

int main() {
  CU_pSuite alg_suite = NULL;
  CU_initialize_registry();
  alg_suite = CU_add_suite("algorithm_system", NULL, NULL);
  CU_add_test(alg_suite, "fill", test_fill);
  CU_add_test(alg_suite, "copy", test_copy);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
