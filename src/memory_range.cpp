#include <ae/memory_range.h>
#include <ae/memory_range_initializer.h>
#include <ae/runtime_error.h>
#include <gtest/gtest.h>

TEST(ae_memory_range_begin, valid_pointer) {
  ae_memory_range_t range;

  int value = 42;
  range.begin = &value;

  EXPECT_EQ(ae_memory_range_begin(&range), &value);
}

TEST(ae_memory_range_begin, null_pointer) {
  EXPECT_EQ(ae_memory_range_begin(nullptr), nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_end, valid_pointer) {
  ae_memory_range_t range;

  int value = 84;
  range.begin = &value;

  EXPECT_EQ(ae_memory_range_begin(&range), &value);
}

TEST(ae_memory_range_end, null_pointer) {
  EXPECT_EQ(ae_memory_range_end(nullptr), nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_empty, empty_range) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x1000);
  EXPECT_TRUE(ae_memory_range_empty(&range));
}

TEST(ae_memory_range_empty, non_empty_range) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);
  EXPECT_FALSE(ae_memory_range_empty(&range));
}

TEST(ae_memory_range_empty, null_pointer) {
  EXPECT_TRUE(ae_memory_range_empty(nullptr));
}

TEST(ae_memory_range_diff, empty_range) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x1000);
  EXPECT_EQ(ae_memory_range_diff(&range), 0);
}

TEST(ae_memory_range_diff, non_empty_range) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);
  EXPECT_EQ(ae_memory_range_diff(&range), (ae_ptrdiff_t)(0x2000 - 0x1000));
}

TEST(ae_memory_range_diff, end_less_than_begin) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x2000, (void *)0x1000);
  EXPECT_LT(ae_memory_range_diff(&range), 0);
}

TEST(ae_memory_range_diff, null_pointer) {
  EXPECT_EQ(ae_memory_range_diff(nullptr), 0);
}

TEST(ae_memory_range_contain_ptr, contains_with_end) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  EXPECT_TRUE(ae_memory_range_contain_ptr(&range, (void *)0x1000, true));
  EXPECT_TRUE(ae_memory_range_contain_ptr(&range, (void *)0x2000, true));
  EXPECT_TRUE(ae_memory_range_contain_ptr(&range, (void *)0x1500, true));

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x0FFF, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x2001, true));
}

TEST(ae_memory_range_contain_ptr, contains_without_end) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  EXPECT_TRUE(ae_memory_range_contain_ptr(&range, (void *)0x1000, false));

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x2000, false));
  EXPECT_TRUE(ae_memory_range_contain_ptr(&range, (void *)0x1500, false));

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x0FFF, false));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x2001, false));
}

TEST(ae_memory_range_contain_ptr, null_pointer) {
  EXPECT_FALSE(ae_memory_range_contain_ptr(nullptr, (void *)0x1000, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(nullptr, (void *)0x1000, false));

  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, false));
}

TEST(ae_memory_range_contain_ptr,
     contains_pointer_when_end_is_less_than_begin) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x2000, (void *)0x1000);

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x1500, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x2000, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x1000, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x0FFF, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)0x2500, true));
}

TEST(ae_memory_range_contain_ptr, nullptr_in_begin) {
  ae_memory_range_t range = ae_memory_range_initializer(nullptr, (void *)100);

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, false));
}

TEST(ae_memory_range_contain_ptr, nullptr_in_end) {
  ae_memory_range_t range = ae_memory_range_initializer((void *)50, nullptr);

  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, false));
}

TEST(ae_memory_range_contain_ptr, both_begin_and_end_are_null) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_TRUE(ae_memory_range_contain_ptr(&range, nullptr, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, nullptr, false));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)1, true));
  EXPECT_FALSE(ae_memory_range_contain_ptr(&range, (void *)1, false));
}

TEST(ae_memory_range_check, empty_range) {
  ae_memory_range_t empty_range = ae_memory_range_empty_initializer();
  EXPECT_TRUE(ae_memory_range_check(&empty_range));
}

TEST(ae_memory_range_check, valid_range) {
  ae_memory_range_t valid_range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);
  EXPECT_TRUE(ae_memory_range_check(&valid_range));
}

