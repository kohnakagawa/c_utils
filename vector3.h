#ifndef VEC3_H
#define VEC3_H

#include "utils.h"
#include <math.h>

// NOTE: T = float, double, int
// pointer type is not allowed.

#define VEC3_TYPE(T) ECLIB_CONCAT(vec3_, T)
#define VEC3_TYPE_DUMMY(T) ECLIB_CONCAT(vec3_t_, T)

#define VEC3_METHOD(T, f) ECLIB_ADD_SUFFIX(VEC3_TYPE(T), f)

#define DECL_VEC3_TYPE(T)                         \
  struct VEC3_TYPE_DUMMY(T);                      \
  typedef struct VEC3_TYPE_DUMMY(T) VEC3_TYPE(T);

#define DEFINE_VEC3_TYPE(T)                   \
  DECL_VEC3_TYPE(T)                           \
  struct VEC3_TYPE_DUMMY(T) {                 \
    T x, y, z;                                \
  };

#define OP_FUNC_TEMPLATE(LHS, OP, RHS)              \
  ECLIB_ADD_SUFFIX(LHS, ECLIB_ADD_SUFFIX(OP, RHS))

#define DECL_VEC3_OP_VEC3(T, OPNAME)                                    \
  void OP_FUNC_TEMPLATE(vec3, OPNAME, VEC3_TYPE(T))(VEC3_TYPE(T)* self, const VEC3_TYPE(T)* v0)
#define DECL_VEC3_OP_VEC3_NEW(T, OPNAME)                                \
  VEC3_TYPE(T) ECLIB_CONCAT(OP_FUNC_TEMPLATE(vec3, OPNAME, VEC3_TYPE(T)), _new)(const VEC3_TYPE(T)* v0, const VEC3_TYPE(T)* v1)
#define DECL_VEC3_OP_SCALAR(T, OPNAME)                                  \
  void OP_FUNC_TEMPLATE(vec3, OPNAME, scalar)(VEC3_TYPE(T)* self, const T v)
#define DECL_VEC3_OP_SCALAR_NEW(T, OPNAME)                              \
  VEC3_TYPE(T) ECLIB_CONCAT(OP_FUNC_TEMPLATE(vec3, OPNAME, scalar), _new)(const VEC3_TYPE(T)* v0, const T v)

#define DECL_VEC3_OP_FUNCS(T, OPNAME)           \
  DECL_VEC3_OP_VEC3(T, OPNAME);                 \
  DECL_VEC3_OP_VEC3_NEW(T, OPNAME);             \
  DECL_VEC3_OP_SCALAR(T, OPNAME);               \
  DECL_VEC3_OP_SCALAR_NEW(T, OPNAME);

#define DEFINE_VEC3_OP_FUNCS(T, OPNAME, OP)     \
  DECL_VEC3_OP_VEC3(T, OPNAME)                  \
  {                                             \
    self->x ECLIB_CONCAT(OP, =) v0->x;          \
    self->y ECLIB_CONCAT(OP, =) v0->y;          \
    self->z ECLIB_CONCAT(OP, =) v0->z;          \
  }                                             \
                                                \
  DECL_VEC3_OP_VEC3_NEW(T, OPNAME)              \
  {                                             \
    VEC3_TYPE(T) ret;                           \
    ret.x = v0->x OP v1->x;                     \
    ret.y = v0->y OP v1->y;                     \
    ret.z = v0->z OP v1->z;                     \
    return ret;                                 \
  }                                             \
                                                \
  DECL_VEC3_OP_SCALAR(T, OPNAME)                \
  {                                             \
    self->x ECLIB_CONCAT(OP, =) v;              \
    self->y ECLIB_CONCAT(OP, =) v;              \
    self->z ECLIB_CONCAT(OP, =) v;              \
  }                                             \
                                                \
  DECL_VEC3_OP_SCALAR_NEW(T, OPNAME)            \
  {                                             \
    VEC3_TYPE(T) ret;                           \
    ret.x = v0->x OP v;                         \
    ret.y = v0->y OP v;                         \
    ret.z = v0->z OP v;                         \
    return ret;                                 \
  }

