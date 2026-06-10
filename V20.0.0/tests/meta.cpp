#include <testpp/testpp.hpp>
#include <set>

TEST(Meta, ExpectPassesBasic) {
    EXPECT_PASSES(EXPECT_TRUE(true));
    EXPECT_PASSES(EXPECT_EQ(1, 1));
    EXPECT_PASSES(EXPECT_FALSE(false));
}

TEST(Meta, ExpectPassesFailsWhenInnerFails) {
    ASSERT_FAILS(EXPECT_PASSES(EXPECT_TRUE(false)));
    ASSERT_FAILS(EXPECT_PASSES(EXPECT_EQ(1, 2)));
}

TEST(Meta, ExpectFailsBasic) {
    EXPECT_FAILS(EXPECT_TRUE(false));
    EXPECT_FAILS(EXPECT_EQ(1, 2));
}

TEST(Meta, ExpectFailsFailsWhenInnerPasses) {
    ASSERT_FAILS(EXPECT_FAILS(EXPECT_TRUE(true)));
    ASSERT_FAILS(EXPECT_FAILS(EXPECT_EQ(1, 1)));
}

TEST(Meta, NestedPasses) {
    EXPECT_PASSES(EXPECT_PASSES(EXPECT_TRUE(true)));
    EXPECT_FAILS(EXPECT_FAILS(EXPECT_TRUE(true)));
}

TEST(Meta, NestedFailures) {
    ASSERT_FAILS(
        EXPECT_PASSES(EXPECT_FAILS(EXPECT_TRUE(true)))
    );

    ASSERT_FAILS(
        EXPECT_FAILS(EXPECT_PASSES(EXPECT_TRUE(true)))
    );
}

TEST(Meta, TripleNesting) {
    EXPECT_PASSES(
        EXPECT_PASSES(
            EXPECT_PASSES(EXPECT_TRUE(true))
        )
    );

    EXPECT_FAILS(
        EXPECT_PASSES(
            EXPECT_FAILS(EXPECT_TRUE(true))
        )
    );
}

TEST(Meta, ComparisonAssertions) {
    EXPECT_PASSES(EXPECT_LT(1, 2));
    EXPECT_FAILS(EXPECT_LT(2, 1));

    EXPECT_PASSES(EXPECT_GT(2, 1));
    EXPECT_FAILS(EXPECT_GT(1, 2));

    EXPECT_PASSES(EXPECT_GE(2, 2));
    EXPECT_FAILS(EXPECT_GE(1, 2));
}

TEST(Meta, FloatAssertions) {
    EXPECT_PASSES(EXPECT_ABS_NEAR(1.0, 1.001, 0.01));
    EXPECT_FAILS(EXPECT_ABS_NEAR(1.0, 1.1, 0.01));

    EXPECT_PASSES(EXPECT_REL_NEAR(100.0, 101.0, 0.02));
    EXPECT_FAILS(EXPECT_REL_NEAR(100.0, 110.0, 0.02));
}

TEST(Meta, NanInfAssertions) {
    EXPECT_PASSES(EXPECT_NAN(std::nan("")));
    EXPECT_FAILS(EXPECT_NAN(1.0));

    EXPECT_PASSES(EXPECT_NOT_NAN(1.0));
    EXPECT_FAILS(EXPECT_NOT_NAN(std::nan("")));

    EXPECT_PASSES(EXPECT_INF(std::numeric_limits<double>::infinity()));
    EXPECT_FAILS(EXPECT_INF(1.0));

    EXPECT_PASSES(EXPECT_POS_INF(std::numeric_limits<double>::infinity()));
    EXPECT_FAILS(EXPECT_POS_INF(-std::numeric_limits<double>::infinity()));

    EXPECT_PASSES(EXPECT_NEG_INF(-std::numeric_limits<double>::infinity()));
    EXPECT_FAILS(EXPECT_NEG_INF(std::numeric_limits<double>::infinity()));
}

TEST(Meta, ContainerAssertions) {
    std::vector<int> a{1,2,3};
    std::vector<int> b{1,2,3};
    std::vector<int> c{3,2,1};

    EXPECT_PASSES(EXPECT_ORDERED_EQ(a, b));
    EXPECT_FAILS(EXPECT_ORDERED_EQ(a, c));

    EXPECT_PASSES(EXPECT_UNORDERED_EQ(a, c));

    std::vector<int> d{1,2};
    EXPECT_FAILS(EXPECT_UNORDERED_EQ(a, d));

    EXPECT_PASSES(EXPECT_EMPTY(std::vector<int>{}));
    EXPECT_FAILS(EXPECT_EMPTY(a));

    EXPECT_PASSES(EXPECT_NEMPTY(a));
    EXPECT_FAILS(EXPECT_NEMPTY(std::vector<int>{}));

    EXPECT_PASSES(EXPECT_SIZE(a, 3));
    EXPECT_FAILS(EXPECT_SIZE(a, 2));
}

