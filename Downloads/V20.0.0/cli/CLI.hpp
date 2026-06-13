#pragma once

#ifndef CLI_H
#define CLI_H

#include <filesystem>
#include <vector>

namespace tppCLI {
    bool GenerateProject(std::vector<std::filesystem::path> files);
    std::filesystem::path GetTestPPDirectory();
}

#endif