#define DECL_VEC3_ALL_OP_FUNCS(T)               \
  DECL_VEC3_OP_FUNCS(T, add)                    \
  DECL_VEC3_OP_FUNCS(T, sub)                    \
  DECL_VEC3_OP_FUNCS(T, mul)                    \
  DECL_VEC3_OP_FUNCS(T, div)

#define DEFINE_VEC3_ALL_OP_FUNCS(T)             \
  DEFINE_VEC3_OP_FUNCS(T, add, +)               \
  DEFINE_VEC3_OP_FUNCS(T, sub, -)               \
  DEFINE_VEC3_OP_FUNCS(T, mul, *)               \
  DEFINE_VEC3_OP_FUNCS(T, div, /)

#define DECL_VEC3_FILL(T) void VEC3_METHOD(T, fill)(VEC3_TYPE(T)* self, const T val)
#define DEFINE_VEC3_FILL(T)                     \
  DECL_VEC3_FILL(T) {                           \
    self->x = self->y = self->z = val;          \
  }

#define DECL_VEC3_CLEAR(T) void VEC3_METHOD(T, clear)(VEC3_TYPE(T)* self)
#define DEFINE_VEC3_CLEAR(T)                    \
  DECL_VEC3_CLEAR(T) {                          \
    self->x = self->y = self->z = 0;            \
  }

#define DECL_VEC3_DOT(T) T VEC3_METHOD(T, dot)(const VEC3_TYPE(T)* v0, const VEC3_TYPE(T)* v1)
#define DEFINE_VEC3_DOT(T)                                \
  DECL_VEC3_DOT(T) {                                      \
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z; \
  }

#define DECL_VEC3_NORM2(T) T VEC3_METHOD(T, norm2)(const VEC3_TYPE(T)* self)
#define DEFINE_VEC3_NORM2(T)                    \
  DECL_VEC3_NORM2(T) {                          \
    return VEC3_METHOD(T, dot)(self, self);     \
  }

#define DECL_VEC3_NORM(T) T VEC3_METHOD(T, norm)(const VEC3_TYPE(T)* self)
#define DEFINE_VEC3_NORM(T)                     \
  DECL_VEC3_NORM(T) {                           \
    return sqrt(VEC3_METHOD(T, norm2)(self));   \
  }

#define DECL_VEC3_NORMALIZE(T) void VEC3_METHOD(T, normalize)(VEC3_TYPE(T)* self)
#define DEFINE_VEC3_NORMALIZE(T)                                    \
  DECL_VEC3_NORMALIZE(T) {                                          \
    OP_FUNC_TEMPLATE(vec3, div, scalar)(self, VEC3_METHOD(T, norm)(self)); \
  }

#define DEFINE_VEC3_METHODS(T)                  \
  DEFINE_VEC3_ALL_OP_FUNCS(T)                   \
  DEFINE_VEC3_FILL(T)                           \
  DEFINE_VEC3_CLEAR(T)                          \
  DEFINE_VEC3_DOT(T)                            \
  DEFINE_VEC3_NORM2(T)                          \
  DEFINE_VEC3_NORM(T)                           \
  DEFINE_VEC3_NORMALIZE(T)

#define DECL_VEC3_METHODS(T)                    \
  DECL_VEC3_ALL_OP_FUNCS(T)                     \
  DECL_VEC3_FILL(T);                            \
  DECL_VEC3_CLEAR(T);                           \
  DECL_VEC3_DOT(T);                             \
  DECL_VEC3_NORM2(T);                           \
  DECL_VEC3_NORM(T);                            \
  DECL_VEC3_NORMALIZE(T);

#endif
