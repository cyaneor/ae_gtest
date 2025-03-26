#include <ae/memory_range_initializer.h>
#include <ae/runtime_error_code.h>
#include <ae/runtime_error.h>
#include <ae/memory_range.h>
#include <gtest/gtest.h>

TEST(ae_memory_range_get_begin, valid_pointer) {
  int value = 42;
  ae_memory_range_t range = ae_memory_range_initializer(&value, nullptr);

  EXPECT_EQ(ae_memory_range_get_begin(&range), &value);
}

TEST(ae_memory_range_get_begin, null_pointer) {
  EXPECT_EQ(ae_memory_range_get_begin(nullptr), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_get_end, valid_pointer) {
  int value = 84;
  ae_memory_range_t range = ae_memory_range_initializer(&value, nullptr);

  EXPECT_EQ(ae_memory_range_get_begin(&range), &value);
}

TEST(ae_memory_range_get_end, null_pointer) {
  EXPECT_EQ(ae_memory_range_get_end(nullptr), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_is_empty, empty_range) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x1000));
  EXPECT_TRUE(ae_memory_range_is_empty(&range));
}

TEST(ae_memory_range_is_empty, non_empty_range) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));
  EXPECT_FALSE(ae_memory_range_is_empty(&range));
}

TEST(ae_memory_range_is_empty, null_pointer) {
  EXPECT_TRUE(ae_memory_range_is_empty(nullptr));
}

TEST(ae_memory_range_diff, empty_range) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x1000));
  EXPECT_EQ(ae_memory_range_diff(&range), 0);
}

TEST(ae_memory_range_diff, non_empty_range) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));
  EXPECT_EQ(ae_memory_range_diff(&range),
            static_cast<ae_ptrdiff_t>(0x2000 - 0x1000));
}

TEST(ae_memory_range_diff, end_less_than_begin) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x2000), reinterpret_cast<void *>(0x1000));
  EXPECT_LT(ae_memory_range_diff(&range), 0);
}

TEST(ae_memory_range_diff, null_pointer) {
  EXPECT_EQ(ae_memory_range_diff(nullptr), 0);
}

TEST(ae_memory_range_has_ptr, contains_without_end) {
  ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));

  EXPECT_TRUE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x1000)));

  EXPECT_TRUE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x2000)));
  EXPECT_TRUE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x1500)));

  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x0FFF)));
  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x2001)));
}

TEST(ae_memory_range_has_ptr, null_pointer) {
  EXPECT_FALSE(
      ae_memory_range_has_ptr(nullptr, reinterpret_cast<void *>(0x1000)));

  ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));

  EXPECT_FALSE(ae_memory_range_has_ptr(&range, nullptr));
}

TEST(ae_memory_range_has_ptr, contains_pointer_when_end_is_less_than_begin) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x2000), reinterpret_cast<void *>(0x1000));

  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x1500)));
  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x2000)));
  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x1000)));
  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x0FFF)));
  EXPECT_FALSE(
      ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(0x2500)));
}

TEST(ae_memory_range_has_ptr, nullptr_in_begin) {
  const ae_memory_range_t range =
      ae_memory_range_initializer(nullptr, reinterpret_cast<void *>(100));
  EXPECT_FALSE(ae_memory_range_has_ptr(&range, nullptr));
}

TEST(ae_memory_range_has_ptr, nullptr_in_end) {
  const ae_memory_range_t range =
      ae_memory_range_initializer(reinterpret_cast<void *>(50), nullptr);
  EXPECT_FALSE(ae_memory_range_has_ptr(&range, nullptr));
}

TEST(ae_memory_range_has_ptr, both_begin_and_end_are_null) {
  constexpr ae_memory_range_t range = ae_memory_range_empty_initializer();
  EXPECT_FALSE(ae_memory_range_has_ptr(&range, nullptr));
  EXPECT_FALSE(ae_memory_range_has_ptr(&range, reinterpret_cast<void *>(1)));
}

TEST(ae_memory_range_has_range, valid_range) {
  ae_memory_range_t self = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x3000));
  EXPECT_TRUE(ae_memory_range_has_range(&self, (void *)0x1500, (void *)0x2500));
}

