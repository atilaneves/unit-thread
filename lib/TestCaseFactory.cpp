#include "TestCaseFactory.hpp"
#include <boost/algorithm/string.hpp>
#include <iostream>


TestCaseFactory& TestCaseFactory::getInstance() {
    static TestCaseFactory instance;
    return instance;
}


bool TestCaseFactory::registerTest(std::string path, TestCaseCreator creator, bool hidden) {
    return _pathToTestInfo.insert(std::make_pair(path, TestInfo(creator, hidden))).second;
}


const std::vector<std::string> TestCaseFactory::getPaths(bool listAll) const {
    std::vector<std::string> paths;
    for(const auto& pathToInfo: _pathToTestInfo) {
        if(!pathToInfo.second.hidden || listAll) paths.emplace_back(pathToInfo.first);
    }
    return paths;
}


static bool isToRun(const std::string& testPathToRun, const std::string& testPath) {
    /**
     * 'Folder' paths end with '/' and match everything in them, foo/bar/ gets foo/bar/baz and foo/bar/boo
     * 'Exact' paths end with anything else and only match exactly
     */
    if(boost::ends_with(testPathToRun, "/")) {
        return boost::starts_with(testPath, testPathToRun);
    } else {
        return testPath == testPathToRun;
    }
}


auto TestCaseFactory::createTests(const std::string& testPathToRun) const -> TestCases {
    TestCases testCases;

    for(const auto& pathToCreator: _pathToTestInfo) {
        const auto& testPath = pathToCreator.first;

        if(!isToRun(testPathToRun, testPath)) continue;

        if(_pathToTestInfo.find(testPath) == _pathToTestInfo.end()) {
            std::cerr << "Could not create test case " << testPath <<
                         " for test path " << testPath << std::endl;
            return TestCases{};
        }

        testCases.emplace_back(std::make_shared<TestCaseWithPath>(testPath, createTest(testPath)));
    }

    return testCases;
}


TestCase* TestCaseFactory::createTest(const std::string& path) const {
    return _pathToTestInfo.at(path).creator();
}
