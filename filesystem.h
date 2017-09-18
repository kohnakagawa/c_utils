#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

#include "utils.h"
#include "string_c.h"

FILE* xfopen(const char* restrict fname,
             const char* restrict mode);
void xfclose(FILE* fp);
size_t get_file_size(FILE* fp);
vector_ptr_string* readlines(FILE* fp);

#endif
