#include "../vector3.h"
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>

DEFINE_VEC3_TYPE(double)
DECL_VEC3_METHODS(double)
DEFINE_VEC3_METHODS(double)

const double err_fp = 1.0e-12;

#define DEFINE_TEST_OP_FUNC(OPNAME, OP)                                 \
  void ECLIB_ADD_SUFFIX(test_vector3, OPNAME)(void) {                   \
    vec3_double lhs = {1.0, 2.5, 5.0}, rhs = {2.3, 54.2, 33.2};         \
    vec3_double v = {33.0, 44.0, 12.0};                                 \
                                                                        \
    vec3_double tmp0 = ECLIB_CONCAT(OP_FUNC_TEMPLATE(vec3, OPNAME, VEC3_TYPE(double)), _new)(&lhs, &rhs); \
    CU_ASSERT_DOUBLE_EQUAL(tmp0.x, (lhs.x OP rhs.x), err_fp);           \
    CU_ASSERT_DOUBLE_EQUAL(tmp0.y, (lhs.y OP rhs.y), err_fp);           \
    CU_ASSERT_DOUBLE_EQUAL(tmp0.z, (lhs.z OP rhs.z), err_fp);           \
                                                                        \
    vec3_double tmp1 = ECLIB_CONCAT(OP_FUNC_TEMPLATE(vec3, OPNAME, double), _new)(&lhs, 13.0); \
    CU_ASSERT_DOUBLE_EQUAL(tmp1.x, (lhs.x OP 13.0), err_fp);                   \
    CU_ASSERT_DOUBLE_EQUAL(tmp1.y, (lhs.y OP 13.0), err_fp);                   \
    CU_ASSERT(tmp1.z == (double)(lhs.z OP 13.0));                       \
                                                                        \
    OP_FUNC_TEMPLATE(vec3, OPNAME, VEC3_TYPE(double))(&lhs, &rhs);      \
    CU_ASSERT_DOUBLE_EQUAL(lhs.x, (1.0 OP 2.3), err_fp);                \
    CU_ASSERT_DOUBLE_EQUAL(lhs.y, (2.5 OP 54.2), err_fp);               \
    CU_ASSERT_DOUBLE_EQUAL(lhs.z, (5.0 OP 33.2), err_fp);               \
                                                                        \
    OP_FUNC_TEMPLATE(vec3, OPNAME, double)(&v, 10.0);                   \
    CU_ASSERT_DOUBLE_EQUAL(v.x, (33.0 OP 10.0), err_fp);                \
    CU_ASSERT_DOUBLE_EQUAL(v.y, (44.0 OP 10.0), err_fp);                \
    CU_ASSERT_DOUBLE_EQUAL(v.z, (12.0 OP 10.0), err_fp);                \
  }

DEFINE_TEST_OP_FUNC(add, +)
DEFINE_TEST_OP_FUNC(sub, -)
DEFINE_TEST_OP_FUNC(mul, *)
DEFINE_TEST_OP_FUNC(div, /)

void test_vector3_fill(void) {
  vec3_double vec;
  vec3_double_fill(&vec, 123.0);
  CU_ASSERT_DOUBLE_EQUAL(vec.x, 123.0, err_fp);
  CU_ASSERT_DOUBLE_EQUAL(vec.y, 123.0, err_fp);
  CU_ASSERT_DOUBLE_EQUAL(vec.z, 123.0, err_fp);
}

void test_vector3_clear(void) {
  vec3_double vec;
  vec3_double_clear(&vec);
  CU_ASSERT_DOUBLE_EQUAL(vec.x, 0.0, err_fp);
  CU_ASSERT_DOUBLE_EQUAL(vec.y, 0.0, err_fp);
  CU_ASSERT_DOUBLE_EQUAL(vec.z, 0.0, err_fp);
}

void test_vector3_dot(void) {
  vec3_double v0 = {12.0, 13.0, 14.0}, v1 = {32.0, 31.0, 89.0};
  const double prod = vec3_double_dot(&v0, &v1);
  CU_ASSERT_DOUBLE_EQUAL(prod, (v0.x*v1.x + v0.y*v1.y + v0.z*v1.z), err_fp);
}

void test_vector3_norm2(void) {
  vec3_double v0 = {12.0, 13.0, 25.0};
  const double norm2 = vec3_double_norm2(&v0);
  CU_ASSERT_DOUBLE_EQUAL(norm2, (v0.x*v0.x + v0.y*v0.y + v0.z*v0.z), err_fp);
}

void test_vector3_norm(void) {
  vec3_double v0 = {12.0, 13.0, 25.0};
  const double norm = vec3_double_norm(&v0);
  CU_ASSERT_DOUBLE_EQUAL(norm, sqrt(v0.x*v0.x + v0.y*v0.y + v0.z*v0.z), err_fp);
}

void test_vector3_normalize(void) {
  vec3_double v0 = {12.0, 13.0, 25.0};
  const double norm = sqrt(v0.x*v0.x + v0.y*v0.y + v0.z*v0.z);
  vec3_double v_ref = {v0.x/norm, v0.y/norm, v0.z/norm};
  vec3_double_normalize(&v0);
  CU_ASSERT_DOUBLE_EQUAL(v0.x, v_ref.x, err_fp);
  CU_ASSERT_DOUBLE_EQUAL(v0.y, v_ref.y, err_fp);
  CU_ASSERT_DOUBLE_EQUAL(v0.z, v_ref.z, err_fp);
}

int main(void) {
  CU_pSuite vector3_suite;
  CU_initialize_registry();
  vector3_suite = CU_add_suite("vector3", NULL, NULL);

  CU_add_test(vector3_suite, "add", test_vector3_add);
  CU_add_test(vector3_suite, "sub", test_vector3_sub);
  CU_add_test(vector3_suite, "mul", test_vector3_mul);
  CU_add_test(vector3_suite, "div", test_vector3_div);
  CU_add_test(vector3_suite, "fill", test_vector3_fill);
  CU_add_test(vector3_suite, "clear", test_vector3_clear);
  CU_add_test(vector3_suite, "dot", test_vector3_dot);
  CU_add_test(vector3_suite, "norm2", test_vector3_norm2);
  CU_add_test(vector3_suite, "norm", test_vector3_norm);
  CU_add_test(vector3_suite, "normalize", test_vector3_normalize);

  CU_console_run_tests();
  CU_cleanup_registry();
  return 0;
}
