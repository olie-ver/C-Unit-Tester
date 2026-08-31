#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <list>
#include <array>

//
// ✅ SET EQUALITY
//

TEST(set, SetEq_Passes_Vector) {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {3, 2, 1};

    EXPECT_SET_EQ(a, b);
}

TEST(set, SetEq_Fails_Vector) {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 4};

    ASSERT_FAILS(EXPECT_SET_EQ(a, b));
}

TEST(set, SetNe_Passes) {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 4};

    EXPECT_SET_NE(a, b);
}

TEST(set, SetNe_Fails) {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {3, 2, 1};

    ASSERT_FAILS(EXPECT_SET_NE(a, b));
}

//
// ✅ SUBSET / SUPERSET
//

TEST(set, Subset_Passes_Vector) {
    std::vector<int> a = {1, 2};
    std::vector<int> b = {1, 2, 3};

    EXPECT_SUBSET(a, b);
}

TEST(set, Subset_Fails_Vector) {
    std::vector<int> a = {1, 4};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(EXPECT_SUBSET(a, b));
}

TEST(set, Superset_Passes_Vector) {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2};

    EXPECT_SUPERSET(a, b);
}

TEST(set, Superset_Fails_Vector) {
    std::vector<int> a = {1, 2};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(EXPECT_SUPERSET(a, b));
}

//
// ✅ STRICT SUBSET
//

TEST(set, StrictSubset_Passes) {
    std::vector<int> a = {1, 2};
    std::vector<int> b = {1, 2, 3};

    EXPECT_STRICT_SUBSET(a, b);
}

TEST(set, StrictSubset_Fails_Equal) {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {3, 2, 1};

    ASSERT_FAILS(EXPECT_STRICT_SUBSET(a, b));
}

TEST(set, StrictSubset_Fails_NotSubset) {
    std::vector<int> a = {1, 4};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(EXPECT_STRICT_SUBSET(a, b));
}

//
// 🔁 ORDERED CONTAINERS (std::set)
//

TEST(set, Works_With_StdSet) {
    std::set<int> a = {1, 2, 3};
    std::set<int> b = {3, 2, 1};

    EXPECT_SET_EQ(a, b);
}

TEST(set, Subset_With_StdSet) {
    std::set<int> a = {1, 2};
    std::set<int> b = {1, 2, 3};

    EXPECT_SUBSET(a, b);
}

//
// 🔁 LIST (non-random access)
//

TEST(set, Works_With_List) {
    std::list<int> a = {1, 2, 3};
    std::list<int> b = {3, 1, 2};

    EXPECT_SET_EQ(a, b);
}

//
// 🔁 ARRAY SUPPORT
//

TEST(set, Works_With_Array) {
    int a[] = {1, 2, 3};
    int b[] = {3, 2, 1};

    EXPECT_SET_EQ(a, b);
}

TEST(set, Subset_Array) {
    int a[] = {1, 2};
    int b[] = {1, 2, 3};

    EXPECT_SUBSET(a, b);
}

//
// ⚠️ DUPLICATE EDGE CASES
//

TEST(set, Duplicates_Ignored_For_SetEq) {
    std::vector<int> a = {1, 1, 2, 3};
    std::vector<int> b = {1, 2, 3};

    EXPECT_SET_EQ(a, b);
}

TEST(set, Duplicates_DoNotBreakSubset) {
    std::vector<int> a = {1, 1, 2};
    std::vector<int> b = {1, 2, 3};

    EXPECT_SUBSET(a, b);
}

//
// 🧪 EMPTY CASES
//

TEST(set, Empty_Subset) {
    std::vector<int> a = {};
    std::vector<int> b = {1, 2, 3};

    EXPECT_SUBSET(a, b);
}

TEST(set, Empty_StrictSubset_Fails) {
    std::vector<int> a = {};
    std::vector<int> b = {};

    ASSERT_FAILS(EXPECT_STRICT_SUBSET(a, b));
}

TEST(set, Empty_SetEq) {
    std::vector<int> a = {};
    std::vector<int> b = {};

    EXPECT_SET_EQ(a, b);
}

TEST(set, Large_Unordered_Input) {
    std::vector<int> a = {5,4,3,2,1};
    std::vector<int> b = {1,2,3,4,5};

    EXPECT_SET_EQ(a, b);
}