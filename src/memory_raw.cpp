#include <ae/runtime_error_code.h>
#include <ae/runtime_error.h>
#include <ae/memory_raw.h>
#include <gtest/gtest.h>

TEST(ae_memory_raw_find_u8, find_subsequence_in_middle) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u8_t rhs[] = {3, 4, 5};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u8, find_subsequence_at_start) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u8_t rhs[] = {1, 2, 3};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u8, find_subsequence_at_end) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u8_t rhs[] = {4, 5, 6};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u8, subsequence_not_found) {
  ae_u8_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u8_t rhs[] = {7, 8, 9};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u8, null_pointer_lhs) {
  ae_u8_t rhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u8(nullptr, nullptr, rhs, rhs + 3));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u8, null_pointer_rhs) {
  ae_u8_t lhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u8(lhs, lhs + 3, nullptr, nullptr));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u8, subsequence_with_single_element) {
  ae_u8_t lhs[] = {1, 2, 3};
  ae_u8_t rhs[] = {2};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u8, subsequence_at_end_with_single_element) {
  ae_u8_t lhs[] = {1, 2, 3};
  ae_u8_t rhs[] = {3};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u8, identical_sequences) {
  ae_u8_t lhs[] = {1, 2, 3};
  ae_u8_t rhs[] = {1, 2, 3};

  const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 3, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u16, find_subsequence_in_middle) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u16_t rhs[] = {3, 4, 5};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u16, find_subsequence_at_start) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u16_t rhs[] = {1, 2, 3};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u16, find_subsequence_at_end) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u16_t rhs[] = {4, 5, 6};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u16, subsequence_not_found) {
  ae_u16_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u16_t rhs[] = {7, 8, 9};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 6, rhs, rhs + 3);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u16, null_pointer_lhs) {
  ae_u16_t rhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u16(nullptr, nullptr, rhs, rhs + 3));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u16, null_pointer_rhs) {
  ae_u16_t lhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u16(lhs, lhs + 3, nullptr, nullptr));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}
TEST(ae_memory_raw_find_u16, subsequence_with_single_element) {
  ae_u16_t lhs[] = {1, 2, 3};
  ae_u16_t rhs[] = {2};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u16, subsequence_at_end_with_single_element) {
  ae_u16_t lhs[] = {1, 2, 3};
  ae_u16_t rhs[] = {3};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u16, identical_sequences) {
  ae_u16_t lhs[] = {1, 2, 3};
  ae_u16_t rhs[] = {1, 2, 3};

  const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 3, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u32, find_subsequence_in_middle) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u32_t rhs[] = {3, 4, 5};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u32, find_subsequence_at_start) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u32_t rhs[] = {1, 2, 3};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u32, find_subsequence_at_end) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u32_t rhs[] = {4, 5, 6};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u32, subsequence_not_found) {
  ae_u32_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u32_t rhs[] = {7, 8, 9};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 6, rhs, rhs + 3);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u32, null_pointer_lhs) {
  ae_u32_t rhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u32(nullptr, nullptr, rhs, rhs + 3));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u32, null_pointer_rhs) {
  ae_u32_t lhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u32(lhs, lhs + 3, nullptr, nullptr));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}
TEST(ae_memory_raw_find_u32, subsequence_with_single_element) {
  ae_u32_t lhs[] = {1, 2, 3};
  ae_u32_t rhs[] = {2};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u32, subsequence_at_end_with_single_element) {
  ae_u32_t lhs[] = {1, 2, 3};
  ae_u32_t rhs[] = {3};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u32, identical_sequences) {
  ae_u32_t lhs[] = {1, 2, 3};
  ae_u32_t rhs[] = {1, 2, 3};

  const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 3, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u64, find_subsequence_in_middle) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u64_t rhs[] = {3, 4, 5};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u64, find_subsequence_at_start) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u64_t rhs[] = {1, 2, 3};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u64, find_subsequence_at_end) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u64_t rhs[] = {4, 5, 6};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 6, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_u64, subsequence_not_found) {
  ae_u64_t lhs[] = {1, 2, 3, 4, 5, 6};
  ae_u64_t rhs[] = {7, 8, 9};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 6, rhs, rhs + 3);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u64, null_pointer_lhs) {
  ae_u64_t rhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u64(nullptr, nullptr, rhs, rhs + 3));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u64, null_pointer_rhs) {
  ae_u64_t lhs[] = {1, 2, 3};

  ASSERT_FALSE(ae_memory_raw_find_u64(lhs, lhs + 3, nullptr, nullptr));
  ASSERT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}
TEST(ae_memory_raw_find_u64, subsequence_with_single_element) {
  ae_u64_t lhs[] = {1, 2, 3};
  ae_u64_t rhs[] = {2};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u64, subsequence_at_end_with_single_element) {
  ae_u64_t lhs[] = {1, 2, 3};
  ae_u64_t rhs[] = {3};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 3, rhs, rhs + 1);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 1) == 0);
}

TEST(ae_memory_raw_find_u64, identical_sequences) {
  ae_u64_t lhs[] = {1, 2, 3};
  ae_u64_t rhs[] = {1, 2, 3};

  const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 3, rhs, rhs + 3);

  ASSERT_NE(result, nullptr);
  EXPECT_TRUE(memcmp(result, rhs, 3) == 0);
}

