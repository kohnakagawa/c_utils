#include "string_c.h"
#include <string.h>
#include "utils.h"

// NOTE: size <- include '\0'
//       len  <- do not include '\0'
struct string_t {
  char* data;
  size_t capacity;
  size_t size;
};

static size_t get_ptr_from_org(const int addr, const size_t len);
static void expand_capacity_if_needed(string* self, const size_t new_size);

#undef INIT_MAX_DATA_SIZE
#define INIT_MAX_DATA_SIZE 4

string* new_string(void) {
  string* self   = (string*) xmalloc(sizeof(string));
  self->data     = (char*) xmalloc(sizeof(char) * INIT_MAX_DATA_SIZE);
  memset(self->data, '\0', sizeof(char) * INIT_MAX_DATA_SIZE);
  self->capacity = INIT_MAX_DATA_SIZE;
  self->size     = 0;
  return self;
}

void delete_string(string* self) {
  xfree(self->data);
  self->data     = NULL;
  self->capacity = 0;
  self->size     = 0;
  xfree(self);
}

void reserve_string(string* self, const size_t new_capacity) {
  self->capacity = new_capacity;
  char* buffer_new = (char*) xmalloc(self->capacity * sizeof(char));
  strcpy(buffer_new, self->data);
  xfree(self->data);
  self->data = buffer_new;
}

void append_string(string* self, string* str) {
  if (self->size == 0 && str->size == 0) return;
  const size_t new_str_size = self->size + str->size - 1; // NOTE: remove duplication of '\0'
  expand_capacity_if_needed(self, new_str_size);
  strcat(self->data, str->data);
  self->size = new_str_size;
}

void append_char(string* self, const char* src) {
  append_char_n(self, src, strlen(src));
}

void append_char_n(string* self, const char* src, const size_t len) {
  if (len == 0) return;
  const size_t new_str_size = self->size + len;
  expand_capacity_if_needed(self, new_str_size);
  strncat(self->data, src, len);
  self->data[new_str_size - 1] = '\0';
  self->size = new_str_size;
}

char* string_to_char(string* self) {
  return self->data;
}

size_t capacity_string(string* self) {
  return self->capacity;
}

size_t size_string(string* self) {
  return self->size;
}

size_t strlen_string(string* self) {
  return self->size - 1;
}

void char_to_string(string* self, const char* src) {
  char_to_string_n(self, src, strlen(src));
}

void char_to_string_n(string* self, const char* src, const size_t len) {
  const size_t capa_required = len + 1;
  expand_capacity_if_needed(self, capa_required);
  strncpy(self->data, src, len);
  self->data[len] = '\0';
  self->size = capa_required;
}

static size_t get_ptr_from_org(const int addr, const size_t len) {
  if (addr < 0) {
    return (size_t) (addr + (int) len);
  } else {
    return (size_t) addr;
  }
}

static void expand_capacity_if_needed(string* self, const size_t new_size) {
  if (new_size > self->capacity) {
    reserve_string(self, new_size * 2);
  }
}

string* slice_string(string* self, const int beg, const int end) {
  const size_t len = strlen_string(self);
  const size_t beg_from_org = get_ptr_from_org(beg, len);
  const size_t end_from_org = get_ptr_from_org(end, len);

  if (beg_from_org >= end_from_org) {
    DEBUG_PRINT("Cannot slice at %s:%s", __FILE__, __LINE__);
    return NULL;
  }
  if (end_from_org >= len) {
    fprintf(stderr, "%s: at %s %d\n", err_msgs[OUT_OF_RANGE], __FILE__, __LINE__);
    return NULL;
  }

  string* ret = new_string();
  char_to_string_n(ret, self->data + beg_from_org, end_from_org - beg_from_org);
  return ret;
}
