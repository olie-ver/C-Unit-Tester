#pragma once

#ifndef RUNNER_H
#define RUNNER_H

#include "Core.hpp"
#include <deque>
#include <map>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#define STR(x) #x

#define UNIQUE_NAME(base, line) base##_##line
#define MAKE_UNIQUE(base, line) UNIQUE_NAME(base, line)

#define TEST_IMPL(suite_name, test_name, line) \
    void suite_name##_##test_name(); \
    static bool MAKE_UNIQUE(register, line) = \
        internal::Runner::registerTest( \
            {STR(suite_name), STR(test_name), suite_name##_##test_name}); \
    void suite_name##_##test_name()

#define TEST(suite_name, test_name) \
    TEST_IMPL(suite_name, test_name, __LINE__)

#define D_TEST(test_name) \
    TEST(Default, test_name)

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief An internal Runner namespace that is used for running tests
    namespace Runner {
        /// @brief The result for the current test
        extern thread_local std::deque<Core::TestResult> TEST_STACK;

        /// @brief gets the global TestRun struct
        Core::TestRun& getTestRun();

        /// @brief The registry containing all the tests to be run
        std::vector<Core::Test>& getRegistry();

        /// @brief A set ensuring no duplicate tests are registered
        std::unordered_set<Core::Test, Core::TestHash>& getAllTests();

        /// @brief A set containing suites that should not be tested
        std::unordered_set<std::string>& getSkipSuites();

        /// @brief A set containing suites that ONLY should be tested
        std::unordered_set<std::string>& getTestOnly();

        /// @brief Checks if a suite should be skipped
        /// @param suite_name the suite name
        /// @return true if the suite should be skipped, false otherwise
        bool shouldSkip(const std::string& suite_name);

        /// @brief Adds a test to the registry under a test suite
        /// @param suite_name The name of the test suite the test is a part of 
        /// @param test The test
        bool registerTest(const Core::Test& test);

        /// @brief Runs all tests added to REGISTRY
        /// @param run The TestRun to put the results in
        void runAllRegisteredTests(Core::TestRun& run, const int num_threads, 
            const int timeout = 0, Core::TimeUnit unit = Core::TimeUnit::Seconds);

        /// @brief Runs the given test
        /// @param test The test to be run
        Core::TestResult runTest(const Core::Test& test);

        /// @brief A function that defines what each thread should do
        /// @param results the results that each thread is feeding into
        void threadWorker(std::vector<Core::TestResult>& results, Core::Test& running);

        /// @brief Creates a watchdog thread
        /// @return a thread
        std::thread createWatchdog(const int& time, const int& num_threads, 
            const std::atomic<bool>& finished, 
            const std::vector<Core::Test>& running, 
            const std::string& timeUnit,
            const std::chrono::steady_clock::time_point& start_time);
    }
}

#endif