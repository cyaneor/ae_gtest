#include <gtest/gtest.h>

#include <ae/str_raw.h>
#include <ae/runtime_error.h>
#include <ae/runtime_error_code.h>
#include <ae/static_string_size.h>

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
  const char src[] = "Hello, World!";
  const ae_usize_t len = ae_static_string_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "Hello, World!");
}

TEST(ae_str_raw_copy_with, copy_empty_string) {
  const char src[] = "";
  const ae_usize_t len = ae_static_string_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "");
}

TEST(ae_str_raw_copy_with, copy_string_with_null_character) {
  const char *src = "Hello\0World";
  const ae_usize_t len = 5;

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "Hello");
}

TEST(ae_str_raw_copy_with, copy_exact_length_string) {
  const char src[] = "ExactLengthTest";
  const ae_usize_t len = ae_static_string_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_STREQ(dest, "ExactLengthTest");
}

TEST(ae_str_raw_copy_with, empty_copy) {
  const char src[] = "";
  const ae_usize_t len = ae_static_string_size(src);
  ae_char_t dest[1] = {};

  ae_str_raw_copy_with(dest, src, len);
  EXPECT_EQ(dest[0], '\0');
}

TEST(ae_str_raw_copy, copy_normal_string) {
  const char src[] = "Hello, World!";
  const ae_usize_t len = ae_static_string_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "Hello, World!");
}

TEST(ae_str_raw_copy, copy_empty_string) {
  const char src[] = "";
  const ae_usize_t len = ae_static_string_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "");
}

TEST(ae_str_raw_copy, copy_string_with_null_character) {
  const char *src = "Hello\0World";
  const ae_usize_t len = 5;

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "Hello");
}

TEST(ae_str_raw_copy, copy_exact_length_string) {
  const char src[] = "ExactLengthTest";
  const ae_usize_t len = ae_static_string_size(src);

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
  const char str[] = "Hello";
  const char src[] = "World!";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "HelloWorld!");
}

TEST(ae_str_raw_cat_from, concat_two_non_empty_strings) {
  const char str[] = "Hello";
  const char src[] = "World!";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "HelloWorld!");
}

TEST(ae_str_raw_cat_from, concat_empty_to_non_empty_string) {
  const char str[] = "Hello";
  const char src[] = "";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "Hello");
}

TEST(ae_str_raw_cat_from, concat_with_null_character) {
  const char str[] = "Hello\0World";
  const char src[] = " Test!";
  const ae_usize_t str_len = 5;
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "Hello Test!");
}

TEST(ae_str_raw_cat_from, concat_exact_length) {
  const char str[] = "Exact";
  const char src[] = "Length";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat_from(result, 0, str, str_len);
  ae_str_raw_cat_from(result, str_len, src, src_len);
  EXPECT_STREQ(result, "ExactLength");
}

TEST(ae_str_raw_cat_with, concat_with_empty_string) {
  const char str[] = "Hello";
  const char src[] = "World!";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat(result, str);
  ae_str_raw_cat_with(result, src, src_len);
  EXPECT_STREQ(result, "HelloWorld!");
}

TEST(ae_str_raw_cat_with, concat_two_non_empty_strings) {
  const char str[] = "Hello";
  const char src[] = "World!";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat(result, str);
  ae_str_raw_cat_with(result, src, src_len);

  EXPECT_STREQ(result, "HelloWorld!");
}

TEST(ae_str_raw_cat_with, concat_empty_to_non_empty_string) {
  const char str[] = "Hello";
  const char src[] = "";
  const ae_usize_t str_len = ae_static_string_size(str);
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat(result, str);
  ae_str_raw_cat_with(result, src, src_len);
  EXPECT_STREQ(result, "Hello");
}

TEST(ae_str_raw_cat_with, concat_with_null_character) {
  const char str[] = "Hello\0World";
  const char src[] = " Test!";
  const ae_usize_t str_len = 5;
  const ae_usize_t src_len = ae_static_string_size(src);

  ae_char_t result[str_len + src_len + 1];
  memset(result, 0, sizeof(result));

  ae_str_raw_cat(result, str);
  ae_str_raw_cat_with(result, src, src_len);
  EXPECT_STREQ(result, "Hello Test!");
}

TEST(str_raw_shift_left_with, shift_zero)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, 0);
    EXPECT_STREQ(result, "Hello");
}

TEST(str_raw_shift_left_with, shift_equal_to_length)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, len);
    EXPECT_STREQ(result, "\0");
}

TEST(str_raw_shift_left_with, shift_greater_than_length)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, len + 1);
    EXPECT_STREQ(result, "\0");
}

TEST(str_raw_shift_left_with, shift_by_one)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, 1);
    EXPECT_STREQ(result, "ello");
}

TEST(str_raw_shift_left_with, shift_by_two)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, 2);
    EXPECT_STREQ(result, "llo");
}

TEST(str_raw_shift_left_with, shift_by_three)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, 3);
    EXPECT_STREQ(result, "lo");
}

TEST(str_raw_shift_left_with, shift_longer_than_string)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = str_raw_shift_left_with(str, len, 100);
    EXPECT_STREQ(result, "\0");
}

