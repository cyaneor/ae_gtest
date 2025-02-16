#include <gtest/gtest.h>
#include <ae/str_raw.h>

TEST(ae_str_raw_len_to, returns_correct_index_for_null_terminator) {
    const ae_char_t *test_str = "Hello";
    ae_usize_t result = ae_str_raw_len_to(test_str, 6);
    EXPECT_EQ(result, 5);
}

TEST(ae_str_raw_len_to, returns_correct_index_for_null_terminator_mid_string) {
    const ae_char_t *test_str = "Hell\0o";
    ae_usize_t result = ae_str_raw_len_to(test_str, 6);
    EXPECT_EQ(result, 4);
}

TEST(ae_str_raw_len_to, handles_empty_string) {
    const ae_char_t *test_str = "";
    ae_usize_t result = ae_str_raw_len_to(test_str, 0);
    EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len_to, returns_full_length_if_no_null_terminator) {
    const ae_char_t *test_str = "Hello";
    ae_usize_t result = ae_str_raw_len_to(test_str, 6);
    EXPECT_EQ(result, 5);
}

TEST(ae_str_raw_len_to, handles_null_terminator_at_end) {
    const ae_char_t *test_str = "Test\0";
    ae_usize_t result = ae_str_raw_len_to(test_str, 5);
    EXPECT_EQ(result, 4);
}

TEST(ae_str_raw_len_to, returns_length_for_shorter_string) {
    const ae_char_t *test_str = "Short";
    ae_usize_t result = ae_str_raw_len_to(test_str, 3);
    EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len_to, correctly_handles_null_input) {
    const ae_char_t *test_str = nullptr;
    ae_usize_t result = ae_str_raw_len_to(test_str, 0);
    EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len_to, handles_single_character_string) {
    const ae_char_t *test_str = "A";
    ae_usize_t result = ae_str_raw_len_to(test_str, 1);
    EXPECT_EQ(result, 0);
}

TEST(ae_str_raw_len, normal) {
    const ae_char_t str[] = "Hello, world!";
    EXPECT_EQ(ae_str_raw_len(str), 13);
}

TEST(ae_str_raw_len, empty_string) {
    const ae_char_t str[] = "";
    EXPECT_EQ(ae_str_raw_len(str), 0);
}

TEST(ae_str_raw_len, null_pointer) {
    EXPECT_EQ(ae_str_raw_len(nullptr), 0);
}

TEST(ae_str_raw_len, single_character) {
    const ae_char_t str[] = "A";
    EXPECT_EQ(ae_str_raw_len(str), 1);
}

TEST(ae_str_raw_len, long_string) {
    const ae_char_t str[] =
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    EXPECT_EQ(ae_str_raw_len(str), 56);
}

