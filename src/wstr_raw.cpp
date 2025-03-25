#include <gtest/gtest.h>
#include <ae/wstr_raw.h>

TEST(ae_wstr_raw_find_char, find_existing_char) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'l';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]);
}

TEST(ae_wstr_raw_find_char, find_non_existing_char) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'z';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, empty_string) {
  const ae_wchar_t str[] = L"";
  ae_usize_t len = 0;
  ae_wchar_t value = L'a';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, zero_length) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 0;
  ae_wchar_t value = L'H';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, repeated_chars) {
  const ae_wchar_t str[] = L"aaaba";
  ae_usize_t len = 5;
  ae_wchar_t value = L'a';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[0]);
}

TEST(ae_wstr_raw_find_char, case_sensitive) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'h';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, russian_chars) {
  const ae_wchar_t str[] = L"Привет";
  ae_usize_t len = 6;
  ae_wchar_t value = L'в';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[3]);
}

TEST(ae_wstr_raw_find_char, japanese_chars) {
  const ae_wchar_t str[] = L"こんにちは";
  ae_usize_t len = 5;
  ae_wchar_t value = L'に';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]);
}

TEST(ae_wstr_raw_find_char, arabic_chars) {
  const ae_wchar_t str[] = L"مرحبًا";
  ae_usize_t len = 6;
  ae_wchar_t value = L'ر';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[1]);
}

TEST(ae_wstr_raw_find_char, chinese_chars) {
  const ae_wchar_t str[] = L"你好";
  ae_usize_t len = 3;
  ae_wchar_t value = L'你';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[0]);
}

TEST(ae_wstr_raw_find_char, korean_chars) {
  const ae_wchar_t str[] = L"안녕하세요";
  ae_usize_t len = 5;
  ae_wchar_t value = L'하';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]);
}

TEST(ae_wstr_raw_find_char, beyond_length) {
  const ae_wchar_t str[] = L"Hello\0World";
  ae_usize_t len = 5;
  ae_wchar_t value = L'W';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, find_null_char) {
  const ae_wchar_t str[] = L"Hello\0";
  ae_usize_t len = 6;
  ae_wchar_t value = L'\0';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[5]);
}

TEST(ae_wstr_raw_find_char, null_string) {
  const ae_wchar_t *str = nullptr;
  ae_usize_t len = 0;
  ae_wchar_t value = L'a';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_of_null_terminator, empty_string) {
  const ae_wchar_t str[] = L"";
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str);
}

TEST(ae_wstr_raw_find_of_null_terminator, single_char_string) {
  const ae_wchar_t str[] = L"a";
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 1);
}

TEST(ae_wstr_raw_find_of_null_terminator, multi_char_string) {
  const ae_wchar_t str[] = L"hello";
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 5);
}

TEST(ae_wstr_raw_find_of_null_terminator, null_pointer) {
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_len, empty_string) {
  const ae_wchar_t str[] = L"";
  ae_usize_t len = ae_wstr_raw_len(str);
  EXPECT_EQ(len, 0);
}

TEST(ae_wstr_raw_len, single_char_string) {
  const ae_wchar_t str[] = L"a";
  ae_usize_t len = ae_wstr_raw_len(str);
  EXPECT_EQ(len, 1);
}

TEST(ae_wstr_raw_len, multi_char_string) {
  const ae_wchar_t str[] = L"hello";
  ae_usize_t len = ae_wstr_raw_len(str);
  EXPECT_EQ(len, 5);
}
