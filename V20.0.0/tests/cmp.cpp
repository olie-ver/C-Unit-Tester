#include <testpp/testpp.hpp>
#include <vector>

/*
----------------------------------------------------------------
    EXPECT_EQ() TESTS
----------------------------------------------------------------
*/

TEST(comparison_torture, equality)
{
    // Basic truths
    ASSERT_PASSES(EXPECT_EQ(0, 0));
    ASSERT_PASSES(EXPECT_EQ(-1, -1));
    ASSERT_PASSES(EXPECT_EQ(42, 42));

    // Basic failures
    ASSERT_FAILS(EXPECT_EQ(0, 1));
    ASSERT_FAILS(EXPECT_EQ(-1, 1));

    // Boundary values
    ASSERT_PASSES(EXPECT_EQ(INT_MAX, INT_MAX));
    ASSERT_PASSES(EXPECT_EQ(INT_MIN, INT_MIN));
    ASSERT_FAILS(EXPECT_EQ(INT_MAX, INT_MIN));

    // Expressions
    ASSERT_PASSES(EXPECT_EQ(2 + 2, 4));
    ASSERT_PASSES(EXPECT_EQ(3 * 3, 9));
    ASSERT_FAILS(EXPECT_EQ(2 * 2, 5));

    // Floating-point precision traps
    ASSERT_FAILS(EXPECT_EQ(0.1 + 0.2, 0.3)); // classic
    ASSERT_PASSES(EXPECT_EQ(1.0, 1.0));

    // Signed vs unsigned (for now skip)
    // ASSERT_PASSES(EXPECT_EQ(-1, (unsigned int)-1));
}

/*
----------------------------------------------------------------
    EXPECT_NE() TESTS
----------------------------------------------------------------
*/

TEST(comparison_torture, inequality)
{
    // Basic truths
    ASSERT_PASSES(EXPECT_NE(0, 1));
    ASSERT_PASSES(EXPECT_NE(-1, 1));

    // Basic failures
    ASSERT_FAILS(EXPECT_NE(5, 5));
    ASSERT_FAILS(EXPECT_NE(-10, -10));

    // Boundary
    ASSERT_PASSES(EXPECT_NE(INT_MAX, INT_MIN));
    ASSERT_FAILS(EXPECT_NE(INT_MAX, INT_MAX));

    // Expressions
    ASSERT_PASSES(EXPECT_NE(2 + 2, 5));
    ASSERT_FAILS(EXPECT_NE(3 * 3, 9));

    // Floating-point weirdness
    ASSERT_PASSES(EXPECT_NE(0.1 + 0.2, 0.3));

    // Signed/unsigned (for now skip)
    // ASSERT_FAILS(EXPECT_NE(-1, (unsigned int)-1));
}

/*
----------------------------------------------------------------
    EXPECT_LT() TESTS
----------------------------------------------------------------
*/

TEST(comparison_torture, less_than)
{
    // Basic truths
    ASSERT_PASSES(EXPECT_LT(1, 2));
    ASSERT_PASSES(EXPECT_LT(-5, -1));

    // Basic failures
    ASSERT_FAILS(EXPECT_LT(2, 1));
    ASSERT_FAILS(EXPECT_LT(5, 5));

    // Boundaries
    ASSERT_PASSES(EXPECT_LT(INT_MIN, INT_MAX));
    ASSERT_FAILS(EXPECT_LT(INT_MAX, INT_MIN));

    // Expressions
    ASSERT_PASSES(EXPECT_LT(2 + 2, 5));
    ASSERT_FAILS(EXPECT_LT(3 * 3, 8));

    // Signed/unsigned trap (for now skip)
    // ASSERT_FAILS(EXPECT_LT(-1, 1u)); // promotion issue

    // Floating-point edge
    ASSERT_PASSES(EXPECT_LT(0.1 + 0.2, 0.3000001));
}

/*
----------------------------------------------------------------
    EXPECT_LE() TESTS
----------------------------------------------------------------
*/

TEST(comparison_torture, less_equal)
{
    // Basic truths
    ASSERT_PASSES(EXPECT_LE(1, 2));
    ASSERT_PASSES(EXPECT_LE(5, 5));

    // Failures
    ASSERT_FAILS(EXPECT_LE(3, 2));

    // Boundaries
    ASSERT_PASSES(EXPECT_LE(INT_MIN, INT_MIN));
    ASSERT_PASSES(EXPECT_LE(INT_MIN, INT_MAX));

    // Expressions
    ASSERT_PASSES(EXPECT_LE(2 + 2, 4));
    ASSERT_FAILS(EXPECT_LE(10, 9));

    // Floating precision
    ASSERT_FAILS(EXPECT_LE(0.1 + 0.2, 0.3));
}

/*
----------------------------------------------------------------
    EXPECT_GT() TESTS
----------------------------------------------------------------
*/

TEST(comparison_torture, greater_than)
{
    // Basic truths
    ASSERT_PASSES(EXPECT_GT(2, 1));
    ASSERT_PASSES(EXPECT_GT(-1, -5));

    // Failures
    ASSERT_FAILS(EXPECT_GT(1, 2));
    ASSERT_FAILS(EXPECT_GT(5, 5));

    // Boundaries
    ASSERT_PASSES(EXPECT_GT(INT_MAX, INT_MIN));
    ASSERT_FAILS(EXPECT_GT(INT_MIN, INT_MAX));

    // Expressions
    ASSERT_PASSES(EXPECT_GT(5 * 2, 9));
    ASSERT_FAILS(EXPECT_GT(3 + 3, 10));

    // Signed/unsigned (for now skip)
    // ASSERT_PASSES(EXPECT_GT((unsigned int)-1, 1));

    // Floating
    ASSERT_PASSES(EXPECT_GT(0.3000001, 0.1 + 0.2));
}

/*
----------------------------------------------------------------
    EXPECT_GE() TESTS
----------------------------------------------------------------
*/

TEST(comparison_torture, greater_equal)
{
    // Basic truths
    ASSERT_PASSES(EXPECT_GE(2, 1));
    ASSERT_PASSES(EXPECT_GE(5, 5));

    // Failures
    ASSERT_FAILS(EXPECT_GE(1, 2));

    // Boundaries
    ASSERT_PASSES(EXPECT_GE(INT_MAX, INT_MAX));
    ASSERT_PASSES(EXPECT_GE(INT_MAX, INT_MIN));

    // Expressions
    ASSERT_PASSES(EXPECT_GE(4 + 4, 8));
    ASSERT_FAILS(EXPECT_GE(3, 10));

    // Floating precision
    ASSERT_PASSES(EXPECT_GE(0.1 + 0.2, 0.3));
}