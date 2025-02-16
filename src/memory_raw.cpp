#include <gtest/gtest.h>
#include <ae/runtime_error_code.h>
#include <ae/runtime_error.h>
#include <ae/memory_raw.h>

TEST(ae_memory_raw_fill_u8, fill_array_with_value) {
    const ae_u8_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    ae_u8_t arr[10] = {0};

    ae_memory_raw_fill_u8(arr, &arr[10], 5);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}


TEST(ae_memory_raw_fill_u8, fill_partial_array) {
    const ae_u8_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
    ae_u8_t arr[10] = {0};

    ae_memory_raw_fill_u8(arr, &arr[5], 3);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill_u8, null_pointer) {
    ae_memory_raw_fill_u8(nullptr, nullptr, 5);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill_u8, zero_length) {
    ae_u8_t arr[10] = {0};
    EXPECT_EQ(ae_memory_raw_fill_u8(arr, arr, 5), arr);
}

TEST(ae_memory_raw_fill_u8, single_byte_fill) {
    ae_u8_t arr[1] = {0};
    ae_memory_raw_fill_u8(arr, &arr[1], 7);
    EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill_u16, fill_array_with_value) {
    const ae_u16_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    ae_u16_t arr[10] = {0};

    ae_memory_raw_fill_u16(arr, &arr[10], 5);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}


TEST(ae_memory_raw_fill_u16, fill_partial_array) {
    const ae_u16_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
    ae_u16_t arr[10] = {0};

    ae_memory_raw_fill_u16(arr, &arr[5], 3);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill_u16, null_pointer) {
    ae_memory_raw_fill_u16(nullptr, nullptr, 5);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill_u16, zero_length) {
    ae_u16_t arr[10] = {0};
    EXPECT_EQ(ae_memory_raw_fill_u16(arr, arr, 5), arr);
}

TEST(ae_memory_raw_fill_u16, single_byte_fill) {
    ae_u16_t arr[1] = {0};
    ae_memory_raw_fill_u16(arr, &arr[1], 7);
    EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill_u32, fill_array_with_value) {
    const ae_u32_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    ae_u32_t arr[10] = {0};

    ae_memory_raw_fill_u32(arr, &arr[10], 5);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}


TEST(ae_memory_raw_fill_u32, fill_partial_array) {
    const ae_u32_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
    ae_u32_t arr[10] = {0};

    ae_memory_raw_fill_u32(arr, &arr[5], 3);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill_u32, null_pointer) {
    ae_memory_raw_fill_u32(nullptr, nullptr, 5);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill_u32, zero_length) {
    ae_u32_t arr[10] = {0};
    EXPECT_EQ(ae_memory_raw_fill_u32(arr, arr, 5), arr);
}

TEST(ae_memory_raw_fill_u32, single_byte_fill) {
    ae_u32_t arr[1] = {0};
    ae_memory_raw_fill_u32(arr, &arr[1], 7);
    EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill_u64, fill_array_with_value) {
    const ae_u64_t expected[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    ae_u64_t arr[10] = {0};

    ae_memory_raw_fill_u64(arr, &arr[10], 5);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}


TEST(ae_memory_raw_fill_u64, fill_partial_array) {
    const ae_u64_t expected[10] = {3, 3, 3, 3, 3, 0, 0, 0, 0, 0};
    ae_u64_t arr[10] = {0};

    ae_memory_raw_fill_u64(arr, &arr[5], 3);
    EXPECT_TRUE(!memcmp(arr, expected, 10));
}

TEST(ae_memory_raw_fill_u64, null_pointer) {
    ae_memory_raw_fill_u64(nullptr, nullptr, 5);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_fill_u64, zero_length) {
    ae_u64_t arr[10] = {0};
    EXPECT_EQ(ae_memory_raw_fill_u64(arr, arr, 5), arr);
}

TEST(ae_memory_raw_fill_u64, single_byte_fill) {
    ae_u64_t arr[1] = {0};
    ae_memory_raw_fill_u64(arr, &arr[1], 7);
    EXPECT_EQ(arr[0], 7);
}

TEST(ae_memory_raw_fill, fill_with32_divisible_length) {
    const size_t len = 32;
    uint8_t buffer[len] = {};

    ae_u8_t value = 0xCD;
    ae_memory_raw_fill(buffer, &buffer[len], value);
    for (unsigned char i: buffer) {
        ASSERT_EQ(i, value);
    }
}

TEST(ae_memory_raw_fill, fill_with16_divisible_length) {
    const size_t len = 16;
    uint8_t buffer[len];

    ae_u8_t value = 0xEF;
    ae_memory_raw_fill(buffer, &buffer[len], value);
    for (unsigned char i: buffer) {
        ASSERT_EQ(i, value);
    }
}

TEST(ae_memory_raw_fill, fill_with8_divisible_length) {
    const size_t len = 8;

    uint8_t buffer[len];
    ae_u8_t value = 0xFF;

    ae_memory_raw_fill(buffer, &buffer[len], value);
    for (unsigned char i: buffer) {
        ASSERT_EQ(i, value);
    }
}

TEST(ae_memory_raw_fill, fill_with_non_divisible_length) {
    const size_t len = 12;

    uint8_t buffer[len];
    ae_u8_t value = 0x01;

    ae_memory_raw_fill(buffer, &buffer[len], value);
    for (unsigned char i: buffer) {
        ASSERT_EQ(i, value);
    }
}

TEST(ae_memory_raw_find_value_u8, null_pointer) {
    EXPECT_EQ(ae_memory_raw_find_value_u8(nullptr, nullptr, 5), nullptr);
}

TEST(ae_memory_raw_find_value_u8, find_value) {
    ae_u8_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u8(arr, &arr[len], 3), &arr[2]);
}