TEST(ae_memory_range_has_range, pointer_inside_range) {
  ae_memory_range_t self = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));
  EXPECT_TRUE(ae_memory_range_has_range(&self, (void *)0x1250, (void *)0x1500));
}

TEST(ae_memory_range_has_range, pointer_outside_range) {
  ae_memory_range_t self = ae_memory_range_empty_initializer();
  EXPECT_FALSE(ae_memory_range_has_range(&self, nullptr, nullptr));
  EXPECT_FALSE(
      ae_memory_range_has_range(&self, (void *)0x1250, (void *)0x1500));
}

TEST(ae_memory_range_is_valid, empty_range) {
  constexpr ae_memory_range_t empty_range = ae_memory_range_empty_initializer();
  EXPECT_FALSE(ae_memory_range_is_valid(&empty_range));
}

TEST(ae_memory_range_is_valid, valid_range) {
  const ae_memory_range_t valid_range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));
  EXPECT_TRUE(ae_memory_range_is_valid(&valid_range));
}

TEST(ae_memory_range_is_valid, range_with_begin_equal_to_end) {
  const ae_memory_range_t range_with_equal_begin_end =
      ae_memory_range_initializer(reinterpret_cast<void *>(0x1000),
                                  reinterpret_cast<void *>(0x1000));
  EXPECT_TRUE(ae_memory_range_is_valid(&range_with_equal_begin_end));
}

TEST(ae_memory_range_is_valid, invalid_range) {
  const ae_memory_range_t invalid_range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x2000), reinterpret_cast<void *>(0x1000));
  EXPECT_FALSE(ae_memory_range_is_valid(&invalid_range));
}

TEST(ae_memory_range_is_valid, begin_is_null) {
  const ae_memory_range_t range =
      ae_memory_range_initializer(nullptr, reinterpret_cast<void *>(0x1000));
  EXPECT_FALSE(ae_memory_range_is_valid(&range));
}

TEST(ae_memory_range_is_valid, end_is_null) {
  const ae_memory_range_t range =
      ae_memory_range_initializer(reinterpret_cast<void *>(0x1000), nullptr);
  EXPECT_FALSE(ae_memory_range_is_valid(&range));
}

TEST(ae_memory_range_size, valid_memory_range) {
  const ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));

  EXPECT_TRUE(ae_memory_range_is_valid(&range));
  EXPECT_EQ(ae_memory_range_size(&range), 4096);
}

TEST(ae_memory_range_size, invalid_memory_range) {
  ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x2000), reinterpret_cast<void *>(0x1000));

  EXPECT_FALSE(ae_memory_range_is_valid(&range));
  EXPECT_EQ(ae_memory_range_size(&range), 0);
}

TEST(ae_memory_range_is_multiple_of_size,
     total_size_is_multiple_of_element_size) {
  char buffer[100]; // Создаем буфер размером 100 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 100);

  EXPECT_TRUE(ae_memory_range_is_multiple_of_size(&range, 10)); // 100 % 10 == 0
}

TEST(ae_memory_range_is_multiple_of_size,
     total_size_is_not_multiple_of_element_size) {
  char buffer[105]; // Создаем буфер размером 105 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 105);

  EXPECT_FALSE(
      ae_memory_range_is_multiple_of_size(&range, 10)); // 105 % 10 != 0
}

TEST(ae_memory_range_is_multiple_of_size, element_size_is_one) {
  char buffer[50]; // Создаем буфер размером 50 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 50);

  EXPECT_TRUE(ae_memory_range_is_multiple_of_size(&range, 1)); // 50 % 1 == 0
}

TEST(ae_memory_range_is_multiple_of_size, total_size_is_zero) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_TRUE(ae_memory_range_is_multiple_of_size(&range, 1)); // 0 % 1 == 0
}

TEST(ae_memory_range_is_multiple_of_size, element_size_is_zero) {
  char buffer[50]; // Создаем буфер размером 50 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 50);

  EXPECT_FALSE(ae_memory_range_is_multiple_of_size(&range, 0));
}

