#include "CLI.hpp"
#include <iostream>

namespace tppCLI {
    std::filesystem::path GetTestPPDirectory() {
        #ifdef __APPLE__
            return std::filesystem::path(std::getenv("HOME")) / ".testpp";
        #elif defined(__linux__)
            return std::filesystem::path(std::getenv("HOME")) / ".testpp";
        #elif defined(_WIN32)
            return std::filesystem::path(std::getenv("USERPROFILE")) / ".testpp";
        #endif
    }
}