TEST(ae_memory_range_check, range_with_begin_equal_to_end) {
  ae_memory_range_t range_with_equal_begin_end =
      ae_memory_range_initializer((void *)0x1000, (void *)0x1000);
  EXPECT_TRUE(ae_memory_range_check(&range_with_equal_begin_end));
}

TEST(ae_memory_range_check, invalid_range) {
  ae_memory_range_t invalid_range =
      ae_memory_range_initializer((void *)0x2000, (void *)0x1000);
  EXPECT_FALSE(ae_memory_range_check(&invalid_range));
}

TEST(ae_memory_range_check, begin_is_null) {
  ae_memory_range_t range =
      ae_memory_range_initializer(nullptr, (void *)0x1000);
  EXPECT_FALSE(ae_memory_range_check(&range));
}

TEST(ae_memory_range_check, end_is_null) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, nullptr);
  EXPECT_FALSE(ae_memory_range_check(&range));
}

TEST(ae_memory_range_total_size, valid_memory_range) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  EXPECT_TRUE(ae_memory_range_check(&range));
  EXPECT_EQ(ae_memory_range_total_size(&range), 4096);
}

TEST(ae_memory_range_total_size, invalid_memory_range) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x2000, (void *)0x1000);

  EXPECT_FALSE(ae_memory_range_check(&range));
  EXPECT_EQ(ae_memory_range_total_size(&range), 0);
}

TEST(ae_memory_range_total_size_multiple_of,
     total_size_is_multiple_of_element_size) {
  char buffer[100]; // Создаем буфер размером 100 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 100);

  EXPECT_TRUE(
      ae_memory_range_total_size_multiple_of(&range, 10)); // 100 % 10 == 0
}

TEST(ae_memory_range_total_size_multiple_of,
     total_size_is_not_multiple_of_element_size) {
  char buffer[105]; // Создаем буфер размером 105 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 105);

  EXPECT_FALSE(
      ae_memory_range_total_size_multiple_of(&range, 10)); // 105 % 10 != 0
}

TEST(ae_memory_range_total_size_multiple_of, element_size_is_one) {
  char buffer[50]; // Создаем буфер размером 50 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 50);

  EXPECT_TRUE(ae_memory_range_total_size_multiple_of(&range, 1)); // 50 % 1 == 0
}

TEST(ae_memory_range_total_size_multiple_of, total_size_is_zero) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_TRUE(ae_memory_range_total_size_multiple_of(&range, 1)); // 0 % 1 == 0
}

TEST(ae_memory_range_total_size_multiple_of, element_size_is_zero) {
  char buffer[50]; // Создаем буфер размером 50 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 50);

  EXPECT_FALSE(ae_memory_range_total_size_multiple_of(&range, 0));
}

TEST(ae_memory_range_total_size_multiple_of, negative_range) {
  char buffer[100]; // Создаем буфер размером 100 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer + 100, buffer);

  EXPECT_TRUE(
      ae_memory_range_total_size_multiple_of(&range, 1)); // -100 % 1 == 0
}

TEST(ae_memory_range_align_of, both_pointers_aligned) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_TRUE(ae_memory_range_align_of(&range, 16)); // 64 и 0 выровнены по 16
}

TEST(ae_memory_range_align_of, begin_pointer_not_aligned) {
  char buffer[64];
  ae_memory_range_t range =
      ae_memory_range_initializer(buffer + 1, buffer + 64);

  EXPECT_FALSE(ae_memory_range_align_of(&range, 16)); // 1 не выровнен по 16
}

TEST(ae_memory_range_align_of, end_pointer_not_aligned) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 63);

  EXPECT_FALSE(ae_memory_range_align_of(&range, 16)); // 63 не выровнен по 16
}

TEST(ae_memory_range_align_of, both_pointers_not_aligned) {
  char buffer[64];
  ae_memory_range_t range =
      ae_memory_range_initializer(buffer + 1, buffer + 63);

  EXPECT_FALSE(
      ae_memory_range_align_of(&range, 16)); // 1 и 63 не выровнены по 16
}

TEST(ae_memory_range_align_of, alignment_size_is_zero) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_FALSE(ae_memory_range_align_of(&range, 0)); // Проверка деления на ноль
}

TEST(ae_memory_range_align_of, alignment_size_is_one) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_TRUE(ae_memory_range_align_of(&range, 1)); // 64 и 0 выровнены по 1
}

