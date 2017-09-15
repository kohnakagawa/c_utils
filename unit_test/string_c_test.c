#include "string_c.h"
#include <stdio.h>
#include <string.h>

void test_new_string();
void test_char_to_string();
void test_append_string();
void test_append_char();
void test_slice_string();
void test_split_string();
void test_eq_string();
void test_string_to_other();

int main() {
  test_new_string();
  test_slice_string();
  test_append_string();
  test_append_char();
  test_split_string();
  test_eq_string();
  test_string_to_other();
  return 0;
}

void test_new_string() {
  string* str0 = new_string_from_char("The Institute");
  string* str1 = new_string_from_char("for solid State Physics");
  printf("%s %s\n", string_to_char(str0), string_to_char(str1));
  string* str2 = new_string_from_string(str1);

  printf("\"%s\" (expected: \"%s\")\n", string_to_char(str2), string_to_char(str1));

  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
}

void test_append_string() {
  string* ptr_str0 = new_string();
  string* ptr_str1 = new_string();
  string* ptr_str2 = new_string();
  string* empty0   = new_string();
  string* empty1   = new_string();

  append_char(ptr_str0, "The Institute ");
  append_char(ptr_str1, "for Solid State Physics (ISSP) ");
  append_char(ptr_str2, "of the University of Tokyo");
  append_char(empty0, "");
  append_char(empty1, "");

  printf("concatenation of \"%s\" and \"%s\" is ", string_to_char(ptr_str0), string_to_char(ptr_str1));
  append_string(ptr_str0, ptr_str1);
  printf("\"%s\"\n", string_to_char(ptr_str0));

  printf("concatenation of \"%s\" and \"%s\" is ", string_to_char(ptr_str0), string_to_char(ptr_str2));
  append_string(ptr_str0, ptr_str2);
  printf("\"%s\"\n", string_to_char(ptr_str0));

  printf("len = %d (exptected is %d)\n", strlen_string(ptr_str0), strlen("The Institute for Solid State Physics (ISSP) of the University of Tokyo"));

  printf("\"%s\" + \"%s\" = ", string_to_char(empty0), string_to_char(ptr_str0));
  append_string(empty0, ptr_str0);
  printf("\"%s\"\n", string_to_char(empty0));

  printf("\"%s\" + \"%s\" = ", string_to_char(ptr_str0), string_to_char(empty1));
  append_string(ptr_str0, empty1);
  printf("\"%s\"\n", string_to_char(ptr_str0));

  delete_string(ptr_str0);
  delete_string(ptr_str1);
  delete_string(ptr_str2);
  delete_string(empty0);
  delete_string(empty1);
}

void test_append_char() {
  string* ptr_str0 = new_string();
  append_char(ptr_str0, "");
  append_char(ptr_str0, "Thisisapen.");
  printf("\"%s\" (expected is \"%s\") \n", string_to_char(ptr_str0), "Thisisapen.");
  printf("len = %d (expected is %d)\n", strlen_string(ptr_str0), strlen("Thisisapen."));
  delete_string(ptr_str0);
}

void test_slice_string() {
  string* ptr_str0 = new_string();
  string* ptr_str1 = new_string();

  append_char(ptr_str0, "Thisisapen.");
  append_char(ptr_str1, "Thisisapen.");

  string* sliced0 = slice_string(ptr_str0, 0, 4);
  string* sliced1 = slice_string(ptr_str0, 2, -5);

  printf("sliced0 = \"%s\" (\"%s\" is expected.)\n", string_to_char(sliced0), "This");
  printf("sliced1 = \"%s\" (\"%s\" is expected.)\n", string_to_char(sliced1), "isis");

  delete_string(ptr_str0);
  delete_string(ptr_str1);
  delete_string(sliced0);
  delete_string(sliced1);
}

void test_split_string() {
  string* ptr_str0 = new_string_from_char("This is a pen.");
  string* ptr_str1 = new_string_from_char("Thisisapen");
  string* ptr_str2 = new_string_from_char("AIUEO\nKAKIKUKEKO\nSASISUSESO\n");
  string* ptr_str3 = new_string_from_char("/path//tsunekoh//nakagawa/koh");

  printf("%s\n", string_to_char(ptr_str0));
  printf("%s\n", string_to_char(ptr_str1));
  printf("%s\n", string_to_char(ptr_str2));
  printf("%s\n", string_to_char(ptr_str3));

  vector_ptr_string* splitted = split_string(ptr_str0, " ");
  size_t splitted_num = vector_ptr_string_size(splitted);
  printf("[");
  for (size_t i = 0; i < splitted_num; i++) {
    printf("%s, ", string_to_char(vector_ptr_string_at_nocheck(splitted, i)));
  }
  printf("]\n");
  delete_splitted_strings(splitted);

  splitted = split_string(ptr_str1, " ");
  splitted_num = vector_ptr_string_size(splitted);
  printf("[");
  for (size_t i = 0; i < splitted_num; i++) {
    printf("%s, ", string_to_char(vector_ptr_string_at_nocheck(splitted, i)));
  }
  printf("]\n");
  delete_splitted_strings(splitted);

  splitted = split_string(ptr_str2, "\n");
  splitted_num = vector_ptr_string_size(splitted);
  printf("[");
  for (size_t i = 0; i < splitted_num; i++) {
    printf("%s, ", string_to_char(vector_ptr_string_at_nocheck(splitted, i)));
  }
  printf("]\n");
  delete_splitted_strings(splitted);

  splitted = split_string(ptr_str3, "/");
  splitted_num = vector_ptr_string_size(splitted);
  printf("splitted_num = %u\n", splitted_num);
  for (size_t i = 0; i < splitted_num; i++) {
    printf("%s, ", string_to_char(vector_ptr_string_at_nocheck(splitted, i)));
  }
  delete_splitted_strings(splitted);

  delete_string(ptr_str0);
  delete_string(ptr_str1);
  delete_string(ptr_str2);
  delete_string(ptr_str3);
}

void test_eq_string() {
  string* str0 = new_string_from_char("This is");
  string* str1 = new_string_from_char("This is");
  string* str2 = new_string_from_char("THIS IS");

  printf("%s == %s: ", string_to_char(str0), string_to_char(str1));
  if (eq_string(str0, str1)) {
    printf("True\n");
  } else {
    printf("False\n");
  }

  printf("%s != %s: ", string_to_char(str0), string_to_char(str2));
  if (!eq_string(str0, str2)) {
    printf("True\n");
  } else {
    printf("False\n");
  }

  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
}

void test_string_to_other() {
  string* str0 = new_string_from_char("10"); // int
  string* str1 = new_string_from_char("10abc"); // int + char mixed
  string* str2 = new_string_from_char("4294967297"); // int64
  string* str3 = new_string_from_char("12.3456"); // float
  string* str4 = new_string_from_char("12.34567890"); // double

  printf("%d (expected 10)\n", string_to_int32_t(str0));
  printf("%lld (expected 4294967297)\n", string_to_int64_t(str2));
  printf("%.4f (expected 12.3456)\n", string_to_float(str3));
  printf("%.8lf (exptected 12.34567890)\n", string_to_double(str4));

  // const int32_t str1_c = string_to_int32_t(str1); // Error occurs at this line

  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
  delete_string(str3);
  delete_string(str4);
}
