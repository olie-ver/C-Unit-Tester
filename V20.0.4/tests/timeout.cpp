#include <testpp/testpp.hpp>
#include <chrono>
#include <thread>

TEST(timeout, fail) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
}