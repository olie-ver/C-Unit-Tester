#include "CLI.hpp"
#include "Helpers.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#define VERSION "Test++ V20.1.0"

int main(int argc, char** argv) {
    std::filesystem::path installRoot = tppCLI::GetInstallPrefix();
    std::filesystem::path run = installRoot / "run";
    std::filesystem::path var = installRoot / "var";
    std::filesystem::path user_exec = run / "build" / "bin" / "testpp_generated";
    std::filesystem::path user_conf = run / "config.conf";
    std::filesystem::path cmake_template = var / "CMakeLists.txt.in";

    if (!std::filesystem::exists(user_conf)) {
        //If there isn't a configuration file, copy over the default 
        std::filesystem::copy_file(var / "default.conf", user_conf);
    }

    //Get the config settings
    tppCLI::Config settings = tppCLI::GetConfig(user_conf);

    if (argc == 1) {
        if (!std::filesystem::exists(user_exec)) {
            std::cout << "No tests to run" << std::endl;
            return EXIT_SUCCESS;
        }

        std::ifstream readConfig(user_conf);
        std::stringstream configSettings;
        configSettings << readConfig.rdbuf();

        std::string cmd = user_exec.string() + " " + configSettings.str();

        std::cout << "Isolated runCommand: " << cmd << std::endl;

        return std::system(cmd.c_str());
    }

    if (argc >= 2) {
        std::string first_arg{argv[1]};

        if (first_arg == "--version") {
            std::cout << VERSION << std::endl;

            return EXIT_SUCCESS;
        }

        if (first_arg == "--reset") {
            std::filesystem::copy_file(var / "default.conf", run / "config.conf", 
                std::filesystem::copy_options::overwrite_existing);
    
            return EXIT_SUCCESS;
        }

        if (first_arg == "--diagnostics") {
            tppHelpers::printDiagnostics(VERSION, installRoot, user_exec, settings);

            return EXIT_SUCCESS;
        }

        if (first_arg == "config") {
            //config the file then return
            tppCLI::CreateConfig(user_conf, argc, argv);
            return EXIT_SUCCESS;
        }
    }

    //gather files and args
    std::vector<std::string> args{" "};

    std::vector<std::filesystem::path> files;

    tppHelpers::getFilesAndArgs(argc, argv, args, files);

    tppHelpers::generateCMake(run / "build" / "CMakeLists.txt", cmake_template, files);

    if (!tppHelpers::configureAndBuild(run)) {
        return EXIT_FAILURE;
    }

    std::string run_command = '\"' + user_exec.string() + '\"';

    // std::cout << "exec path: " << run_command << std::endl;

    return std::system(run_command.c_str());
}