TEST(ae_memory_raw_find_rev_u8, find_substring_in_string) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u8_t rhs[] = {0x03, 0x04};

  const ae_u8_t *result = ae_memory_raw_find_rev_u8(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u8, substring_not_found) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u8_t rhs[] = {0x07, 0x08};

  const ae_u8_t *result = ae_memory_raw_find_rev_u8(lhs, &lhs[6], rhs, &rhs[2]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u8, find_substring_at_end) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u8_t rhs[] = {0x05, 0x06};

  const ae_u8_t *result = ae_memory_raw_find_rev_u8(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u8, empty_arrays) {
  const ae_u8_t *result =
      ae_memory_raw_find_rev_u8(nullptr, nullptr, nullptr, nullptr);

  ASSERT_EQ(result, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u8, rhs_longer_than_lhs) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03};
  ae_u8_t rhs[] = {0x01, 0x02, 0x03, 0x04};

  const ae_u8_t *result = ae_memory_raw_find_rev_u8(lhs, &lhs[3], rhs, &rhs[4]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u8, null_pointer_check) {
  ae_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04};
  ae_u8_t rhs[] = {0x03, 0x04};

  ae_memory_raw_find_rev_u8(nullptr, &lhs[4], rhs, &rhs[2]);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u16, find_substring_in_string) {
  ae_u16_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u16_t rhs[] = {0x03, 0x04};

  const ae_u16_t *result =
      ae_memory_raw_find_rev_u16(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u16, substring_not_found) {
  ae_u16_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u16_t rhs[] = {0x07, 0x08};

  const ae_u16_t *result =
      ae_memory_raw_find_rev_u16(lhs, &lhs[6], rhs, &rhs[2]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u16, find_substring_at_end) {
  ae_u16_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u16_t rhs[] = {0x05, 0x06};

  const ae_u16_t *result =
      ae_memory_raw_find_rev_u16(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u16, empty_arrays) {
  const ae_u16_t *result =
      ae_memory_raw_find_rev_u16(nullptr, nullptr, nullptr, nullptr);

  ASSERT_EQ(result, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u16, rhs_longer_than_lhs) {
  ae_u16_t lhs[] = {0x01, 0x02, 0x03};
  ae_u16_t rhs[] = {0x01, 0x02, 0x03, 0x04};

  const ae_u16_t *result =
      ae_memory_raw_find_rev_u16(lhs, &lhs[3], rhs, &rhs[4]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u16, null_pointer_check) {
  ae_u16_t lhs[] = {0x01, 0x02, 0x03, 0x04};
  ae_u16_t rhs[] = {0x03, 0x04};

  ae_memory_raw_find_rev_u16(nullptr, &lhs[4], rhs, &rhs[2]);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u32, find_substring_in_string) {
  ae_u32_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u32_t rhs[] = {0x03, 0x04};

  const ae_u32_t *result =
      ae_memory_raw_find_rev_u32(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u32, substring_not_found) {
  ae_u32_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u32_t rhs[] = {0x07, 0x08};

  const ae_u32_t *result =
      ae_memory_raw_find_rev_u32(lhs, &lhs[6], rhs, &rhs[2]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u32, find_substring_at_end) {
  ae_u32_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u32_t rhs[] = {0x05, 0x06};

  const ae_u32_t *result =
      ae_memory_raw_find_rev_u32(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u32, empty_arrays) {
  const ae_u32_t *result =
      ae_memory_raw_find_rev_u32(nullptr, nullptr, nullptr, nullptr);

  ASSERT_EQ(result, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u32, rhs_longer_than_lhs) {
  ae_u32_t lhs[] = {0x01, 0x02, 0x03};
  ae_u32_t rhs[] = {0x01, 0x02, 0x03, 0x04};

  const ae_u32_t *result =
      ae_memory_raw_find_rev_u32(lhs, &lhs[3], rhs, &rhs[4]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u32, null_pointer_check) {
  ae_u32_t lhs[] = {0x01, 0x02, 0x03, 0x04};
  ae_u32_t rhs[] = {0x03, 0x04};

  ae_memory_raw_find_rev_u32(nullptr, &lhs[4], rhs, &rhs[2]);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u64, find_substring_in_string) {
  ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u64_t rhs[] = {0x03, 0x04};

  const ae_u64_t *result =
      ae_memory_raw_find_rev_u64(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u64, substring_not_found) {
  ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u64_t rhs[] = {0x07, 0x08};

  const ae_u64_t *result =
      ae_memory_raw_find_rev_u64(lhs, &lhs[6], rhs, &rhs[2]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u64, find_substring_at_end) {
  ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  ae_u64_t rhs[] = {0x05, 0x06};

  const ae_u64_t *result =
      ae_memory_raw_find_rev_u64(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u64, empty_arrays) {
  const ae_u64_t *result =
      ae_memory_raw_find_rev_u64(nullptr, nullptr, nullptr, nullptr);

  ASSERT_EQ(result, nullptr);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u64, rhs_longer_than_lhs) {
  ae_u64_t lhs[] = {0x01, 0x02, 0x03};
  ae_u64_t rhs[] = {0x01, 0x02, 0x03, 0x04};

  const ae_u64_t *result =
      ae_memory_raw_find_rev_u64(lhs, &lhs[3], rhs, &rhs[4]);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u64, null_pointer_check) {
  ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04};
  ae_u64_t rhs[] = {0x03, 0x04};

  ae_memory_raw_find_rev_u64(nullptr, &lhs[4], rhs, &rhs[2]);
  EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
            AE_RUNTIME_ERROR_NULL_POINTER);
}