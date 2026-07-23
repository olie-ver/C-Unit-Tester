#include "CLI.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#define VERSION "Test++ V20.1.0"

int main(int argc, char** argv)
{
    // std::cout << "from CLI:" << std::endl;
    // for (int i = 0; i < argc; i++) {
    //     std::cout << argv[i] << " ";
    // }
    // std::cout << std::endl;

    std::filesystem::path installRoot = tppCLI::GetInstallPrefix();

    std::filesystem::path workDir = tppCLI::GetWorkingDirectory();

    std::filesystem::create_directories(workDir);
    std::filesystem::remove_all(workDir / "build/CMakeCache.txt");

    std::filesystem::path configPath = workDir / "config.txt";

    if (!std::filesystem::exists(configPath)) {
        tppCLI::CreateConfig(configPath);
    }

    std::filesystem::path executable = workDir / "build/bin/testpp_generated";
    // std::filesystem::path executable = "build/bin/cliTest";

    if (argc == 1)
    {
        if (!std::filesystem::exists(executable))
        {
            std::cout << "No tests to run\n";
            return EXIT_SUCCESS;
        }

        std::ifstream readConfig(configPath);
        std::stringstream configSettings;
        configSettings << readConfig.rdbuf();

        std::string cmd = executable.string() + " " + configSettings.str();

        // std::cout << "Isolated runCommand: " << cmd << std::endl;

        return std::system(cmd.c_str());
    }

    if (argc >= 2) {
        std::string flag(argv[1]);
        std::transform(flag.begin(), flag.end(), flag.begin(), [](unsigned char c) { return std::tolower(c); });

        if (flag.find("--version") != std::string::npos) {
            std::cout << VERSION << std::endl;
            return EXIT_SUCCESS;
        }

        if (flag == "--reset") {
            tppCLI::CreateConfig(configPath);
            return EXIT_SUCCESS;
        }

        if (flag == "config") {
            tppCLI::CreateConfig(configPath, argc, argv);
            return EXIT_SUCCESS;
        }
    }    

    std::vector<std::string> args{" "};

    std::vector<std::filesystem::path> files;

    for (int i = 1; i < argc; i++) {
        std::filesystem::path p(argv[i]);

        if (std::filesystem::is_regular_file(p))
        {
            // std::cout << "FILE: " << p << std::endl;
            files.push_back(std::filesystem::absolute(p));
        } 
        else if (std::filesystem::is_directory(p))
        {
            for (const auto& entry :
                std::filesystem::recursive_directory_iterator(p))
            {
                if (entry.path().extension() == ".cpp")
                {
                    // std::cout << "FILE: " << entry.path() << std::endl;
                    files.push_back(std::filesystem::absolute(entry.path()));
                }
            }
        } else {
            // std::cout << "ARG: " << p.string() << std::endl;
            args.push_back(p.string());
        }
    }

    if (!files.empty()) {
        bool success = tppCLI::GenerateProject(files);

        if (!success) {
            return EXIT_FAILURE;
        }

        std::string configureCommand = std::string("cmake -S \"")
                                        + workDir.string()
                                        + "\" -B \""
                                        + (workDir / "build").string()
                                        + "\"";

        int configureResult = std::system(configureCommand.c_str());

        if (configureResult != 0)
        {
            std::cerr << "Failed to configure project\n";
            return EXIT_FAILURE;
        }

        std::filesystem::path buildDir = workDir / "build";

        std::string buildCommand = std::string("cmake --build \"") 
                                    + buildDir.string()
                                    + std::string("\" --parallel"); 

        int buildResult = std::system(buildCommand.c_str());

        if (buildResult != 0)
        {
            std::cerr << "Failed to build project\n";
            return EXIT_FAILURE;
        }
    }

    // Source - https://stackoverflow.com/a/5689061
    // Posted by sehe, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-06-11, License - CC BY-SA 3.0

    const char* const delim = " ";

    std::ostringstream imploded;
    //copy the args over
    std::copy(args.begin(), args.end(), std::ostream_iterator<std::string>(imploded, delim));

    //read the config settings
    std::ifstream readConfig(configPath);
    std::stringstream configSettings;
    configSettings << readConfig.rdbuf();
    
    //runCommand is path => configSettings => explicit settings (the explicit settings override any configSettings)
    std::string runCommand = executable.string() + " " + configSettings.str() + " " + imploded.str();

    // std::cout << "runCommand: " << runCommand << "\n";

    return std::system(runCommand.c_str());
}