TEST(Meta, ContainsAssertions) {
    std::vector<int> v{1,2,3};

    EXPECT_PASSES(EXPECT_CONTAINS(v, 2));
    EXPECT_FAILS(EXPECT_CONTAINS(v, 5));

    EXPECT_PASSES(EXPECT_DOES_NOT_CONTAIN(v, 5));
    EXPECT_FAILS(EXPECT_DOES_NOT_CONTAIN(v, 2));

    EXPECT_PASSES(EXPECT_ALL(v, [](int x){ return x > 0; }));
    EXPECT_FAILS(EXPECT_ALL(v, [](int x){ return x > 2; }));

    EXPECT_PASSES(EXPECT_NONE(v, [](int x){ return x < 0; }));
    EXPECT_FAILS(EXPECT_NONE(v, [](int x){ return x == 2; }));
}

TEST(Meta, SetAssertions) {
    std::set<int> a{1,2,3};
    std::set<int> b{1,2,3};
    std::set<int> c{1,2};

    EXPECT_PASSES(EXPECT_SET_EQ(a, b));
    EXPECT_FAILS(EXPECT_SET_EQ(a, c));

    EXPECT_PASSES(EXPECT_SUBSET(c, a));
    EXPECT_FAILS(EXPECT_SUBSET(a, c));

    EXPECT_PASSES(EXPECT_SUPERSET(a, c));
    EXPECT_FAILS(EXPECT_SUPERSET(c, a));

    EXPECT_PASSES(EXPECT_STRICT_SUBSET(c, a));
    ASSERT_FAILS(EXPECT_STRICT_SUBSET(a, a));
}

TEST(Meta, StringAssertions) {
    std::string s = "hello";

    EXPECT_PASSES(EXPECT_STR_EQ(s, "hello"));
    EXPECT_FAILS(EXPECT_STR_EQ(s, "world"));

    EXPECT_PASSES(EXPECT_STR_NE(s, "world"));
    EXPECT_FAILS(EXPECT_STR_NE(s, "hello"));

    EXPECT_PASSES(EXPECT_STR_EMT(""));
    EXPECT_FAILS(EXPECT_STR_EMT(s));

    EXPECT_PASSES(EXPECT_STR_NEMT(s));
    EXPECT_FAILS(EXPECT_STR_NEMT(""));

    EXPECT_PASSES(EXPECT_STR_CONTAINS(s, "ell"));
    EXPECT_FAILS(EXPECT_STR_CONTAINS(s, "xyz"));

    EXPECT_PASSES(EXPECT_STR_STARTS_WITH(s, "he"));
    EXPECT_FAILS(EXPECT_STR_STARTS_WITH(s, "el"));

    EXPECT_PASSES(EXPECT_STR_ENDS_WITH(s, "lo"));
    EXPECT_FAILS(EXPECT_STR_ENDS_WITH(s, "he"));
}

TEST(Meta, PointerAssertions) {
    int x = 5;
    int* p = &x;
    int* n = nullptr;

    EXPECT_PASSES(EXPECT_NOT_NULL(p));
    EXPECT_FAILS(EXPECT_NOT_NULL(n));

    EXPECT_PASSES(EXPECT_NULL(n));
    EXPECT_FAILS(EXPECT_NULL(p));
}

TEST(Meta, ThrowAssertions) {
    EXPECT_PASSES(EXPECT_THROWS(throw std::runtime_error("err")));
    EXPECT_FAILS(EXPECT_THROWS([](){}()));

    EXPECT_PASSES(EXPECT_DOES_NOT_THROW([](){}()));
    EXPECT_FAILS(EXPECT_DOES_NOT_THROW(throw std::runtime_error("err")));

    EXPECT_PASSES(EXPECT_THROWS_MSG(
        throw std::runtime_error("hello"), "hello"));

    EXPECT_FAILS(EXPECT_THROWS_MSG(
        throw std::runtime_error("actual"), "expected"));
}

TEST(Meta, MetaRecursion) {
    EXPECT_PASSES(EXPECT_PASSES(EXPECT_TRUE(true)));
    EXPECT_PASSES(EXPECT_FAILS(EXPECT_TRUE(false)));
}

TEST(Meta, MetaRecursionFailures) {
    ASSERT_FAILS(
        EXPECT_PASSES(EXPECT_FAILS(EXPECT_TRUE(true)))
    );

    ASSERT_FAILS(
        EXPECT_FAILS(EXPECT_PASSES(EXPECT_TRUE(true)))
    );
}