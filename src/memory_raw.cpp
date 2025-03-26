#include <gtest/gtest.h>
#include <ae/runtime_error_code.h>
#include <ae/runtime_error.h>
#include <ae/memory_raw.h>

TEST(ae_memory_raw_compare, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare, compare32) {
  unsigned char lhs[32] = {0};
  unsigned char rhs[32] = {0};

  const void *result = ae_memory_raw_compare(lhs, lhs + 32, rhs, rhs + 32);
  EXPECT_EQ(result, nullptr);

  rhs[15] = 1;

  result = ae_memory_raw_compare(lhs, lhs + 32, rhs, rhs + 32);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 15);
}

TEST(ae_memory_raw_compare, compare16) {
  unsigned char lhs[16] = {0};
  unsigned char rhs[16] = {0};

  const void *result = ae_memory_raw_compare(lhs, lhs + 16, rhs, rhs + 16);
  EXPECT_EQ(result, nullptr);

  rhs[7] = 1;

  result = ae_memory_raw_compare(lhs, lhs + 16, rhs, rhs + 16);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 7);
}

TEST(ae_memory_raw_compare, compare_same_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare, compare_different_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]),
            nullptr);
}

TEST(ae_memory_raw_compare, compare_different_values) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 0, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare, empty_array) {
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(ae_memory_raw_compare(nullptr, nullptr, rhs, &rhs[rhs_len]),
            nullptr);
}

TEST(ae_memory_raw_compare, compare_equal_after_different_elements) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(ae_memory_raw_compare_from_end, null_pointers) {
  EXPECT_EQ(ae_memory_raw_compare_from_end(nullptr, nullptr, nullptr, nullptr),
            nullptr);
}

TEST(ae_memory_raw_compare_from_end, compare_same_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare_from_end(lhs, &lhs[len], rhs, &rhs[len]),
            nullptr);
}

TEST(ae_memory_raw_compare_from_end, compare_different_length) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(
      ae_memory_raw_compare_from_end(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]),
      &lhs[4]);
}

TEST(ae_memory_raw_compare_from_end, compare_different_values) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {1, 2, 3, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare_from_end(lhs, &lhs[len], rhs, &rhs[len]),
            &lhs[3]);
}

TEST(ae_memory_raw_compare_from_end, empty_array) {
  ae_u8_t rhs[] = {1, 2, 3};
  ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

  EXPECT_EQ(
      ae_memory_raw_compare_from_end(nullptr, nullptr, rhs, &rhs[rhs_len]),
      nullptr);
}

TEST(ae_memory_raw_compare_from_end, compare_equal_after_different_elements) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  ae_u8_t rhs[] = {6, 7, 8, 4, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare_from_end(lhs, &lhs[len], rhs, &rhs[len]),
            &lhs[2]);
}

TEST(ae_memory_raw_compare_from_end, compare_same_last_elements) {
  ae_u8_t lhs[] = {0, 0, 0, 0, 5};
  ae_u8_t rhs[] = {0, 0, 0, 0, 5};
  ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

  EXPECT_EQ(ae_memory_raw_compare_from_end(lhs, &lhs[len], rhs, &rhs[len]),
            nullptr);
}

