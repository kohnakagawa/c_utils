#include "string_c.h"
#include <stdio.h>
#include <string.h>

void test_new_string();
void test_char_to_string();
void test_append_string();
void test_append_char();
void test_slice_string();

int main() {
  test_new_string();
  test_slice_string();
  test_append_string();
  test_append_char();
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

