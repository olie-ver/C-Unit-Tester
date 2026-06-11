#include "CLI.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
    std::filesystem::create_directories(".testpp");

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
            std::cerr << "error: " << p << " does not exist\n";
            return EXIT_FAILURE;
        }
    }

    if (!files.empty()) {
        bool success = GenerateProject(files);

        if (!success) {
            return EXIT_FAILURE;
        }

        int configureResult = std::system("cmake -S .testpp -B .testpp/build");

        if (configureResult != 0)
        {
            std::cerr << "Failed to configure project\n";
            return EXIT_FAILURE;
        }

        int buildResult = std::system("cmake --build .testpp/build --parallel");

        if (buildResult != 0)
        {
            std::cerr << "Failed to build project\n";
            return EXIT_FAILURE;
        }
    }

    int runResult = std::system(".testpp/build/bin/testpp_generated");

    return EXIT_SUCCESS;
}