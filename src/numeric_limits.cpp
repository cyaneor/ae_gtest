#include <ae/numeric_limits.h>
#include <gtest/gtest.h>

TEST(numeric_limits, char_type_size) {
  EXPECT_EQ(sizeof(char), AE_CHAR_T_SIZE);
}

TEST(numeric_limits, short_type_size) {
  EXPECT_EQ(sizeof(short), AE_SHORT_T_SIZE);
}

TEST(numeric_limits, int_type_size) {
  EXPECT_EQ(sizeof(int), AE_INT_T_SIZE);
}

TEST(numeric_limits, long_type_size) {
  EXPECT_EQ(sizeof(long), AE_LONG_T_SIZE);
}

TEST(numeric_limits, llong_type_size) {
  EXPECT_EQ(sizeof(long long), AE_LLONG_T_SIZE);
}

TEST(numeric_limits, uchar_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned char>::min(), AE_UCHAR_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned char>::max(), AE_UCHAR_T_MAX);
}

TEST(numeric_limits, ushort_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned short>::min(), AE_USHORT_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned short>::max(), AE_USHORT_T_MAX);
}

TEST(numeric_limits, uint_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned int>::min(), AE_UINT_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned int>::max(), AE_UINT_T_MAX);
}

TEST(numeric_limits, ulong_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned long>::min(), AE_ULONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned long>::max(), AE_ULONG_T_MAX);
}

TEST(numeric_limits, ullong_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned long long>::min(), AE_ULLONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned long long>::max(), AE_ULLONG_T_MAX);
}

TEST(numeric_limits, schar_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed char>::min(), AE_SCHAR_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed char>::max(), AE_SCHAR_T_MAX);
}

TEST(numeric_limits, sshort_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed short>::min(), AE_SSHORT_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed short>::max(), AE_SSHORT_T_MAX);
}

TEST(numeric_limits, sint_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed int>::min(), AE_SINT_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed int>::max(), AE_SINT_T_MAX);
}

TEST(numeric_limits, slong_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed long>::min(), AE_SLONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed long>::max(), AE_SLONG_T_MAX);
}

TEST(numeric_limits, sllong_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed long long>::min(), AE_SLLONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed long long>::max(), AE_SLLONG_T_MAX);
}