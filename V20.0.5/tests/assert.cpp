#include <testpp/testpp.hpp>
#include <testpp/internal/Core.hpp>
#include <testpp/internal/Runner.hpp>

TEST(intentionally_fail_assert, short_circuit_check) {
    //Create a temporary NON REGISTERED test
    internal::Core::Test temp;
    temp.suite_name = "intentionally_fail_assert";
    temp.test_name = "assert_short_circuit";
    temp.test = []() {
        ASSERT_TRUE(false); //this needs no proof 
        ASSERT_FALSE(true); //neither does this
    };

    //run it in our framework
    internal::Core::TestResult testResult = internal::Runner::runTest(temp);

    //check that we don't get 2 failures
    ASSERT_SIZE(testResult.failures, 1);
}
