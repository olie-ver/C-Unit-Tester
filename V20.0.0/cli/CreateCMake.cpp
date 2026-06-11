#include "CLI.hpp"
#include <fstream>

bool GenerateProject(std::vector<std::filesystem::path> files)
{
    std::filesystem::create_directories(".testpp");

    std::ofstream cmake(".testpp/CMakeLists.txt");

    if (!cmake) {
        return false;
    }

    cmake << "cmake_minimum_required(VERSION 3.20)\n";
    cmake << "project(testpp_generated)\n\n";

    cmake << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)\n\n";

    cmake << "find_package(testpp REQUIRED)\n\n";

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