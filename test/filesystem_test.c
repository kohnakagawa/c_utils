#include "filesystem.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

const char data[][128] = {
  "Temperature 305",
  "Pressure 1",
  "Number 1000",
  "Viscosity 12"
};

void write_to_file(const char* fname) {
  FILE* fp = xfopen(fname, "w");
  const int num_data = sizeof(data) / sizeof(data[0]);
  for (int i = 0; i < num_data; i++) {
    fprintf(fp, "%s\n", data[i]);
  }
  xfclose(fp);
}

void test_readlinest() {
  const char* fname = "./sample.txt";
  write_to_file(fname);

  FILE* fp = xfopen(fname, "r");
  vector_ptr_string* vptr_string = readlines(fp);
  const size_t num_lines = vector_ptr_string_size(vptr_string);
  for (size_t i = 0; i < num_lines; i++) {
    CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(vptr_string, i)),
                           data[i]);
  }
  delete_splitted_strings(vptr_string);
  xfclose(fp);
}

int main() {
  CU_pSuite fsystem_suite = NULL;
  CU_initialize_registry();
  fsystem_suite = CU_add_suite("file_system", NULL, NULL);
  CU_add_test(fsystem_suite, "readlines", test_readlinest);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