TEST(str_raw_shift_left, shift_by_two) {
    ae_char_t str[] = "abcdef";
    ae_char_t expected[] = "cdef";
    
    EXPECT_STREQ(str_raw_shift_left(str, 2), expected);
}

TEST(str_raw_shift_left, shift_by_zero) {
    ae_char_t str[] = "abcdef";
    ae_char_t expected[] = "abcdef";
    
    EXPECT_STREQ(str_raw_shift_left(str, 0), expected);
}

TEST(str_raw_shift_left, shift_by_length) {
    ae_char_t str[] = "abcdef";
    ae_char_t expected[] = "";
    
    EXPECT_STREQ(str_raw_shift_left(str, 6), expected);
}

TEST(str_raw_shift_left, shift_on_empty_string) {
    ae_char_t str[] = "";
    ae_char_t expected[] = "";
    
    EXPECT_STREQ(str_raw_shift_left(str, 3), expected);
}

TEST(str_raw_shift_left, shift_by_more_than_length) {
    ae_char_t str[] = "abc";
    ae_char_t expected[] = "";
    
    EXPECT_STREQ(str_raw_shift_left(str, 5), expected);
}

TEST(str_raw_shift_right_for, shift_less_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t len = 6;
    ae_usize_t shift = 2;
    ae_char_t value = 'X';

    ae_char_t expected[] = "XXabcd";
    str_raw_shift_right_for(str, len, shift, value);
    EXPECT_STREQ(str, expected);
}

TEST(str_raw_shift_right_for, shift_greater_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t len = 6;
    ae_usize_t shift = 8;
    ae_char_t value = 'X';
    
    ae_char_t expected[] = "\0abcdef";
    str_raw_shift_right_for(str, len, shift, value);
    EXPECT_STREQ(str, expected);
}

TEST(str_raw_shift_right_for, no_shift)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t len = 6;
    ae_usize_t shift = 0;
    ae_char_t value = 'X';
    
    ae_char_t expected[] = "abcdef";
    str_raw_shift_right_for(str, len, shift, value);
    EXPECT_STREQ(str, expected);
}

TEST(str_raw_shift_right_for, empty_string)
{
    ae_char_t str[] = "";
    ae_usize_t len = 0;
    ae_usize_t shift = 2;
    ae_char_t value = 'X';
    
    ae_char_t expected[] = "";
    str_raw_shift_right_for(str, len, shift, value);
    EXPECT_STREQ(str, expected);
}

TEST(str_raw_shift_right_for, fill_value)
{
    ae_char_t str[] = "hello";
    ae_usize_t len = 5;
    ae_usize_t shift = 3;
    ae_char_t value = 'Z';
    
    ae_char_t expected[] = "ZZZhe";
    str_raw_shift_right_for(str, len, shift, value);
    EXPECT_STREQ(str, expected);
}

TEST(str_raw_shift_right_for, edge_case)
{
    ae_char_t str[] = "xyz";
    ae_usize_t len = 3;
    ae_usize_t shift = 3;
    ae_char_t value = 'A';

    ae_char_t expected[] = "\0yz";
    str_raw_shift_right_for(str, len, shift, value);
    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right_with, shift_less_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t len = 6;
    ae_usize_t shift = 2;

    ae_char_t expected[] = "  abcd";
    str_raw_shift_right_with(str, len, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right_with, shift_greater_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t len = 6;
    ae_usize_t shift = 8;

    ae_char_t expected[] = "\0bcdef";
    str_raw_shift_right_with(str, len, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right_with, no_shift)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t len = 6;
    ae_usize_t shift = 0;

    ae_char_t expected[] = "abcdef";
    str_raw_shift_right_with(str, len, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right_with, empty_string)
{
    ae_char_t str[] = "";
    ae_usize_t len = 0;
    ae_usize_t shift = 2;

    ae_char_t expected[] = "";
    str_raw_shift_right_with(str, len, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right_with, fill_space)
{
    ae_char_t str[] = "hello";
    ae_usize_t len = 5;
    ae_usize_t shift = 3;

    ae_char_t expected[] = "   he";
    str_raw_shift_right_with(str, len, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right_with, edge_case)
{
    ae_char_t str[] = "xyz";
    ae_usize_t len = 3;
    ae_usize_t shift = 3;

    ae_char_t expected[] = "\0yz";
    str_raw_shift_right_with(str, len, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right, shift_less_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t shift = 2;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "  abcd";
    str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right, shift_greater_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t shift = 8;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "\0bcdef";
    str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right, no_shift)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t shift = 0;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "abcdef";
    str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right, empty_string)
{
    ae_char_t str[] = "";
    ae_usize_t shift = 2;

    ae_char_t expected[] = "";
    str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, 1), 0);
}

TEST(str_raw_shift_right, fill_space)
{
    ae_char_t str[] = "hello";
    ae_usize_t shift = 3;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "   he";
    str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(str_raw_shift_right, edge_case)
{
    ae_char_t str[] = "xyz";
    ae_usize_t shift = 3;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "\0yz\0";
    str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}