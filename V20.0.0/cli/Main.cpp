#include "CLI.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>

int main(int argc, char** argv)
{
    std::filesystem::path installRoot = tppCLI::GetTestPPDirectory();
    std::filesystem::create_directories(installRoot);

    std::filesystem::path executable = installRoot / "build/bin/testpp_generated";

    if (argc == 1)
    {
        if (!std::filesystem::exists(executable))
        {
            std::cout << "No tests to run\n";
            return EXIT_SUCCESS;
        }

        return std::system(executable.c_str());
    }

    std::vector<std::string> args{" "};

    std::vector<std::filesystem::path> files;

    for (int i = 1; i < argc; i++) {
        std::filesystem::path p(argv[i]);

        if (std::filesystem::is_regular_file(p))
        {
            files.push_back(std::filesystem::absolute(p));
        } 
        else if (std::filesystem::is_directory(p))
        {
            for (const auto& entry :
                std::filesystem::recursive_directory_iterator(p))
            {
                if (entry.path().extension() == ".cpp")
                {
                    files.push_back(std::filesystem::absolute(entry.path()));
                }
            }
        } else {
            args.push_back(p);
        }
    }

    if (!files.empty()) {
        bool success = tppCLI::GenerateProject(files);

        if (!success) {
            return EXIT_FAILURE;
        }

        std::string configureCommand = std::string("cmake -S \"") 
                                        + installRoot.string() 
                                        + std::string("\" -B \"") 
                                        + installRoot.string()  
                                        + std::string("/build\"");

        int configureResult = std::system(configureCommand.c_str());

        if (configureResult != 0)
        {
            std::cerr << "Failed to configure project\n";
            return EXIT_FAILURE;
        }

        std::filesystem::path buildDir = installRoot / "build";

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
    std::copy(args.begin(), args.end(), std::ostream_iterator<std::string>(imploded, delim));
    
    std::string runCommand = executable.string() + imploded.str();

    std::cout << runCommand << "\n";

    return std::system(runCommand.c_str());
}