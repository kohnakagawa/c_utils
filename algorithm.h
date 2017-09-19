#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include "utils.h"
#include <stdint.h>

#define DECL_FILL(T) T* ECLIB_ADD_SUFFIX(fill, T)(T* dst, const double c, const size_t n)
#define DEFINE_FILL(T)                          \
  DECL_FILL(T) {                                \
    for (size_t i = 0; i < n; i++) {            \
      *dst++ = c;                               \
    }                                           \
    return dst;                                 \
  }

#define DECL_COPY(T) T* ECLIB_ADD_SUFFIX(copy, T)(T* __restrict dst, T* __restrict src, const size_t n)
#define DEFINE_COPY(T)                          \
  DECL_COPY(T) {                                \
    for (size_t i = 0; i < n; i++) {            \
      *dst++ = *src++;                          \
    }                                           \
    return dst;                                 \
  }

#endif
