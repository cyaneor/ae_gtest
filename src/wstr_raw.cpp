#include <gtest/gtest.h>
#include <ae/wstr_raw.h>

TEST(ae_wstr_raw_find_char, find_existing_char) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'l';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]);
}

TEST(ae_wstr_raw_find_char, find_non_existing_char) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'z';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, empty_string) {
  const ae_wchar_t str[] = L"";
  ae_usize_t len = 0;
  ae_wchar_t value = L'a';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, zero_length) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 0;
  ae_wchar_t value = L'H';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, repeated_chars) {
  const ae_wchar_t str[] = L"aaaba";
  ae_usize_t len = 5;
  ae_wchar_t value = L'a';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[0]);
}

TEST(ae_wstr_raw_find_char, case_sensitive) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'h';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, russian_chars) {
  const ae_wchar_t str[] = L"\u041F\u0440\u0438\u0432\u0435\u0442";  // Привет
  ae_usize_t len = 6;
  ae_wchar_t value = L'\u0432';  // в
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[3]);
}

TEST(ae_wstr_raw_find_char, japanese_chars) {
  const ae_wchar_t str[] = L"\u3053\u3093\u306B\u3061\u306F";  // こんにちは
  ae_usize_t len = 5;
  ae_wchar_t value = L'\u306B';  // に
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]);
}

TEST(ae_wstr_raw_find_char, arabic_chars) {
  const ae_wchar_t str[] = L"\u0645\u0631\u062D\u0628\u064B\u0627";  // مرحبًا
  ae_usize_t len = 6;
  ae_wchar_t value = L'\u0631';  // ر
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[1]);
}

TEST(ae_wstr_raw_find_char, chinese_chars) {
  const ae_wchar_t str[] = L"\u4F60\u597D";  // 你好
  ae_usize_t len = 2;  // Исправлено: длина строки 2, а не 3
  ae_wchar_t value = L'\u4F60';  // 你
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[0]);
}

TEST(ae_wstr_raw_find_char, korean_chars) {
  const ae_wchar_t str[] = L"\uC548\uB155\uD558\uC138\uC694";  // 안녕하세요
  ae_usize_t len = 5;
  ae_wchar_t value = L'\uD558';  // 하
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]);
}

TEST(ae_wstr_raw_find_char, beyond_length) {
  const ae_wchar_t str[] = L"Hello\0World";
  ae_usize_t len = 5;
  ae_wchar_t value = L'W';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_char, find_null_char) {
  const ae_wchar_t str[] = L"Hello\0";
  ae_usize_t len = 6;
  ae_wchar_t value = L'\0';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[5]);
}

TEST(ae_wstr_raw_find_char, null_string) {
  const ae_wchar_t *str = nullptr;
  ae_usize_t len = 0;
  ae_wchar_t value = L'a';
  const ae_wchar_t * result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_find_of_null_terminator, empty_string) {
  const ae_wchar_t str[] = L"";
  const ae_wchar_t * result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str);
}

TEST(ae_wstr_raw_find_of_null_terminator, single_char_string) {
  const ae_wchar_t str[] = L"a";
  const ae_wchar_t * result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 1);
}

TEST(ae_wstr_raw_find_of_null_terminator, multi_char_string) {
  const ae_wchar_t str[] = L"hello";
  const ae_wchar_t * result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 5);
}

TEST(ae_wstr_raw_find_of_null_terminator, null_pointer) {
  const ae_wchar_t * result = ae_wstr_raw_find_of_null_terminator(nullptr);
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

TEST(ae_wstr_raw_set_value, set_single_character) {
  ae_wchar_t buffer[1] = {L'A'};
  ae_wchar_t value = L'Z';

  ae_wstr_raw_set_value(buffer, 1, value);

  EXPECT_EQ(buffer[0], L'Z');
}

TEST(ae_wstr_raw_set_value, set_multiple_characters) {
  ae_wchar_t buffer[3] = {L'A', L'B', L'C'};
  ae_wchar_t value = L'X';

  ae_wstr_raw_set_value(buffer, 3, value);

  EXPECT_EQ(buffer[0], L'X');
  EXPECT_EQ(buffer[1], L'X');
  EXPECT_EQ(buffer[2], L'X');
}

TEST(ae_wstr_raw_set_value, set_zero_length) {
  ae_wchar_t buffer[3] = {L'A', L'B', L'C'};
  ae_wchar_t value = L'X';

  ae_wstr_raw_set_value(buffer, 0, value);

  // Проверяем, что ничего не изменилось
  EXPECT_EQ(buffer[0], L'A');
  EXPECT_EQ(buffer[1], L'B');
  EXPECT_EQ(buffer[2], L'C');
}

TEST(ae_wstr_raw_set_value, set_different_values) {
  ae_wchar_t buffer[2] = {L'A', L'B'};

  // Тест с разными значениями
  ae_wstr_raw_set_value(buffer, 2, L'1');
  EXPECT_EQ(buffer[0], L'1');
  EXPECT_EQ(buffer[1], L'1');

  ae_wstr_raw_set_value(buffer, 2, L'@');
  EXPECT_EQ(buffer[0], L'@');
  EXPECT_EQ(buffer[1], L'@');
}

TEST(ae_wstr_raw_copy, copy_equal_length) {
  ae_wchar_t src[] = {L'A', L'B', L'C'};
  ae_wchar_t dst[3] = {0};

  ae_wchar_t * result = ae_wstr_raw_copy(dst, 3, src, 3);

  EXPECT_EQ(dst[0], L'A');
  EXPECT_EQ(dst[1], L'B');
  EXPECT_EQ(dst[2], L'C');
  EXPECT_EQ(result, dst + 3);
}

TEST(ae_wstr_raw_copy, copy_shorter_source) {
  ae_wchar_t src[] = {L'X', L'Y'};
  ae_wchar_t dst[3] = {L'A', L'B', L'C'};

  ae_wchar_t * result = ae_wstr_raw_copy(dst, 3, src, 2);

  EXPECT_EQ(dst[0], L'X');
  EXPECT_EQ(dst[1], L'Y');
  EXPECT_EQ(dst[2], L'C');  // Последний символ не должен измениться
  EXPECT_EQ(result, dst + 2);
}

TEST(ae_wstr_raw_copy, copy_longer_source) {
  ae_wchar_t src[] = {L'P', L'Q', L'R', L'S'};
  ae_wchar_t dst[2] = {0};

  ae_wchar_t * result = ae_wstr_raw_copy(dst, 2, src, 4);

  EXPECT_EQ(dst[0], L'P');
  EXPECT_EQ(dst[1], L'Q');
  EXPECT_EQ(result, dst + 2);
}

TEST(ae_wstr_raw_copy, copy_zero_length) {
  ae_wchar_t src[] = {L'A', L'B'};
  ae_wchar_t dst[2] = {L'X', L'Y'};

  ae_wchar_t * result = ae_wstr_raw_copy(dst, 0, src, 2);

  EXPECT_EQ(dst[0], L'X');
  EXPECT_EQ(dst[1], L'Y');
  EXPECT_EQ(result, dst);
}

TEST(ae_wstr_raw_copy, copy_empty_source) {
  ae_wchar_t src[] = {0};
  ae_wchar_t dst[2] = {L'A', L'B'};

  ae_wchar_t * result = ae_wstr_raw_copy(dst, 2, src, 0);

  EXPECT_EQ(dst[0], L'A');
  EXPECT_EQ(dst[1], L'B');
  EXPECT_EQ(result, dst);
}