TEST(ae_memory_range_is_multiple_of_size, negative_range) {
  char buffer[100]; // Создаем буфер размером 100 байт
  ae_memory_range_t range = ae_memory_range_initializer(buffer + 100, buffer);

  EXPECT_TRUE(ae_memory_range_is_multiple_of_size(&range, 1)); // -100 % 1 == 0
}

TEST(ae_memory_range_is_aligned, both_pointers_aligned) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_TRUE(ae_memory_range_is_aligned(&range, 16)); // 64 и 0 выровнены по 16
}

TEST(ae_memory_range_is_aligned, begin_pointer_not_aligned) {
  char buffer[64];
  ae_memory_range_t range =
      ae_memory_range_initializer(buffer + 1, buffer + 64);

  EXPECT_FALSE(ae_memory_range_is_aligned(&range, 16)); // 1 не выровнен по 16
}

TEST(ae_memory_range_is_aligned, end_pointer_not_aligned) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 63);

  EXPECT_FALSE(ae_memory_range_is_aligned(&range, 16)); // 63 не выровнен по 16
}

TEST(ae_memory_range_is_aligned, both_pointers_not_aligned) {
  char buffer[64];
  ae_memory_range_t range =
      ae_memory_range_initializer(buffer + 1, buffer + 63);

  EXPECT_FALSE(
      ae_memory_range_is_aligned(&range, 16)); // 1 и 63 не выровнены по 16
}

TEST(ae_memory_range_is_aligned, alignment_size_is_zero) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_FALSE(
      ae_memory_range_is_aligned(&range, 0)); // Проверка деления на ноль
}

TEST(ae_memory_range_is_aligned, alignment_size_is_one) {
  char buffer[64];
  ae_memory_range_t range = ae_memory_range_initializer(buffer, buffer + 64);

  EXPECT_TRUE(ae_memory_range_is_aligned(&range, 1)); // 64 и 0 выровнены по 1
}

TEST(ae_memory_range_set, reset_with_valid_pointers) {
  int a = 5, b = 10;
  ae_memory_range_t range = ae_memory_range_initializer(&a, &b);

  // Проверяем, что begin указывает на a
  EXPECT_EQ(ae_memory_range_get_begin(&range), &a);

  // Проверяем, что end указывает на b
  EXPECT_EQ(ae_memory_range_get_end(&range), &b);
}

TEST(ae_memory_range_set, reset_with_null_pointer) {
  ae_memory_range_set(nullptr, nullptr, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_set, reset_with_null_begin) {
  ae_memory_range_t range;
  int b = 10;

  // Сбрасываем указатели с нулевым begin
  ae_memory_range_set(&range, nullptr, &b);

  // Проверяем, что begin равен nullptr
  EXPECT_EQ(ae_memory_range_get_begin(&range), nullptr);

  // Проверяем, что end указывает на b
  EXPECT_EQ(ae_memory_range_get_end(&range), &b);
}

TEST(ae_memory_range_set, reset_with_null_end) {
  ae_memory_range_t range;
  int a = 5;

  // Сбрасываем указатели с нулевым end
  ae_memory_range_set(&range, &a, nullptr);

  // Проверяем, что begin указывает на a
  EXPECT_EQ(ae_memory_range_get_begin(&range), &a);

  // Проверяем, что end равен nullptr
  EXPECT_EQ(ae_memory_range_get_end(&range), nullptr);
}

TEST(ae_memory_range_assign, assign_with_valid_range) {
  ae_memory_range_t source;
  ae_memory_range_t destination;

  int a = 5, b = 10;

  // Инициализируем исходный диапазон
  ae_memory_range_set(&source, &a, &b);

  // Присваиваем диапазон
  ae_memory_range_assign(&destination, &source);

  // Проверяем, что begin указывает на a
  EXPECT_EQ(ae_memory_range_get_begin(&destination), &a);

  // Проверяем, что end указывает на b
  EXPECT_EQ(ae_memory_range_get_end(&destination), &b);
}

TEST(ae_memory_range_assign, assign_with_null_source) {
  ae_memory_range_t destination;

  // Проверка на нулевой указатель
  ae_memory_range_assign(&destination, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_assign, assign_with_null_destination) {
  ae_memory_range_t source;
  int a = 5, b = 10;

  // Инициализируем исходный диапазон
  ae_memory_range_set(&source, &a, &b);

  // Проверка на нулевой указатель
  ae_memory_range_assign(nullptr, &source);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_assign, assign_with_both_null) {
  // Проверка на оба нулевых указателя
  ae_memory_range_assign(nullptr, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_range_assign_with_validate, assigns_valid_range) {
  ae_memory_range_t src = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1000), reinterpret_cast<void *>(0x2000));
  ae_memory_range_t dst = ae_memory_range_empty_initializer();

  ae_memory_range_assign_with_validate(&dst, &src);
  EXPECT_TRUE(ae_memory_range_is_equal(&dst, &src));
}

TEST(ae_memory_range_assign_with_validate, rejects_invalid_range) {
  ae_memory_range_t src = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x3000), reinterpret_cast<void *>(0x2000));
  ae_memory_range_t dst = ae_memory_range_empty_initializer();

  ae_memory_range_assign_with_validate(&dst, &src);
  EXPECT_FALSE(ae_memory_range_is_equal(&dst, &src));
}

