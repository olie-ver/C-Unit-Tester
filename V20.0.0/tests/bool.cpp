#include <testpp/testpp.hpp>

// --- Literal sanity but enforced through wrapper ---
TEST(boolean_torture, literal_true_passes)
{
    ASSERT_PASSES(EXPECT_TRUE(true));
}

TEST(boolean_torture, literal_false_fails)
{
    ASSERT_FAILS(EXPECT_TRUE(false));
}

TEST(boolean_torture, false_passes_expect_false)
{
    ASSERT_PASSES(EXPECT_FALSE(false));
}

TEST(boolean_torture, true_fails_expect_false)
{
    ASSERT_FAILS(EXPECT_FALSE(true));
}

// --- Double negation traps ---
TEST(boolean_torture, double_negation_true)
{
    ASSERT_PASSES(EXPECT_TRUE(!!true));
}

TEST(boolean_torture, double_negation_false)
{
    ASSERT_PASSES(EXPECT_FALSE(!!false));
}

TEST(boolean_torture, negated_true_fails)
{
    ASSERT_FAILS(EXPECT_TRUE(!true));
}

TEST(boolean_torture, negated_false_fails_false_check)
{
    ASSERT_FAILS(EXPECT_FALSE(!false));
}

// --- Integer conversions ---
TEST(boolean_torture, zero_is_false)
{
    ASSERT_PASSES(EXPECT_FALSE(0));
}

TEST(boolean_torture, nonzero_is_true)
{
    ASSERT_PASSES(EXPECT_TRUE(42));
}

TEST(boolean_torture, negative_is_true)
{
    ASSERT_PASSES(EXPECT_TRUE(-1));
}

TEST(boolean_torture, zero_fails_true)
{
    ASSERT_FAILS(EXPECT_TRUE(0));
}

TEST(boolean_torture, nonzero_fails_false)
{
    ASSERT_FAILS(EXPECT_FALSE(7));
}

// --- Pointer semantics ---
TEST(boolean_torture, null_pointer_false)
{
    int* ptr = nullptr;
    ASSERT_PASSES(EXPECT_FALSE(ptr));
}

TEST(boolean_torture, nonnull_pointer_true)
{
    int value = 5;
    int* ptr = &value;
    ASSERT_PASSES(EXPECT_TRUE(ptr));
}

TEST(boolean_torture, null_pointer_fails_true)
{
    int* ptr = nullptr;
    ASSERT_FAILS(EXPECT_TRUE(ptr));
}

// --- Boolean expressions ---
TEST(boolean_torture, and_expression_true)
{
    ASSERT_PASSES(EXPECT_TRUE(true && true));
}

TEST(boolean_torture, and_expression_false)
{
    ASSERT_PASSES(EXPECT_FALSE(true && false));
}

TEST(boolean_torture, or_expression_true)
{
    ASSERT_PASSES(EXPECT_TRUE(false || true));
}

TEST(boolean_torture, or_expression_false)
{
    ASSERT_PASSES(EXPECT_FALSE(false || false));
}

// --- Mixed operator precedence ---
TEST(boolean_torture, precedence_without_parentheses)
{
    ASSERT_PASSES(EXPECT_TRUE(true || false && false)); // true || (false && false)
}

TEST(boolean_torture, precedence_with_parentheses)
{
    ASSERT_PASSES(EXPECT_FALSE((true || false) && false));
}

// --- Comparison results feeding booleans ---
TEST(boolean_torture, comparison_true)
{
    ASSERT_PASSES(EXPECT_TRUE(5 > 3));
}

TEST(boolean_torture, comparison_false)
{
    ASSERT_PASSES(EXPECT_FALSE(3 > 5));
}

TEST(boolean_torture, equality_true)
{
    ASSERT_PASSES(EXPECT_TRUE(4 == 4));
}

TEST(boolean_torture, inequality_false)
{
    ASSERT_PASSES(EXPECT_FALSE(4 != 4));
}

// --- Ternary operator weirdness ---
TEST(boolean_torture, ternary_true_branch)
{
    ASSERT_PASSES(EXPECT_TRUE(true ? true : false));
}

TEST(boolean_torture, ternary_false_branch)
{
    ASSERT_PASSES(EXPECT_FALSE(false ? true : false));
}

// --- Chained logical madness ---
TEST(boolean_torture, chained_logic_true)
{
    ASSERT_PASSES(EXPECT_TRUE((true && true) || (false && true)));
}

TEST(boolean_torture, chained_logic_false)
{
    ASSERT_PASSES(EXPECT_FALSE((false && true) || (false && false)));
}

// --- Intentional failure edge cases ---
TEST(boolean_torture, true_expression_expected_false)
{
    ASSERT_FAILS(EXPECT_FALSE(true && true));
}

TEST(boolean_torture, false_expression_expected_true)
{
    ASSERT_FAILS(EXPECT_TRUE(false || false));
}

// --- Bool variables (non-literal paths) ---
TEST(boolean_torture, bool_variable_true)
{
    bool b = true;
    ASSERT_PASSES(EXPECT_TRUE(b));
}

TEST(boolean_torture, bool_variable_false)
{
    bool b = false;
    ASSERT_PASSES(EXPECT_FALSE(b));
}

TEST(boolean_torture, bool_variable_mutation)
{
    bool b = false;
    b = !b;
    ASSERT_PASSES(EXPECT_TRUE(b));
}

// --- Extremely subtle: assignment vs evaluation ---
TEST(boolean_torture, assignment_inside_expression)
{
    bool b = false;
    ASSERT_PASSES(EXPECT_TRUE(b = true)); // assignment returns true
}

TEST(boolean_torture, assignment_returns_false)
{
    bool b = true;
    ASSERT_PASSES(EXPECT_FALSE(b = false)); // assignment returns false
}