TEST(ae_memory_range_size, size_is_multiple_of_element_size) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_EQ(ae_memory_range_size(&range, 16), 4); // 64 / 16 = 4
}

TEST(ae_memory_range_size, size_is_not_multiple_of_element_size) {
  char buffer[65];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 65);

  EXPECT_EQ(ae_memory_range_size(&range, 16), 0);
  EXPECT_EQ(ae_runtime_error_clear_code(),
            AE_RUNTIME_ERROR_SIZE_IS_NOT_MULTIPLE_OF_ELEMENT_SIZE);
}

TEST(ae_memory_range_size, size_is_zero) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer);

  EXPECT_EQ(ae_memory_range_size(&range, 1), 0); // 0 / 1 = 0
}

TEST(ae_memory_range_size, element_size_is_one) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_EQ(ae_memory_range_size(&range, 1), 64); // 64 / 1 = 64
}

TEST(ae_memory_range_size, element_size_is_zero) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_EQ(ae_memory_range_size(&range, 0), 0);
  EXPECT_EQ(ae_runtime_error_clear_code(),
            AE_RUNTIME_ERROR_SIZE_IS_NOT_MULTIPLE_OF_ELEMENT_SIZE);
}

TEST(ae_memory_range_size, negative_range) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer + 64, buffer);

  EXPECT_EQ(ae_memory_range_size(&range, 1), 0); // -64 / 1 = 0
}

TEST(ae_memory_range_reset, reset_with_valid_pointers) {
  ae_memory_range_t range;
  int a = 5, b = 10;

  // Сбрасываем указатели
  ae_memory_range_reset(&range, &a, &b);

  // Проверяем, что begin указывает на a
  EXPECT_EQ(range.begin, &a);

  // Проверяем, что end указывает на b
  EXPECT_EQ(range.end, &b);
}

TEST(ae_memory_range_reset, reset_with_null_pointer) {
  ae_memory_range_reset(nullptr, nullptr, nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_reset, reset_with_null_begin) {
  ae_memory_range_t range;
  int b = 10;

  // Сбрасываем указатели с нулевым begin
  ae_memory_range_reset(&range, nullptr, &b);

  // Проверяем, что begin равен nullptr
  EXPECT_EQ(range.begin, nullptr);

  // Проверяем, что end указывает на b
  EXPECT_EQ(range.end, &b);
}

TEST(ae_memory_range_reset, reset_with_null_end) {
  ae_memory_range_t range;
  int a = 5;

  // Сбрасываем указатели с нулевым end
  ae_memory_range_reset(&range, &a, nullptr);

  // Проверяем, что begin указывает на a
  EXPECT_EQ(range.begin, &a);

  // Проверяем, что end равен nullptr
  EXPECT_EQ(range.end, nullptr);
}

TEST(ae_memory_range_assign, assign_with_valid_range) {
  ae_memory_range_t source;
  ae_memory_range_t destination;

  int a = 5, b = 10;

  // Инициализируем исходный диапазон
  ae_memory_range_reset(&source, &a, &b);

  // Присваиваем диапазон
  ae_memory_range_assign(&destination, &source);

  // Проверяем, что begin указывает на a
  EXPECT_EQ(destination.begin, &a);

  // Проверяем, что end указывает на b
  EXPECT_EQ(destination.end, &b);
}

TEST(ae_memory_range_assign, assign_with_null_source) {
  ae_memory_range_t destination;

  // Проверка на нулевой указатель
  ae_memory_range_assign(&destination, nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_assign, assign_with_null_destination) {
  ae_memory_range_t source;
  int a = 5, b = 10;

  // Инициализируем исходный диапазон
  ae_memory_range_reset(&source, &a, &b);

  // Проверка на нулевой указатель
  ae_memory_range_assign(nullptr, &source);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_assign, assign_with_both_null) {
  // Проверка на оба нулевых указателя
  ae_memory_range_assign(nullptr, nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_assign_with_validate, assigns_valid_range) {
  ae_memory_range_t src =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);
  ae_memory_range_t dst = ae_memory_range_empty_initializer();

  ae_memory_range_assign_with_validate(&dst, &src);
  EXPECT_TRUE(ae_memory_range_equal(&dst, &src));
}

TEST(ae_memory_range_assign_with_validate, rejects_invalid_range) {
  ae_memory_range_t src =
      ae_memory_range_initializer((void *)0x3000, (void *)0x2000);
  ae_memory_range_t dst = ae_memory_range_empty_initializer();

  ae_memory_range_assign_with_validate(&dst, &src);
  EXPECT_FALSE(ae_memory_range_equal(&dst, &src));
}

TEST(ae_memory_range_assign_with_validate, assigns_empty_range) {
  ae_memory_range_t src =
      ae_memory_range_initializer((void *)nullptr, (void *)nullptr);
  ae_memory_range_t dst = ae_memory_range_empty_initializer();

  ae_memory_range_assign_with_validate(&dst, &src);
  EXPECT_TRUE(ae_memory_range_equal(&dst, &src));
}

TEST(ae_memory_range_reset_with_size, begin_is_null_pointer) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();
  ae_memory_range_reset_with_size(&range, nullptr, 100);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_INVALID_ARGUMENT);
}

