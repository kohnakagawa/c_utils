#ifndef STRING_C_H
#define STRING_C_H

#include <stddef.h>

struct string_t;
typedef struct string_t string;

string* new_string(void);
void delete_string(string* self);
void reserve_string(string* self, const size_t new_capacity);
void append_string(string* self, string* str);
void append_char(string* self, const char* src);
void append_char_n(string* self, const char* src, const size_t len);
size_t capacity_string(string* self);
size_t size_string(string* self);
size_t strlen_string(string* self);
char* string_to_char(string* self);
void char_to_string(string* self, const char* src);
void char_to_string_n(string* self, const char* src, const size_t n);
string* slice_string(string* self, const int beg, const int end);
#endif
