#include "CLI.hpp"
#include <iostream>

namespace tppCLI {
    std::filesystem::path GetTestPPDirectory() {
        #ifdef __APPLE__
            return std::filesystem::path(std::getenv("HOME")) / ".testpp";
        #elif define(__linux__)
            return std::filesystem::path(std::getenv("HOME")) / ".testpp";
        #elif define(_WIN32)
            return std::filesystem::path(std::getenv("USERPROFILE")) / ".testpp";
        #endif
    }
}