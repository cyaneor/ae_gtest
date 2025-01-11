#include <gtest/gtest.h>
#include <ae/runtime_error_code.h>
#include <ae/runtime_error.h>
#include <ae/memory_raw.h>

TEST(ae_memory_raw_fill8, fill_array_with_value) {
  const ae_u8_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
  ae_u8_t arr[10] = {0};

  ae_memory_raw_fill8(arr, 10, 5);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill8, fill_partial_array) {
  const ae_u8_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
  ae_u8_t arr[10] = {0};

  ae_memory_raw_fill8(arr, 5, 3);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill8, null_pointer) {
  ae_memory_raw_fill8(nullptr, 10, 5);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill8, zero_length) {
  ae_u8_t arr[10] = {0};
  EXPECT_EQ(ae_memory_raw_fill8(arr, 0, 5), arr);
}

TEST(ae_memory_raw_fill8, single_byte_fill) {
  ae_u8_t arr[1] = {0};
  ae_memory_raw_fill8(arr, 1, 7);
  EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill16, fill_array_with_value) {
  const ae_u16_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
  ae_u16_t arr[10] = {0};

  ae_memory_raw_fill16(arr, 10, 5);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill16, fill_partial_array) {
  const ae_u16_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
  ae_u16_t arr[10] = {0};

  ae_memory_raw_fill16(arr, 5, 3);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill16, null_pointer) {
  ae_memory_raw_fill16(nullptr, 10, 5);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill16, zero_length) {
  ae_u16_t arr[10] = {0};
  EXPECT_EQ(ae_memory_raw_fill16(arr, 0, 5), arr);
}

TEST(ae_memory_raw_fill16, single_byte_fill) {
  ae_u16_t arr[1] = {0};
  ae_memory_raw_fill16(arr, 1, 7);
  EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill32, fill_array_with_value) {
  const ae_u32_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
  ae_u32_t arr[10] = {0};

  ae_memory_raw_fill32(arr, 10, 5);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill32, fill_partial_array) {
  const ae_u32_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
  ae_u32_t arr[10] = {0};

  ae_memory_raw_fill32(arr, 5, 3);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill32, null_pointer) {
  ae_memory_raw_fill32(nullptr, 10, 5);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill32, zero_length) {
  ae_u32_t arr[10] = {0};
  EXPECT_EQ(ae_memory_raw_fill32(arr, 0, 5), arr);
}

TEST(ae_memory_raw_fill32, single_byte_fill) {
  ae_u32_t arr[1] = {0};
  ae_memory_raw_fill32(arr, 1, 7);
  EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill64, fill_array_with_value) {
  const ae_u64_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
  ae_u64_t arr[10] = {0};

  ae_memory_raw_fill64(arr, 10, 5);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill64, fill_partial_array) {
  const ae_u64_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
  ae_u64_t arr[10] = {0};

  ae_memory_raw_fill64(arr, 5, 3);
  EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill64, null_pointer) {
  ae_memory_raw_fill64(nullptr, 10, 5);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill64, zero_length) {
  ae_u64_t arr[10] = {0};
  EXPECT_EQ(ae_memory_raw_fill64(arr, 0, 5), arr);
}

TEST(ae_memory_raw_fill64, single_byte_fill) {
  ae_u64_t arr[1] = {0};
  ae_memory_raw_fill64(arr, 1, 7);
  EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill, fill_with64_divisible_length) {
  const size_t len = 64;
  uint8_t buffer[len];

  ae_u8_t value = 0xAB;
  void *result = ae_memory_raw_fill(buffer, len, value);

  for (unsigned char i : buffer) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_fill, fill_with32_divisible_length) {
  const size_t len = 32;
  uint8_t buffer[len] = {};

  ae_u8_t value = 0xCD;
  void *result = ae_memory_raw_fill(buffer, len, value);

  for (unsigned char i : buffer) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_fill, fill_with16_divisible_length) {
  const size_t len = 16;
  uint8_t buffer[len];

  ae_u8_t value = 0xEF;
  void *result = ae_memory_raw_fill(buffer, len, value);

  for (unsigned char i : buffer) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_fill, fill_with8_divisible_length) {
  const size_t len = 8;

  uint8_t buffer[len];
  ae_u8_t value = 0xFF;

  void *result = ae_memory_raw_fill(buffer, len, value);
  for (unsigned char i : buffer) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_fill, fill_with_non_divisible_length) {
  const size_t len = 12; // Не делится на 64, 32 или 16

  uint8_t buffer[len];
  ae_u8_t value = 0x01;

  void *result = ae_memory_raw_fill(buffer, len, value);
  for (unsigned char i : buffer) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_find8_val, null_pointer) {
  ae_u8_t *ptr = nullptr;
  EXPECT_EQ(ae_memory_raw_find8_val(ptr, 10, 5), nullptr);
}

