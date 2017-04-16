#ifndef UTILS_H
#define UTILS_H

#define CONCATNATE(x, y) x ## y
#define CONCAT(x, y) CONCATNATE(x, y)

#include <stdio.h>
#include <stdlib.h>

// helper functions
static inline void* xmalloc(size_t size) {
  void* ptr_ret = malloc(size);
  if (NULL == ptr_ret) {
    fprintf(stderr, "Cannot allocate resources at %s %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  return ptr_ret;
}

static inline void xfree(void* ptr) {
  free(ptr);
}

// helper macros
#ifdef DEBUG
#define DEBUG_PRINT(...)                        \
  do {                                          \
    fprintf(stderr, __VA_ARGS__);               \
  } while (0)
#else
#define DEBUG_PRINT(...) do {} while (0)
#endif

#include "err_msgs.h"

#define RANGE_CHECK(self, idx)                                          \
  do {                                                                  \
    if ((idx) >= (self)->size) {                                        \
      fprintf(stderr, "%s: at %s %d\n", err_msgs[OUT_OF_RANGE], __FILE__, __LINE__); \
      exit(EXIT_FAILURE);                                               \
    }                                                                   \
  } while (0)

#endif
