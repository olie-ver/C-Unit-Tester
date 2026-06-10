#include <tester/internal/Core.hpp>
#include <tester/internal/Renderer.hpp>
#include <tester/internal/Runner.hpp>

//Gets the verbosity flag from an argument
internal::Renderer::Verbosity getVerbFlag(const std::string& arg);

//Gets the number of threads from an argument
int getNumThreads(const std::string& arg);

//Gets the SUITES to skip testing for
void getSkip(const std::string& arg, std::unordered_set<std::string>& suites);

//Gets the SUITES to ONLY test
void getTestOnly(const std::string& arg, std::unordered_set<std::string>& suites);

//Renders how to use the application
void renderUsage(char* bad_flag);