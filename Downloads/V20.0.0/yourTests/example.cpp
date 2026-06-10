#include <testpp/testpp.hpp>

D_TEST(example) {
    EXPECT_TRUE(true);
}

TEST(another_example, another_example) {
    int a = 5;
    int b = 10;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    EXPECT_EQ(a, 10);
}