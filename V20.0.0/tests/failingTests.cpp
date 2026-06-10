#include <testpp/testpp.hpp>

D_TEST(fail1) {
    EXPECT_FALSE(true);
    EXPECT_FALSE(1);
    EXPECT_TRUE(false);
    ASSERT_FAILS(EXPECT_TRUE(true));
}

D_TEST(fail2) {
    EXPECT_FALSE(true);
    EXPECT_FALSE(1);
    EXPECT_TRUE(false);
    ASSERT_FAILS(EXPECT_TRUE(true));
}

D_TEST(fail3) {
    EXPECT_FALSE(true);
    EXPECT_FALSE(1);
    EXPECT_TRUE(false);
    ASSERT_FAILS(EXPECT_TRUE(true));
}

D_TEST(fail4) {
    EXPECT_FALSE(true);
    EXPECT_FALSE(1);
    EXPECT_TRUE(false);
    ASSERT_FAILS(EXPECT_TRUE(true));
}

D_TEST(fail5) {
    ASSERT_FALSE(true);
    ASSERT_FALSE(1);
    ASSERT_TRUE(false);
    EXPECT_FAILS(ASSERT_TRUE(true));
}