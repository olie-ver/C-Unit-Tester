#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Runner.hpp>
#include <testpp/internal/Renderer.hpp>
#include <atomic>
#include <chrono>
#include <iostream>

namespace internal {
    namespace Runner {
        std::atomic<size_t> next_index{0};

        void threadWorker(std::vector<Core::TestResult>& results, Core::Test& running) {
            std::vector<Core::Test>& REGISTRY = getRegistry();
            size_t size = REGISTRY.size();
    
            while (true) {
                size_t index = next_index.fetch_add(1);

                if (index >= REGISTRY.size()) {
                    break;
                }

                Core::Test& test = REGISTRY[index];

                //if the test's suite_name is marked to be skipped, skip it
                if (shouldSkip(test.suite_name)) {
                    Core::TestResult skip;
                    skip.suiteName = test.suite_name;
                    skip.testName = test.test_name;
                    skip.test_status = Core::TestStatus::Skipped;

                    skip.execution_ms = 0.0;

                    results[index] = skip;

                    if (Renderer::shouldStream) {
                        Renderer::stream(
                            '[' + std::to_string(index + 1) + '/' +
                            std::to_string(size) +
                            "][SKIPPED]: " +
                            test.suite_name + " -> " +
                            test.test_name + '\n'
                        );
                    }
                } else {
                    running = test;

                    if (Renderer::shouldStream) {
                        Renderer::stream(
                            '[' + std::to_string(index + 1) + '/' +
                            std::to_string(size) +
                            "][STARTED]: " +
                            test.suite_name + " -> " +
                            test.test_name + '\n'
                        );
                    }

                    //only allow non-skipped tests to be run
                    results[index] = runTest(test);

                    if (Renderer::shouldStream) {
                        Renderer::stream(
                            '[' + std::to_string(index + 1) + '/' +
                            std::to_string(size) +
                            "][ENDED]: " +
                            test.suite_name + " -> " +
                            test.test_name + '\n'
                        );
                    }
                }
            }
        }

        std::thread createWatchdog(const int& time, const int& num_threads, 
            const std::atomic<bool>& finished, 
            const std::vector<Core::Test>& running, 
            const std::string& timeUnit,
            const std::chrono::steady_clock::time_point& start_time) 
        {
            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            return std::thread([&time, &finished, &running, &num_threads, &timeUnit, &start_time]() {
                while (!finished.load()) {
                    clock::time_point now = clock::now();
                    int elapsed = std::chrono::duration_cast<ms>(now - start_time).count();

                    if (elapsed >= time) {
                        std::cerr << "\nGLOBAL TEST TIMEOUT EXCEEDED (" << time << ' '
                            << timeUnit << ")\n";

                        //print out what each thread is running
                        for (int i = 0; i < num_threads; i++) {
                            std::cout << "Thread " << i << " is running test: "
                                << running[i].suite_name << " -> " << running[i].test_name << '\n';
                        }
                        std::abort();
                    }

                    std::this_thread::sleep_for(ms(100));
                }
            });
        }
    }
}