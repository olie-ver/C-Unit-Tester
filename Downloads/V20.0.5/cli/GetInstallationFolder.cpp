#include "CLI.hpp"
#include <iostream>

#ifdef __APPLE__
    #include <mach-o/dyld.h>
#endif

namespace tppCLI {
    std::filesystem::path GetInstallPrefix() {
        #ifdef __APPLE__
            uint32_t size = 0;
            _NSGetExecutablePath(nullptr, &size);

            std::string buffer(size, '\0');
            _NSGetExecutablePath(buffer.data(), &size);

            auto exePath = std::filesystem::canonical(std::filesystem::path(buffer.c_str()));

            return exePath.parent_path().parent_path();
        #elif defined(__linux__)
            std::filesystem::path exe = std::filesystem::canonical("/proc/self/exe");
            return exe.parent_path().parent_path();
        #elif defined(_WIN32) || defined(_WIN64)
            return std::filesystem::path(std::getenv("USERPROFILE")) / ".testpp";
        #endif
    }

    std::filesystem::path GetWorkingDirectory() {
        #ifdef _WIN32
            const char* home = std::getenv("USERPROFILE");
        #else
            const char* home = std::getenv("HOME");
        #endif

        if (!home) {
            throw std::runtime_error("Unable to determine home directory");
        }

        return std::filesystem::path(home) / ".testpp";
    }
}