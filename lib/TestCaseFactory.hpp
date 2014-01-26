#ifndef TESTCASEFACTORY_HPP_
#define TESTCASEFACTORY_HPP_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "TestCase.hpp"


typedef std::function<TestCase*()> TestCaseCreator;
template<class T> TestCase* testCaseCreator() { return new T; }

struct TestInfo {
    TestCaseCreator creator;
    bool hidden;
    TestInfo(TestCaseCreator c, bool h):creator{c}, hidden{h} {}
};


class TestCaseFactory {
public:

    struct TestCaseWithPath;
    using TestCases = std::vector<std::shared_ptr<TestCaseWithPath>>;

    static TestCaseFactory& getInstance();
    bool registerTest(std::string path, TestCaseCreator creator, bool hidden = false);
    const std::vector<std::string> getPaths(bool listAll = true) const;
    TestCases createTests(const std::string& testPathToRun) const;

    struct TestCaseWithPath {
        const std::string _path;
        std::shared_ptr<TestCase> const _testCase;
        TestCaseWithPath(const std::string& p, TestCase* t):_path(p), _testCase(t) { }
        const std::string& getPath() const { return _path; }
        TestCase::Tuple doTest() { return _testCase->doTest(); }
    };

private:

    std::map<std::string, TestInfo> _pathToTestInfo;

    TestCase* createTest(const std::string& path) const;

    TestCaseFactory() { }
    TestCaseFactory(const TestCaseFactory&);
    TestCaseFactory& operator=(const TestCaseFactory&);
};



#endif
