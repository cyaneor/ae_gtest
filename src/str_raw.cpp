#include <gtest/gtest.h>

#include <ae/str_raw.h>
#include <ae/runtime_error.h>
#include <ae/runtime_error_code.h>

TEST(ae_str_raw_len_with, returns_correct_index_for_null_terminator) {
  const ae_char_t *test_str = "Hello";
  ae_usize_t result = ae_str_raw_len_with(test_str, 6);
  EXPECT_EQ(result, 5);
}

TEST(ae_str_raw_len_with,
     returns_correct_index_for_null_terminator_mid_string) {
  const ae_char_t *test_str = "Hell\0o";
  ae_usize_t result = ae_str_raw_len_with(test_str, 6);
  EXPECT_EQ(result, 4);
}

TEST(ae_str_raw_len_with, handles_empty_string) {
  const ae_char_t *test_str = "";
  ae_usize_t result = ae_str_raw_len_with(test_str, 0);
  EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len_with, returns_full_length_if_no_null_terminator) {
  const ae_char_t *test_str = "Hello";
  ae_usize_t result = ae_str_raw_len_with(test_str, 6);
  EXPECT_EQ(result, 5);
}

TEST(ae_str_raw_len_with, handles_null_terminator_at_end) {
  const ae_char_t *test_str = "Test\0";
  ae_usize_t result = ae_str_raw_len_with(test_str, 5);
  EXPECT_EQ(result, 4);
}

TEST(ae_str_raw_len_with, returns_length_for_shorter_string) {
  const ae_char_t *test_str = "Short";
  ae_usize_t result = ae_str_raw_len_with(test_str, 3);
  EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len_with, correctly_handles_null_input) {
  const ae_char_t *test_str = nullptr;
  ae_usize_t result = ae_str_raw_len_with(test_str, 0);
  EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len_with, handles_single_character_string) {
  const ae_char_t *test_str = "A";
  ae_usize_t result = ae_str_raw_len_with(test_str, 1);
  EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len, normal) {
  const ae_char_t str[] = "Hello, world!";
  EXPECT_EQ(ae_str_raw_len(str), 13);
}

TEST(ae_str_raw_len, empty_string) {
  const ae_char_t str[] = "";
  EXPECT_EQ(ae_str_raw_len(str), 0);
}

TEST(ae_str_raw_len, null_pointer) {
  EXPECT_EQ(ae_str_raw_len(nullptr), 0);
}

TEST(ae_str_raw_len, single_character) {
  const ae_char_t str[] = "A";
  EXPECT_EQ(ae_str_raw_len(str), 1);
}

TEST(ae_str_raw_len, long_string) {
  const ae_char_t str[] =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
  EXPECT_EQ(ae_str_raw_len(str), 56);
}

TEST(ae_str_raw_copy_with, copy_normal_string) {
  const char *src = "Hello, World!";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "Hello, World!");
}

TEST(ae_str_raw_copy_with, copy_empty_string) {
  const char *src = "";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "");
}

TEST(ae_str_raw_copy_with, copy_string_with_null_character) {
  const char *src = "Hello\0World";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "Hello");
}

TEST(ae_str_raw_copy_with, copy_exact_length_string) {
  const char *src = "ExactLengthTest";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "ExactLengthTest");
}

TEST(ae_str_raw_copy_with, empty_copy) {
  const char *src = "";
  size_t len = 0;
  ae_char_t dest[1] = {};

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_EQ(dest[0], '\0');
}

TEST(ae_str_raw_copy, copy_normal_string) {
  const char *src = "Hello, World!";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "Hello, World!");
}

TEST(ae_str_raw_copy, copy_empty_string) {
  const char *src = "";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "");
}

TEST(ae_str_raw_copy, copy_string_with_null_character) {
  const char *src = "Hello\0World";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "Hello");
}

TEST(ae_str_raw_copy, copy_exact_length_string) {
  const char *src = "ExactLengthTest";
  size_t len = ae_str_raw_len(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "ExactLengthTest");
}

TEST(ae_str_raw_copy, empty_string) {
  const char *src = "";
  ae_char_t dest[1] = {};

  ae_str_raw_copy(dest, src);
  EXPECT_EQ(dest[0], '\0');
}

TEST(ae_str_raw_copy, null_pointer) {
  ae_char_t *dest = nullptr;
  const char *src = "SomeString";

  ae_str_raw_copy(dest, src);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_str_raw_cat_from, concat_with_empty_string) {
  const char *str = "Hello";
  const char *src = "World!";
  size_t str_len = ae_str_raw_len(str);
  size_t src_len = ae_str_raw_len(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "HelloWorld!");
}

TEST(ae_str_raw_cat_from, concat_two_non_empty_strings) {
  const char *str = "Hello";
  const char *src = "World!";
  size_t str_len = ae_str_raw_len(str);
  size_t src_len = ae_str_raw_len(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "HelloWorld!");
}

TEST(ae_str_raw_cat_from, concat_empty_to_non_empty_string) {
  const char *str = "Hello";
  const char *src = "";
  size_t str_len = ae_str_raw_len(str);
  size_t src_len = ae_str_raw_len(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "Hello");
}

TEST(ae_str_raw_cat_from, concat_with_null_character) {
  const char *str = "Hello\0World";
  const char *src = " Test!";
  size_t str_len = ae_str_raw_len(str);
  size_t src_len = ae_str_raw_len(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "Hello Test!");
}

TEST(ae_str_raw_cat_from, concat_exact_length) {
  const char *str = "Exact";
  const char *src = "Length";
  size_t str_len = ae_str_raw_len(str);
  size_t src_len = ae_str_raw_len(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "ExactLength");
}