#include <gtest/gtest.h>
#include <ae/str_raw.h>

TEST(ae_str_raw_find_char, find_existing_char_in_middle) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = 'w';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str + 7);
  EXPECT_EQ(*result, 'w');
}

TEST(ae_str_raw_find_char, find_first_char) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = 'H';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str);
  EXPECT_EQ(*result, 'H');
}

TEST(ae_str_raw_find_char, find_last_char) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = '!';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str + len - 1);
  EXPECT_EQ(*result, '!');
}

TEST(ae_str_raw_find_char, char_not_found) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = 'z';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_str_raw_find_char, empty_string) {
  const char *str = "";
  ae_usize_t len = 0;
  ae_char_t value = 'a';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_str_raw_find_char, single_char_string_found) {
  const char *str = "x";
  ae_usize_t len = 1;
  ae_char_t value = 'x';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str);
  EXPECT_EQ(*result, 'x');
}

TEST(ae_str_raw_find_char, single_char_string_not_found) {
  const char *str = "x";
  ae_usize_t len = 1;
  ae_char_t value = 'y';
  const ae_str_raw_t result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_str_raw_find_of_null_terminator, non_empty_string) {
  const char *str = "Hello, world!";
  const ae_str_raw_t result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + strlen(str));
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_find_of_null_terminator, empty_string) {
  const char *str = "";
  const ae_str_raw_t result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str);
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_find_of_null_terminator, single_char_string) {
  const char *str = "x";
  const ae_str_raw_t result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 1);
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_find_of_null_terminator, multiple_nulls) {
  const char str[] = {'H', 'i', '\0', '!', '\0'};
  const ae_str_raw_t result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 2);
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_len, non_empty_string) {
  const char *str = "Hello, world!";
  ae_usize_t result = ae_str_raw_len(str);
  EXPECT_EQ(result, strlen(str));
  EXPECT_EQ(result, 13);
}

TEST(ae_str_raw_len, empty_string) {
  const char *str = "";
  ae_usize_t result = ae_str_raw_len(str);
  EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len, single_char_string) {
  const char *str = "x";
  ae_usize_t result = ae_str_raw_len(str);
  EXPECT_EQ(result, 1);
}

TEST(ae_str_raw_len, multiple_nulls) {
  const char str[] = {'H', 'i', '\0', '!', '\0'};
  ae_usize_t result = ae_str_raw_len(str);
  EXPECT_EQ(result, 2);
}