TEST(ae_memory_range_assign_with_validate, assigns_empty_range) {
  ae_memory_range_t src = ae_memory_range_empty_initializer();
  ae_memory_range_t dst = ae_memory_range_empty_initializer();

  ae_memory_range_assign_with_validate(&dst, &src);
  EXPECT_TRUE(ae_memory_range_is_equal(&dst, &src));
}

TEST(ae_memory_range_set_with_size, begin_is_null_pointer) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();
  ae_memory_range_set_with_size(&range, nullptr, 100);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_INVALID_ARGUMENT);
}

TEST(ae_memory_range_set_with_fallback, valid_pointer) {
  int data[10] = {};
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  ae_memory_range_set_with_fallback(&range, data, 10 * sizeof(data[0]));

  EXPECT_EQ(ae_memory_range_get_begin(&range), data);
  EXPECT_EQ(ae_memory_range_get_end(&range), &data[10]);
}

TEST(ae_memory_range_set_with_fallback, begin_is_null_pointer) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  ae_memory_range_set_with_fallback(&range, nullptr, 10);

  EXPECT_EQ(ae_memory_range_get_begin(&range), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range), nullptr);
}

TEST(ae_memory_range_clear, clear_function_resets_start_and_end_to_nullptr) {
  ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678));

  EXPECT_NE(ae_memory_range_get_begin(&range), nullptr);
  EXPECT_NE(ae_memory_range_get_end(&range), nullptr);

  ae_memory_range_clear(&range);

  EXPECT_EQ(ae_memory_range_get_begin(&range), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range), nullptr);
}

TEST(ae_memory_range_clear, clear_function_does_not_affect_other_data) {
  ae_memory_range_t range = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678));

  void *old_start = ae_memory_range_get_begin(&range);
  void *old_end = ae_memory_range_get_end(&range);

  ae_memory_range_clear(&range);

  EXPECT_EQ(ae_memory_range_get_begin(&range), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range), nullptr);
  EXPECT_NE(old_start, nullptr);
  EXPECT_NE(old_end, nullptr);
}

TEST(ae_memory_range_swap, swap_changes_values) {
  ae_memory_range_t range1 = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678));
  ae_memory_range_t range2 = ae_memory_range_initializer(
      reinterpret_cast<void *>(0xABCD), reinterpret_cast<void *>(0xEF01));

  ae_memory_range_swap(&range1, &range2);

  EXPECT_EQ(ae_memory_range_get_begin(&range1),
            reinterpret_cast<void *>(0xABCD));
  EXPECT_EQ(ae_memory_range_get_end(&range1), reinterpret_cast<void *>(0xEF01));

  EXPECT_EQ(ae_memory_range_get_begin(&range2),
            reinterpret_cast<void *>(0x1234));
  EXPECT_EQ(ae_memory_range_get_end(&range2), reinterpret_cast<void *>(0x5678));
}