TEST(ae_memory_raw_copy, copy_with64_divisible_length) {
  const size_t len = 64;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xAB;

  memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, &dst[len], src, &src[len]);
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

  memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, &dst[len], src, &src[len]);
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

  memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, &dst[len], src, &src[len]);
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

  memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy, copy_with_non_divisible_length) {
  const size_t len = 12;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0x01;

  memset(src, value, len);
  void *result = ae_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(ae_memory_raw_copy_from_end, copy_rev_with64_divisible_length) {
  const size_t len = 64;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xAB;

  memset(src, value, len);
  void *result = ae_memory_raw_copy_from_end(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_from_end, copy_rev_with32_divisible_length) {
  const size_t len = 32;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xCD;

  memset(src, value, len);
  void *result = ae_memory_raw_copy_from_end(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_from_end, copy_rev_with16_divisible_length) {
  const size_t len = 16;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xEF;

  memset(src, value, len);
  void *result = ae_memory_raw_copy_from_end(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_from_end, copy_rev_with8_divisible_length) {
  const size_t len = 8;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0xFF;

  memset(src, value, len);
  void *result = ae_memory_raw_copy_from_end(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_copy_from_end, copy_rev_with_non_divisible_length) {
  const size_t len = 12;
  uint8_t src[len];
  uint8_t dst[len];
  ae_u8_t value = 0x01;

  memset(src, value, len);
  void *result = ae_memory_raw_copy_from_end(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (size_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(ae_memory_raw_move, move64_bytes) {
  uint64_t src[] = {1, 2, 3, 4};
  uint64_t dst[4];

  void *result = ae_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move, move32_bytes) {
  uint32_t src[] = {1, 2, 3, 4};
  uint32_t dst[4];

  void *result = ae_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move, move16_bytes) {
  uint16_t src[] = {1, 2, 3, 4};
  uint16_t dst[4];

  void *result = ae_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move, move8_bytes) {
  uint8_t src[] = {1, 2, 3, 4};
  uint8_t dst[4];

  void *result = ae_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(ae_memory_raw_move, move64_bytes_overlap) {
  uint64_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = ae_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(ae_memory_raw_move, move32_bytes_overlap) {
  uint32_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = ae_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(ae_memory_raw_move, move16_bytes_overlap) {
  uint16_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = ae_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(ae_memory_raw_move, move8_bytes_overlap) {
  uint8_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = ae_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(ae_memory_raw_find, NormalTest) {
  const ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  const ae_u8_t rhs[] = {3, 4};

  const void *result = ae_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
  EXPECT_EQ(result,
            lhs + 2); // Мы ожидаем, что совпадение будет начиная с элемента 3
}

TEST(ae_memory_raw_find, null_pointer) {
  const ae_u8_t *lhs = nullptr;
  const ae_u8_t rhs[] = {3, 4};

  ae_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find, empty_lhs) {
  const ae_u8_t *lhs = nullptr;
  const ae_u8_t rhs[] = {3, 4};

  const void *result = ae_memory_raw_find(lhs, lhs, rhs, rhs + 2);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find, empty_rhs) {
  const ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  const ae_u8_t *rhs = nullptr;

  const void *result = ae_memory_raw_find(lhs, lhs + 5, rhs, rhs);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find, no_match) {
  const ae_u8_t lhs[] = {1, 2, 3, 4, 5};
  const ae_u8_t rhs[] = {6, 7};

  const void *result = ae_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find, match_at_start) {
  const ae_u8_t lhs[] = {3, 4, 5};
  const ae_u8_t rhs[] = {3, 4};

  const void *result = ae_memory_raw_find(lhs, lhs + 3, rhs, rhs + 2);
  EXPECT_EQ(result, lhs);
}

TEST(ae_memory_raw_find_from_end, find_substring_in_string) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u8_t rhs[] = {0x03, 0x04};

  const void *result = ae_memory_raw_find_from_end(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_from_end, substring_not_found) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u8_t rhs[] = {0x07, 0x08};

  const void *result = ae_memory_raw_find_from_end(lhs, &lhs[6], rhs, &rhs[2]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_from_end, find_substring_at_end) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u8_t rhs[] = {0x05, 0x06};

  const void *result = ae_memory_raw_find_from_end(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_from_end, empty_arrays) {
  const void *result =
      ae_memory_raw_find_from_end(nullptr, nullptr, nullptr, nullptr);

  ASSERT_EQ(result, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_from_end, rhs_longer_than_lhs) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03};
  ae_u8_t rhs[] = {0x01, 0x02, 0x03, 0x04};

  const void *result = ae_memory_raw_find_from_end(lhs, &lhs[3], rhs, &rhs[4]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_from_end, null_pointer_check) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04};
  ae_u8_t rhs[] = {0x03, 0x04};

  ae_memory_raw_find_from_end(nullptr, &lhs[4], rhs, &rhs[2]);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}