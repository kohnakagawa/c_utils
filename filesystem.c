#include "filesystem.h"
#include <sys/stat.h>

FILE* xfopen(const char* restrict fname,
             const char* restrict mode) {
  FILE* fp;
  if ((fp = fopen(fname, mode)) == NULL) {
    perror("Error occurs at xfopen");
    exit(1);
  } else {
    return fp;
  }
}

void xfclose(FILE* fp) {
  fclose(fp);
}

/* security issue: http://www.jpcert.or.jp/sc-rules/c-fio19-c.html */
size_t get_file_size(FILE* fp) {
  struct stat stbuf;
  const int fd = fileno(fp);
  if (fstat(fd, &stbuf) == -1) {
    perror("Error occurs at get_file_size");
    exit(1);
  }
  return stbuf.st_size;
}

vector_ptr_string* readlines(FILE* fp) {
  string* buffer = new_string();
  const size_t file_size = get_file_size(fp) + 1; // include '\0'
  resize_noinit_string(buffer, file_size);
  size_t readed_size = fread(string_to_char(buffer), sizeof(char), file_size, fp);
  ECLIB_UNUSED_VAR(readed_size);
  vector_ptr_string* ret = split_string(buffer, "\n");
  delete_string(buffer);
  return ret;
}
