#include <ae/memory_block.h>
#include <ae/memory_block_initializer.h>
#include <ae/runtime_error.h>
#include <ae/static_array_size.h>
#include <gtest/gtest.h>

TEST(ae_memory_block_element_size, valid_pointer) {
  const ae_memory_block_t block = ae_memory_block_empty_initializer(42);
  EXPECT_EQ(ae_memory_block_element_size(&block), 42);
}

TEST(ae_memory_block_element_size, null_pointer) {
  ae_memory_block_element_size(nullptr);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_block_size, valid_pointer) {
  int buffer[] = {0, 1, 2, 3, 4, 5, 6};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[7], sizeof(int));

  EXPECT_EQ(ae_memory_block_size(&block), ae_static_array_size(buffer));
}

TEST(ae_memory_block_size, null_pointer) {
  EXPECT_EQ(ae_memory_block_size(nullptr), 0);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_block_empty, block_is_empty_when_size_is_zero) {
  const ae_memory_block_t block = ae_memory_block_empty_initializer(24);
  EXPECT_TRUE(ae_memory_block_empty(&block));
}

TEST(ae_memory_block_empty, block_is_not_empty_when_size_is_non_zero) {
  char buffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[9], sizeof(char));
  EXPECT_FALSE(ae_memory_block_empty(&block));
}

TEST(ae_memory_block_empty, block_is_not_empty_when_raw_memory_is_not_empty) {
  char buffer[] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[9], sizeof(char));
  EXPECT_FALSE(ae_memory_block_empty(&block));
}

TEST(ae_memory_block_swap, swap_blocks_with_equal_element_size) {
  char self_buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  ae_memory_block_t self =
      ae_memory_block_initializer(self_buffer, &self_buffer[9], sizeof(char));

  char source_buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
  ae_memory_block_t source = ae_memory_block_initializer(
      source_buffer, &source_buffer[9], sizeof(char));

  ae_memory_block_swap(&self, &source);

  EXPECT_EQ(self.begin, &source_buffer[0]);
  EXPECT_EQ(self.end, &source_buffer[9]);
  EXPECT_EQ(source.begin, &self_buffer[0]);
  EXPECT_EQ(source.end, &self_buffer[9]);
}

TEST(ae_memory_block_swap, swap_blocks_with_different_element_size) {
  ae_memory_block_t self = ae_memory_block_empty_initializer(24);
  ae_memory_block_t source = ae_memory_block_empty_initializer(12);

  ae_memory_block_swap(&self, &source);
  EXPECT_EQ(ae_runtime_error_clear_code(),
            AE_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);
}

TEST(ae_memory_block_exchange, swap_blocks_with_equal_element_size) {
  char self_buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  ae_memory_block_t self =
      ae_memory_block_initializer(self_buffer, &self_buffer[9], sizeof(char));

  char source_buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
  ae_memory_block_t source = ae_memory_block_initializer(
      source_buffer, &source_buffer[9], sizeof(char));

  ae_memory_block_exchange(&self, &source);

  EXPECT_EQ(self.begin, &source_buffer[0]);
  EXPECT_EQ(self.end, &source_buffer[9]);
  EXPECT_EQ(source.begin, nullptr);
  EXPECT_EQ(source.end, nullptr);
}

TEST(ae_memory_block_exchange, swap_blocks_with_different_element_size) {
  ae_memory_block_t self = ae_memory_block_empty_initializer(24);
  ae_memory_block_t source = ae_memory_block_empty_initializer(12);

  ae_memory_block_exchange(&self, &source);
  EXPECT_EQ(ae_runtime_error_clear_code(),
            AE_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);
}

TEST(ae_memory_block_element_base_address, valid_pointer_returns_base_address) {
  int buffer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(int));

  const void *ptr =
      ae_memory_block_element_base_address(&block, reinterpret_cast<char *>(&buffer[4]) + 2);

  EXPECT_EQ(ptr, &buffer[4]); // Округление вниз до 4
}