TEST(ae_memory_raw_find8_val, find_value) {
  ae_u8_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find8_val(arr, len, 3), &arr[2]);
}

TEST(ae_memory_raw_find8_val, value_not_found) {
  ae_u8_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find8_val(arr, len, 6), nullptr);
}

TEST(ae_memory_raw_find8_val, empty_array) {
  ae_u8_t *arr = nullptr;
  ae_usize_t len = 0;

  EXPECT_EQ(ae_memory_raw_find8_val(arr, len, 3), nullptr);
}

TEST(ae_memory_raw_find8_val, find_first_element) {
  ae_u8_t arr[] = {5, 6, 7, 8};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find8_val(arr, len, 5), &arr[0]);
}

TEST(ae_memory_raw_find16_val, null_pointer) {
  ae_u16_t *ptr = nullptr;
  EXPECT_EQ(ae_memory_raw_find16_val(ptr, 10, 5), nullptr);
}

TEST(ae_memory_raw_find16_val, find_value) {
  ae_u16_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find16_val(arr, len, 3), &arr[2]);
}

TEST(ae_memory_raw_find16_val, value_not_found) {
  ae_u16_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find16_val(arr, len, 6), nullptr);
}

TEST(ae_memory_raw_find16_val, empty_array) {
  ae_u16_t *arr = nullptr;
  ae_usize_t len = 0;

  EXPECT_EQ(ae_memory_raw_find16_val(arr, len, 3), nullptr);
}

TEST(ae_memory_raw_find16_val, find_first_element) {
  ae_u16_t arr[] = {5, 6, 7, 8};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find16_val(arr, len, 5), &arr[0]);
}

TEST(ae_memory_raw_find32_val, null_pointer) {
  ae_u32_t *ptr = nullptr;
  EXPECT_EQ(ae_memory_raw_find32_val(ptr, 10, 5), nullptr);
}

TEST(ae_memory_raw_find32_val, find_value) {
  ae_u32_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find32_val(arr, len, 3), &arr[2]);
}

TEST(ae_memory_raw_find32_val, value_not_found) {
  ae_u32_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find32_val(arr, len, 6), nullptr);
}

TEST(ae_memory_raw_find32_val, empty_array) {
  ae_u32_t *arr = nullptr;
  ae_usize_t len = 0;

  EXPECT_EQ(ae_memory_raw_find32_val(arr, len, 3), nullptr);
}

TEST(ae_memory_raw_find32_val, find_first_element) {
  ae_u32_t arr[] = {5, 6, 7, 8};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find32_val(arr, len, 5), &arr[0]);
}

TEST(ae_memory_raw_find64_val, null_pointer) {
  ae_u64_t *ptr = nullptr;
  EXPECT_EQ(ae_memory_raw_find64_val(ptr, 10, 5), nullptr);
}

TEST(ae_memory_raw_find64_val, find_value) {
  ae_u64_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find64_val(arr, len, 3), &arr[2]);
}

TEST(ae_memory_raw_find64_val, value_not_found) {
  ae_u64_t arr[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find64_val(arr, len, 6), nullptr);
}

TEST(ae_memory_raw_find64_val, empty_array) {
  EXPECT_EQ(ae_memory_raw_find64_val(nullptr, 0, 3), nullptr);
}

TEST(ae_memory_raw_find64_val, find_first_element) {
  ae_u64_t arr[] = {5, 6, 7, 8};
  ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

  EXPECT_EQ(ae_memory_raw_find64_val(arr, len, 5), &arr[0]);
}

