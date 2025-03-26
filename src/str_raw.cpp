#include <gtest/gtest.h>
#include <ae/str_raw.h>

TEST(ae_str_raw_find_char, find_existing_char_in_middle) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = 'w';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str + 7);
  EXPECT_EQ(*result, 'w');
}

TEST(ae_str_raw_find_char, find_first_char) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = 'H';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str);
  EXPECT_EQ(*result, 'H');
}

TEST(ae_str_raw_find_char, find_last_char) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = '!';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str + len - 1);
  EXPECT_EQ(*result, '!');
}

TEST(ae_str_raw_find_char, char_not_found) {
  const char *str = "Hello, world!";
  ae_usize_t len = strlen(str);
  ae_char_t value = 'z';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_str_raw_find_char, empty_string) {
  const char *str = "";
  ae_usize_t len = 0;
  ae_char_t value = 'a';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_str_raw_find_char, single_char_string_found) {
  const char *str = "x";
  ae_usize_t len = 1;
  ae_char_t value = 'x';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, str);
  EXPECT_EQ(*result, 'x');
}

TEST(ae_str_raw_find_char, single_char_string_not_found) {
  const char *str = "x";
  ae_usize_t len = 1;
  ae_char_t value = 'y';
  const ae_char_t * result = ae_str_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_str_raw_find_of_null_terminator, non_empty_string) {
  const char *str = "Hello, world!";
  const ae_char_t * result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + strlen(str));
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_find_of_null_terminator, empty_string) {
  const char *str = "";
  const ae_char_t * result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str);
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_find_of_null_terminator, single_char_string) {
  const char *str = "x";
  const ae_char_t * result = ae_str_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 1);
  EXPECT_EQ(*result, '\0');
}

TEST(ae_str_raw_find_of_null_terminator, multiple_nulls) {
  const char str[] = {'H', 'i', '\0', '!', '\0'};
  const ae_char_t * result = ae_str_raw_find_of_null_terminator(str);
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

TEST(ae_str_raw_set_value, set_single_character) {
  ae_char_t buffer[1] = {'A'};
  ae_char_t value = 'Z';

  ae_str_raw_set_value(buffer, 1, value);

  EXPECT_EQ(buffer[0], 'Z');
}

TEST(ae_str_raw_set_value, set_multiple_characters) {
  ae_char_t buffer[3] = {'A', 'B', 'C'};
  ae_char_t value = 'X';

  ae_str_raw_set_value(buffer, 3, value);

  EXPECT_EQ(buffer[0], 'X');
  EXPECT_EQ(buffer[1], 'X');
  EXPECT_EQ(buffer[2], 'X');
}

TEST(ae_str_raw_set_value, set_zero_length) {
  ae_char_t buffer[3] = {'A', 'B', 'C'};
  ae_char_t value = 'X';

  ae_str_raw_set_value(buffer, 0, value);

  EXPECT_EQ(buffer[0], 'A');
  EXPECT_EQ(buffer[1], 'B');
  EXPECT_EQ(buffer[2], 'C');
}

TEST(ae_str_raw_set_value, set_different_values) {
  ae_char_t buffer[2] = {'A', 'B'};

  ae_str_raw_set_value(buffer, 2, '1');
  EXPECT_EQ(buffer[0], '1');
  EXPECT_EQ(buffer[1], '1');

  ae_str_raw_set_value(buffer, 2, '@');
  EXPECT_EQ(buffer[0], '@');
  EXPECT_EQ(buffer[1], '@');
}

TEST(ae_str_raw_set_value, set_special_characters) {
  ae_char_t buffer[2] = {'A', 'B'};
  ae_char_t value = '\n';

  ae_str_raw_set_value(buffer, 2, value);

  EXPECT_EQ(buffer[0], '\n');
  EXPECT_EQ(buffer[1], '\n');
}

TEST(ae_str_raw_copy, copy_equal_length) {
  ae_char_t src[] = {'A', 'B', 'C'};
  ae_char_t dst[3] = {0};

  ae_char_t * result = ae_str_raw_copy(dst, 3, src, 3);

  EXPECT_EQ(dst[0], 'A');
  EXPECT_EQ(dst[1], 'B');
  EXPECT_EQ(dst[2], 'C');
  EXPECT_EQ(result, dst + 3);
}

TEST(ae_str_raw_copy, copy_shorter_source) {
  ae_char_t src[] = {'X', 'Y'};
  ae_char_t dst[3] = {'A', 'B', 'C'};

  ae_char_t * result = ae_str_raw_copy(dst, 3, src, 2);

  EXPECT_EQ(dst[0], 'X');
  EXPECT_EQ(dst[1], 'Y');
  EXPECT_EQ(dst[2], 'C');  // Последний символ не должен измениться
  EXPECT_EQ(result, dst + 2);
}

TEST(ae_str_raw_copy, copy_longer_source) {
  ae_char_t src[] = {'P', 'Q', 'R', 'S'};
  ae_char_t dst[2] = {0};

  ae_char_t * result = ae_str_raw_copy(dst, 2, src, 4);

  EXPECT_EQ(dst[0], 'P');
  EXPECT_EQ(dst[1], 'Q');
  EXPECT_EQ(result, dst + 2);
}

TEST(ae_str_raw_copy, copy_zero_length) {
  ae_char_t src[] = {'A', 'B'};
  ae_char_t dst[2] = {'X', 'Y'};

  ae_char_t * result = ae_str_raw_copy(dst, 0, src, 2);

  EXPECT_EQ(dst[0], 'X');
  EXPECT_EQ(dst[1], 'Y');
  EXPECT_EQ(result, dst);
}

TEST(ae_str_raw_copy, copy_empty_source) {
  ae_char_t src[] = {0};
  ae_char_t dst[2] = {'A', 'B'};

  ae_char_t * result = ae_str_raw_copy(dst, 2, src, 0);

  EXPECT_EQ(dst[0], 'A');
  EXPECT_EQ(dst[1], 'B');
  EXPECT_EQ(result, dst);
}

TEST(ae_str_raw_copy, copy_special_characters) {
  ae_char_t src[] = {'\n', '\t', '\0'};
  ae_char_t dst[3] = {0};

  ae_char_t * result = ae_str_raw_copy(dst, 3, src, 3);

  EXPECT_EQ(dst[0], '\n');
  EXPECT_EQ(dst[1], '\t');
  EXPECT_EQ(dst[2], '\0');
  EXPECT_EQ(result, dst + 3);
}