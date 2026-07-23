#pragma once

#ifndef CLI_H
#define CLI_H

#include <filesystem>
#include <vector>
#include <string>

namespace tppCLI {
    //Holds all the default values for the framework
    struct Config {
        int num_threads = 1;
        int timeout = 0;

        std::string jsonFile = "";
        std::string jUnitFile = "";

        std::string verbosity = "";
        std::string time_unit = "";

        std::string skipSuites = "";
        std::string testOnlySuites = "";

        int stdoutSize = 0;
        int stderrSize = 0;

        bool stream = false;
    };

    //Creates a Config struct from the arguments you pass in and does validate them
    //  before writing to memory
    void CreateConfig(std::filesystem::path path, int argc, char** argv);

    //Gets the settings from the config file, does NOT validate them, so if you're a user,
    //  don't change anything in the config file manually
    const Config GetConfig(std::filesystem::path path);

    /// @brief Gets the path to the root folder of where Test++ is installed
    /// @return The path of the root folder where Test++ is installed
    std::filesystem::path GetInstallPrefix();
}

#endif