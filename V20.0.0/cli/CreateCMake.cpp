#include "CLI.hpp"
#include <fstream>

namespace tppCLI {
    bool GenerateProject(std::vector<std::filesystem::path> files)
    {
        auto installRoot = GetTestPPDirectory();
        std::filesystem::create_directories(installRoot);

        std::filesystem::path cmakePath = installRoot / "CMakeLists.txt";
        std::string cmakePathStr = cmakePath.string(); 

        std::ofstream cmake(cmakePath);

        if (!cmake) {
            return false;
        }

        cmake << "cmake_minimum_required(VERSION 3.20)\n";
        cmake << "project(testpp_generated)\n\n";

        cmake << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)\n\n";

        cmake << "list(PREPEND CMAKE_PREFIX_PATH \"" << installRoot.string() << "\")\n";

        cmake << "find_package(testpp REQUIRED)\n\n";

        //debug
        cmake << "get_target_property(\n";
        cmake << "    TESTPP_INCLUDES\n";
        cmake << "    testpp::testpp\n";
        cmake << "    INTERFACE_INCLUDE_DIRECTORIES\n";
        cmake << ")\n";

        cmake << "message(STATUS \"testpp includes = ${TESTPP_INCLUDES}\")\n";

        cmake << "get_target_property(\n";
        cmake << "    TESTPP_MAIN_INCLUDES\n";
        cmake << "    testpp::testpp_main\n";
        cmake << "    INTERFACE_INCLUDE_DIRECTORIES\n";
        cmake << ")\n";

        cmake << "message (STATUS \"testpp_main includes = ${TESTPP_MAIN_INCLUDES}\")\n";
        //end of debug

        cmake << "add_executable(testpp_generated\n";

        for (const auto& file : files) {
            cmake << "    \"" << file.string() << "\"\n";
        }

        cmake << ")\n\n";

        cmake << "target_link_libraries(\n";
        cmake << "    testpp_generated\n";
        cmake << "    PRIVATE\n";
        cmake << "    testpp::testpp_main\n";
        cmake << ")\n";

        return true;
    }
}