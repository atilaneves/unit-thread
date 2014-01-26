#include "TestSuite.hpp"
#include "TestCaseFactory.hpp"
#include <memory>
#include <iostream>
#include <future>


TestSuite::TestSuite(std::launch policy):
    _policy(policy), _numTestsRun() {
}


void TestSuite::addFailure(const std::string& name) {
    _failures.push_back(name);
}


using std::chrono::duration_cast;
template<typename CLOCK, typename START>
static double getElapsedSeconds(CLOCK clock, const START start) {
    //cast to ms first to get fractional amount of seconds
    return duration_cast<std::chrono::milliseconds>(clock.now() - start).count() / 1000.0;
}


double TestSuite::run() {
    const bool listAll = false; //leave hidden out
    const auto paths = TestCaseFactory::getInstance().getPaths(listAll);
    std::cout << "Running all " << paths.size() << " tests" << std::endl;
    return run(paths);
}


double TestSuite::run(const std::vector<std::string>& pathsToRun) {
    std::cout << "Running tests...\n\n";
    std::chrono::high_resolution_clock clock;
    const auto start = clock.now();

    std::vector<std::future<std::string>> futures;
    for(const auto& pathToRun: pathsToRun) {
        auto testCases = TestCaseFactory::getInstance().createTests(pathToRun);
        for(auto& testCase: testCases) {
            futures.emplace_back(std::async(_policy, [testCase, this]() {
                        bool success;
                        std::string output;
                        std::tie(success, output) = testCase->doTest();
                        if(!success) addFailure(testCase->getPath());
                        return testCase->getPath() + ":\n" + output;
                    }));
            _numTestsRun++;
        }
    }

    for(auto& f: futures) {
        std::cout << f.get();
    }

    std::cout << std::endl;
    for(auto failure: _failures) {
        std::cout << "Test " << failure << " failed." << std::endl;
    }

    return getElapsedSeconds(clock, start);
}