TEST(ae_memory_raw_compare8, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare8(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare8, compare_same_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare8, compare_different_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8(lhs, lhs_len, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare8, compare_different_values) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 0, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare8, empty_array) {
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare8, compare_equal_after_different_elements) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8(lhs, len, rhs, len), &lhs[0]);
}

TEST(ae_memory_raw_compare16, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare16(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare16, compare_same_length) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare16, compare_different_length) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16(lhs, lhs_len, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare16, compare_different_values) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {1, 2, 0, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare16, empty_array) {
  ae_u16_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare16, compare_equal_after_different_elements) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {6, 7, 16, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16(lhs, len, rhs, len), &lhs[0]);
}

TEST(ae_memory_raw_compare32, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare32(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare32, compare_same_length) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare32, compare_different_length) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32(lhs, lhs_len, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare32, compare_different_values) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {1, 2, 0, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare32, empty_array) {
  ae_u32_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare32, compare_equal_after_different_elements) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {6, 7, 16, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32(lhs, len, rhs, len), &lhs[0]);
}

TEST(ae_memory_raw_compare64, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare64(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare64, compare_same_length) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare64, compare_different_length) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64(lhs, lhs_len, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare64, compare_different_values) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {1, 2, 0, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare64, empty_array) {
  ae_u64_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare64, compare_equal_after_different_elements) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {6, 7, 16, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64(lhs, len, rhs, len), &lhs[0]);
}

TEST(ae_memory_raw_compare8_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare8_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare8_rev, compare_same_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare8_rev, compare_different_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8_rev(lhs, lhs_len, rhs, rhs_len), &lhs[4]);
}

TEST(ae_memory_raw_compare8_rev, compare_different_values) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8_rev(lhs, len, rhs, len), &lhs[3]);
}

TEST(ae_memory_raw_compare8_rev, empty_array) {
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8_rev(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare8_rev, compare_equal_after_different_elements) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8_rev(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare8_rev, compare_same_last_elements) {
  ae_u8_t lhs[] = {0, 0, 0, 0, 5};
  ae_u8_t rhs[] = {0, 0, 0, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare8_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare16_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare16_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare16_rev, compare_same_length) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare16_rev, compare_different_length) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16_rev(lhs, lhs_len, rhs, rhs_len), &lhs[4]);
}

TEST(ae_memory_raw_compare16_rev, compare_different_values) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {1, 2, 3, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16_rev(lhs, len, rhs, len), &lhs[3]);
}

TEST(ae_memory_raw_compare16_rev, empty_array) {
  ae_u16_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16_rev(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare16_rev, compare_equal_after_different_elements) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5};
  ae_u16_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16_rev(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare16_rev, compare_same_last_elements) {
  ae_u16_t lhs[] = {0, 0, 0, 0, 5};
  ae_u16_t rhs[] = {0, 0, 0, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare16_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare32_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare32_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare32_rev, compare_same_length) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare32_rev, compare_different_length) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32_rev(lhs, lhs_len, rhs, rhs_len), &lhs[4]);
}

TEST(ae_memory_raw_compare32_rev, compare_different_values) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {1, 2, 3, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32_rev(lhs, len, rhs, len), &lhs[3]);
}

TEST(ae_memory_raw_compare32_rev, empty_array) {
  ae_u32_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32_rev(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare32_rev, compare_equal_after_different_elements) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5};
  ae_u32_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32_rev(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare32_rev, compare_same_last_elements) {
  ae_u32_t lhs[] = {0, 0, 0, 0, 5};
  ae_u32_t rhs[] = {0, 0, 0, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare32_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare64_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare64_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_compare64_rev, compare_same_length) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_compare64_rev, compare_different_length) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64_rev(lhs, lhs_len, rhs, rhs_len), &lhs[4]);
}

TEST(ae_memory_raw_compare64_rev, compare_different_values) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {1, 2, 3, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64_rev(lhs, len, rhs, len), &lhs[3]);
}

TEST(ae_memory_raw_compare64_rev, empty_array) {
  ae_u64_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64_rev(nullptr, 0, rhs, rhs_len), nullptr);
}

TEST(ae_memory_raw_compare64_rev, compare_equal_after_different_elements) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5};
  ae_u64_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64_rev(lhs, len, rhs, len), &lhs[2]);
}