TEST(ae_memory_range_reset_with_fallback, valid_pointer) {
  int data[10] = {};
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  ae_memory_range_reset_with_fallback(&range, data, 10 * sizeof(data[0]));

  EXPECT_EQ(range.begin, data);
  EXPECT_EQ(range.end, &data[10]);
}

TEST(ae_memory_range_reset_with_fallback, begin_is_null_pointer) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  ae_memory_range_reset_with_fallback(&range, nullptr, 10);

  EXPECT_EQ(range.begin, nullptr);
  EXPECT_EQ(range.end, nullptr);
}

TEST(ae_memory_range_clear, clear_function_resets_start_and_end_to_nullptr) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1234, (void *)0x5678);

  EXPECT_NE(range.begin, nullptr);
  EXPECT_NE(range.end, nullptr);

  ae_memory_range_clear(&range);

  EXPECT_EQ(range.begin, nullptr);
  EXPECT_EQ(range.end, nullptr);
}

TEST(ae_memory_range_clear, clear_function_does_not_affect_other_data) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1234, (void *)0x5678);

  void *old_start = range.begin;
  void *old_end = range.end;

  ae_memory_range_clear(&range);

  EXPECT_EQ(range.begin, nullptr);
  EXPECT_EQ(range.end, nullptr);
  EXPECT_NE(old_start, nullptr);
  EXPECT_NE(old_end, nullptr);
}

TEST(ae_memory_range_shallow_copy,
     copy_superficial_returns_correct_start_and_end) {
  ae_memory_range_t original =
      ae_memory_range_initializer((void *)0x1234, (void *)0x5678);

  ae_memory_range_t copy = ae_memory_range_shallow_copy(&original);

  EXPECT_EQ(copy.begin, original.begin);
  EXPECT_EQ(copy.end, original.end);
}

TEST(ae_memory_range_shallow_copy,
     copy_superficial_creates_distinct_object) {
  ae_memory_range_t original =
      ae_memory_range_initializer((void *)0x1234, (void *)0x5678);

  ae_memory_range_t copy = ae_memory_range_shallow_copy(&original);
  EXPECT_NE(&copy, &original);
}

TEST(ae_memory_range_shallow_copy, copy_superficial_handles_null_pointers) {
  ae_memory_range_t original = ae_memory_range_empty_initializer();
  ae_memory_range_t copy = ae_memory_range_shallow_copy(&original);

  EXPECT_EQ(copy.begin, nullptr);
  EXPECT_EQ(copy.end, nullptr);
}

TEST(ae_memory_range_swap, swap_changes_values) {
  ae_memory_range_t range1 =
      ae_memory_range_make((void *)0x1234, (void *)0x5678);
  ae_memory_range_t range2 =
      ae_memory_range_make((void *)0xABCD, (void *)0xEF01);

  ae_memory_range_swap(&range1, &range2);

  EXPECT_EQ(range1.begin, reinterpret_cast<void *>(0xABCD));
  EXPECT_EQ(range1.end, reinterpret_cast<void *>(0xEF01));

  EXPECT_EQ(range2.begin, reinterpret_cast<void *>(0x1234));
  EXPECT_EQ(range2.end, reinterpret_cast<void *>(0x5678));
}

