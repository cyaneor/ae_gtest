#include <gtest/gtest.h>
#include <ae/wstr_raw.h>

TEST(ae_wstr_raw_find_char, find_existing_char) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5; // длина строки без нулевого терминала
  ae_wchar_t value = L'l';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[2]); // 'l' находится на позиции 2
}

TEST(ae_wstr_raw_find_char, find_non_existing_char) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'z';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr); // символ 'z' не найден
}

// Тест 3: Поиск в пустой строке
TEST(ae_wstr_raw_find_char, empty_string) {
  const ae_wchar_t str[] = L"";
  ae_usize_t len = 0;
  ae_wchar_t value = L'a';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr); // строка пустая, ничего не найдено
}

TEST(ae_wstr_raw_find_char, zero_length) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 0;
  ae_wchar_t value = L'H';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr); // длина 0, ничего не найдено
}

TEST(ae_wstr_raw_find_char, repeated_chars) {
  const ae_wchar_t str[] = L"aaaba";
  ae_usize_t len = 5;
  ae_wchar_t value = L'a';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[0]); // первое 'a' на позиции 0
}

TEST(ae_wstr_raw_find_char, case_sensitive) {
  const ae_wchar_t str[] = L"Hello";
  ae_usize_t len = 5;
  ae_wchar_t value = L'h';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr); // 'h' не найден, так как в строке 'H'
}

TEST(ae_wstr_raw_find_char, unicode_chars) {
  const ae_wchar_t str[] = L"Привет";
  ae_usize_t len = 6;
  ae_wchar_t value = L'в';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[3]); // 'в' на позиции 3
}

// Тест 8: Поиск за пределами указанной длины
TEST(ae_wstr_raw_find_char, beyond_length) {
  const ae_wchar_t str[] = L"Hello\0World";
  ae_usize_t len = 5;
  ae_wchar_t value = L'W';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr); // 'W' за пределами len
}

TEST(ae_wstr_raw_find_char, find_null_char) {
  const ae_wchar_t str[] = L"Hello\0";
  ae_usize_t len = 6; // включая нулевой символ
  ae_wchar_t value = L'\0';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, &str[5]); // нулевой символ на позиции 5
}

TEST(ae_wstr_raw_find_char, null_string) {
  const ae_wchar_t *str = nullptr;
  ae_usize_t len = 0;
  ae_wchar_t value = L'a';
  const ae_wstr_raw_t result = ae_wstr_raw_find_char(str, len, value);
  EXPECT_EQ(result, nullptr); // str = nullptr и len = 0
}

TEST(ae_wstr_raw_find_of_null_terminator, empty_string) {
  const ae_wchar_t str[] = L"";
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str);  // Ожидаем указатель на начало (где сразу L'\0')
}

TEST(ae_wstr_raw_find_of_null_terminator, single_char_string) {
  const ae_wchar_t str[] = L"a";
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 1);  // Ожидаем указатель на L'\0' после 'a'
}

TEST(ae_wstr_raw_find_of_null_terminator, multi_char_string) {
  const ae_wchar_t str[] = L"hello";
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(str);
  EXPECT_EQ(result, str + 5);  // Ожидаем указатель на L'\0' после "hello"
}

TEST(ae_wstr_raw_find_of_null_terminator, null_pointer) {
  const ae_wstr_raw_t result = ae_wstr_raw_find_of_null_terminator(nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_wstr_raw_len, empty_string) {
  const ae_wchar_t str[] = L"";
  ae_usize_t len = ae_wstr_raw_len(str);
  EXPECT_EQ(len, 0);  // Длина пустой строки — 0
}

TEST(ae_wstr_raw_len, single_char_string) {
  const ae_wchar_t str[] = L"a";
  ae_usize_t len = ae_wstr_raw_len(str);
  EXPECT_EQ(len, 1);  // Длина строки с одним символом — 1
}

TEST(ae_wstr_raw_len, multi_char_string) {
  const ae_wchar_t str[] = L"hello";
  ae_usize_t len = ae_wstr_raw_len(str);
  EXPECT_EQ(len, 5);  // Длина строки "hello" — 5
}