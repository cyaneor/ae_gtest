#include <ae/memory_raw.h>
#include <gtest/gtest.h>

TEST(ae_memory_raw_fill, fill_array_with_value) {
  unsigned char array[5];
  unsigned char value = 42;
  auto *result = (unsigned char *)ae_memory_raw_fill(array, array + 5, value);

  // Check if the return value is correct
  ASSERT_EQ(result, array + 5);

  // Check each element of the array
  for (unsigned char i : array) {
    EXPECT_EQ(i, value);
  }
}

TEST(ae_memory_raw_fill, handle_empty_range) {
  unsigned char array[5] = {0};
  unsigned char value = 42;
  auto *result = (unsigned char *)ae_memory_raw_fill(array, array, value);

  // Check if the return value is correct
  ASSERT_EQ(result, array);

  // Verify that the array remains unchanged
  for (unsigned char i : array) {
    EXPECT_EQ(i, 0);
  }
}

TEST(ae_memory_raw_fill, fill_partial_array) {
  unsigned char array[5] = {0};
  unsigned char value = 42;
  auto *result = (unsigned char *)ae_memory_raw_fill(array, array + 3, value);

  // Check if the return value is correct
  ASSERT_EQ(result, array + 3);

  // Check the filled part of the array
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(array[i], value);
  }

  // Verify that the rest of the array remains unchanged
  for (int i = 3; i < 5; ++i) {
    EXPECT_EQ(array[i], 0);
  }
}

TEST(ae_memory_raw_copy, correct_copy_no_overlap) {
  char source[] = "Test source";
  char destination[20];

  // Calling the copy function
  ae_memory_raw_copy(destination, destination + sizeof(destination), source,
                     source + sizeof(source));

  // Verifying that the data was copied correctly
  EXPECT_EQ(memcmp(source, destination, sizeof(source)), 0);
}

TEST(ae_memory_raw_copy, copy_different_sizes) {
  char source[] = "Short";

  // Initialization with zeros for the purity of the experiment
  char destination[20] = {0};

  // Calling the copy function
  ae_memory_raw_copy(destination, destination + 10, source,
                     source + sizeof(source));

  // Verifying that the data was copied correctly
  EXPECT_EQ(memcmp(source, destination, sizeof(source)), 0);

  // Checking that the rest of the assignment has not been changed
  EXPECT_EQ(memcmp(destination + sizeof(source), "\0\0\0\0\0\0", 6), 0);
}
TEST(ae_memory_raw_compare_from_end, CommonMemoryCell) {
  const char lhs[] = "Hello";
  const char *lhs_begin = lhs;
  const char *lhs_end = lhs + 4;

  const char rhs[] = "World";
  const char *rhs_begin = rhs;
  const char *rhs_end = rhs + 4;

  const void *result =
      ae_memory_raw_compare_from_end(lhs_begin, lhs_end, rhs_begin, rhs_end);

  ASSERT_EQ(result, lhs_end);
}

TEST(ae_memory_raw_compare, null_pointers) {
  const void *result =
      ae_memory_raw_compare(nullptr, nullptr, nullptr, nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_compare, non_overlapping_identical) {
  char lhs[] = "test";
  char rhs[] = "test";
  const void *result = ae_memory_raw_compare(lhs, lhs + 4, rhs, rhs + 4);
  EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_compare, non_overlapping_different) {
  char lhs[] = "test1";
  char rhs[] = "test2";
  const void *result = ae_memory_raw_compare(lhs, lhs + 5, rhs, rhs + 5);
  EXPECT_NE(result, nullptr);
}

TEST(ae_memory_raw_compare, overlapping_regions) {
  char buffer[] = "testtest";
  const void *result =
      ae_memory_raw_compare(buffer, buffer + 4, buffer + 4, buffer + 8);

  // Assuming LUNA_PTR_IS_OVERLAP will return true for overlapping regions
  EXPECT_EQ(result, nullptr);
}

TEST(ae_memory_raw_compare, non_equal_regions) {
  const char lhs[] = "abcdef";
  const char rhs[] = "abcxyz";
  const void *result = ae_memory_raw_compare(lhs, lhs + 5, rhs, rhs + 5);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(*static_cast<const char *>(result), 'd');
}

TEST(ae_memory_raw_compare, equal_regions) {
  const char lhs[] = "abcdef";
  const char rhs[] = "abcdef";
  const void *result = ae_memory_raw_compare(lhs, lhs + 5, rhs, rhs + 5);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_compare_from_end, non_equal_regions) {
  const char lhs[] = "abcdef";
  const char rhs[] = "abcxyz";
  const void *result =
      ae_memory_raw_compare_from_end(lhs, lhs + 5, rhs, rhs + 5);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(*static_cast<const char *>(result), 'f');
}

TEST(ae_memory_raw_compare_from_end, equal_regions) {
  const char lhs[] = "abcdef";
  const char rhs[] = "abcdef";
  const void *result =
      ae_memory_raw_compare_from_end(lhs, lhs + 5, rhs, rhs + 5);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_compare_from_end, overlapping_regions) {
  char buffer[] = "abcdefabcdef";
  const void *result = ae_memory_raw_compare_from_end(buffer, buffer + 5,
                                                      buffer + 6, buffer + 11);
  ASSERT_EQ(result, nullptr);
}

TEST(ae_memory_raw_copy_from_end, copy_int_array) {
  int src[] = {1, 2, 3, 4, 5};
  int dest[5] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 5, src, src + 5);

  EXPECT_EQ(dest[0], 1);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 3);
  EXPECT_EQ(dest[3], 4);
  EXPECT_EQ(dest[4], 5);
}

