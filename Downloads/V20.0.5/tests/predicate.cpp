#include <testpp/testpp.hpp>
#include <vector>
#include <array>

TEST(predicate, AllOf_Passes_Vector) {
    std::vector<int> v = {2, 4, 6, 8};

    EXPECT_ALL(v, [](int x) {
        return x % 2 == 0;
    });
}

TEST(predicate, AllOf_Fails_Vector) {
    std::vector<int> v = {2, 3, 6};

    ASSERT_FAILS(EXPECT_ALL(v, [](int x) {
        return x % 2 == 0;
    }));
}

TEST(predicate, AnyOf_Passes_Vector) {
    std::vector<int> v = {1, 3, 4};

    EXPECT_SOME(v, [](int x) {
        return x % 2 == 0;
    });
}

TEST(predicate, AnyOf_Fails_Vector) {
    std::vector<int> v = {1, 3, 5};

    ASSERT_FAILS(EXPECT_SOME(v, [](int x) {
        return x % 2 == 0;
    }));
}

TEST(predicate, NoneOf_Passes_Vector) {
    std::vector<int> v = {1, 3, 5};

    EXPECT_NONE(v, [](int x) {
        return x % 2 == 0;
    });
}

TEST(predicate, NoneOf_Fails_Vector) {
    std::vector<int> v = {1, 2, 3};

    ASSERT_FAILS(EXPECT_NONE(v, [](int x) {
        return x % 2 == 0;
    }));
}

TEST(predicate, AllOf_Array) {
    int arr[] = {10, 20, 30};

    EXPECT_ALL(arr, [](int x) {
        return x > 0;
    });
}

TEST(predicate, AnyOf_Array) {
    int arr[] = {-1, -2, 5};

    EXPECT_SOME(arr, [](int x) {
        return x > 0;
    });
}

TEST(predicate, NoneOf_Array) {
    int arr[] = {-1, -2, -3};

    EXPECT_NONE(arr, [](int x) {
        return x > 0;
    });
}

TEST(predicate, Empty_AllOf) {
    std::vector<int> v;

    EXPECT_ALL(v, [](int) { return false; });
    // Should PASS (vacuously true)
}

TEST(predicate, Empty_AnyOf) {
    std::vector<int> v;

    ASSERT_FAILS(EXPECT_SOME(v, [](int) { return true; }));
    // Should FAIL
}

TEST(predicate, Empty_NoneOf) {
    std::vector<int> v;

    EXPECT_NONE(v, [](int) { return true; });
    // Should PASS
}

TEST(predicate, SingleElement_AllOf) {
    std::vector<int> v = {2};

    EXPECT_ALL(v, [](int x) { return x == 2; });
}

TEST(predicate, SingleElement_NoneOf) {
    std::vector<int> v = {2};

    EXPECT_NONE(v, [](int x) { return x == 3; });
}

TEST(predicate, StopsEarly_AllOf) {
    std::vector<int> v = {2, 4, 6, 7, 8};

    ASSERT_FAILS(EXPECT_ALL(v, [](int x) {
        return x % 2 == 0;
    }));
}

TEST(predicate, LambdaCapture) {
    int threshold = 5;
    std::vector<int> v = {6, 7, 8};

    EXPECT_ALL(v, [threshold](int x) {
        return x > threshold;
    });
}