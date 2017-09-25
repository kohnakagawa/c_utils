#include "ec_lib/vector.h"

// instantiate functions and struct
DEFINE_VECTOR_TYPE(double)
DECL_VECTOR_METHODS(double)
DEFINE_VECTOR_METHODS(double)

void test_vector(void) {
  vector_double* ptr_vd = vector_double_new();

  const double val[] = {1, 5, 4, 6, 5};
  const size_t val_size = sizeof(val) / sizeof(double);

  for (size_t i = 0; i < val_size; i++) {
    vector_double_push_back(ptr_vd, val[i]);
  }
  for (size_t i = 0; i < val_size; i++) {
    printf("val[%d] = %f, ptr_vd[%d] = %f\n", i, val[i], i, vector_double_at(ptr_vd, i));
  }

  vector_double_delete(ptr_vd);
}

int main(void) {
  test_vector();
  return 0;
}
