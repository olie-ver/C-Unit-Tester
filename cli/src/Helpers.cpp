#include "Helpers.hpp"
#include "CLI.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

namespace tppHelpers {
    void printDiagnostics(const char* VERSION, 
        const std::filesystem::path& installRoot, 
        const std::filesystem::path& user_exec,
        const tppCLI::Config& settings
    )
    {
        std::cout << "Version: " << VERSION << '\n';
        std::cout << "Installation Folder: " << installRoot << '\n';

        std::cout << "Test Executable Built: ";

        bool user_exec_exists = std::filesystem::exists(user_exec);

        if (user_exec_exists) {
            std::cout << "True\n";
        } else {
            std::cout << "False\n";
        }

        std::cout << "Configurations:";
        std::cout << "\n\tnum_threads = " << settings.num_threads;
        std::cout << "\n\tverbosity = " << settings.verbosity;
        std::cout << "\n\ttimeout = " << settings.timeout;
        std::cout << "\n\ttime_unit = " << settings.time_unit;
        std::cout << "\n\tstdoutSize = " << settings.stdoutSize;
        std::cout << "\n\tstderrSize = " << settings.stderrSize;
        std::cout << "\n\tstreaming: ";

        if (settings.stream) {
            std::cout << "On";
        } else {
            std::cout << "Off";
        }

        std::cout << "\n\tjsonFile: ";
        if (settings.jsonFile == "") {
            std::cout << "no file";
        } else {
            std::cout << settings.jsonFile;
        }

        std::cout << "\n\tjUnitFile: ";
        if (settings.jUnitFile == "") {
            std::cout << "no file";
        } else {
            std::cout << settings.jUnitFile;
        }

        std::cout << "\n\tskipSuites: ";
        if (settings.skipSuites == "") {
            std::cout << "no suites to skip";
        } else {
            std::cout << settings.skipSuites;
        }

        std::cout << "\n\ttestOnlySuites: ";
        if (settings.testOnlySuites == "") {
            std::cout << "no suites to only test";
        } else {
            std::cout << settings.testOnlySuites;
        }

        std::cout << std::endl;
    }

    void getFilesAndArgs(int argc, char** argv,
        std::vector<std::string>& args, 
        std::vector<std::filesystem::path>& files
    ) 
    {
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
    }

    void generateCMake(
        const std::filesystem::path& write_loc,
        const std::filesystem::path& cmake_template, 
        const std::vector<std::filesystem::path>& files
    ) 
    {
        const std::string replace = "@USER_SOURCES@";

        std::ifstream readCmakeTemplate(cmake_template);
        std::stringstream cmake;
        cmake << readCmakeTemplate.rdbuf();
        std::string generate_executable(cmake.str());

        std::ostringstream imploded;
        for (size_t i = 0; i < files.size(); i++) {
            imploded << files[i] << "\n\t";
        }

        size_t replace_start = generate_executable.find(replace);

        std::string generate_command = generate_executable.replace(replace_start, replace.size(), imploded.str());

        std::ofstream out(write_loc, std::ios::out | std::ios::trunc);
        out << generate_command;
        out.close();
    }

    bool configureAndBuild(const std::filesystem::path& run) {    
        std::string build_dir = (run / "build").string();

        std::string configure = "cmake -S \"" + build_dir +  "\" -B \"" + build_dir + "\"";

        int configResult = std::system(configure.c_str());

        if (configResult != 0) {
            std::cerr << "Failed to configure project" << std::endl;
            return false;
        }

        std::string build = "cmake --build \"" + build_dir + "\"";

        int buildResult = std::system(build.c_str());

        if (buildResult != 0) {
            std::cerr << "Failed to build project" << std::endl;
            return false;
        }

        return true;
    }
}