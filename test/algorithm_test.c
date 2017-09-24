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

#define EQ_INT32_T(a, b) (*(a) == *(b))
DEFINE_UNIQUE(int32_t, EQ_INT32_T)

void test_unique() {
  int32_t a[20] = {1, 2, 3, 4, 4, 4, 40, 3, 3, 3, 5, 12, 12, 0};
  int32_t* last_it = unique_int32_t(a, 20);
  int32_t ans[] = {1, 2, 3, 4, 40, 3, 5, 12, 0};

  int32_t* first_it = a;
  int32_t* ans_it   = ans;
  for (int32_t* it = first_it; it != last_it; (++it, ++ans_it)) {
    CU_ASSERT_EQUAL(*it, *ans_it);
  }
}

int main() {
  CU_pSuite alg_suite = NULL;
  CU_initialize_registry();
  alg_suite = CU_add_suite("algorithm_system", NULL, NULL);
  CU_add_test(alg_suite, "fill", test_fill);
  CU_add_test(alg_suite, "copy", test_copy);
  CU_add_test(alg_suite, "unique", test_unique);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
