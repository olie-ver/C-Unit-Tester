#pragma once

#ifndef CLI_HELPERS_H
#define CLI_HELPERS_H

#include "CLI.hpp"

namespace tppHelpers {
    void printDiagnostics(const char* VERSION, 
        const std::filesystem::path& installRoot, 
        const std::filesystem::path& user_exec,
        const tppCLI::Config& settings
    );

    void getFilesAndArgs(int argc, char** argv,
        std::vector<std::string>& args, 
        std::vector<std::filesystem::path>& files
    );

    void generateCMake(
        const std::filesystem::path& write_loc,
        const std::filesystem::path& cmake_template, 
        const std::vector<std::filesystem::path>& files
    );

    bool configureAndBuild(const std::filesystem::path& run);
}

#endif