TEST(ae_memory_range_swap, swap_with_nullptr) {
  ae_memory_range_t range1 = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678));
  ae_memory_range_t range2 = ae_memory_range_empty_initializer();

  ae_memory_range_swap(&range1, &range2);

  EXPECT_EQ(ae_memory_range_get_begin(&range1), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range1), nullptr);

  EXPECT_EQ(ae_memory_range_get_begin(&range2),
            reinterpret_cast<void *>(0x1234));
  EXPECT_EQ(ae_memory_range_get_end(&range2), reinterpret_cast<void *>(0x5678));
}

TEST(ae_memory_range_swap, swap_both_nullptr) {
  ae_memory_range_t range1 = ae_memory_range_empty_initializer();
  ae_memory_range_t range2 = ae_memory_range_empty_initializer();

  ae_memory_range_swap(&range1, &range2);

  EXPECT_EQ(ae_memory_range_get_begin(&range1), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range1), nullptr);

  EXPECT_EQ(ae_memory_range_get_begin(&range2), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range2), nullptr);
}

TEST(ae_memory_range_exchange, exchange_changes_values) {
  ae_memory_range_t range1 = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678));
  ae_memory_range_t range2 = ae_memory_range_initializer(
      reinterpret_cast<void *>(0xABCD), reinterpret_cast<void *>(0xEF01));

  ae_memory_range_exchange(&range1, &range2);

  EXPECT_EQ(ae_memory_range_get_begin(&range2), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range2), nullptr);

  EXPECT_EQ(ae_memory_range_get_begin(&range1),
            reinterpret_cast<void *>(0xABCD));
  EXPECT_EQ(ae_memory_range_get_end(&range1), reinterpret_cast<void *>(0xEF01));
}

TEST(ae_memory_range_exchange, exchange_with_nullptr) {
  ae_memory_range_t range1 = ae_memory_range_initializer(
      reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678));
  ae_memory_range_t range2 = ae_memory_range_empty_initializer();

  ae_memory_range_exchange(&range1, &range2);

  EXPECT_EQ(ae_memory_range_get_begin(&range1), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range1), nullptr);
  EXPECT_EQ(ae_memory_range_get_begin(&range2), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range2), nullptr);
}

TEST(ae_memory_range_exchange, exchange_both_nullptr) {
  ae_memory_range_t range1 = ae_memory_range_empty_initializer();
  ae_memory_range_t range2 = ae_memory_range_empty_initializer();

  ae_memory_range_exchange(&range1, &range2);

  EXPECT_EQ(ae_memory_range_get_begin(&range1), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range1), nullptr);
  EXPECT_EQ(ae_memory_range_get_begin(&range2), nullptr);
  EXPECT_EQ(ae_memory_range_get_end(&range2), nullptr);
}

TEST(ae_memory_range_at_from_begin, valid_index) {
  char data[] = "ABCDEFGHI";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  EXPECT_EQ(ae_memory_range_at_from_begin(&range, 0), &data[0]);
  EXPECT_EQ(ae_memory_range_at_from_begin(&range, 5), &data[5]);
  EXPECT_EQ(ae_memory_range_at_from_begin(&range, 9), &data[9]);
}

TEST(ae_memory_range_at_from_begin, index_out_of_range) {
  char data[] = "ABCDEFGHI";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  EXPECT_EQ(ae_memory_range_at_from_begin(&range, 10), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);

  EXPECT_EQ(ae_memory_range_at_from_begin(&range, 11), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at_from_begin, negative_index) {
  char data[] = "ABCDEFGHI";
  ae_memory_range_t range = ae_memory_range_initializer(data, data + 10);

  EXPECT_EQ(ae_memory_range_at_from_begin(&range, -1), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at_from_begin, empty_range) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_EQ(ae_memory_range_at_from_begin(&range, 0), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at_from_end, valid_offset) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  void *ptr = ae_memory_range_at_from_end(&range, 0);
  EXPECT_EQ(ptr, memory + 9);

  ptr = ae_memory_range_at_from_end(&range, 1);
  EXPECT_EQ(ptr, memory + 8);

  ptr = ae_memory_range_at_from_end(&range, 9);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_at_from_end, out_of_bounds) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  ae_memory_range_at_from_end(&range, 10);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at_from_end, empty_range) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_EQ(ae_memory_range_at_from_end(&range, 0), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at_from_end, single_element_range) {
  ae_u8_t memory[1] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[1]);

  void *ptr = ae_memory_range_at_from_end(&range, 0);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_at_from_end, multiple_elements_range) {
  ae_u8_t memory[5] = {1, 2, 3, 4, 5};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[5]);

  EXPECT_EQ(*(static_cast<ae_u8_t *>(ae_memory_range_at_from_end(&range, 0))),
            5);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ae_memory_range_at_from_end(&range, 1))),
            4);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ae_memory_range_at_from_end(&range, 2))),
            3);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ae_memory_range_at_from_end(&range, 3))),
            2);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ae_memory_range_at_from_end(&range, 4))),
            1);
}