TEST(ae_memory_raw_copy_from_end, copy_char_array) {
  char src[] = {'a', 'b', 'c', 'd', 'e'};
  char dest[5] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 5, src, src + 5);

  EXPECT_EQ(dest[0], 'a');
  EXPECT_EQ(dest[1], 'b');
  EXPECT_EQ(dest[2], 'c');
  EXPECT_EQ(dest[3], 'd');
  EXPECT_EQ(dest[4], 'e');
}

TEST(ae_memory_raw_copy_from_end, copy_short_array) {
  short src[] = {10, 20, 30, 40, 50};
  short dest[5] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 5, src, src + 5);

  EXPECT_EQ(dest[0], 10);
  EXPECT_EQ(dest[1], 20);
  EXPECT_EQ(dest[2], 30);
  EXPECT_EQ(dest[3], 40);
  EXPECT_EQ(dest[4], 50);
}

TEST(ae_memory_raw_copy_from_end, copy_float_array) {
  float src[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  float dest[5] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 5, src, src + 5);

  EXPECT_EQ(dest[0], 1.1f);
  EXPECT_EQ(dest[1], 2.2f);
  EXPECT_EQ(dest[2], 3.3f);
  EXPECT_EQ(dest[3], 4.4f);
  EXPECT_EQ(dest[4], 5.5f);
}

TEST(ae_memory_raw_copy_from_end, copy_double_array) {
  double src[] = {1.11, 2.22, 3.33, 4.44, 5.55};
  double dest[5] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 5, src, src + 5);

  EXPECT_EQ(dest[0], 1.11);
  EXPECT_EQ(dest[1], 2.22);
  EXPECT_EQ(dest[2], 3.33);
  EXPECT_EQ(dest[3], 4.44);
  EXPECT_EQ(dest[4], 5.55);
}

// Тест для пустых массивов
TEST(ae_memory_raw_copy_from_end, empty_arrays) {
  int src[5] = {0};
  int dest[5] = {0};

  ae_memory_raw_copy_from_end(dest + 5, dest, src + 5, src);

  EXPECT_EQ(dest[0], 0);
  EXPECT_EQ(dest[1], 0);
  EXPECT_EQ(dest[2], 0);
  EXPECT_EQ(dest[3], 0);
  EXPECT_EQ(dest[4], 0);
}

TEST(ae_memory_raw_copy_from_end, same_size_arrays) {
  int src[] = {5, 10, 15, 20};
  int dest[4] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 4, src, src + 4);

  EXPECT_EQ(dest[0], 5);
  EXPECT_EQ(dest[1], 10);
  EXPECT_EQ(dest[2], 15);
  EXPECT_EQ(dest[3], 20);
}

// Тест для копирования на частичные массивы
TEST(ae_memory_raw_copy_from_end, partial_copy) {
  int src[] = {1, 2, 3, 4, 5};
  int dest[5] = {0};

  ae_memory_raw_copy_from_end(dest + 3, dest + 5, src + 2, src + 4);

  EXPECT_EQ(dest[0], 0);
  EXPECT_EQ(dest[1], 0);
  EXPECT_EQ(dest[2], 0);
  EXPECT_EQ(dest[3], 3);
  EXPECT_EQ(dest[4], 4);
}

TEST(ae_memory_raw_copy_from_end, aligned_copy) {
  alignas(AE_U64_T_SIZE) int src[] = {1, 2, 3, 4, 5};
  alignas(AE_U64_T_SIZE) int dest[5] = {0};

  ae_memory_raw_copy_from_end(dest, dest + 5, src, src + 5);

  EXPECT_EQ(dest[0], 1);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 3);
  EXPECT_EQ(dest[3], 4);
  EXPECT_EQ(dest[4], 5);
}

