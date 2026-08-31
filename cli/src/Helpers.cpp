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
        const tppCLI::CXX& user_cxx,
        const tppCLI::Config& settings
    )
    {
        std::cout << "Version: " << VERSION << "\n\n";
        std::cout << "Installation Folder: " << installRoot << "\n\n";

        std::cout << "Test Executable Built: ";

        bool user_exec_exists = std::filesystem::exists(user_exec);

        if (user_exec_exists) {
            std::cout << "True\n";
            std::cout << "Test Executable Path: " << user_exec.c_str() << "\n\n";
        } else {
            std::cout << "False\n\n";
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

        std::cout << "\n\ncxx_flags: " << user_cxx.flags;
        std::cout << "\ncxx standard: " << "-std=c++" << user_cxx.standard;

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
                args.push_back(p.string());
            }
        }
    }

    void printHelp() {
        std::cout << "help:\n";
        std::cout << "commands:\n";
        std::cout << "\ttestpp --help - prints out information on how to use Test++\n";
        std::cout << "\ttestpp --version - prints out the version of Test++\n";
        std::cout << "\ttestpp --diagnostics - prints our information about your version of Test++"
                            " as well as your settings\n\n";

        std::cout << "\ttestpp - runs the last built executable, if there is one\n";
        std::cout << "\ttestpp [files/directories] - adds files to the generated executable and runs it\n";
        std::cout << "\ttestpp [flags] - runs the last built executable under the specified flags\n";
        std::cout << "\ttestpp [pattern] - a combination of the above two commands where [pattern] is"
                                         " a set of files/directories and flags\n\n";

        std::cout << "\ttestpp --reset - resets both your configuration and compiler flag settings\n";
        std::cout << "\ttestpp --reset-flags - resets only your configuration settings\n";
        std::cout << "\ttestpp --reset-cxx - resets only your compiler flag settings\n";

        std::cout << "\ttestpp config [flags] - configures your Test++ settings\n";
        std::cout << "\ttestpp cxx_flags [compiler_flags] - configures your Test++ compiler flags."
                            "\n\t\tType them in as if you were passing them directly to the compiler\n\n";
        
        std::cout << "Supported [flags]:\n";
        std::cout << "\tVerbosity: --v= or --verbosity=\n";
        std::cout << "\tThreads: --t= or --numthreads= or --threads=\n";
        std::cout << "\tTimeout: --timeout= or --timeout_sec= or --timeout_ms=\n";
        std::cout << "\tSkip Suites: --s= or --skip=\n";
        std::cout << "\tTest Only Suites: --testonly= or --test_only= or --to= or t_o=\n\n";
        std::cout << "\tJSON Output: --json PATH_TO_FILE\n";
        std::cout << "\tXML Output: --junit PATH_TO_FILE or --xml PATH_TO_FILE\n";
        std::cout << "\tstdout output length: --stdoutsize= or --stdout=\n";
        std::cout << "\tstderr output length: --stderrsize= or --stderr=\n";
        std::cout << "\tstdout and stderr output length (1024 chars): --truncate\n";
        std::cout << "\tStream Progress: --stream\n";
        std::cout << "\nSuites being skipped must be separated by ',' with NO space in between\n";
        std::cout << "\nSupported verbosity flags: default, minimum, passonly, failonly, failonlymin\n";
    }

    void generateCMake(
        const std::filesystem::path& install_prefix,
        const std::filesystem::path& write_loc,
        const std::filesystem::path& cmake_template, 
        const std::vector<std::filesystem::path>& files,
        const tppCLI::CXX& cxxFlags
    ) 
    {
        const std::string installReplace = "@INSTALL_PREFIX@";
        const std::string replace = "@USER_SOURCES@";
        const std::string cxxReplace = "@USER_CXX_FLAGS@";
        const std::string stdReplace = "@CXX_STANDARD@";

        std::ifstream readCmakeTemplate(cmake_template);
        std::stringstream cmake;
        cmake << readCmakeTemplate.rdbuf();
        std::string generate_executable(cmake.str());

        std::ostringstream imploded;
        for (size_t i = 0; i < files.size(); i++) {
            imploded << files[i] << "\n\t";
        }

        generate_executable.replace(
            generate_executable.find(installReplace),
            installReplace.size(),
            install_prefix.string()
        );

        generate_executable.replace(
            generate_executable.find(replace),
            replace.size(),
            imploded.str()
        );

        generate_executable.replace(
            generate_executable.find(cxxReplace),
            cxxReplace.size(),
            cxxFlags.flags
        );

        generate_executable.replace(
            generate_executable.find(stdReplace),
            stdReplace.size(),
            cxxFlags.standard
        );

        std::ofstream out(write_loc);
        out << generate_executable;
        out.close();
    }

    bool configureAndBuild(const std::filesystem::path& run) {    
        std::string build_dir = run.string();

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