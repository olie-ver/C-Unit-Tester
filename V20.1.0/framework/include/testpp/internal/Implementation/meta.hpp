#pragma once

#ifndef META_H
#define META_H

#include "../Core.hpp"
#include "../Runner.hpp"
#include <functional>
#include <optional>
#include <string>

namespace internal {
    namespace impl_meta {
        inline std::optional<Core::FailureInfo>
        passes(const std::function<void()>& test, const char* testName, 
            const char* file, const uint32_t line)
        {
            Core::TestResult& current = Runner::TEST_STACK.back();
            size_t oldSize = current.failures.size();

            //needs to take into account for things that throw => the assertion tests
            try {
                test();
            } catch(...) {

            }

            //if the number of failures grew
            if (oldSize < current.failures.size()) {
                //Get the last failure
                Core::FailureInfo prev = current.failures.back();
                //Delete it
                current.failures.pop_back();
                //Return a new one
                return Core::FailureInfo(
                    std::string("Expected test: ") + testName 
                    + " to pass, but it failed with message:\n"
                    + prev.message,
                    file,
                    line
                );
            }

            //in the case that the other test passes, this passes, so we can return
            return std::nullopt;
        }

        inline std::optional<Core::FailureInfo>
        fails(const std::function<void()>& test, const char* testName, 
            const char* file, const uint32_t line)
        {
            Core::TestResult& current = Runner::TEST_STACK.back();
            size_t oldSize = current.failures.size();

            try {
                test();
            } catch(...) {

            }

            //if the number of failures didn't change
            if (oldSize == current.failures.size()) {
                std::string error = std::string("Expected test: ") + testName + " to fail, but it passed";
                //modify the old failure message to use this function's failure message
                return Core::FailureInfo(
                    error,
                    file,
                    line
                );
            } else { //the test failed => this one passed => erase its error message
                current.failures.pop_back();
                return std::nullopt;
            }
        }

        inline std::optional<Core::FailureInfo>
        failsWithMessage(const std::function<void()>& test, const char* testName, 
            const std::string msg, const char* file, const uint32_t line)
        {
            Core::TestResult& current = Runner::TEST_STACK.back();
            size_t oldSize = current.failures.size();

            try {
                test();
            } catch(...) {

            }

            //if the number of failures didn't change
            if (oldSize == current.failures.size()) {
                std::string error = std::string("Expected test: ") + testName + " to fail, but it passed";
                //modify the old failure message to use this function's failure message
                return Core::FailureInfo(
                    error,
                    file,
                    line
                );
            } else { //The test failed
                Core::FailureInfo last = current.failures.back();

                current.failures.pop_back();

                if (msg != last.message) { //failed with wrong message
                    return Core::FailureInfo(
                        "Expected test to fail with message: \n\t\"" 
                        + msg
                        + "\"\n    but it failed with message: \n\t\""
                        + last.message + "\"",
                        file,
                        line
                    );
                }

                return std::nullopt; //failed with correct message
            }
        }
    }
}

#endif