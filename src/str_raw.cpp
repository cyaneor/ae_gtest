#include <gtest/gtest.h>

#include <ae/str_raw.h>
#include <ae/runtime_error.h>
#include <ae/runtime_error_code.h>

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

TEST(ae_str_raw_copy_ex, copy_normal_string) {
  const char src[] = "Hello, World!";
  const ae_usize_t len = ae_str_raw_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_ex(dest, src, len);
  EXPECT_STREQ(dest, "Hello, World!");
}

TEST(ae_str_raw_copy_ex, copy_empty_string) {
  const char src[] = "";
  const ae_usize_t len = ae_str_raw_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_ex(dest, src, len);
  EXPECT_STREQ(dest, "");
}

TEST(ae_str_raw_copy_ex, copy_string_with_null_character) {
  const char *src = "Hello\0World";
  const ae_usize_t len = 5;

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_ex(dest, src, len);
  EXPECT_STREQ(dest, "Hello");
}

TEST(ae_str_raw_copy_ex, copy_exact_length_string) {
  const char src[] = "ExactLengthTest";
  const ae_usize_t len = ae_str_raw_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy_ex(dest, src, len);
  EXPECT_STREQ(dest, "ExactLengthTest");
}

TEST(ae_str_raw_copy_ex, empty_copy) {
  const char src[] = "";
  const ae_usize_t len = ae_str_raw_size(src);
  ae_char_t dest[1] = {};

  ae_str_raw_copy_ex(dest, src, len);
  EXPECT_EQ(dest[0], '\0');
}

TEST(ae_str_raw_copy, copy_normal_string) {
  const char src[] = "Hello, World!";
  const ae_usize_t len = ae_str_raw_size(src);

  ae_char_t dest[len + 1];
  memset(dest, 0, sizeof(dest));

  ae_str_raw_copy(dest, src);
  EXPECT_STREQ(dest, "Hello, World!");
}

TEST(ae_str_raw_copy, copy_empty_string) {
  const char src[] = "";
  const ae_usize_t len = ae_str_raw_size(src);

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
  const ae_usize_t len = ae_str_raw_size(src);

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

TEST(ae_str_raw_shift_left_ex, shift_zero)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, 0);
    EXPECT_STREQ(result, "Hello");
}

TEST(ae_str_raw_shift_left_ex, shift_equal_to_length)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, len);
    EXPECT_STREQ(result, "\0");
}

TEST(ae_str_raw_shift_left_ex, shift_greater_than_length)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, len + 1);
    EXPECT_STREQ(result, "\0");
}

TEST(ae_str_raw_shift_left_ex, shift_by_one)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, 1);
    EXPECT_STREQ(result, "ello");
}

TEST(ae_str_raw_shift_left_ex, shift_by_two)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, 2);
    EXPECT_STREQ(result, "llo");
}

TEST(ae_str_raw_shift_left_ex, shift_by_three)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, 3);
    EXPECT_STREQ(result, "lo");
}

TEST(ae_str_raw_shift_left_ex, shift_longer_than_string)
{
    ae_char_t str[] = "Hello";
    ae_usize_t len = strlen(str);
    ae_char_t *result = ae_str_raw_shift_left_ex(str, len, 100);
    EXPECT_STREQ(result, "\0");
}

TEST(ae_str_raw_shift_left, shift_by_two) {
    ae_char_t str[] = "abcdef";
    ae_char_t expected[] = "cdef";
    
    EXPECT_STREQ(ae_str_raw_shift_left(str, 2), expected);
}

TEST(ae_str_raw_shift_left, shift_by_zero) {
    ae_char_t str[] = "abcdef";
    ae_char_t expected[] = "abcdef";
    
    EXPECT_STREQ(ae_str_raw_shift_left(str, 0), expected);
}

TEST(ae_str_raw_shift_left, shift_by_length) {
    ae_char_t str[] = "abcdef";
    ae_char_t expected[] = "";
    
    EXPECT_STREQ(ae_str_raw_shift_left(str, 6), expected);
}

TEST(ae_str_raw_shift_left, shift_on_empty_string) {
    ae_char_t str[] = "";
    ae_char_t expected[] = "";
    
    EXPECT_STREQ(ae_str_raw_shift_left(str, 3), expected);
}

TEST(ae_str_raw_shift_left, shift_by_more_than_length) {
    ae_char_t str[] = "abc";
    ae_char_t expected[] = "";
    
    EXPECT_STREQ(ae_str_raw_shift_left(str, 5), expected);
}

TEST(ae_str_raw_shift_right, shift_less_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t shift = 2;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "  abcd";
    ae_str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(ae_str_raw_shift_right, shift_greater_than_len)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t shift = 8;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "\0bcdef";
    ae_str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(ae_str_raw_shift_right, no_shift)
{
    ae_char_t str[] = "abcdef";
    ae_usize_t shift = 0;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "abcdef";
    ae_str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(ae_str_raw_shift_right, empty_string)
{
    ae_char_t str[] = "";
    ae_usize_t shift = 2;

    ae_char_t expected[] = "";
    ae_str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, 1), 0);
}