TEST(ae_memory_range_swap, swap_with_nullptr) {
  ae_memory_range_t range1 =
      ae_memory_range_make((void *)0x1234, (void *)0x5678);
  ae_memory_range_t range2 = ae_memory_range_make_empty();

  ae_memory_range_swap(&range1, &range2);

  EXPECT_EQ(range1.begin, nullptr);
  EXPECT_EQ(range1.end, nullptr);

  EXPECT_EQ(range2.begin, reinterpret_cast<void *>(0x1234));
  EXPECT_EQ(range2.end, reinterpret_cast<void *>(0x5678));
}

TEST(ae_memory_range_swap, swap_both_nullptr) {
  ae_memory_range_t range1 = ae_memory_range_make_empty();
  ae_memory_range_t range2 = ae_memory_range_make_empty();

  ae_memory_range_swap(&range1, &range2);

  EXPECT_EQ(range1.begin, nullptr);
  EXPECT_EQ(range1.end, nullptr);

  EXPECT_EQ(range2.begin, nullptr);
  EXPECT_EQ(range2.end, nullptr);
}

TEST(ae_memory_range_exchange, exchange_changes_values) {
  ae_memory_range_t range1 =
      ae_memory_range_make((void *)0x1234, (void *)0x5678);
  ae_memory_range_t range2 =
      ae_memory_range_make((void *)0xABCD, (void *)0xEF01);

  ae_memory_range_exchange(&range1, &range2);

  EXPECT_EQ(range2.begin, nullptr);
  EXPECT_EQ(range2.end, nullptr);

  EXPECT_EQ(range1.begin, reinterpret_cast<void *>(0xABCD));
  EXPECT_EQ(range1.end, reinterpret_cast<void *>(0xEF01));
}

TEST(ae_memory_range_exchange, exchange_with_nullptr) {
  ae_memory_range_t range1 =
      ae_memory_range_make((void *)0x1234, (void *)0x5678);
  ae_memory_range_t range2 = ae_memory_range_make_empty();

  ae_memory_range_exchange(&range1, &range2);

  EXPECT_EQ(range1.begin, nullptr);
  EXPECT_EQ(range1.end, nullptr);
  EXPECT_EQ(range2.begin, nullptr);
  EXPECT_EQ(range2.end, nullptr);
}

TEST(ae_memory_range_exchange, exchange_both_nullptr) {
  ae_memory_range_t range1 = ae_memory_range_make_empty();
  ae_memory_range_t range2 = ae_memory_range_make_empty();

  ae_memory_range_exchange(&range1, &range2);

  EXPECT_EQ(range1.begin, nullptr);
  EXPECT_EQ(range1.end, nullptr);
  EXPECT_EQ(range2.begin, nullptr);
  EXPECT_EQ(range2.end, nullptr);
}

TEST(ae_memory_range_contain_range, contain_range_within_bounds_with_end) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  void *begin = reinterpret_cast<void *>(0x1500);
  void *end = reinterpret_cast<void *>(0x1800);

  EXPECT_TRUE(ae_memory_range_contain_range(&range, begin, end, true));
}

TEST(ae_memory_range_contain_range, contain_range_with_end) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  void *begin = reinterpret_cast<void *>(0x1500);
  void *end = reinterpret_cast<void *>(0x2000);

  EXPECT_TRUE(ae_memory_range_contain_range(&range, begin, end, true));
}

TEST(ae_memory_range_contain_range, contain_range_outside_bounds) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  void *begin = reinterpret_cast<void *>(0x0500);
  void *end = reinterpret_cast<void *>(0x2500);

  EXPECT_FALSE(ae_memory_range_contain_range(&range, begin, end, true));
}

TEST(ae_memory_range_contain_range, contain_range_partially_within_bounds) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  void *begin = reinterpret_cast<void *>(0x1500);
  void *end = reinterpret_cast<void *>(0x2500);

  EXPECT_FALSE(ae_memory_range_contain_range(&range, begin, end, true));
}

TEST(ae_memory_range_contain_range, contain_range_with_begin_outside) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  void *begin = reinterpret_cast<void *>(0x0500);
  void *end = reinterpret_cast<void *>(0x1500);

  EXPECT_FALSE(ae_memory_range_contain_range(&range, begin, end, true));
}

TEST(ae_memory_range_contain_range, contain_range_without_end) {
  ae_memory_range_t range =
      ae_memory_range_initializer((void *)0x1000, (void *)0x2000);

  void *begin = reinterpret_cast<void *>(0x1500);
  void *end = reinterpret_cast<void *>(0x2000);

  EXPECT_FALSE(ae_memory_range_contain_range(&range, begin, end, false));
}

