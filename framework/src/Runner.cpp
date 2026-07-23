#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Runner.hpp>
#include <atomic>
#include <chrono>
#include <deque>
#include <iostream>
#include <thread>

namespace internal {
    namespace Runner {
        thread_local std::deque<Core::TestResult> TEST_STACK;

        Core::TestRun& getTestRun() {
            static Core::TestRun instance;
            return instance;
        }

        std::vector<Core::Test>& getRegistry() {
            static std::vector<Core::Test> instance;
            return instance;
        }

        std::unordered_set<Core::Test, Core::TestHash>& getAllTests() {
            static std::unordered_set<Core::Test, Core::TestHash> instance;
            return instance;
        }

        #ifdef _WIN32

        DeathContext& getDeathContext()
        {
            static DeathContext ctx;
            return ctx;
        }

        void runSingleTest(size_t testIndex)
        {
            auto& registry = getRegistry();

            for (auto& test : registry)
            {
                if (test.index == testIndex)
                {
                    runTest(test);
                    return;
                }
            }

            std::abort();
        }

        #endif

        std::unordered_set<std::string>& getSkipSuites() {
            static std::unordered_set<std::string> instance;
            return instance;
        }

        std::unordered_set<std::string>& getTestOnly()
        {
            static std::unordered_set<std::string> instance;
            return instance;
        }

        bool shouldSkip(const std::string& suite_name) {
            auto& skip = getSkipSuites();
            auto& specific = getTestOnly();
            return skip.contains(suite_name) || (specific.size() != 0 && !specific.contains(suite_name));
        }

        bool registerTest(Core::Test test)
        {
            auto& ALL_TESTS = getAllTests();

            auto [it, inserted] = ALL_TESTS.insert(test);
            if (!inserted) {
                std::cerr << "Test under suite: " << test.suite_name
                        << " has duplicate name: " << test.test_name << std::endl;
                std::abort();
            }

            std::vector<Core::Test>& REGISTRY = getRegistry();

            #ifdef _WIN32
            test.index = REGISTRY.size();
            #endif

            REGISTRY.push_back(test);
            return true;
        }

        void runAllRegisteredTests(Core::TestRun& run, const int num_threads, 
            const int timeout, Core::TimeUnit unit)
        {   
            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();

            std::atomic<bool> finished{false};
            std::thread watchdog;

            std::vector<Core::Test>& REGISTRY = getRegistry();

            //create our thread pool:
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            std::vector<Core::Test> running;
            running.resize(num_threads);

            std::vector<Core::TestResult> results;
            results.resize(REGISTRY.size());

            //threads start
            for (int i = 0; i < num_threads; i++) {
                threads.emplace_back(threadWorker, std::ref(results), std::ref(running[i]));
            }

            if (timeout > 0) {
                int time = 0;
                std::string timeUnit;
                switch (unit) {
                    case Core::TimeUnit::Seconds:
                        time = timeout * 1000;
                        timeUnit = "seconds";
                        break;
                    case Core::TimeUnit::Milliseconds:
                        time = timeout;
                        timeUnit = "milliseconds";
                        break;
                }

                watchdog = createWatchdog(time, num_threads, finished, running, timeUnit, start_time);
            }

            //join them
            for (int i = 0; i < num_threads; i++) {
                threads[i].join();
            }

            finished.store(true);

            clock::time_point end_time = clock::now();

            if (watchdog.joinable()) {
                watchdog.join();
            }

            //aggregate results
            for (size_t i = 0; i < results.size(); i++) {
                Core::TestResult& result = results[i];
                std::string& suite_name = result.suiteName;
                run.results[suite_name].push_back(result);
                run.total++;
            }

            run.totalMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();
        }

        Core::TestResult runTest(const Core::Test& test) {
            TEST_STACK.push_back({});
            Core::TestResult& CURRENT_TEST = TEST_STACK.back();
            CURRENT_TEST.suiteName = test.suite_name;
            CURRENT_TEST.testName = test.test_name;
            CURRENT_TEST.test_status = Core::TestStatus::Passed;

            #ifdef _WIN32
                getDeathContext().currentDeath = 0;
                CURRENT_TEST.index = test.index;
            #endif

            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();
        
            try {
                test.test();
                clock::time_point end_time = clock::now();

                CURRENT_TEST.execution_ms =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                if (!CURRENT_TEST.failures.empty()) {
                    CURRENT_TEST.test_status =  Core::TestStatus::Failed;
                }

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            } catch (...) { //we don't care what error gets thrown, we end the test
                clock::time_point end_time = clock::now();

                CURRENT_TEST.execution_ms =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                CURRENT_TEST.test_status =  Core::TestStatus::Failed;

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            }
        }
    }
}