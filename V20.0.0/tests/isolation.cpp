#include <testpp/testpp.hpp>
#include <iostream>

// isolateRun([]{
//     *(int*)nullptr = 5;
// });

// isolateRun([]{
//     abort();
// });

// isolateRun([]{
//     while(true){}
// });


TEST(isolation, death) {
    // internal::impl_iso::death([]{*(int*)nullptr = 5;});
    // EXPECT_EQ(5, 2);
    EXPECT_STDOUT_CONTAINS([](){ std::cout << "Wazzup" << std::endl; }, "Wazzup ");
}