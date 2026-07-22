#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Main.hpp>
#include <algorithm>
#include <iostream>
#include <thread>

int getNumThreads(const std::string &arg)
{
    size_t pos{};

    //find out the max number of threads this hardware can support
    int max_threads = std::max(std::thread::hardware_concurrency(), 1u);
    //clamp the number of threads in the argument between 1 and the max
    return std::max(std::min(std::stoi(arg, &pos), max_threads), 1);
}

internal::Renderer::Verbosity getVerbFlag(const std::string &arg)
{
    if (arg == "minimum") {
        return internal::Renderer::Verbosity::Minimum;
    } else if (arg == "passonly" || arg == "pass_only") {
        return internal::Renderer::Verbosity::PassOnly;
    } else if (arg == "failonly" || arg == "fail_only"
        || arg == "failonlyall" || arg == "fail_only_all") 
    {
        return internal::Renderer::Verbosity::FailOnlyAll;
    } else if (arg == "failonlymin" || arg == "fail_only_min")
    {
        return internal::Renderer::Verbosity::FailOnlyMin;
    }

    return internal::Renderer::Verbosity::Default;
}

void getSkip(const std::string& arg, std::unordered_set<std::string>& suites)
{
    std::string suite;
    std::stringstream args(arg);

    while(std::getline(args, suite, ','))
    {
        suites.insert(suite);
    }
}

void getTestOnly(const std::string &arg, std::unordered_set<std::string>& suites)
{
    std::string suite;
    std::stringstream args(arg);

    while(std::getline(args, suite, ','))
    {
        suites.insert(suite);
    }
}

void renderUsage(char* bad_flag) {
    std::cerr << "Unknown flag: " << bad_flag << std::endl;
    std::cerr << "Usage: ./pathToExecutable --flags\n" << std::endl;
    std::cerr << "Supported flags:" << std::endl;
    std::cerr << "\tVerbosity: --v= or --verbosity=" << std::endl;
    std::cerr << "\tThreads: --t= or --num_threads= or --threads=" << std::endl;
    std::cerr << "\tTimeout: --timeout= or --timeout_sec= or --timeout_ms=" << std::endl;
    std::cerr << "\tSkip Suites: --s= or --skip=" << std::endl;
    std::cerr << "\tTest Only Suites: --testonly= or --test_only= or --to= or t_o=\n" << std::endl;
    std::cerr << "\t JSON Output: --json PATH_TO_FILE" << std::endl;
    std::cerr << "\t XML Output: --junit PATH_TO_FILE or --xml PATH_TO_FILE" << std::endl;
    std::cerr << "\t stdout output length: --truncatestdout= or truncstdout" << std::endl;
    std::cerr << "\t stderr output length: --truncatestderr= or truncstderr" << std::endl;
    std::cerr << "\t stdout and stderr output length (1024 chars): --truncate" << std::endl;
    std::cerr << "Supported verbosity flags: ";
    std::cerr << "default, minimum, passonly, failonly, failonlymin" << std::endl;
    std::cerr << "Suites being skipped must be separated by ',' with NO space in between" << std::endl;
}