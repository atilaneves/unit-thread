#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <vector>
#include <string>
#include <future>

#include "TestCase.hpp"
#include "TestCaseFactory.hpp"



class TestSuite {
public:


    TestSuite(std::launch policy = std::launch::async);
    /**
     * Returns the elapsed time in seconds
     */
    double run();
    double run(const std::vector<std::string>& testsToRun);

    int getNumTestsRun() const { return _numTestsRun; }
    int getNumFailures() const { return _failures.size(); }

private:

    const std::launch _policy;
    std::vector<std::string> _failures;
    size_t _numTestsRun;

    void addFailure(const std::string& name);
};


#endif
