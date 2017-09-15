#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include "utils.h"
#include <stdint.h>

#define ADD_TYPE_SUFFIX(func, T) CONCAT(func, CONCAT(_, T))

#define DECL_MEMSET(T) T* ADD_TYPE_SUFFIX(memset, T)(T* dst, const double c, const size_t n)
#define DEFINE_MEMSET(T)                        \
  DECL_MEMSET(T) {                              \
    for (size_t i = 0; i < n; i++) {            \
      *dst++ = c;                               \
    }                                           \
    return dst;                                 \
  }

#define DECL_MEMCPY(T) T* ADD_TYPE_SUFFIX(memcpy, T)(T* __restrict dst, T* __restrict src, const size_t n)
#define DEFINE_MEMCPY(T)                        \
  DECL_MEMCPY(T) {                              \
    for (size_t i = 0; i < n; i++) {            \
      *dst++ = *src++;                          \
    }                                           \
    return dst;                                 \
  }

DECL_MEMSET(int32_t);
DECL_MEMSET(double);
DECL_MEMSET(float);

DECL_MEMCPY(int32_t);
DECL_MEMCPY(double);
DECL_MEMCPY(float);

#endif
