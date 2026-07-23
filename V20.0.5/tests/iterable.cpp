#include <testpp/testpp.hpp>
#include "_dataStructs.hpp"
#include <vector>
#include <list>

TEST(IterableTest, OrderedEqPassesSameSequence) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2, 3};

    ASSERT_PASSES(EXPECT_ORDERED_EQ(a, b));
}

TEST(IterableTest, OrderedEqFailsDifferentOrder) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{3, 2, 1};

    ASSERT_FAILS(EXPECT_ORDERED_EQ(a, b));
}

TEST(IterableTest, OrderedEqFailsDifferentSize) {
    std::vector<int> a{1, 2};
    std::vector<int> b{1, 2, 3};

    ASSERT_FAILS(EXPECT_ORDERED_EQ(a, b));
}

TEST(IterableTest, OrderedNePassesWhenDifferent) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2, 4};

    ASSERT_PASSES(EXPECT_ORDERED_NE(a, b));
}

TEST(IterableTest, OrderedNeFailsWhenSame) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2, 3};

    ASSERT_FAILS(EXPECT_ORDERED_NE(a, b));
}

TEST(IterableTest, UnorderedEqPassesDifferentOrder) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{3, 1, 2};

    ASSERT_PASSES(EXPECT_UNORDERED_EQ(a, b)); //failing?
}

TEST(IterableTest, UnorderedEqFailsDifferentElements) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2, 4};

    ASSERT_FAILS(EXPECT_UNORDERED_EQ(a, b)); //passing?
}

TEST(IterableTest, UnorderedEqHandlesDuplicatesCorrectly) {
    std::vector<int> a{1, 1, 2};
    std::vector<int> b{1, 2, 2};

    ASSERT_FAILS(EXPECT_UNORDERED_EQ(a, b)); //passing?
}

TEST(IterableTest, EmptyPasses) {
    std::vector<int> a{};
    EXPECT_EMPTY(a);
}

TEST(IterableTest, EmptyFailsWhenNotEmpty) {
    std::vector<int> a{1};
    ASSERT_FAILS(EXPECT_EMPTY(a));
}

TEST(IterableTest, NEmptyPasses) {
    std::vector<int> a{1};
    EXPECT_NEMPTY(a);
}

TEST(IterableTest, NEmptyFailsWhenEmpty) {
    std::vector<int> a{};
    ASSERT_FAILS(EXPECT_NEMPTY(a));
}

TEST(IterableTest, SizePasses) {
    std::vector<int> a{1, 2, 3};
    EXPECT_SIZE(a, 3);
}

TEST(IterableTest, SizeFails) {
    std::vector<int> a{1, 2, 3};
    ASSERT_FAILS(EXPECT_SIZE(a, 2));
}

TEST(IterableTest, ContainsPasses) {
    std::vector<int> a{1, 2, 3};
    EXPECT_CONTAINS(a, 2);
}

TEST(IterableTest, ContainsFails) {
    std::vector<int> a{1, 2, 3};
    ASSERT_FAILS(EXPECT_CONTAINS(a, 4));
}

TEST(IterableTest, DoesNotContainPasses) {
    std::vector<int> a{1, 2, 3};
    EXPECT_DOES_NOT_CONTAIN(a, 4);
}

TEST(IterableTest, DoesNotContainFails) {
    std::vector<int> a{1, 2, 3};
    ASSERT_FAILS(EXPECT_DOES_NOT_CONTAIN(a, 2));
}

TEST(IterableTest, WorksAcrossContainerTypes) {
    std::vector<int> a{1, 2, 3};
    std::list<int> b{1, 2, 3};

    EXPECT_ORDERED_EQ(a, b);
}

TEST(IterableTest, UnorderedEqEmptyContainers) {
    std::vector<int> a{};
    std::vector<int> b{};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, UnorderedEqHashBasic) {
    std::vector<EqAndHash> a{{1}, {2}, {3}};
    std::vector<EqAndHash> b{{3}, {2}, {1}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, UnorderedEqHashDuplicateMismatch) {
    std::vector<EqAndHash> a{{1}, {1}, {2}};
    std::vector<EqAndHash> b{{1}, {2}, {2}};

    ASSERT_FAILS(EXPECT_UNORDERED_EQ(a, b));
}

TEST(IterableTorture, UnorderedEqHandlesHashCollisions) {
    std::vector<BadHash> a{{1}, {2}, {3}};
    std::vector<BadHash> b{{3}, {2}, {1}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, UnorderedEqSortPath) {
    std::vector<EqAndLess> a{{3}, {1}, {2}};
    std::vector<EqAndLess> b{{2}, {3}, {1}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, UnorderedEqSortDuplicateMismatch) {
    std::vector<EqAndLess> a{{1}, {1}, {2}};
    std::vector<EqAndLess> b{{1}, {2}, {2}};

    ASSERT_FAILS(EXPECT_UNORDERED_EQ(a, b));
}

TEST(IterableTorture, SortPathDifferentInitialOrder) {
    std::vector<EqAndLess> a{{5}, {4}, {3}, {2}, {1}};
    std::vector<EqAndLess> b{{1}, {2}, {3}, {4}, {5}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, UnorderedEqFallbackPath) {
    std::vector<OnlyEq> a{{1}, {2}, {3}};
    std::vector<OnlyEq> b{{3}, {2}, {1}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, FallbackDuplicateMismatch) {
    std::vector<OnlyEq> a{{1}, {1}, {2}};
    std::vector<OnlyEq> b{{1}, {2}, {2}};

    ASSERT_FAILS(EXPECT_UNORDERED_EQ(a, b));
}

TEST(IterableTorture, FallbackWorstCaseMatching) {
    std::vector<OnlyEq> a{{1}, {2}, {3}, {4}, {5}};
    std::vector<OnlyEq> b{{5}, {4}, {3}, {2}, {1}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, MixedContainerTypesHashPath) {
    std::vector<EqAndHash> a{{1}, {2}, {3}};
    std::list<EqAndHash> b{{3}, {2}, {1}};

    EXPECT_UNORDERED_EQ(a, b);
}

TEST(IterableTorture, UnorderedEqSizeMismatchEarlyExit) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2};

    ASSERT_FAILS(EXPECT_UNORDERED_EQ(a, b));
}

TEST(IterableTorture, ContainsWithDuplicates) {
    std::vector<int> a{1, 1, 1};

    EXPECT_CONTAINS(a, 1);
}

TEST(IterableTorture, DoesNotContainWithDuplicates) {
    std::vector<int> a{1, 1, 1};

    EXPECT_DOES_NOT_CONTAIN(a, 2);
}

TEST(IterableTorture, OrderedVsUnorderedDifference) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{3, 2, 1};

    EXPECT_UNORDERED_EQ(a, b);
    ASSERT_FAILS(EXPECT_ORDERED_EQ(a, b));
}

TEST(IterableTorture, DoesNotMutateInputs) {
    std::vector<int> a{3, 2, 1};
    std::vector<int> b{1, 2, 3};

    EXPECT_UNORDERED_EQ(a, b);

    std::vector<int> c{3, 2, 1};

    // Ensure original order preserved
    EXPECT_ORDERED_EQ(a, c);
}

TEST(IterableTorture, AllElementsSame) {
    std::vector<int> a(100, 42);
    std::vector<int> b(100, 42);

    EXPECT_UNORDERED_EQ(a, b);
}