TEST(ae_memory_block_element_base_address, pointer_out_of_range_error) {
  int buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  const ae_memory_block_t block = ae_memory_block_empty_initializer(sizeof(int));
  ae_memory_block_element_base_address(&block, &buffer[4]);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_OUT_OF_RANGE);
}

TEST(ae_memory_block_element_base_address, zero_element_size_error) {
  char buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  const ae_memory_block_t block = ae_memory_block_initializer(buffer, &buffer[10], 0);
  ae_memory_block_element_base_address(&block, (char *)&buffer[4] + 2);
  EXPECT_EQ(ae_runtime_error_clear_code(), AE_RUNTIME_ERROR_ZERO_ELEMENT_SIZE);
}

TEST(ae_memory_block_has_index, valid_index_returns_true) {
  char buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(char));

  EXPECT_TRUE(ae_memory_block_has_index(&block, 0, false)); // Первый элемент
  EXPECT_TRUE(ae_memory_block_has_index(&block, 5, false)); // Средний элемент
  EXPECT_TRUE(ae_memory_block_has_index(&block, 9, false)); // Последний элемент
}

TEST(ae_memory_block_has_index, invalid_index_returns_false) {
  unsigned long long buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(unsigned long long));

  // На один больше максимального
  EXPECT_FALSE(ae_memory_block_has_index(&block, 10, false));

  // Значительно больше максимального
  EXPECT_FALSE(ae_memory_block_has_index(&block, 15, false));
}

TEST(ae_memory_block_at, at_from_begin_valid_index) {
  int buffer[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(int));

  // Проверяем доступ к элементам с начала

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_at_const(&block, 0, false)),
            9); // Первый элемент

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_at_const(&block, 5, false)),
            4); // Шестой элемент

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_at_const(&block, 9, false)),
            0); // Десятый элемент
}

TEST(ae_memory_block_at, at_from_begin_invalid_index) {
  char buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(char));

  EXPECT_EQ(ae_memory_block_at_const(&block, 10, false),
            nullptr); // На один больше максимального

  EXPECT_EQ(ae_memory_block_at_const(&block, 15, false),
            nullptr); // Значительно больше максимального
}

TEST(ae_memory_block_at, at_from_end_valid_index) {
  char buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(char));

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_at_const(&block, 0, true)),
            'J'); // Последний элемент

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_at_const(&block, 5, true)),
            'E'); // Шестой с конца

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_at_const(&block, 9, true)),
            'A'); // Первый элемент
}

TEST(ae_memory_block_at, at_from_end_invalid_index) {
  char buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(char));

  EXPECT_EQ(ae_memory_block_at_const(&block, 10, true),
            nullptr); // На один больше максимального

  EXPECT_EQ(ae_memory_block_at_const(&block, 15, true),
            nullptr); // Значительно больше максимального
}

TEST(ae_memory_block_front, front_returns_first_element) {
  char buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(char));

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_front_const(&block)), 'A'); // Первый элемент
}

TEST(ae_memory_block_back, back_returns_last_element) {
  char buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  const ae_memory_block_t block =
      ae_memory_block_initializer(buffer, &buffer[10], sizeof(char));

  EXPECT_EQ(*static_cast<const char *>(ae_memory_block_back_const(&block)), 'J'); // Последний элемент
}

TEST(ae_memory_block_front, front_on_empty_block_returns_null) {
  const ae_memory_block_t block = ae_memory_block_empty_initializer(1);
  EXPECT_EQ(ae_memory_block_front_const(&block), nullptr); // Ожидаем nullptr
}

TEST(ae_memory_block_back, back_on_empty_block_returns_null) {
  const ae_memory_block_t block = ae_memory_block_empty_initializer(1);
  EXPECT_EQ(ae_memory_block_back_const(&block), nullptr); // Ожидаем nullptr
}