TEST(ae_memory_raw_copy_from_end, copy_struct_array) {
  struct MyStruct {
    int a;
    float b;
  };

  MyStruct src[] = {{1, 1.1f}, {2, 2.2f}, {3, 3.3f}};
  MyStruct dest[3] = {};

  ae_memory_raw_copy_from_end(dest, dest + 3, src, src + 3);

  EXPECT_EQ(dest[0].a, 1);
  EXPECT_EQ(dest[0].b, 1.1f);
  EXPECT_EQ(dest[1].a, 2);
  EXPECT_EQ(dest[1].b, 2.2f);
  EXPECT_EQ(dest[2].a, 3);
  EXPECT_EQ(dest[2].b, 3.3f);
}

TEST(ae_memory_raw_copy_from_end, copy_with_null_values) {
  int src[] = {0, 0, 0, 0, 0};
  int dest[5] = {0};

  ae_memory_raw_copy_from_end(dest + 5, dest, src + 5, src);

  EXPECT_EQ(dest[0], 0);
  EXPECT_EQ(dest[1], 0);
  EXPECT_EQ(dest[2], 0);
  EXPECT_EQ(dest[3], 0);
  EXPECT_EQ(dest[4], 0);
}

TEST(ae_memory_raw_move, move8_bit_no_overlap) {
    size_t size = 10;
    uint8_t src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t dest[10] = {0};

    uint8_t expected[10];
    memmove(expected, src, size);

    ae_memory_raw_move(dest, dest + size, src, src + size);
    EXPECT_TRUE(!ae_memory_raw_compare(dest, dest + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move8_bit_with_overlap) {
    size_t size = 10;
    uint8_t buffer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    uint8_t expected[10];
    memmove(expected, buffer, size);

    ae_memory_raw_move(buffer + 2, buffer + size, buffer, buffer + size);
    EXPECT_TRUE(!ae_memory_raw_compare(buffer, buffer + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move16_bit_no_overlap) {
    size_t size = 5;
    uint16_t src[5] = {10, 20, 30, 40, 50};
    uint16_t dest[5] = {0};

    uint16_t expected[5];
    memmove(expected, src, size * sizeof(uint16_t));

    ae_memory_raw_move(dest, dest + size, src, src + size);
    EXPECT_TRUE(!ae_memory_raw_compare(dest, dest + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move16_bit_with_overlap) {
    size_t size = 5;
    uint16_t buffer[5] = {10, 20, 30, 40, 50};

    uint16_t expected[5];
    memmove(expected, buffer, size * sizeof(uint16_t));

    ae_memory_raw_move(buffer + 2, buffer + size, buffer, buffer + size);
    EXPECT_TRUE(!ae_memory_raw_compare(buffer, buffer + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move32_bit_no_overlap) {
    size_t size = 5;
    uint32_t src[5] = {100, 200, 300, 400, 500};
    uint32_t dest[5] = {0};

    uint32_t expected[5];
    memmove(expected, src, size * sizeof(uint32_t));

    ae_memory_raw_move(dest, dest + size, src, src + size);
    EXPECT_TRUE(!ae_memory_raw_compare(dest, dest + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move32_bit_with_overlap) {
    size_t size = 5;
    uint32_t buffer[5] = {100, 200, 300, 400, 500};

    uint32_t expected[5];
    memmove(expected, buffer, size * sizeof(uint32_t));

    ae_memory_raw_move(buffer + 2, buffer + size, buffer, buffer + size);
    EXPECT_TRUE(!ae_memory_raw_compare(buffer, buffer + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move64_bit_no_overlap) {
    size_t size = 5;
    uint64_t src[5] = {1000, 2000, 3000, 4000, 5000};
    uint64_t dest[5] = {0};

    uint64_t expected[5];
    memmove(expected, src, size * sizeof(uint64_t));

    ae_memory_raw_move(dest, dest + size, src, src + size);
    EXPECT_TRUE(!ae_memory_raw_compare(dest, dest + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move64_bit_with_overlap) {
    size_t size = 5;
    uint64_t buffer[5] = {1000, 2000, 3000, 4000, 5000};

    uint64_t expected[5];
    memmove(expected, buffer, size * sizeof(uint64_t));

    ae_memory_raw_move(buffer + 2, buffer + size, buffer, buffer + size);
    EXPECT_TRUE(!ae_memory_raw_compare(buffer, buffer + size, expected, expected + size));
}

TEST(ae_memory_raw_move, move_with_different_alignments) {
    size_t size = 10;
    uint8_t src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t dest[10] = {0};

    uint8_t expected[10];
    memmove(expected, src, size);

    ae_memory_raw_move(dest, dest + size, src, src + size);
    EXPECT_TRUE(!ae_memory_raw_compare(dest, dest + size, expected, expected + size));
}