TEST(ae_memory_raw_compare64_rev, compare_same_last_elements) {
  ae_u64_t lhs[] = {0, 0, 0, 0, 5};
  ae_u64_t rhs[] = {0, 0, 0, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare64_rev(lhs, len, rhs, len), nullptr);
}

TEST(ae_memory_raw_copy8, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy8(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy8, copy_same_length) {
  ae_u8_t src[] = {1, 2, 3, 4, 5};
  ae_u8_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u8_t *result = ae_memory_raw_copy8(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy8, copy_short_to_long) {
  ae_u8_t src[] = {1, 2, 3};
  ae_u8_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u8_t *result = ae_memory_raw_copy8(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  for (ae_usize_t i = 0; i < src_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }

  for (ae_usize_t i = src_len; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], 0);
  }
}

TEST(ae_memory_raw_copy8, copy_long_to_short) {
  ae_u8_t src[] = {1, 2, 3, 4, 5};
  ae_u8_t dst[3];
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u8_t *result = ae_memory_raw_copy8(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  for (ae_usize_t i = 0; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy8, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy8(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy8, correct_copy) {
  ae_u8_t src[] = {10, 20, 30, 40, 50};
  ae_u8_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u8_t *result = ae_memory_raw_copy8(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy16, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy16(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy16, copy_same_length) {
  ae_u16_t src[] = {1, 2, 3, 4, 5};
  ae_u16_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u16_t *result = ae_memory_raw_copy16(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy16, copy_short_to_long) {
  ae_u16_t src[] = {1, 2, 3};
  ae_u16_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u16_t *result = ae_memory_raw_copy16(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  for (ae_usize_t i = 0; i < src_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }

  for (ae_usize_t i = src_len; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], 0);
  }
}

TEST(ae_memory_raw_copy16, copy_long_to_short) {
  ae_u16_t src[] = {1, 2, 3, 4, 5};
  ae_u16_t dst[3];
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u16_t *result = ae_memory_raw_copy16(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  for (ae_usize_t i = 0; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy16, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy16(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy16, correct_copy) {
  ae_u16_t src[] = {10, 20, 30, 40, 50};
  ae_u16_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u16_t *result = ae_memory_raw_copy16(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy32, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy16(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy32, copy_same_length) {
  ae_u32_t src[] = {1, 2, 3, 4, 5};
  ae_u32_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u32_t *result = ae_memory_raw_copy32(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy32, copy_short_to_long) {
  ae_u32_t src[] = {1, 2, 3};
  ae_u32_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u32_t *result = ae_memory_raw_copy32(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  for (ae_usize_t i = 0; i < src_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }

  for (ae_usize_t i = src_len; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], 0);
  }
}

TEST(ae_memory_raw_copy32, copy_long_to_short) {
  ae_u32_t src[] = {1, 2, 3, 4, 5};
  ae_u32_t dst[3];
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u32_t *result = ae_memory_raw_copy32(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  for (ae_usize_t i = 0; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy32, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy32(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy32, correct_copy) {
  ae_u32_t src[] = {10, 20, 30, 40, 50};
  ae_u32_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u32_t *result = ae_memory_raw_copy32(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy64, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy64(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy64, copy_same_length) {
  ae_u64_t src[] = {1, 2, 3, 4, 5};
  ae_u64_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u64_t *result = ae_memory_raw_copy64(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy64, copy_short_to_long) {
  ae_u64_t src[] = {1, 2, 3};
  ae_u64_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u64_t *result = ae_memory_raw_copy64(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  for (ae_usize_t i = 0; i < src_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }

  for (ae_usize_t i = src_len; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], 0);
  }
}

TEST(ae_memory_raw_copy64, copy_long_to_short) {
  ae_u64_t src[] = {1, 2, 3, 4, 5};
  ae_u64_t dst[3];
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u64_t *result = ae_memory_raw_copy64(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  for (ae_usize_t i = 0; i < dst_len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy64, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy64(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy64, correct_copy) {
  ae_u64_t src[] = {10, 20, 30, 40, 50};
  ae_u64_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u64_t *result = ae_memory_raw_copy64(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_copy, copy_with64_divisible_length) {
  const size_t len = 64;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xAB;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy, copy_with32_divisible_length) {
  const size_t len = 32;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xCD;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy, copy_with16_divisible_length) {
  const size_t len = 16;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xEF;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy, copy_with8_divisible_length) {
  const size_t len = 8;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xFF;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy, copy_with_non_divisible_length) {
  const size_t len = 12; // Не делится на 64, 32 или 16
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0x01;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy8_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy8_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy8_rev, copy_same_length) {
  ae_u8_t src[] = {1, 2, 3, 4, 5};
  ae_u8_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u8_t *result = ae_memory_raw_copy8_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy8_rev, copy_short_to_long) {
  ae_u8_t src[] = {1, 2, 3};
  ae_u8_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u8_t *result = ae_memory_raw_copy8_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  ae_u8_t expected[] = {0, 0, 1, 2, 3};
  EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy8_rev, copy_long_to_short) {
  ae_u8_t src[] = {1, 2, 3, 4, 5};
  ae_u8_t dst[3] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u8_t *result = ae_memory_raw_copy8_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  ae_u8_t expected[] = {3, 4, 5};
  EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy8_rev, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy8_rev(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy8_rev, correct_copy) {
  ae_u8_t src[] = {10, 20, 30, 40, 50};
  ae_u8_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u8_t *result = ae_memory_raw_copy8_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy16_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy16_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy16_rev, copy_same_length) {
  ae_u16_t src[] = {1, 2, 3, 4, 5};
  ae_u16_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u16_t *result = ae_memory_raw_copy16_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy16_rev, copy_short_to_long) {
  ae_u16_t src[] = {1, 2, 3};
  ae_u16_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u16_t *result = ae_memory_raw_copy16_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  ae_u16_t expected[] = {0, 0, 1, 2, 3};
  EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy16_rev, copy_long_to_short) {
  ae_u16_t src[] = {1, 2, 3, 4, 5};
  ae_u16_t dst[3] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u16_t *result = ae_memory_raw_copy16_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  ae_u16_t expected[] = {3, 4, 5};
  EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy16_rev, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy16_rev(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy16_rev, correct_copy) {
  ae_u16_t src[] = {10, 20, 30, 40, 50};
  ae_u16_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u16_t *result = ae_memory_raw_copy16_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy32_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy32_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy32_rev, copy_same_length) {
  ae_u32_t src[] = {1, 2, 3, 4, 5};
  ae_u32_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u32_t *result = ae_memory_raw_copy32_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy32_rev, copy_short_to_long) {
  ae_u32_t src[] = {1, 2, 3};
  ae_u32_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u32_t *result = ae_memory_raw_copy32_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  ae_u32_t expected[] = {0, 0, 1, 2, 3};
  EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy32_rev, copy_long_to_short) {
  ae_u32_t src[] = {1, 2, 3, 4, 5};
  ae_u32_t dst[3] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u32_t *result = ae_memory_raw_copy32_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  ae_u32_t expected[] = {3, 4, 5};
  EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy32_rev, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy32_rev(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy32_rev, correct_copy) {
  ae_u32_t src[] = {10, 20, 30, 40, 50};
  ae_u32_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u32_t *result = ae_memory_raw_copy32_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy64_rev, null_pointers) {
  EXPECT_EQ(ae_memory_raw_copy64_rev(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_copy64_rev, copy_same_length) {
  ae_u64_t src[] = {1, 2, 3, 4, 5};
  ae_u64_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u64_t *result = ae_memory_raw_copy64_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy64_rev, copy_short_to_long) {
  ae_u64_t src[] = {1, 2, 3};
  ae_u64_t dst[5] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u64_t *result = ae_memory_raw_copy64_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + src_len);

  ae_u64_t expected[] = {0, 0, 1, 2, 3};
  EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy64_rev, copy_long_to_short) {
  ae_u64_t src[] = {1, 2, 3, 4, 5};
  ae_u64_t dst[3] = {};
  ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
  ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

  ae_u64_t *result = ae_memory_raw_copy64_rev(dst, dst_len, src, src_len);
  EXPECT_EQ(result, dst + dst_len);

  ae_u64_t expected[] = {3, 4, 5};
  EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy64_rev, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_copy64_rev(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_copy64_rev, correct_copy) {
  ae_u64_t src[] = {10, 20, 30, 40, 50};
  ae_u64_t dst[5] = {};
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u64_t *result = ae_memory_raw_copy64_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy_rev, copy_rev_with64_divisible_length) {
  const size_t len = 64;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xAB;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with32_divisible_length) {
  const size_t len = 32;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xCD;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with16_divisible_length) {
  const size_t len = 16;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xEF;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with8_divisible_length) {
  const size_t len = 8;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xFF;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with_non_divisible_length) {
  const size_t len = 12;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0x01;

  std::memset(src, value, len);
  void *result = ae_memory_raw_copy_rev(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_move8, null_pointers) {
  EXPECT_EQ(ae_memory_raw_move8(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_move8, move_without_overlap) {
  ae_u8_t src[] = {1, 2, 3, 4, 5};
  ae_u8_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u8_t *result = ae_memory_raw_move8(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move8, move_with_overlap) {
  ae_u8_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u8_t *result = ae_memory_raw_move8(buffer + 2, len - 2, buffer, len - 2);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 2; ++i) {
    EXPECT_EQ(buffer[i + 2], (i + 1));
  }
}

TEST(ae_memory_raw_move8, move_same_buffer) {
  ae_u8_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u8_t *result = ae_memory_raw_move8(buffer, len, buffer, len);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(buffer[i], i + 1);
  }
}

TEST(ae_memory_raw_move8, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_move8(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_move8, move_same_length) {
  ae_u8_t src[] = {1, 2, 3, 4, 5};
  ae_u8_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u8_t *result = ae_memory_raw_move8(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move8, move_adjacent_with_overlap) {
  ae_u8_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u8_t *result = ae_memory_raw_move8(buffer + 1, len - 1, buffer, len - 1);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 1; ++i) {
    EXPECT_EQ(buffer[i + 1], (i + 1));
  }
}

TEST(ae_memory_raw_move16, null_pointers) {
  EXPECT_EQ(ae_memory_raw_move16(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_move16, move_without_overlap) {
  ae_u16_t src[] = {1, 2, 3, 4, 5};
  ae_u16_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u16_t *result = ae_memory_raw_move16(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move16, move_with_overlap) {
  ae_u16_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u16_t *result = ae_memory_raw_move16(buffer + 2, len - 2, buffer, len - 2);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 2; ++i) {
    EXPECT_EQ(buffer[i + 2], (i + 1));
  }
}

TEST(ae_memory_raw_move16, move_same_buffer) {
  ae_u16_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u16_t *result = ae_memory_raw_move16(buffer, len, buffer, len);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(buffer[i], i + 1);
  }
}

TEST(ae_memory_raw_move16, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_move16(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_move16, move_same_length) {
  ae_u16_t src[] = {1, 2, 3, 4, 5};
  ae_u16_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u16_t *result = ae_memory_raw_move16(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move16, move_adjacent_with_overlap) {
  ae_u16_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u16_t *result = ae_memory_raw_move16(buffer + 1, len - 1, buffer, len - 1);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 1; ++i) {
    EXPECT_EQ(buffer[i + 1], (i + 1));
  }
}

TEST(ae_memory_raw_move32, null_pointers) {
  EXPECT_EQ(ae_memory_raw_move32(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_move32, move_without_overlap) {
  ae_u32_t src[] = {1, 2, 3, 4, 5};
  ae_u32_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u32_t *result = ae_memory_raw_move32(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move32, move_with_overlap) {
  ae_u32_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u32_t *result = ae_memory_raw_move32(buffer + 2, len - 2, buffer, len - 2);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 2; ++i) {
    EXPECT_EQ(buffer[i + 2], (i + 1));
  }
}

TEST(ae_memory_raw_move32, move_same_buffer) {
  ae_u32_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u32_t *result = ae_memory_raw_move32(buffer, len, buffer, len);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(buffer[i], i + 1);
  }
}

TEST(ae_memory_raw_move32, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_move32(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_move32, move_same_length) {
  ae_u32_t src[] = {1, 2, 3, 4, 5};
  ae_u32_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u32_t *result = ae_memory_raw_move32(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move32, move_adjacent_with_overlap) {
  ae_u32_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u32_t *result = ae_memory_raw_move32(buffer + 1, len - 1, buffer, len - 1);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 1; ++i) {
    EXPECT_EQ(buffer[i + 1], (i + 1));
  }
}

TEST(ae_memory_raw_move64, null_pointers) {
  EXPECT_EQ(ae_memory_raw_move64(nullptr, 10, nullptr, 10), nullptr);
}

TEST(ae_memory_raw_move64, move_without_overlap) {
  ae_u64_t src[] = {1, 2, 3, 4, 5};
  ae_u64_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  // Перемещаем данные из src в dst
  ae_u64_t *result = ae_memory_raw_move64(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move64, move_with_overlap) {
  ae_u64_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u64_t *result = ae_memory_raw_move64(buffer + 2, len - 2, buffer, len - 2);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 2; ++i) {
    EXPECT_EQ(buffer[i + 2], (i + 1));
  }
}

TEST(ae_memory_raw_move64, move_same_buffer) {
  ae_u64_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u64_t *result = ae_memory_raw_move64(buffer, len, buffer, len);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(buffer[i], i + 1);
  }
}

TEST(ae_memory_raw_move64, empty_arrays) {
  EXPECT_EQ(ae_memory_raw_move64(nullptr, 0, nullptr, 0), nullptr);
}

TEST(ae_memory_raw_move64, move_same_length) {
  ae_u64_t src[] = {1, 2, 3, 4, 5};
  ae_u64_t dst[5];
  ae_usize_t len = sizeof(src) / sizeof(src[0]);

  ae_u64_t *result = ae_memory_raw_move64(dst, len, src, len);
  EXPECT_EQ(result, dst + len);

  for (ae_usize_t i = 0; i < len; ++i) {
    EXPECT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move64, move_adjacent_with_overlap) {
  ae_u64_t buffer[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

  ae_u64_t *result = ae_memory_raw_move64(buffer + 1, len - 1, buffer, len - 1);
  EXPECT_EQ(result, buffer + len);

  for (ae_usize_t i = 0; i < len - 1; ++i) {
    EXPECT_EQ(buffer[i + 1], (i + 1));
  }
}

TEST(ae_memory_raw_move, move64_bytes) {
    uint64_t src[] = {1, 2, 3, 4};
    uint64_t dst[4];

    void *result =
            ae_memory_raw_move(dst, 4 * sizeof(uint64_t), src, 4 * sizeof(uint64_t));
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move32_bytes) {
    uint32_t src[] = {1, 2, 3, 4};
    uint32_t dst[4];

    void *result =
            ae_memory_raw_move(dst, 4 * sizeof(uint32_t), src, 4 * sizeof(uint32_t));
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move16_bytes) {
    uint16_t src[] = {1, 2, 3, 4};
    uint16_t dst[4];

    void *result =
            ae_memory_raw_move(dst, 4 * sizeof(uint16_t), src, 4 * sizeof(uint16_t));
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move8_bytes) {
    uint8_t src[] = {1, 2, 3, 4};
    uint8_t dst[4];

    void *result = ae_memory_raw_move(dst, 4, src, 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move64_bytes_overlap) {
    uint64_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Исходные и целевые участки данных перекрываются
    void *result = ae_memory_raw_move(buf + 2, 4 * sizeof(uint64_t), buf, 4 * sizeof(uint64_t));
    ASSERT_EQ(result, &buf[6]);

    // Проверяем, что данные были правильно перемещены
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(ae_memory_raw_move, move32_bytes_overlap) {
    uint32_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Исходные и целевые участки данных перекрываются
    void *result = ae_memory_raw_move(buf + 2, 4 * sizeof(uint32_t), buf, 4 * sizeof(uint32_t));
    ASSERT_EQ(result, &buf[6]);

    // Проверяем, что данные были правильно перемещены
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(ae_memory_raw_move, move16_bytes_overlap) {
    uint16_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Исходные и целевые участки данных перекрываются
    void *result = ae_memory_raw_move(buf + 2, 4 * sizeof(uint16_t), buf, 4 * sizeof(uint16_t));
    ASSERT_EQ(result, &buf[6]);

    // Проверяем, что данные были правильно перемещены
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(ae_memory_raw_move, move8_bytes_overlap) {
    uint8_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Исходные и целевые участки данных перекрываются
    void *result = ae_memory_raw_move(buf + 2, 4, buf, 4);
    ASSERT_EQ(result, &buf[6]);

    // Проверяем, что данные были правильно перемещены
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}
