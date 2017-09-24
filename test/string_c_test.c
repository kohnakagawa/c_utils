#include "string_c.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>

void test_new_string() {
  string* str0 = new_string_from_char_n("The Institute", 4);
  string* str1 = new_string_from_char("for solid State Physics");
  string* str2 = new_string_from_string(str1);
  string* str3 = new_string();
  CU_ASSERT_STRING_EQUAL(string_to_char(str0), "The ");
  CU_ASSERT_STRING_EQUAL(string_to_char(str2), string_to_char(str1));
  for (size_t i = 0; i < capacity_string(str3); i++) {
    CU_ASSERT_EQUAL(string_to_char(str3)[i], '\0');
  }
  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
  delete_string(str3);
}

void test_append_string() {
  string* str0   = new_string_from_char("The Institute ");
  string* str1   = new_string_from_char("for Solid State Physics (ISSP) ");
  string* str2   = new_string_from_char("of the University of Tokyo");
  string* empty0 = new_string_from_char("");
  string* empty1 = new_string_from_char("");
  append_string(str0, str1);
  CU_ASSERT_STRING_EQUAL(string_to_char(str0), "The Institute for Solid State Physics (ISSP) ");
  append_string(str0, str2);
  CU_ASSERT_STRING_EQUAL(string_to_char(str0),
                         "The Institute for Solid State Physics (ISSP) of the University of Tokyo");
  append_string(empty0, str0);
  CU_ASSERT_STRING_EQUAL(string_to_char(empty0),
                         "The Institute for Solid State Physics (ISSP) of the University of Tokyo");
  append_string(str0, empty1);
  CU_ASSERT_STRING_EQUAL(string_to_char(str0),
                         "The Institute for Solid State Physics (ISSP) of the University of Tokyo");
  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
  delete_string(empty0);
  delete_string(empty1);
}

void test_append_char() {
  string* str0 = new_string();
  string* str1 = new_string_from_char("This is a pen.");

  append_char(str0, "");
  append_char(str0, "Thisisapen.");
  CU_ASSERT_STRING_EQUAL(string_to_char(str0), "Thisisapen.");
  CU_ASSERT_EQUAL(strlen_string(str0), strlen("Thisisapen."));

  append_char(str1, " That is ");
  CU_ASSERT_STRING_EQUAL(string_to_char(str1), "This is a pen. That is ");
  append_char_n(str1, "a pen.  ", 6);
  CU_ASSERT_STRING_EQUAL(string_to_char(str1), "This is a pen. That is a pen.");

  delete_string(str0);
  delete_string(str1);
}

void test_strlen_string() {
  string* str = new_string_from_char("This is a pen.");
  CU_ASSERT_EQUAL(strlen_string(str), strlen("This is a pen."));
  delete_string(str);
}

void test_slice_string() {
  string* str0 = new_string_from_char("Thisisapen.");
  string* sliced0 = slice_string(str0, 0, 4);
  string* sliced1 = slice_string(str0, 2, -5);
  CU_ASSERT_STRING_EQUAL(string_to_char(sliced0), "This");
  CU_ASSERT_STRING_EQUAL(string_to_char(sliced1), "isis");
  delete_string(str0);
  delete_string(sliced0);
  delete_string(sliced1);
}

void test_split_string() {
  string* str0 = new_string_from_char("This is a pen.");
  string* str1 = new_string_from_char("Thisisapen");
  string* str2 = new_string_from_char("AIUEO\nKAKIKUKEKO\nSASISUSESO\n");
  string* str3 = new_string_from_char("/path//tsunekoh//nakagawa/koh");

  vector_ptr_string* splitted = split_string(str0, " ");
  size_t splitted_num = vector_ptr_string_size(splitted);
  CU_ASSERT_EQUAL(splitted_num, 4);
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 0)),
                         "This");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 1)),
                         "is");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 2)),
                         "a");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 3)),
                         "pen.");
  delete_splitted_strings(splitted);

  splitted = split_string(str1, " ");
  splitted_num = vector_ptr_string_size(splitted);
  CU_ASSERT_EQUAL(splitted_num, 1);
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 0)),
                         "Thisisapen");
  delete_splitted_strings(splitted);

  splitted = split_string(str2, "\n");
  splitted_num = vector_ptr_string_size(splitted);
  CU_ASSERT_EQUAL(splitted_num, 3);
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 0)),
                         "AIUEO");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 1)),
                         "KAKIKUKEKO");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 2)),
                         "SASISUSESO");
  delete_splitted_strings(splitted);

  splitted = split_string(str3, "/");
  splitted_num = vector_ptr_string_size(splitted);
  CU_ASSERT_EQUAL(splitted_num, 4);
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 0)),
                         "path");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 1)),
                         "tsunekoh");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 2)),
                         "nakagawa");
  CU_ASSERT_STRING_EQUAL(string_to_char(vector_ptr_string_at_nocheck(splitted, 3)),
                         "koh");
  delete_splitted_strings(splitted);

  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
  delete_string(str3);
}

void test_eq_string() {
  string* str0 = new_string_from_char("This is");
  string* str1 = new_string_from_char("This is");
  string* str2 = new_string_from_char("THIS IS");

  CU_ASSERT_STRING_EQUAL(string_to_char(str0), string_to_char(str1));
  CU_ASSERT_STRING_NOT_EQUAL(string_to_char(str0), string_to_char(str2));

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

  CU_ASSERT_EQUAL(string_to_int32_t(str0), 10);
  CU_ASSERT_EQUAL(string_to_int64_t(str2), 4294967297);
  CU_ASSERT_DOUBLE_EQUAL(string_to_float(str3), 12.3456, 1e-6);
  CU_ASSERT_DOUBLE_EQUAL(string_to_double(str4), 12.34567890, 1e-15);

  // const int32_t str1_c = string_to_int32_t(str1); // Error occurs at this line

  delete_string(str0);
  delete_string(str1);
  delete_string(str2);
  delete_string(str3);
  delete_string(str4);
}

int main() {
  CU_pSuite string_suite;
  CU_initialize_registry();
  string_suite = CU_add_suite("string", NULL, NULL);
  CU_add_test(string_suite, "new_string", test_new_string);
  CU_add_test(string_suite, "append_string", test_append_string);
  CU_add_test(string_suite, "append_char", test_append_char);
  CU_add_test(string_suite, "strlen_string", test_strlen_string);
  CU_add_test(string_suite, "slice_string", test_slice_string);
  CU_add_test(string_suite, "split_string", test_split_string);
  CU_add_test(string_suite, "eq_string", test_eq_string);
  CU_add_test(string_suite, "string_to_other", test_string_to_other);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
