#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Core.hpp>
#include <testpp/internal/Renderer.hpp>
#include <testpp/internal/Runner.hpp>
#include <testpp/internal/Main.hpp>
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <cstring>
#endif

int main(int argc, char** argv) {
#ifdef _WIN32
    if (argc == 4 && !strcmp("--isolation", argv[1])) {
        auto& ctx = internal::Runner::getDeathContext();

        ctx.childMode = true;
        ctx.targetTest = std::stoull(argv[2]);
        ctx.targetDeath = std::stoull(argv[3]);

        internal::Runner::runSingleTest(ctx.targetTest);

        return EXIT_SUCCESS;
    }
#endif

    int num_threads = 1;
    int timeout = 0;

    internal::Renderer::Verbosity verbFlag = internal::Renderer::Verbosity::Default;
    internal::Core::TimeUnit unit = internal::Core::TimeUnit::Seconds;
    auto& skipSuites = internal::Runner::getSkipSuites();
    auto& testOnlySuites = internal::Runner::getTestOnly();

    std::string jsonFile = "";
    std::string jUnitFile = "";

    int stdoutSize = 0;
    int stderrSize = 0;

    // process the arguments
    for (int i = 1; i < argc; i++) {
        std::string flag(argv[i]);
        

        std::cout << "FLAG: " << flag << std::endl;


        std::transform(flag.begin(), flag.end(), flag.begin(), 
            [](unsigned char c) { return std::tolower(c); });

        if (flag.find("--v=") != std::string::npos 
            || flag.find("--verbosity=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);
            verbFlag = getVerbFlag(arg);
        } else if (flag.find("--num_threads=") != std::string::npos
            || flag.find("--threads=") != std::string::npos
            || flag.find("--t=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);

            try {
                num_threads = getNumThreads(arg);
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        } else if (flag.find("--s=") != std::string::npos 
            || flag.find("--skip=") != std::string::npos)
        {
            std::string originalFlag(argv[i]);
            std::string arg = originalFlag.substr(originalFlag.find('=') + 1);
            getSkip(arg, skipSuites);
        } else if (flag.find("--testonly=") != std::string::npos
            || flag.find("--test_only=") != std::string::npos
            || flag.find("--t_o=") != std::string::npos 
            || flag.find("--to=") != std::string::npos)
        {
            std::string originalFlag(argv[i]);
            std::string arg = originalFlag.substr(originalFlag.find('=') + 1);
            getTestOnly(arg, testOnlySuites);
        } else if (flag.find("--timeout") != std::string::npos 
            && flag.find('=') != std::string::npos)
        {
            if (flag.find("_ms=") != std::string::npos) {
                unit = internal::Core::TimeUnit::Milliseconds;
            }

            std::string arg = flag.substr(flag.find('=') + 1);

            try {
                size_t pos{};
                timeout = std::stoi(arg, &pos);
                if (timeout < 0) {
                    std::cerr << "timeout duration must be nonnegative" << std::endl;
                    return EXIT_FAILURE;
                }
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        } else if (flag == "--json") {
            if (i != argc - 1) {
                jsonFile = argv[++i];
                if (!jsonFile.ends_with(".json")) {
                    std::cerr << "Invalid .json path: " << jsonFile << std::endl;
                    return EXIT_FAILURE;
                }
            } else {
                std::cerr << "Missing .json file path after --json flag" << std::endl;
                return EXIT_FAILURE;
            }
        } else if (flag == "--junit" || flag == "--xml") {
            if (i != argc - 1) {
                jUnitFile = argv[++i];
                if (!jUnitFile.ends_with(".xml")) {
                    std::cerr << "Invalid .xml path: " << jUnitFile << std::endl;
                    return EXIT_FAILURE;
                }
            } else {
                std::cerr << "Missing .xml file path after --junit/--xml flag" << std::endl;
                return EXIT_FAILURE;
            }
        } else if (flag.find("--truncatestdout=") != std::string::npos 
            || flag.find("--truncstdout=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);

            try {
                size_t pos{};
                stdoutSize = std::stoi(arg, &pos);
                if (stdoutSize < 0) {
                    std::cerr << "stdout output length must be nonnegative" << std::endl;
                    return EXIT_FAILURE;
                }
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        } else if (flag.find("--truncatestderr=") != std::string::npos 
            || flag.find("--truncstderr=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);

            try {
                size_t pos{};
                stderrSize = std::stoi(arg, &pos);
                if (stderrSize < 0) {
                    std::cerr << "stderr output length must be nonnegative" << std::endl;
                    return EXIT_FAILURE;
                }
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        } else if (flag == "--truncate") {
            stdoutSize = 1024;
            stderrSize = 1024;
        } else if (flag == "--stream") {
            internal::Renderer::shouldStream = true;
        } else {
            renderUsage(argv[i]);
            return EXIT_FAILURE;
        }
    }

    internal::Core::TestRun& testRun = internal::Runner::getTestRun();

    internal::Runner::runAllRegisteredTests(testRun, num_threads, timeout, unit);

    internal::Renderer::ConsoleRenderer renderer(verbFlag, jsonFile, jUnitFile, stdoutSize, stderrSize);

    renderer.render(testRun);
    return EXIT_SUCCESS;
}
