#include <testpp/testpp.hpp>

TEST(FloatBasic, AbsoluteEquality)
{
    ASSERT_PASSES(EXPECT_ABS_NEAR(1.0, 1.0, 0.0));
    ASSERT_PASSES(EXPECT_ABS_NEAR(1.0, 1.0001, 0.001));

    ASSERT_FAILS(EXPECT_ABS_NEAR(1.0, 1.1, 0.01));
}

TEST(FloatBasic, RelativeEquality)
{
    ASSERT_PASSES(EXPECT_REL_NEAR(100.0, 101.0, 0.02));
    ASSERT_PASSES(EXPECT_REL_NEAR(0.5, 0.51, 0.05));

    ASSERT_FAILS(EXPECT_REL_NEAR(100.0, 110.0, 0.05));
}

TEST(FloatBasic, CombinedNear)
{
    ASSERT_PASSES(EXPECT_NEAR(1.0, 1.00001, 0.0001, 0.0001));
    ASSERT_PASSES(EXPECT_NEAR(1000.0, 1001.0, 0.1, 0.01));

    ASSERT_FAILS(EXPECT_NEAR(1.0, 1.1, 0.0001, 0.0001));
}

TEST(FloatTorture, PrecisionIssues)
{
    ASSERT_PASSES(EXPECT_NEAR(0.1 + 0.2, 0.3, 1e-9, 1e-9));

    ASSERT_FAILS(EXPECT_ABS_NEAR(0.1 + 0.2, 0.3, 0.0)); // classic failure

    ASSERT_PASSES(EXPECT_NEAR(0.1 * 3, 0.3, 1e-9, 1e-9));
}

TEST(FloatTorture, MagnitudeDifferences)
{
    ASSERT_PASSES(EXPECT_REL_NEAR(1e9, 1e9 + 1e6, 0.01));
    ASSERT_FAILS(EXPECT_ABS_NEAR(1e9, 1e9 + 1e6, 1.0));

    ASSERT_PASSES(EXPECT_ABS_NEAR(1e-9, 2e-9, 1e-9));
    ASSERT_FAILS(EXPECT_REL_NEAR(1e-9, 2e-9, 0.1));
}

TEST(FloatTorture, ZeroHandling)
{
    ASSERT_PASSES(EXPECT_ABS_NEAR(0.0, -0.0, 0.0));

    ASSERT_PASSES(EXPECT_NEAR(0.0, 1e-10, 1e-9, 1.0));
    ASSERT_FAILS(EXPECT_REL_NEAR(0.0, 1e-5, 0.01)); // relative near zero is tricky
}

TEST(FloatTorture, NaNChecks)
{
    double nan = std::numeric_limits<double>::quiet_NaN();

    ASSERT_PASSES(EXPECT_NAN(nan));
    ASSERT_FAILS(EXPECT_NOT_NAN(nan));

    ASSERT_FAILS(EXPECT_ABS_NEAR(nan, nan, 1.0)); // NaN != NaN
}

TEST(FloatTorture, InfinityChecks)
{
    double inf = std::numeric_limits<double>::infinity();
    double neg_inf = -std::numeric_limits<double>::infinity();

    ASSERT_PASSES(EXPECT_INF(inf));
    ASSERT_PASSES(EXPECT_POS_INF(inf));
    ASSERT_PASSES(EXPECT_NEG_INF(neg_inf));

    ASSERT_FAILS(EXPECT_POS_INF(neg_inf));
    ASSERT_FAILS(EXPECT_NEG_INF(inf));
}

TEST(FloatTorture, MixedFloatTypes)
{
    float a = 1.0f;
    double b = 1.0;

    ASSERT_PASSES(EXPECT_ABS_NEAR(a, b, 0.0));

    ASSERT_PASSES(EXPECT_NEAR(a, b + 1e-7, 1e-6, 1e-6));
    ASSERT_FAILS(EXPECT_ABS_NEAR(a, b + 1e-3, 1e-6));
}

TEST(FloatTorture, Cancellation)
{
    double a = 1e16;
    double b = a + 1;
    double c = a + 2;

    ASSERT_PASSES(EXPECT_ABS_NEAR(a, b, 0.0)); 
    ASSERT_PASSES(EXPECT_ABS_NEAR(a, b, 1.0));
    
    ASSERT_FAILS(EXPECT_ABS_NEAR(a, c, 0.0));
    ASSERT_PASSES(EXPECT_ABS_NEAR(a, c, 2.0));

    ASSERT_PASSES(EXPECT_REL_NEAR(a, b, 1e-15));
}

TEST(FloatTorture, Symmetry)
{
    ASSERT_PASSES(EXPECT_NEAR(1.0, 1.00001, 1e-4, 1e-4));
    ASSERT_PASSES(EXPECT_NEAR(1.00001, 1.0, 1e-4, 1e-4));
}

TEST(FloatTorture, NonTransitive)
{
    double a = 1.0;
    double b = 1.00009;
    double c = 1.00018;

    ASSERT_PASSES(EXPECT_NEAR(a, b, 1e-4, 1e-4));
    ASSERT_PASSES(EXPECT_NEAR(b, c, 1e-4, 1e-4));

    // This may fail depending on implementation — that's OK and informative
    ASSERT_FAILS(EXPECT_NEAR(a, c, 1e-4, 1e-4));
}