TEST(ae_str_raw_shift_right, fill_space)
{
    ae_char_t str[] = "hello";
    ae_usize_t shift = 3;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "   he";
    ae_str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(ae_str_raw_shift_right, edge_case)
{
    ae_char_t str[] = "xyz";
    ae_usize_t shift = 3;
    ae_usize_t len = ae_str_raw_len(str);

    ae_char_t expected[] = "\0yz\0";
    ae_str_raw_shift_right(str, shift);

    EXPECT_EQ(memcmp(str, expected, len + 1), 0);
}

TEST(ae_str_raw_trim_left, empty_string) {
    ae_char_t input[] = "";
    ae_char_t* result = ae_str_raw_trim_left(input);
    EXPECT_STREQ(result, "");
}

TEST(ae_str_raw_trim_left, string_with_only_whitespace) {
    ae_char_t input[] = "    \n\r\t\v\x00";
    ae_char_t* result = ae_str_raw_trim_left(input);
    EXPECT_STREQ(result, "");
}

TEST(ae_str_raw_trim_left, string_without_whitespace) {
    ae_char_t input[] = "Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left(input);
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left, string_with_whitespace_at_beginning) {
    ae_char_t input[] = "   Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left(input);
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left, string_with_control_characters_at_beginning) {
    ae_char_t input[] = "\n\t  Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left(input);
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left, string_with_mixed_whitespace_and_text) {
    ae_char_t input[] = " \n\r\t  Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left(input);
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left_ex, empty_string) {
    ae_char_t input[] = "";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, " \n\r\t\v\x00");
    EXPECT_STREQ(result, "");
}

TEST(ae_str_raw_trim_left_ex, string_with_only_trim_characters) {
    ae_char_t input[] = "    \n\r\t\v\x00";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, " \n\r\t\v\x00");
    EXPECT_STREQ(result, "");
}

TEST(ae_str_raw_trim_left_ex, string_without_trim_characters) {
    ae_char_t input[] = "Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, " \n\r\t\v\x00");
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left_ex, string_with_leading_spaces) {
    ae_char_t input[] = "   Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, " \n\r\t\v\x00");
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left_ex, string_with_leading_control_characters) {
    ae_char_t input[] = "\n\t  Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, " \n\r\t\v\x00");
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left_ex, string_with_multiple_trim_characters) {
    ae_char_t input[] = " \n  \t Hello, world!";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, " \n\r\t\v\x00");
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left_ex, string_with_custom_trim_characters) {
    ae_char_t input[] = "abcHello, world!";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, "abc");
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(ae_str_raw_trim_left_ex, string_with_no_matching_trim_characters) {
    ae_char_t input[] = "xyzHello, world!";
    ae_char_t* result = ae_str_raw_trim_left_ex(input, "abc");
    EXPECT_STREQ(result, "xyzHello, world!");
}

TEST(ae_str_raw_concat, concatenate_two_strings) {
  ae_char_t str[50] = "Hello, ";
  const ae_char_t* src = "World!";

  ae_str_raw_concat(str, src);
  EXPECT_STREQ(str, "Hello, World!");
}

TEST(ae_str_raw_concat, concatenate_with_empty_string) {
  ae_char_t str[50] = "Hello, ";
  const ae_char_t* src = "";

  ae_str_raw_concat(str, src);
  EXPECT_STREQ(str, "Hello, ");
}

TEST(ae_str_raw_concat, concatenate_empty_string_with_another) {
  ae_char_t str[50] = "";
  const ae_char_t* src = "World!";

  ae_str_raw_concat(str, src);
  EXPECT_STREQ(str, "World!");
}

TEST(ae_str_raw_concat, null_pointer_input) {
  ae_char_t* str = nullptr;
  const ae_char_t* src = "Test";

  ae_str_raw_concat(str, src);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_str_raw_trim_right, trim_right_spaces) {
  ae_char_t str[50] = "Hello World!   ";
  
  ae_str_raw_trim_right(str);
  EXPECT_STREQ(str, "Hello World!");
}

TEST(ae_str_raw_trim_right, trim_right_newline_and_tabs) {
  ae_char_t str[50] = "Text with newline \n\r\t\v\x00";
  
  ae_str_raw_trim_right(str);
  EXPECT_STREQ(str, "Text with newline");
}

TEST(ae_str_raw_trim_right, trim_right_empty_string) {
  ae_char_t str[50] = "";
  
  ae_str_raw_trim_right(str);
  EXPECT_STREQ(str, "");
}

TEST(ae_str_raw_trim_right, trim_right_no_spaces) {
  ae_char_t str[50] = "NoSpacesHere";
  
  ae_str_raw_trim_right(str);
  EXPECT_STREQ(str, "NoSpacesHere");
}

