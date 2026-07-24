#include "CLI.hpp" 
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

namespace tppCLI {
    void CreateConfig(std::filesystem::path path, int argc, char** argv) {
        //read in the current config settings
        Config config = GetConfig(path);
        size_t pos{};

        for (size_t i = 2; i < argc; i++) {
            std::string flag(argv[i]);
            std::transform(flag.begin(), flag.end(), flag.begin(), [](unsigned char c) { return std::tolower(c); });

            if (flag.find("--v=") != std::string::npos 
                || flag.find("--verbosity=") != std::string::npos)
            {
                std::string arg = flag.substr(flag.find('=') + 1);

                if (arg == "minimum" || arg == "passonly" || arg == "pass_only" ||
                    arg == "failonly" || arg == "fail_only" || arg == "failonlyall" || 
                    arg == "fail_only_all" || arg == "failonlymin" || arg == "fail_only_min" ||
                    arg == "default") 
                {
                    config.verbosity = arg;
                } else {
                    std::cerr << "unknown verbosity flag: " << arg << "\n";
                    std::cerr << "supported verbosity flags are: minimum, passonly, pass_only, failonly"
                                 ",\n fail_only, failonlyall, fail_only_all, failonlymin, fail_only_min"
                                 ",\n and default";
                    std::abort();  
                }
            } else if (flag.find("--numthreads=") != std::string::npos
                || flag.find("--threads=") != std::string::npos
                || flag.find("--t=") != std::string::npos)
            {
                std::string arg = flag.substr(flag.find('=') + 1);
            
                try {
                    config.num_threads = stoi(arg, &pos);
                } catch (std::invalid_argument const& ex) {
                    std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                    std::abort();
                } catch (std::out_of_range const& ex) {
                    std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag.find("--s=") != std::string::npos 
                || flag.find("--skip=") != std::string::npos)
            {
                std::string originalFlag(argv[i]);
                std::string arg = originalFlag.substr(originalFlag.find('=') + 1);

                config.skipSuites = arg;
            } else if (flag.find("--testonly=") != std::string::npos
                || flag.find("--test_only=") != std::string::npos
                || flag.find("--t_o=") != std::string::npos 
                || flag.find("--to=") != std::string::npos)
            {
                std::string originalFlag(argv[i]);
                std::string arg = originalFlag.substr(originalFlag.find('=') + 1);
                
                config.testOnlySuites = arg;
            } else if (flag.find("--timeout") != std::string::npos 
                && flag.find('=') != std::string::npos)
            {
                if (flag.find("_ms=") != std::string::npos) {
                    config.time_unit = "ms";
                }

                std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.timeout = std::stoi(arg, &pos);
                    if (config.timeout < 0) {
                        std::cerr << "timeout duration must be nonnegative" << std::endl;
                        std::abort();
                    }
                } catch (std::invalid_argument const& ex) {
                    std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                    std::abort();
                } catch (std::out_of_range const& ex) {
                    std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag == "--json") {
                if (i != argc - 1) {
                    config.jsonFile = argv[++i];
                    if (!config.jsonFile.ends_with(".json")) {
                        std::cerr << "Invalid .json path: " << config.jsonFile << std::endl;
                        std::abort();
                    }
                } else {
                    std::cerr << "Missing .json file path after --json flag" << std::endl;
                    std::abort();
                }
            } else if (flag == "--junit" || flag == "--xml") {
                if (i != argc - 1) {
                    config.jUnitFile = argv[++i];
                    if (!config.jUnitFile.ends_with(".xml")) {
                        std::cerr << "Invalid .xml path: " << config.jUnitFile << std::endl;
                        std::abort();
                    }
                } else {
                    std::cerr << "Missing .xml file path after --junit/--xml flag" << std::endl;
                    std::abort();
                }
            } else if (flag.find("--stdoutsize=") != std::string::npos 
                || flag.find("--stdout=") != std::string::npos)
            {
                std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.stdoutSize = std::stoi(arg, &pos);
                    if (config.stdoutSize < 0) {
                        std::cerr << "stdout output length must be nonnegative" << std::endl;
                        std::abort();
                    }
                } catch (std::invalid_argument const& ex) {
                    std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                    std::abort();
                } catch (std::out_of_range const& ex) {
                    std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag.find("--stderrsize=") != std::string::npos 
                || flag.find("--stderr=") != std::string::npos)
            {  std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.stderrSize = std::stoi(arg, &pos);
                    if (config.stderrSize < 0) {
                        std::cerr << "stderr output length must be nonnegative" << std::endl;
                        std::abort();
                    }
                } catch (std::invalid_argument const& ex) {
                    std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                    std::abort();
                } catch (std::out_of_range const& ex) {
                    std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag == "--truncate") {
                config.stdoutSize = 1024;
                config.stderrSize = 1024;
            } else if (flag.find("--stream=") != std::string::npos) {
                std::string arg = flag.substr(flag.find('=') + 1);
                config.stream = arg == "true";
            } else if (flag == "--stream") {
                config.stream = true;
            }
        }

        std::ofstream configFile(path, std::ios::out | std::ios::trunc);

        configFile << "--numthreads=" << config.num_threads;
        configFile << " --timeout";
        if (config.time_unit == "ms") {
            configFile << "_ms";
        }
        configFile << "=" << config.timeout;

        if (config.verbosity != "") {
            configFile << " --verbosity=" << config.verbosity;
        }

        if (config.jsonFile != "") {
            configFile <<  " --json " << config.jsonFile;
        }

        if (config.jUnitFile != "") {
            configFile << " --junit " << config.jUnitFile;
        }
        
        if (config.skipSuites != "") {
            configFile << " --skip=" << config.skipSuites;
        }

        if (config.testOnlySuites != "") {
            configFile << " --testonly=" << config.testOnlySuites;
        }

        configFile << " --stdoutsize=" << config.stdoutSize;
        configFile << " --stderrsize=" << config.stderrSize;

        if (config.stream) {
            configFile << " --stream";
        }
    }

    const Config GetConfig(std::filesystem::path path)
    {
        Config config;

        std::ifstream file(path);
        std::string flag;
        size_t pos{};

        while (file >> flag)
        {
            if (flag.find("--v=") != std::string::npos
                || flag.find("--verbosity=") != std::string::npos)
            {
                config.verbosity = flag.substr(flag.find('=') + 1);
            }
            else if (flag.find("--numthreads=") != std::string::npos)
            {
                config.num_threads = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag.find("--skip=") != std::string::npos)
            {
                config.skipSuites = flag.substr(flag.find('=') + 1);
            }
            else if (flag.find("--testonly=") != std::string::npos)
            {
                config.testOnlySuites = flag.substr(flag.find('=') + 1);
            }
            else if (flag.find("--timeout") != std::string::npos
                    && flag.find('=') != std::string::npos)
            {
                config.time_unit =
                    (flag.find("_ms=") != std::string::npos) ? "ms" : "sec";

                config.timeout = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag == "--json")
            {
                file >> config.jsonFile;
            }
            else if (flag == "--junit")
            {
                file >> config.jUnitFile;
            }
            else if (flag == "--xml")
            {
                file >> config.jUnitFile;
            }
            else if (flag.find("--stdoutsize=") != std::string::npos)
            {
                config.stdoutSize = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag.find("--stderrsize=") != std::string::npos)
            {
                config.stderrSize = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag == "--truncate")
            {
                config.stdoutSize = 1024;
                config.stderrSize = 1024;
            }
            else if (flag == "--stream")
            {
                config.stream = true;
            }
        }

        return config;
    }
}