TEST(ae_memory_range_at, from_begin) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  void *ptr = ae_memory_range_at(&range, 3, false);
  EXPECT_EQ(ptr, memory + 3);

  ptr = ae_memory_range_at(&range, 7, false);
  EXPECT_EQ(ptr, memory + 7);

  ptr = ae_memory_range_at(&range, 0, false);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_at, from_end) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  void *ptr = ae_memory_range_at(&range, 0, true);
  EXPECT_EQ(ptr, memory + 9);

  ptr = ae_memory_range_at(&range, 1, true);
  EXPECT_EQ(ptr, memory + 8);

  ptr = ae_memory_range_at(&range, 9, true);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_at, out_of_bounds_reversed) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  ae_memory_range_at(&range, 10, true);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at, out_of_bounds_not_reversed) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  ae_memory_range_at(&range, 10, false);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_at, single_element_range) {
  ae_u8_t memory[1] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[1]);

  void *ptr = ae_memory_range_at(&range, 0, false);
  EXPECT_EQ(ptr, memory);

  ptr = ae_memory_range_at(&range, 0, true);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_at, empty_range) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_EQ(ae_memory_range_at(&range, 0, false), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);

  EXPECT_EQ(ae_memory_range_at(&range, 0, true), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_front, valid_range) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  void *ptr = ae_memory_range_front(&range);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_front, empty_range) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();

  EXPECT_EQ(ae_memory_range_front(&range), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_range_front, single_element_range) {
  ae_u8_t memory[1] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[1]);

  void *ptr = ae_memory_range_front(&range);
  EXPECT_EQ(ptr, memory);
}

TEST(ae_memory_range_front, multiple_elements_range) {
  ae_u8_t memory[5] = {1, 2, 3, 4, 5};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[5]);

  void *ptr = ae_memory_range_front(&range);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ptr)), 1);
}

TEST(ae_memory_range_front, zero_element) {
  ae_u8_t memory[10] = {0};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[10]);

  memory[0] = 100;

  void *ptr = ae_memory_range_front(&range);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ptr)), 100);
}

TEST(ae_memory_block_back, multiple_elements_range) {
  ae_u8_t memory[5] = {1, 2, 3, 4, 5};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[5]);

  void *ptr = ae_memory_range_back(&range);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ptr)), 5);
}

TEST(ae_memory_block_back, single_element_range) {
  ae_u8_t memory[1] = {10};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[1]);

  void *ptr = ae_memory_range_back(&range);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ptr)), 10);
}

TEST(ae_memory_block_back, empty_range) {
  ae_memory_range_t range = ae_memory_range_empty_initializer();
  EXPECT_EQ(ae_memory_range_back(&range), nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_block_back, range_with_zero_first_element) {
  ae_u8_t memory[5] = {0, 2, 3, 4, 5};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[5]);

  void *ptr = ae_memory_range_back(&range);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ptr)), 5);
}

TEST(ae_memory_block_back, range_with_identical_elements) {
  ae_u8_t memory[5] = {7, 7, 7, 7, 7};
  ae_memory_range_t range = ae_memory_range_initializer(memory, &memory[5]);

  void *ptr = ae_memory_range_back(&range);
  EXPECT_EQ(*(static_cast<ae_u8_t *>(ptr)), 7);
}
