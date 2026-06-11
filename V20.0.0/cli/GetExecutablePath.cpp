#include "CLI.hpp"

#include <stdexcept>

#ifdef __APPLE__
    #include <mach-o/dyld.h>
    #include <limits.h>
#endif

#ifdef __linux__
    #include <unistd.h>
    #include <limits.h>
#endif

#ifdef _WIN32
    #include <windows.h>
#endif

std::filesystem::path GetExecutablePath() {
    #ifdef __APPLE__
        // _NSGetExecutablePath
         char buffer[PATH_MAX];
        uint32_t size = sizeof(buffer);

        if (_NSGetExecutablePath(buffer, &size) != 0) {
            throw std::runtime_error("Failed to determine executable path");
        }

        return std::filesystem::canonical(buffer);
    #elif defined(__linux__)
        // /proc/self/exe
        char buffer[PATH_MAX];

        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);

        if (len == -1) {
            throw std::runtime_error("Failed to determine executable path");
        }

        buffer[len] = '\0';

        return std::filesystem::canonical(buffer);
    #elif defined(_WIN32) 
        wchar_t buffer[MAX_PATH];

        DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);

        if (len == 0) {
            throw std::runtime_error("Failed to determine executable path");
        }

        return std::filesystem::path(buffer);
    #else
        #error Unsupported platform
    #endif
}