#include "filesystem.h"

void readlines_test();

int main() {
  readlines_test();
}

void readlines_test() {
  FILE* fp = xfopen("sample.txt", "r");
  vector_ptr_string* vptr_string = readlines(fp);
  const size_t num_lines = vector_ptr_string_size(vptr_string);
  for (size_t i = 0; i < num_lines; i++) {
    printf("\"%s\"\n", string_to_char(vector_ptr_string_at_nocheck(vptr_string, i)));
    vector_ptr_string* words_in_line = split_string(vector_ptr_string_at_nocheck(vptr_string, i), " ");
    const size_t num_words = vector_ptr_string_size(words_in_line);
    for (size_t j = 0; j < num_words; j++) {
      printf("\"%s\" ", string_to_char(vector_ptr_string_at_nocheck(words_in_line, j)));
    }
    delete_splitted_strings(words_in_line);
    printf("\n");
  }
  delete_splitted_strings(vptr_string);
  xfclose(fp);
}
