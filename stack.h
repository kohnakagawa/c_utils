#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <string.h>
#include "utils.h"

#define STACK_TYPE(T) ECLIB_CONCAT(stack_, T)
#define STACK_REF(T) ECLIB_CONCAT(stackref_, T)
#define STACK_TYPE_DUMMY(T) ECLIB_CONCAT(stack_t_, T)

#define STACK_METHOD(T, f) ECLIB_CONCAT(ECLIB_CONCAT(STACK_TYPE(T), _), f)

#undef INIT_MAX_DATA_SIZE
#define INIT_MAX_DATA_SIZE 128

#define DECL_STACK_TYPE(T)                                              \
  struct STACK_TYPE_DUMMY(T);                                           \
  typedef struct STACK_TYPE_DUMMY(T) STACK_TYPE(T);                     \
  typedef struct STACK_TYPE_DUMMY(T)* STACK_REF(T);

#define DEFINE_STACK_TYPE(T)                        \
  DECL_STACK_TYPE(T)                                \
  struct STACK_TYPE_DUMMY(T) {                      \
    T* data;                                        \
    size_t size;                                    \
    size_t capacity;                                \
  };

// private members
#define DECL_STACK_RESERVE(T) void STACK_METHOD(T, reserve)(STACK_REF(T) self, size_t new_capacity)
#define DEFINE_STACK_RESERVE(T)                               \
  DECL_STACK_RESERVE(T) {                                     \
    self->capacity = new_capacity;                            \
    T* buffer_new = (T*) xmalloc(self->capacity * sizeof(T)); \
    memcpy(buffer_new, self->data, self->size * sizeof(T));   \
    xfree(self->data);                                        \
    self->data = buffer_new;                                  \
  }

// public members
#define DECL_STACK_NEW(T) STACK_REF(T) STACK_METHOD(T, new)(void)
#define DEFINE_STACK_NEW(T)                                             \
  DECL_STACK_NEW(T) {                                                   \
    STACK_REF(T) self = (STACK_REF(T)) xmalloc(sizeof(STACK_TYPE(T)));  \
    self->size = 0;                                                     \
    self->capacity = INIT_MAX_DATA_SIZE;                                \
    self->data = (T*) xmalloc(self->capacity * sizeof(T));              \
    return self;                                                        \
  }

#define DECL_STACK_DELETE(T) void STACK_METHOD(T, delete)(STACK_REF(T) self)
#define DEFINE_STACK_DELETE(T)                          \
  DECL_STACK_DELETE(T) {                                \
    free(self->data);                                   \
    self->data = NULL;                                  \
    free(self);                                         \
  }

#define DECL_STACK_PUSH(T) void STACK_METHOD(T, push)(STACK_REF(T) self, const T in)
#define DEFINE_STACK_PUSH(T)                                  \
  DECL_STACK_PUSH(T) {                                        \
    if ((self->size + 1) >= self->capacity) {                 \
      STACK_METHOD(T, reserve)(self, self->capacity * 2);     \
    }                                                         \
    self->data[self->size++] = in;                            \
  }

#define DECL_STACK_POP(T) T STACK_METHOD(T, pop)(STACK_REF(T) self)
#define DEFINE_STACK_POP(T)                                             \
  DECL_STACK_POP(T) {                                                   \
    if (STACK_METHOD(T, empty)(self)) {                                 \
      fprintf(stderr, "%s: at %s %d\n", err_msgs[OUT_OF_RANGE], __FILE__, __LINE__); \
      exit(EXIT_FAILURE);                                               \
    }                                                                   \
    self->size--;                                                       \
    return self->data[self->size];                                      \
  }

#define DECL_STACK_SIZE(T) size_t STACK_METHOD(T, size)(STACK_REF(T) self)
#define DEFINE_STACK_SIZE(T)                    \
  DECL_STACK_SIZE(T) {                          \
    return self->size;                          \
  }

#define DECL_STACK_EMPTY(T) bool STACK_METHOD(T, empty)(STACK_REF(T) self)
#define DEFINE_STACK_EMPTY(T)                         \
  DECL_STACK_EMPTY(T) {                               \
    return (bool)(0 == self->size);                   \
  }

#define DECL_STACK_TOP(T) T STACK_METHOD(T, top)(STACK_REF(T) self)
#define DEFINE_STACK_TOP(T)                     \
  DECL_STACK_TOP(T) {                           \
    return self->data[self->size - 1];          \
  }

#define DEFINE_STACK_METHODS(T) \
  DEFINE_STACK_RESERVE(T)       \
  DEFINE_STACK_NEW(T)           \
  DEFINE_STACK_DELETE(T)        \
  DEFINE_STACK_PUSH(T)          \
  DEFINE_STACK_POP(T)           \
  DEFINE_STACK_SIZE(T)          \
  DEFINE_STACK_EMPTY(T)         \
  DEFINE_STACK_TOP(T)

#define DECL_STACK_METHODS(T) \
  DECL_STACK_RESERVE(T);      \
  DECL_STACK_NEW(T);          \
  DECL_STACK_DELETE(T);       \
  DECL_STACK_PUSH(T);         \
  DECL_STACK_POP(T);          \
  DECL_STACK_SIZE(T);         \
  DECL_STACK_EMPTY(T);        \
  DECL_STACK_TOP(T);

#endif
