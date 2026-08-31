#include "CLI.hpp"
#include "Helpers.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#define VERSION "Test++ V20.1.3"

#define DEFAULT_FLAGS "default_flag.conf"

int main(int argc, char** argv) {
    std::filesystem::path installRoot = tppCLI::GetInstallPrefix();

    std::filesystem::path run = installRoot / "run";
    std::filesystem::path var = installRoot / "var";
    std::filesystem::path user_exec = run / "bin" / "testpp_generated";
    std::filesystem::path user_conf = run / "config_flags.conf";
    std::filesystem::path user_cxx = run / "config_cxx.conf";
    std::filesystem::path cmake_template = var / "CMakeLists.txt.in";

    std::filesystem::remove(run / "CMakeCache.txt");

    if (!std::filesystem::exists(user_conf)) {
        //If there isn't a configuration file, copy over the default 
        std::filesystem::copy_file(var / DEFAULT_FLAGS, user_conf);
    }

    if (!std::filesystem::exists(user_cxx)) {
        //If there isn't a cxx file, copy over the default 
        std::filesystem::copy_file(var / "default_cxx.conf", user_cxx);
    }

    std::ifstream readConfig(user_conf);
    std::stringstream configSettings;
    configSettings << readConfig.rdbuf();

    const tppCLI::CXX& cxx = tppCLI::getCXX(user_cxx);

    if (argc == 1) {
        if (!std::filesystem::exists(user_exec)) {
            std::cout << "No tests to run" << std::endl;
            return EXIT_SUCCESS;
        }

        std::string cmd = '\"' + user_exec.string() + '\"' + " " + configSettings.str();

        return std::system(cmd.c_str());
    }

    if (argc >= 2) {
        std::string first_arg{argv[1]};

        if (first_arg == "--help") {
            tppHelpers::printHelp();
            
            return EXIT_SUCCESS;
        }

        if (first_arg == "--version") {
            std::cout << VERSION << std::endl;

            return EXIT_SUCCESS;
        }

        if (first_arg == "--reset") {
            std::filesystem::copy_file(var / DEFAULT_FLAGS, user_conf, 
                std::filesystem::copy_options::overwrite_existing);

            std::filesystem::copy_file(var / "default_cxx.conf", user_cxx,
                std::filesystem::copy_options::overwrite_existing);
    
            return EXIT_SUCCESS;
        }

        if (first_arg == "--reset-flags") {
            std::filesystem::copy_file(var / DEFAULT_FLAGS, user_conf, 
                std::filesystem::copy_options::overwrite_existing);
            return EXIT_SUCCESS;
        }

        if (first_arg == "--reset-cxx") {
            std::filesystem::copy_file(var / "default_cxx.conf", user_cxx,
                std::filesystem::copy_options::overwrite_existing);
    
            return EXIT_SUCCESS;
        }

        if (first_arg == "--diagnostics") {
            //Get the config settings
            const tppCLI::Config& settings = tppCLI::GetConfig(user_conf);
            tppHelpers::printDiagnostics(VERSION, installRoot, user_exec, cxx, settings);

            return EXIT_SUCCESS;
        }

        if (first_arg == "config") {
            //config the file then return
            tppCLI::CreateConfig(user_conf, argc, argv);
            return EXIT_SUCCESS;
        }

        if (first_arg == "cxx_flags") {
            //write to the cxx flag file then return
            std::ofstream cxx_stream(user_cxx.c_str(), std::ios::trunc);
            std::string flags = "Flags: ";
            std::string std = "Standard: ";
            for (int i = 2; i < argc; i++) {
                if (std::string_view(argv[i]).find("-std=c++") != std::string_view::npos) {
                    std += argv[i];
                } else {
                    flags += argv[i];
                    flags += " ";
                }
            }
            cxx_stream << flags << '\n';
            cxx_stream << std;
            return EXIT_SUCCESS;
        }
    }

    //gather files and args
    std::vector<std::string> args{" "};

    std::vector<std::filesystem::path> files;

    tppHelpers::getFilesAndArgs(argc, argv, args, files);

    //if no files were specifed, rerun the generated executable
    //  under any flags that were given
    if (files.size() == 0) {
        if (!std::filesystem::exists(user_exec)) {
            std::cout << "No tests to run" << std::endl;
            return EXIT_SUCCESS;
        }

        std::stringstream argStream;

        for (size_t i = 0; i < args.size(); i++) {
            argStream << args[i] << " ";
        }

        std::string run_command = '\"' + user_exec.string() + '\"' + " " + configSettings.str() + argStream.str();
        return std::system(run_command.c_str());
    }

    tppHelpers::generateCMake(installRoot, run / "CMakeLists.txt", cmake_template, files, cxx);

    if (!tppHelpers::configureAndBuild(run)) {
        return EXIT_FAILURE;
    }

    std::stringstream argStream;

    for (size_t i = 0; i < args.size(); i++) {
        argStream << args[i] << " ";
    }

    //Run command is "user_exec" configSettings arguments
    // arguments override any configSettings so it's all good to just add them in front
    std::string run_command = '\"' + user_exec.string() + '\"' + " " + configSettings.str() + argStream.str();

    return std::system(run_command.c_str());
}