TEST(ae_str_raw_trim_right, trim_right_spaces_at_start) {
  ae_char_t str[50] = "   LeadingSpaces";
  
  ae_str_raw_trim_right(str);
  EXPECT_STREQ(str, "   LeadingSpaces");
}

TEST(ae_str_raw_trim_right, trim_right_multiple_spaces) {
  ae_char_t str[50] = "Text with multiple spaces     ";
  
  ae_str_raw_trim_right(str);
  EXPECT_STREQ(str, "Text with multiple spaces");
}

TEST(ae_str_raw_trim_right_ex, trim_right_with_spaces) {
  ae_char_t str[50] = "Hello World!   ";
  const char characters[] = " ";

  ae_str_raw_trim_right_ex(str, characters);
  EXPECT_STREQ(str, "Hello World!");
}

TEST(ae_str_raw_trim_right_ex, trim_right_with_newline_and_tabs) {
  ae_char_t str[50] = "Text with newline \n\r\t\v\x00";
  const char characters[] = "\n\r\t\v\x00";

  ae_str_raw_trim_right_ex(str, characters);
  EXPECT_STREQ(str, "Text with newline ");
}

TEST(ae_str_raw_trim_right_ex, trim_right_empty_string) {
  ae_char_t str[50] = "";
  const char characters[] = " \n\r\t\v\x00";

  ae_str_raw_trim_right_ex(str, characters);
  EXPECT_STREQ(str, "");
}

TEST(ae_str_raw_trim_right_ex, trim_right_no_match) {
  ae_char_t str[50] = "NoSpacesHere";
  const char characters[] = " \n\r\t\v\x00";

  ae_str_raw_trim_right_ex(str, characters);
  EXPECT_STREQ(str, "NoSpacesHere");
}

TEST(ae_str_raw_trim_right_ex, trim_right_spaces_at_start) {
  ae_char_t str[50] = "   LeadingSpaces";
  const char characters[] = " ";

  ae_str_raw_trim_right_ex(str, characters);
  EXPECT_STREQ(str, "   LeadingSpaces");
}

TEST(ae_str_raw_trim_right_ex, trim_right_multiple_spaces_and_symbols) {
  ae_char_t str[50] = "Text with multiple spaces \n\r\t   ";
  const char characters[] = " \n\r\t";

  ae_str_raw_trim_right_ex(str, characters);
  EXPECT_STREQ(str, "Text with multiple spaces");
}

TEST(ae_str_raw_trim, trim_ascii_chars)
{
  ae_char_t input[] = "  \tHello World!\t  ";
  ae_char_t* result = ae_str_raw_trim(input);
  
  ae_char_t expected[] = "Hello World!";
  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim, no_trim_needed)
{
  ae_char_t input[] = "HelloWorld";
  ae_char_t* result = ae_str_raw_trim(input);
  
  EXPECT_STREQ(result, input);
}

TEST(ae_str_raw_trim, only_spaces_and_tabs)
{
  ae_char_t input[] = "   \t \t   ";
  ae_char_t* result = ae_str_raw_trim(input);
  
  ae_char_t expected[] = "";
  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim, single_character)
{
  ae_char_t input[] = "a";
  ae_char_t* result = ae_str_raw_trim(input);
  
  ae_char_t expected[] = "a";
  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim, empty_string)
{
  ae_char_t input[] = "";
  ae_char_t* result = ae_str_raw_trim(input);
  
  ae_char_t expected[] = "";
  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim_ex, trim_specific_characters)
{
  ae_char_t input[] = "  \tHello World!  \t";
  ae_char_t trim_chars[] = " \t";

  ae_char_t* result = ae_str_raw_trim_ex(input, trim_chars);
  ae_char_t expected[] = "Hello World!";

  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim_ex, no_characters_to_trim)
{
  ae_char_t input[] = "HelloWorld";
  ae_char_t trim_chars[] = " \t";

  ae_char_t* result = ae_str_raw_trim_ex(input, trim_chars);
  EXPECT_STREQ(result, input);
}

TEST(ae_str_raw_trim_ex, only_trim_characters)
{
  ae_char_t input[] = " \t \t ";
  ae_char_t trim_chars[] = " \t";

  ae_char_t* result = ae_str_raw_trim_ex(input, trim_chars);
  ae_char_t expected[] = "";

  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim_ex, trim_only_spaces)
{
  ae_char_t input[] = "   Hello World!   ";
  ae_char_t trim_chars[] = " ";

  ae_char_t* result = ae_str_raw_trim_ex(input, trim_chars);
  ae_char_t expected[] = "Hello World!";
  EXPECT_STREQ(result, expected);
}

TEST(ae_str_raw_trim_ex, empty_string)
{
  ae_char_t input[] = "";
  ae_char_t trim_chars[] = " \t";

  ae_char_t* result = ae_str_raw_trim_ex(input, trim_chars);
  ae_char_t expected[] = "";

  EXPECT_STREQ(result, expected);
}