TEST(ae_memory_raw_find_value_u8, value_not_found) {
    ae_u8_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u8(arr, &arr[len], 6), nullptr);
}

TEST(ae_memory_raw_find_value_u8, empty_array) {
    ae_u8_t *arr = nullptr;
    ae_usize_t len = 0;

    EXPECT_EQ(ae_memory_raw_find_value_u8(arr, &arr[len], 3), nullptr);
}

TEST(ae_memory_raw_find_value_u8, find_first_element) {
    ae_u8_t arr[] = {5, 6, 7, 8};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u8(arr, &arr[len], 5), &arr[0]);
}

TEST(ae_memory_raw_find_value_u16, null_pointer) {
    EXPECT_EQ(ae_memory_raw_find_value_u16(nullptr, nullptr, 5), nullptr);
}

TEST(ae_memory_raw_find_value_u16, find_value) {
    ae_u16_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u16(arr, &arr[len], 3), &arr[2]);
}

TEST(ae_memory_raw_find_value_u16, value_not_found) {
    ae_u16_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u16(arr, &arr[len], 6), nullptr);
}

TEST(ae_memory_raw_find_value_u16, empty_array) {
    ae_u16_t *arr = nullptr;
    ae_usize_t len = 0;

    EXPECT_EQ(ae_memory_raw_find_value_u16(arr, &arr[len], 3), nullptr);
}

TEST(ae_memory_raw_find_value_u16, find_first_element) {
    ae_u16_t arr[] = {5, 6, 7, 8};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u16(arr, &arr[len], 5), &arr[0]);
}

TEST(ae_memory_raw_find_value_u32, null_pointer) {
    EXPECT_EQ(ae_memory_raw_find_value_u32(nullptr, nullptr, 5), nullptr);
}

TEST(ae_memory_raw_find_value_u32, find_value) {
    ae_u32_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u32(arr, &arr[len], 3), &arr[2]);
}

TEST(ae_memory_raw_find_value_u32, value_not_found) {
    ae_u32_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u32(arr, &arr[len], 6), nullptr);
}

TEST(ae_memory_raw_find_value_u32, empty_array) {
    ae_u32_t *arr = nullptr;
    ae_usize_t len = 0;

    EXPECT_EQ(ae_memory_raw_find_value_u32(arr, &arr[len], 3), nullptr);
}

TEST(ae_memory_raw_find_value_u32, find_first_element) {
    ae_u32_t arr[] = {5, 6, 7, 8};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u32(arr, &arr[len], 5), &arr[0]);
}

TEST(ae_memory_raw_find_value_u64, null_pointer) {
    EXPECT_EQ(ae_memory_raw_find_value_u64(nullptr, nullptr, 5), nullptr);
}

TEST(ae_memory_raw_find_value_u64, find_value) {
    ae_u64_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u64(arr, &arr[len], 3), &arr[2]);
}

TEST(ae_memory_raw_find_value_u64, value_not_found) {
    ae_u64_t arr[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u64(arr, &arr[len], 6), nullptr);
}

TEST(ae_memory_raw_find_value_u64, empty_array) {
    ae_u64_t *arr = nullptr;
    ae_usize_t len = 0;

    EXPECT_EQ(ae_memory_raw_find_value_u64(arr, &arr[len], 3), nullptr);
}

TEST(ae_memory_raw_find_value_u64, find_first_element) {
    ae_u64_t arr[] = {5, 6, 7, 8};
    ae_usize_t len = sizeof(arr) / sizeof(arr[0]);

    EXPECT_EQ(ae_memory_raw_find_value_u64(arr, &arr[len], 5), &arr[0]);
}

