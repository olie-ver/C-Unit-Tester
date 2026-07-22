#include <testpp/testpp.hpp>
#include <string>

using namespace std;

// =========================
// Equality / Inequality
// =========================
TEST(String, Equality) {
    EXPECT_STR_EQ("hello", "hello");
    EXPECT_STR_EQ(string("abc"), string("abc"));

    EXPECT_STR_NE("hello", "world");
    EXPECT_STR_NE(string("abc"), string("def"));

    ASSERT_FAILS(EXPECT_STR_EQ("hello", "world"));
    ASSERT_FAILS(EXPECT_STR_NE("same", "same"));
}

// =========================
// Empty / Non-empty
// =========================
TEST(String, Emptiness) {
    EXPECT_STR_EMT("");
    EXPECT_STR_EMT(string("")); //weird

    EXPECT_STR_NEMT("a");
    EXPECT_STR_NEMT(string("not empty")); //weird

    ASSERT_FAILS(EXPECT_STR_EMT("not empty"));
    ASSERT_FAILS(EXPECT_STR_NEMT(""));
}

// =========================
// Contains
// =========================
TEST(String, Contains) {
    EXPECT_STR_CONTAINS("hello world", "world");
    EXPECT_STR_CONTAINS(string("abcdef"), string("cd"));

    // edge cases
    EXPECT_STR_CONTAINS("abc", "");   // empty substring
    EXPECT_STR_CONTAINS("", "");      // both empty

    ASSERT_FAILS(EXPECT_STR_CONTAINS("hello", "xyz"));
    ASSERT_FAILS(EXPECT_STR_CONTAINS("", "a"));
}

// =========================
// Starts With
// =========================
TEST(String, StartsWith) {
    EXPECT_STR_STARTS_WITH("hello world", "hello");
    EXPECT_STR_STARTS_WITH(string("abcdef"), string("abc"));

    // edge cases
    EXPECT_STR_STARTS_WITH("abc", "");
    EXPECT_STR_STARTS_WITH("", "");

    ASSERT_FAILS(EXPECT_STR_STARTS_WITH("hello", "world"));
    ASSERT_FAILS(EXPECT_STR_STARTS_WITH("", "a"));
}

// =========================
// Ends With
// =========================
TEST(String, EndsWith) {
    EXPECT_STR_ENDS_WITH("hello world", "world");
    EXPECT_STR_ENDS_WITH(string("abcdef"), string("def"));

    // edge cases
    EXPECT_STR_ENDS_WITH("abc", "");
    EXPECT_STR_ENDS_WITH("", "");

    ASSERT_FAILS(EXPECT_STR_ENDS_WITH("hello", "he"));
    ASSERT_FAILS(EXPECT_STR_ENDS_WITH("", "a"));
}