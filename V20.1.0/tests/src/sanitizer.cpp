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

TEST(asan, HeapOverflow) {
    int* arr = new int[4];
    arr[100] = 1;
    delete[] arr;
}