TEST(ae_memory_raw_compare_u8, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_u8(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_u8, compare_same_length) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u8(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_u8, compare_different_length) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u8(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u8, compare_different_values) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {1, 2, 0, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u8(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_u8, empty_array) {
    ae_u8_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u8(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u8, compare_equal_after_different_elements) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u8(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(ae_memory_raw_compare_u16, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_u16(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_u16, compare_same_length) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u16(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_u16, compare_different_length) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u16(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u16, compare_different_values) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {1, 2, 0, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u16(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_u16, empty_array) {
    ae_u16_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u16(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u16, compare_equal_after_different_elements) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u16(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(ae_memory_raw_compare_u32, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_u32(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_u32, compare_same_length) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u32(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_u32, compare_different_length) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u32(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u32, compare_different_values) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {1, 2, 0, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u32(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_u32, empty_array) {
    ae_u32_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u32(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u32, compare_equal_after_different_elements) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u32(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(ae_memory_raw_compare_u64, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_u64(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_u64, compare_same_length) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u64(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_u64, compare_different_length) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u64(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u64, compare_different_values) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {1, 2, 0, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u64(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_u64, empty_array) {
    ae_u64_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u64(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_u64, compare_equal_after_different_elements) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_u64(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(ae_memory_raw_compare_rev_u8, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_rev_u8(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_rev_u8, compare_same_length) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u8(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u8, compare_different_length) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u8(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), &lhs[4]);
}

TEST(ae_memory_raw_compare_rev_u8, compare_different_values) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {1, 2, 3, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u8(lhs, &lhs[len], rhs, &rhs[len]), &lhs[3]);
}

TEST(ae_memory_raw_compare_rev_u8, empty_array) {
    ae_u8_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u8(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u8, compare_equal_after_different_elements) {
    ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    ae_u8_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u8(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_rev_u8, compare_same_last_elements) {
    ae_u8_t lhs[] = {0, 0, 0, 0, 5};
    ae_u8_t rhs[] = {0, 0, 0, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u8(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u16, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_rev_u16(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_rev_u16, compare_same_length) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u16(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u16, compare_different_length) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u16(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), &lhs[4]);
}

TEST(ae_memory_raw_compare_rev_u16, compare_different_values) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {1, 2, 3, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u16(lhs, &lhs[len], rhs, &rhs[len]), &lhs[3]);
}

TEST(ae_memory_raw_compare_rev_u16, empty_array) {
    ae_u16_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u16(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u16, compare_equal_after_different_elements) {
    ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    ae_u16_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u16(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_rev_u16, compare_same_last_elements) {
    ae_u16_t lhs[] = {0, 0, 0, 0, 5};
    ae_u16_t rhs[] = {0, 0, 0, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u16(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u32, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_rev_u32(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_rev_u32, compare_same_length) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u32(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u32, compare_different_length) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u32(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), &lhs[4]);
}

TEST(ae_memory_raw_compare_rev_u32, compare_different_values) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {1, 2, 3, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u32(lhs, &lhs[len], rhs, &rhs[len]), &lhs[3]);
}

TEST(ae_memory_raw_compare_rev_u32, empty_array) {
    ae_u32_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u32(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u32, compare_equal_after_different_elements) {
    ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    ae_u32_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u32(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_rev_u32, compare_same_last_elements) {
    ae_u32_t lhs[] = {0, 0, 0, 0, 5};
    ae_u32_t rhs[] = {0, 0, 0, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u32(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u64, null_pointers) {
    EXPECT_EQ(ae_memory_raw_compare_rev_u64(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_compare_rev_u64, compare_same_length) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u64(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u64, compare_different_length) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {1, 2, 3};
    ae_usize_t lhs_len = sizeof(lhs) / sizeof(lhs[0]);
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u64(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), &lhs[4]);
}

TEST(ae_memory_raw_compare_rev_u64, compare_different_values) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {1, 2, 3, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u64(lhs, &lhs[len], rhs, &rhs[len]), &lhs[3]);
}

TEST(ae_memory_raw_compare_rev_u64, empty_array) {
    ae_u64_t rhs[] = {1, 2, 3};
    ae_usize_t rhs_len = sizeof(rhs) / sizeof(rhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u64(nullptr, nullptr, rhs, &rhs[rhs_len]), nullptr);
}

TEST(ae_memory_raw_compare_rev_u64, compare_equal_after_different_elements) {
    ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    ae_u64_t rhs[] = {6, 7, 8, 4, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u64(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(ae_memory_raw_compare_rev_u64, compare_same_last_elements) {
    ae_u64_t lhs[] = {0, 0, 0, 0, 5};
    ae_u64_t rhs[] = {0, 0, 0, 0, 5};
    ae_usize_t len = sizeof(lhs) / sizeof(lhs[0]);

    EXPECT_EQ(ae_memory_raw_compare_rev_u64(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(ae_memory_raw_copy_u8, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_u8(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_u8, copy_same_length) {
    ae_u8_t src[] = {1, 2, 3, 4, 5};
    ae_u8_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u8_t *result = ae_memory_raw_copy_u8(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u8, copy_short_to_long) {
    ae_u8_t src[] = {1, 2, 3};
    ae_u8_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u8_t *result = ae_memory_raw_copy_u8(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + src_len);

    for (ae_usize_t i = 0; i < src_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }

    for (ae_usize_t i = src_len; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], 0);
    }
}

TEST(ae_memory_raw_copy_u8, copy_long_to_short) {
    ae_u8_t src[] = {1, 2, 3, 4, 5};
    ae_u8_t dst[3];
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u8_t *result = ae_memory_raw_copy_u8(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + dst_len);

    for (ae_usize_t i = 0; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u8, correct_copy) {
    ae_u8_t src[] = {10, 20, 30, 40, 50};
    ae_u8_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u8_t *result = ae_memory_raw_copy_u8(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u16, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_u16(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_u16, copy_same_length) {
    ae_u16_t src[] = {1, 2, 3, 4, 5};
    ae_u16_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u16_t *result = ae_memory_raw_copy_u16(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u16, copy_short_to_long) {
    ae_u16_t src[] = {1, 2, 3};
    ae_u16_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u16_t *result = ae_memory_raw_copy_u16(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + src_len);

    for (ae_usize_t i = 0; i < src_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }

    for (ae_usize_t i = src_len; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], 0);
    }
}

TEST(ae_memory_raw_copy_u16, copy_long_to_short) {
    ae_u16_t src[] = {1, 2, 3, 4, 5};
    ae_u16_t dst[3];
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u16_t *result = ae_memory_raw_copy_u16(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + dst_len);

    for (ae_usize_t i = 0; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u16, correct_copy) {
    ae_u16_t src[] = {10, 20, 30, 40, 50};
    ae_u16_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u16_t *result = ae_memory_raw_copy_u16(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u32, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_u32(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_u32, copy_same_length) {
    ae_u32_t src[] = {1, 2, 3, 4, 5};
    ae_u32_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u32_t *result = ae_memory_raw_copy_u32(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u32, copy_short_to_long) {
    ae_u32_t src[] = {1, 2, 3};
    ae_u32_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u32_t *result = ae_memory_raw_copy_u32(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + src_len);

    for (ae_usize_t i = 0; i < src_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }

    for (ae_usize_t i = src_len; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], 0);
    }
}

TEST(ae_memory_raw_copy_u32, copy_long_to_short) {
    ae_u32_t src[] = {1, 2, 3, 4, 5};
    ae_u32_t dst[3];
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u32_t *result = ae_memory_raw_copy_u32(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + dst_len);

    for (ae_usize_t i = 0; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u32, correct_copy) {
    ae_u32_t src[] = {10, 20, 30, 40, 50};
    ae_u32_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u32_t *result = ae_memory_raw_copy_u32(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u64, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_u64(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_u64, copy_same_length) {
    ae_u64_t src[] = {1, 2, 3, 4, 5};
    ae_u64_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u64_t *result = ae_memory_raw_copy_u64(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u64, copy_short_to_long) {
    ae_u64_t src[] = {1, 2, 3};
    ae_u64_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u64_t *result = ae_memory_raw_copy_u64(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + src_len);

    for (ae_usize_t i = 0; i < src_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }

    for (ae_usize_t i = src_len; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], 0);
    }
}

TEST(ae_memory_raw_copy_u64, copy_long_to_short) {
    ae_u64_t src[] = {1, 2, 3, 4, 5};
    ae_u64_t dst[3];
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u64_t *result = ae_memory_raw_copy_u64(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + dst_len);

    for (ae_usize_t i = 0; i < dst_len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_copy_u64, correct_copy) {
    ae_u64_t src[] = {10, 20, 30, 40, 50};
    ae_u64_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u64_t *result = ae_memory_raw_copy_u64(dst, &dst[len], src, &src[len]);
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

    memset(src, value, len);
    void *result = ae_memory_raw_copy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i: dst) {
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

    for (unsigned char i: dst) {
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

    for (unsigned char i: dst) {
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

    for (unsigned char i: dst) {
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

    for (unsigned char i: dst) {
        ASSERT_EQ(i, value);
    }
}

TEST(ae_memory_raw_copy_rev_u8, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_rev_u8(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_rev_u8, copy_same_length) {
    ae_u8_t src[] = {1, 2, 3, 4, 5};
    ae_u8_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u8_t *result = ae_memory_raw_copy_rev_u8(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy_rev_u8, copy_short_to_long) {
    ae_u8_t src[] = {1, 2, 3};
    ae_u8_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u8_t *result = ae_memory_raw_copy_rev_u8(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + (dst_len - src_len));

    ae_u8_t expected[] = {0, 0, 1, 2, 3};
    EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy_rev_u8, copy_long_to_short) {
    ae_u8_t src[] = {1, 2, 3, 4, 5};
    ae_u8_t dst[3] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u8_t *result = ae_memory_raw_copy_rev_u8(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst);

    ae_u8_t expected[] = {3, 4, 5};
    EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy_rev_u8, correct_copy) {
    ae_u8_t src[] = {10, 20, 30, 40, 50};
    ae_u8_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u8_t *result = ae_memory_raw_copy_rev_u8(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy_rev_u16, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_rev_u16(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_rev_u16, copy_same_length) {
    ae_u16_t src[] = {1, 2, 3, 4, 5};
    ae_u16_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u16_t *result = ae_memory_raw_copy_rev_u16(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy_rev_u16, copy_short_to_long) {
    ae_u16_t src[] = {1, 2, 3};
    ae_u16_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u16_t *result = ae_memory_raw_copy_rev_u16(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + (dst_len - src_len));

    ae_u16_t expected[] = {0, 0, 1, 2, 3};
    EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy_rev_u16, copy_long_to_short) {
    ae_u16_t src[] = {1, 2, 3, 4, 5};
    ae_u16_t dst[3] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u16_t *result = ae_memory_raw_copy_rev_u16(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst);

    ae_u16_t expected[] = {3, 4, 5};
    EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy_rev_u16, correct_copy) {
    ae_u16_t src[] = {10, 20, 30, 40, 50};
    ae_u16_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u16_t *result = ae_memory_raw_copy_rev_u16(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy_rev_u32, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_rev_u32(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_rev_u32, copy_same_length) {
    ae_u32_t src[] = {1, 2, 3, 4, 5};
    ae_u32_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u32_t *result = ae_memory_raw_copy_rev_u32(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy_rev_u32, copy_short_to_long) {
    ae_u32_t src[] = {1, 2, 3};
    ae_u32_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u32_t *result = ae_memory_raw_copy_rev_u32(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + (dst_len - src_len));

    ae_u32_t expected[] = {0, 0, 1, 2, 3};
    EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy_rev_u32, copy_long_to_short) {
    ae_u32_t src[] = {1, 2, 3, 4, 5};
    ae_u32_t dst[3] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u32_t *result = ae_memory_raw_copy_rev_u32(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst);

    ae_u32_t expected[] = {3, 4, 5};
    EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy_rev_u32, correct_copy) {
    ae_u32_t src[] = {10, 20, 30, 40, 50};
    ae_u32_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u32_t *result = ae_memory_raw_copy_rev_u32(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy_rev_u64, null_pointers) {
    EXPECT_EQ(ae_memory_raw_copy_rev_u64(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_copy_rev_u64, copy_same_length) {
    ae_u64_t src[] = {1, 2, 3, 4, 5};
    ae_u64_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u64_t *result = ae_memory_raw_copy_rev_u64(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(src, dst, len));
}

TEST(ae_memory_raw_copy_rev_u64, copy_short_to_long) {
    ae_u64_t src[] = {1, 2, 3};
    ae_u64_t dst[5] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u64_t *result = ae_memory_raw_copy_rev_u64(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst + (dst_len - src_len));

    ae_u64_t expected[] = {0, 0, 1, 2, 3};
    EXPECT_TRUE(!memcmp(dst, expected, 5));
}

TEST(ae_memory_raw_copy_rev_u64, copy_long_to_short) {
    ae_u64_t src[] = {1, 2, 3, 4, 5};
    ae_u64_t dst[3] = {};
    ae_usize_t src_len = sizeof(src) / sizeof(src[0]);
    ae_usize_t dst_len = sizeof(dst) / sizeof(dst[0]);

    ae_u64_t *result = ae_memory_raw_copy_rev_u64(dst, &dst[dst_len], src, &src[src_len]);
    EXPECT_EQ(result, dst);

    ae_u64_t expected[] = {3, 4, 5};
    EXPECT_TRUE(!memcmp(dst, expected, 3));
}

TEST(ae_memory_raw_copy_rev_u64, correct_copy) {
    ae_u64_t src[] = {10, 20, 30, 40, 50};
    ae_u64_t dst[5] = {};
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u64_t *result = ae_memory_raw_copy_rev_u64(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    EXPECT_TRUE(!memcmp(dst, src, 3));
}

TEST(ae_memory_raw_copy_rev, copy_rev_with64_divisible_length) {
    const size_t len = 64;
    uint8_t src[len];
    uint8_t dst[len];
    ae_u8_t value = 0xAB;

    memset(src, value, len);
    void *result = ae_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (size_t i = 0; i < len; ++i) {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with32_divisible_length) {
    const size_t len = 32;
    uint8_t src[len];
    uint8_t dst[len];
    ae_u8_t value = 0xCD;

    memset(src, value, len);
    void *result = ae_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (size_t i = 0; i < len; ++i) {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with16_divisible_length) {
    const size_t len = 16;
    uint8_t src[len];
    uint8_t dst[len];
    ae_u8_t value = 0xEF;

    memset(src, value, len);
    void *result = ae_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (size_t i = 0; i < len; ++i) {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with8_divisible_length) {
    const size_t len = 8;
    uint8_t src[len];
    uint8_t dst[len];
    ae_u8_t value = 0xFF;

    memset(src, value, len);
    void *result = ae_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (size_t i = 0; i < len; ++i) {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(ae_memory_raw_copy_rev, copy_rev_with_non_divisible_length) {
    const size_t len = 12;
    uint8_t src[len];
    uint8_t dst[len];
    ae_u8_t value = 0x01;

    memset(src, value, len);
    void *result = ae_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (size_t i = 0; i < len; ++i) {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(ae_memory_raw_move_u8, null_pointers) {
    EXPECT_EQ(ae_memory_raw_move_u8(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_move_u8, move_without_overlap) {
    ae_u8_t src[] = {1, 2, 3, 4, 5};
    ae_u8_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u8_t *result = ae_memory_raw_move_u8(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u8, move_with_overlap) {
    ae_u8_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u8_t *result = ae_memory_raw_move_u8(buffer + 2, buffer + len, buffer, buffer + len - 2);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 2; ++i) {
        EXPECT_EQ(buffer[i + 2], (i + 1));
    }
}

TEST(ae_memory_raw_move_u8, move_same_buffer) {
    ae_u8_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u8_t *result = ae_memory_raw_move_u8(buffer, &buffer[len], buffer, &buffer[len]);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
}

TEST(ae_memory_raw_move_u8, move_same_length) {
    ae_u8_t src[] = {1, 2, 3, 4, 5};
    ae_u8_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u8_t *result = ae_memory_raw_move_u8(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u8, move_adjacent_with_overlap) {
    ae_u8_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u8_t *result = ae_memory_raw_move_u8(buffer + 1, buffer + len, buffer, buffer + len - 1);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 1; ++i) {
        EXPECT_EQ(buffer[i + 1], (i + 1));
    }
}

TEST(ae_memory_raw_move_u16, null_pointers) {
    EXPECT_EQ(ae_memory_raw_move_u16(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_move_u16, move_without_overlap) {
    ae_u16_t src[] = {1, 2, 3, 4, 5};
    ae_u16_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u16_t *result = ae_memory_raw_move_u16(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u16, move_with_overlap) {
    ae_u16_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u16_t *result = ae_memory_raw_move_u16(buffer + 2, buffer + len, buffer, buffer + len - 2);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 2; ++i) {
        EXPECT_EQ(buffer[i + 2], (i + 1));
    }
}

TEST(ae_memory_raw_move_u16, move_same_buffer) {
    ae_u16_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u16_t *result = ae_memory_raw_move_u16(buffer, &buffer[len], buffer, &buffer[len]);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
}

TEST(ae_memory_raw_move_u16, move_same_length) {
    ae_u16_t src[] = {1, 2, 3, 4, 5};
    ae_u16_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u16_t *result = ae_memory_raw_move_u16(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u16, move_adjacent_with_overlap) {
    ae_u16_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u16_t *result = ae_memory_raw_move_u16(buffer + 1, buffer + len, buffer, buffer + len - 1);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 1; ++i) {
        EXPECT_EQ(buffer[i + 1], (i + 1));
    }
}

TEST(ae_memory_raw_move_u32, null_pointers) {
    EXPECT_EQ(ae_memory_raw_move_u32(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_move_u32, move_without_overlap) {
    ae_u32_t src[] = {1, 2, 3, 4, 5};
    ae_u32_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u32_t *result = ae_memory_raw_move_u32(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u32, move_with_overlap) {
    ae_u32_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u32_t *result = ae_memory_raw_move_u32(buffer + 2, buffer + len, buffer, buffer + len - 2);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 2; ++i) {
        EXPECT_EQ(buffer[i + 2], (i + 1));
    }
}

TEST(ae_memory_raw_move_u32, move_same_buffer) {
    ae_u32_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u32_t *result = ae_memory_raw_move_u32(buffer, &buffer[len], buffer, &buffer[len]);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
}

TEST(ae_memory_raw_move_u32, move_same_length) {
    ae_u32_t src[] = {1, 2, 3, 4, 5};
    ae_u32_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u32_t *result = ae_memory_raw_move_u32(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u32, move_adjacent_with_overlap) {
    ae_u32_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u32_t *result = ae_memory_raw_move_u32(buffer + 1, buffer + len, buffer, buffer + len - 1);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 1; ++i) {
        EXPECT_EQ(buffer[i + 1], (i + 1));
    }
}

TEST(ae_memory_raw_move_u64, null_pointers) {
    EXPECT_EQ(ae_memory_raw_move_u64(nullptr, nullptr, nullptr, nullptr), nullptr);
}

TEST(ae_memory_raw_move_u64, move_without_overlap) {
    ae_u64_t src[] = {1, 2, 3, 4, 5};
    ae_u64_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u64_t *result = ae_memory_raw_move_u64(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u64, move_with_overlap) {
    ae_u64_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u64_t *result = ae_memory_raw_move_u64(buffer + 2, buffer + len, buffer, buffer + len - 2);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 2; ++i) {
        EXPECT_EQ(buffer[i + 2], (i + 1));
    }
}

TEST(ae_memory_raw_move_u64, move_same_buffer) {
    ae_u64_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u64_t *result = ae_memory_raw_move_u64(buffer, &buffer[len], buffer, &buffer[len]);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
}

TEST(ae_memory_raw_move_u64, move_same_length) {
    ae_u64_t src[] = {1, 2, 3, 4, 5};
    ae_u64_t dst[5];
    ae_usize_t len = sizeof(src) / sizeof(src[0]);

    ae_u64_t *result = ae_memory_raw_move_u64(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (ae_usize_t i = 0; i < len; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move_u64, move_adjacent_with_overlap) {
    ae_u64_t buffer[] = {1, 2, 3, 4, 5};
    ae_usize_t len = sizeof(buffer) / sizeof(buffer[0]);

    ae_u64_t *result = ae_memory_raw_move_u64(buffer + 1, buffer + len, buffer, buffer + len - 1);
    EXPECT_EQ(result, buffer + len);

    for (ae_usize_t i = 0; i < len - 1; ++i) {
        EXPECT_EQ(buffer[i + 1], (i + 1));
    }
}

TEST(ae_memory_raw_move, move64_bytes) {
    uint64_t src[] = {1, 2, 3, 4};
    uint64_t dst[4];

    void *result =
            ae_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move32_bytes) {
    uint32_t src[] = {1, 2, 3, 4};
    uint32_t dst[4];

    void *result =
            ae_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move16_bytes) {
    uint16_t src[] = {1, 2, 3, 4};
    uint16_t dst[4];

    void *result =
            ae_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(ae_memory_raw_move, move8_bytes) {
    uint8_t src[] = {1, 2, 3, 4};
    uint8_t dst[4];

    void *result =
            ae_memory_raw_move(dst, dst + 4, src, src + 4);
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

    void *result =
            ae_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
    ASSERT_EQ(result, &buf[6]);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(ae_memory_raw_move, move16_bytes_overlap) {
    uint16_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    void *result =
            ae_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
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

TEST(ae_memory_raw_find_u8, NormalTest) {
    const ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u8_t rhs[] = {3, 4};

    const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, lhs + 2);  // Мы ожидаем, что совпадение будет начиная с элемента 3
}

TEST(ae_memory_raw_find_u8, null_pointer) {
    const ae_u8_t *lhs = nullptr;
    const ae_u8_t rhs[] = {3, 4};

    ae_memory_raw_find_u8(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u8, empty_lhs) {
    const ae_u8_t *lhs = nullptr;
    const ae_u8_t rhs[] = {3, 4};

    const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u8, empty_rhs) {
    const ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u8_t *rhs = nullptr;

    const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 5, rhs, rhs);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u8, no_match) {
    const ae_u8_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u8_t rhs[] = {6, 7};

    const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u8, match_at_start) {
    const ae_u8_t lhs[] = {3, 4, 5};
    const ae_u8_t rhs[] = {3, 4};

    const ae_u8_t *result = ae_memory_raw_find_u8(lhs, lhs + 3, rhs, rhs + 2);
    EXPECT_EQ(result, lhs);
}

TEST(ae_memory_raw_find_u16, null_pointer) {
    const ae_u16_t *lhs = nullptr;
    const ae_u16_t rhs[] = {3, 4};

    ae_memory_raw_find_u16(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u16, empty_lhs) {
    const ae_u16_t *lhs = nullptr;
    const ae_u16_t rhs[] = {3, 4};

    const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u16, empty_rhs) {
    const ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u16_t *rhs = nullptr;

    const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 5, rhs, rhs);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u16, no_match) {
    const ae_u16_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u16_t rhs[] = {6, 7};

    const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u16, match_at_start) {
    const ae_u16_t lhs[] = {3, 4, 5};
    const ae_u16_t rhs[] = {3, 4};

    const ae_u16_t *result = ae_memory_raw_find_u16(lhs, lhs + 3, rhs, rhs + 2);
    EXPECT_EQ(result, lhs);
}

TEST(ae_memory_raw_find_u32, null_pointer) {
    const ae_u32_t *lhs = nullptr;
    const ae_u32_t rhs[] = {3, 4};

    ae_memory_raw_find_u32(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u32, empty_lhs) {
    const ae_u32_t *lhs = nullptr;
    const ae_u32_t rhs[] = {3, 4};

    const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u32, empty_rhs) {
    const ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u32_t *rhs = nullptr;

    const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 5, rhs, rhs);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u32, no_match) {
    const ae_u32_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u32_t rhs[] = {6, 7};

    const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u32, match_at_start) {
    const ae_u32_t lhs[] = {3, 4, 5};
    const ae_u32_t rhs[] = {3, 4};

    const ae_u32_t *result = ae_memory_raw_find_u32(lhs, lhs + 3, rhs, rhs + 2);
    EXPECT_EQ(result, lhs);
}

TEST(ae_memory_raw_find_u64, null_pointer) {
    const ae_u64_t *lhs = nullptr;
    const ae_u64_t rhs[] = {3, 4};

    ae_memory_raw_find_u64(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_u64, empty_lhs) {
    const ae_u64_t *lhs = nullptr;
    const ae_u64_t rhs[] = {3, 4};

    const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u64, empty_rhs) {
    const ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u64_t *rhs = nullptr;

    const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 5, rhs, rhs);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u64, no_match) {
    const ae_u64_t lhs[] = {1, 2, 3, 4, 5};
    const ae_u64_t rhs[] = {6, 7};

    const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_u64, match_at_start) {
    const ae_u64_t lhs[] = {3, 4, 5};
    const ae_u64_t rhs[] = {3, 4};

    const ae_u64_t *result = ae_memory_raw_find_u64(lhs, lhs + 3, rhs, rhs + 2);
    EXPECT_EQ(result, lhs);
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
    const ae_u8_t *result = ae_memory_raw_find_rev_u8(nullptr, nullptr, nullptr, nullptr);

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

    const ae_u16_t *result = ae_memory_raw_find_rev_u16(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u16, substring_not_found) {
    ae_u16_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    ae_u16_t rhs[] = {0x07, 0x08};

    const ae_u16_t *result = ae_memory_raw_find_rev_u16(lhs, &lhs[6], rhs, &rhs[2]);
    ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u16, find_substring_at_end) {
    ae_u16_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    ae_u16_t rhs[] = {0x05, 0x06};

    const ae_u16_t *result = ae_memory_raw_find_rev_u16(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u16, empty_arrays) {
    const ae_u16_t *result = ae_memory_raw_find_rev_u16(nullptr, nullptr, nullptr, nullptr);

    ASSERT_EQ(result, nullptr);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u16, rhs_longer_than_lhs) {
    ae_u16_t lhs[] = {0x01, 0x02, 0x03};
    ae_u16_t rhs[] = {0x01, 0x02, 0x03, 0x04};

    const ae_u16_t *result = ae_memory_raw_find_rev_u16(lhs, &lhs[3], rhs, &rhs[4]);
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

    const ae_u32_t *result = ae_memory_raw_find_rev_u32(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u32, substring_not_found) {
    ae_u32_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    ae_u32_t rhs[] = {0x07, 0x08};

    const ae_u32_t *result = ae_memory_raw_find_rev_u32(lhs, &lhs[6], rhs, &rhs[2]);
    ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u32, find_substring_at_end) {
    ae_u32_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    ae_u32_t rhs[] = {0x05, 0x06};

    const ae_u32_t *result = ae_memory_raw_find_rev_u32(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u32, empty_arrays) {
    const ae_u32_t *result = ae_memory_raw_find_rev_u32(nullptr, nullptr, nullptr, nullptr);

    ASSERT_EQ(result, nullptr);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u32, rhs_longer_than_lhs) {
    ae_u32_t lhs[] = {0x01, 0x02, 0x03};
    ae_u32_t rhs[] = {0x01, 0x02, 0x03, 0x04};

    const ae_u32_t *result = ae_memory_raw_find_rev_u32(lhs, &lhs[3], rhs, &rhs[4]);
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

    const ae_u64_t *result = ae_memory_raw_find_rev_u64(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 2);
}

TEST(ae_memory_raw_find_rev_u64, substring_not_found) {
    ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    ae_u64_t rhs[] = {0x07, 0x08};

    const ae_u64_t *result = ae_memory_raw_find_rev_u64(lhs, &lhs[6], rhs, &rhs[2]);
    ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u64, find_substring_at_end) {
    ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    ae_u64_t rhs[] = {0x05, 0x06};

    const ae_u64_t *result = ae_memory_raw_find_rev_u64(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 4);
}

TEST(ae_memory_raw_find_rev_u64, empty_arrays) {
    const ae_u64_t *result = ae_memory_raw_find_rev_u64(nullptr, nullptr, nullptr, nullptr);

    ASSERT_EQ(result, nullptr);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(ae_memory_raw_find_rev_u64, rhs_longer_than_lhs) {
    ae_u64_t lhs[] = {0x01, 0x02, 0x03};
    ae_u64_t rhs[] = {0x01, 0x02, 0x03, 0x04};

    const ae_u64_t *result = ae_memory_raw_find_rev_u64(lhs, &lhs[3], rhs, &rhs[4]);
    ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_find_rev_u64, null_pointer_check) {
    ae_u64_t lhs[] = {0x01, 0x02, 0x03, 0x04};
    ae_u64_t rhs[] = {0x03, 0x04};

    ae_memory_raw_find_rev_u64(nullptr, &lhs[4], rhs, &rhs[2]);
    EXPECT_EQ(ae_error_get_code_and_clear(ae_runtime_error()),
              AE_RUNTIME_ERROR_NULL_POINTER);
}