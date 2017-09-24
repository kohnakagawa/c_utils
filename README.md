[![Build Status](https://travis-ci.org/kohnakagawa/ec_lib.svg?branch=master)](https://travis-ci.org/kohnakagawa/ec_lib)
[![codecov](https://codecov.io/gh/kohnakagawa/ec_lib/branch/master/graph/badge.svg)](https://codecov.io/gh/kohnakagawa/ec_lib)

ec_lib ( = enhanced c library)
=============
My simple C language library 

## Requirements
* C99 compiler
* CUnit (for unit test)

## Features
* simple C++ STL like container classes
  * vector (vector.h)
  * string (string_c.c)
  * stack (stack.c)
  * 3D vector (vector3.h)
* simple filesystem library (filesystem.c)
* simple algorithm header library (algorithm.h)
  * fill
  * copy

## How to use
### Example of vector

``` c
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
    printf("%f\n", vector_double_at(ptr_vd, i));
  }

  vector_double_delete(ptr_vd);
}

int main(void) {
  test_vector();
  return 0;
}
```

## Acknowledgement
* [blog post by KMC](http://kmc.hatenablog.jp/entry/2015/12/09/051358) (in Japanese).