TEST(ae_memory_range_at, at_valid_index) {
  char data[] = "ABCDEFGHI";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  EXPECT_EQ(ae_memory_range_at(&range, 0), &data[0]);
  EXPECT_EQ(ae_memory_range_at(&range, 5), &data[5]);
  EXPECT_EQ(ae_memory_range_at(&range, 9), &data[9]);
}

TEST(ae_memory_range_at, at_index_out_of_range) {
  char data[] = "ABCDEFGHI";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  EXPECT_EQ(ae_memory_range_at(&range, 10), nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);

  EXPECT_EQ(ae_memory_range_at(&range, 11), nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at, at_negative_index) {
  char data[] = "ABCDEFGHI";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  EXPECT_EQ(ae_memory_range_at(&range, -1), nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at, at_empty_range) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_EQ(ae_memory_range_at(&range, 0), nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_make_sub_range, MakeSubRangeValid) {
  char data[] = "ABCDEFGHIJ";

  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);
  ae_memory_range_t sub_range =
      ae_memory_range_make_sub_range(&range, &data[2], &data[5], true);

  EXPECT_EQ(sub_range.begin, &data[2]);
  EXPECT_EQ(sub_range.end, &data[5]);
}

TEST(ae_memory_range_make_sub_range, make_sub_range_exclusive_end) {
  char data[] = "ABCDEFGHIJ";

  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);
  ae_memory_range_t sub_range =
      ae_memory_range_make_sub_range(&range, &data[2], &data[5], false);

  EXPECT_EQ(sub_range.begin, &data[2]);
  EXPECT_EQ(sub_range.end, &data[5]);
}

TEST(ae_memory_range_make_sub_range, make_sub_range_invalid_begin) {
  char data[] = "ABCDEFGHIJ";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  auto sub_range =
      ae_memory_range_make_sub_range(&range, &data[10], &data[5], true);

  EXPECT_EQ(sub_range.begin, nullptr);
  EXPECT_EQ(sub_range.end, nullptr);
}

TEST(ae_memory_range_make_sub_range, make_sub_range_invalid_end) {
  char data[] = "ABCDEFGHIJ";

  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);
  ae_memory_range_make_sub_range(&range, &data[2], &data[11], true);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_make_sub_range, make_sub_range_empty_range) {
  char data[1] = {};

  ae_memory_range_t range = ae_memory_range_initializer(data, data);
  ae_memory_range_make_sub_range(&range, data, data, true);
  EXPECT_EQ(ae_runtime_error_clear_code(),
            AE_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
}

TEST(ae_memory_range_insert, insert_value_success) {
  char data[] = "ABCDEFGHIJ";
  ae_memory_range_t memory_range = ae_memory_range_initializer(data, &data[11]);

  ae_memory_range_insert(&memory_range, 0, 'a');
  EXPECT_STREQ(data, "aBCDEFGHIJ");
}

TEST(ae_memory_range_insert, insert_value_out_of_bounds) {
  char data[] = "ABCDEFGHIJ";
  ae_memory_range_t memory_range = ae_memory_range_initializer(data, &data[11]);

  ae_memory_range_insert(&memory_range, 100, 'b');
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_insert, insert_value_empty_range) {
  ae_memory_range_t memory_range = ae_memory_range_empty_initializer();
  ae_memory_range_insert(&memory_range, 0, 100);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_insert, insert_value_last_index) {
  char data[] = "ABCDEFGHIJ";
  ae_memory_range_t memory_range = ae_memory_range_initializer(data, &data[11]);

  ae_memory_range_insert(&memory_range, 9, '0');
  EXPECT_STREQ(data, "ABCDEFGHI0");
}

TEST(ae_memory_range_insert_range, insert_range_success) {
  char data[] = "0000000000";
  ae_memory_range_t memory_range = ae_memory_range_initializer(data, &data[11]);

  const char values[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  ae_memory_range_insert_range(&memory_range, 0, values, &values[6]);
  EXPECT_STREQ(data, "ABCDEF0000");
}

TEST(ae_memory_range_insert_range, insert_range_empty_range) {
  ae_memory_range_t memory_range = ae_memory_range_empty_initializer();

  const char values[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  ae_memory_range_insert_range(&memory_range, 0, values, &values[6]);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}
