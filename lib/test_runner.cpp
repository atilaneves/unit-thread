#include "test_runner.hpp"
#include "unit_thread.hpp"
#include "console.hpp"
#include <iostream>
#include <tuple>
#include <boost/program_options.hpp>


namespace options = boost::program_options;


static options::options_description getOptionsDesc() {
    options::options_description desc("Usage: test <options> testcase1 testcase2 ...\n"
                                      "(each must either be a full testcase path or end with '/'");
    desc.add_options()
        ("help,h", "produce help message")
        ("list,l", "list avaiable test cases")
        ("single,s", "run in a single thread");
    return desc;
}

static options::variables_map getOptVars(int argc, char* argv[], const options::options_description& desc) {
    options::variables_map vars;
    options::store(options::parse_command_line(argc, argv, desc), vars);
    options::notify(vars);
    return vars;
}

static void printPaths() {
    std::cout << "Test cases:\n\n";
    for(const auto& path: TestCaseFactory::getInstance().getPaths()) {
        std::cout << path << std::endl;
    }
    std::cout << std::endl;
}

static constexpr int CARRY_ON = -1;
//returns err_code, policy
static std::tuple<int, std::launch> handleOptions(int argc, char* argv[]) {
    const auto desc = getOptionsDesc();
    std::launch policy = std::launch::deferred;
    try {
        const auto vars = getOptVars(argc, argv, desc);

        if(vars.count("help")) {
            std::cout << desc;
            return std::make_tuple(0, policy);
        }
        if(vars.count("list")) {
            printPaths();
            return std::make_tuple(0, policy);
        }

        policy = vars.count("single") ? std::launch::deferred : std::launch::async;
    } catch(options::error&) {
        std::cerr << "Error parsing options" << std::endl;
        std::cout << desc;
        return std::make_tuple(1, policy);
    }

    return std::make_tuple(CARRY_ON, policy);
}

static std::vector<std::string> getTestsToRun(int argc, char *argv[], int firstTestIndex) {
    std::vector<std::string> testsToRun;
    for(int i = firstTestIndex; i < argc; ++i) {
        testsToRun.emplace_back(argv[i]);
    }
    return testsToRun;
}

static double runTests(int argc, char *argv[], TestSuite& testSuite, int firstTestIndex) {
    return argc > firstTestIndex ? testSuite.run(getTestsToRun(argc, argv, firstTestIndex)) : testSuite.run();
}

int runTests(int argc, char* argv[]) {
    const auto optionTuple = handleOptions(argc, argv);
    const auto rc = std::get<0>(optionTuple);
    if(rc != CARRY_ON) {
        return rc;
    }

    const auto policy = std::get<1>(optionTuple);
    const int firstTestIndex = policy == std::launch::deferred ? 2 : 1; //option means args further down
    TestSuite testSuite(policy);
    const auto elapsed = runTests(argc, argv, testSuite, firstTestIndex);

    if(!testSuite.getNumTestsRun()) {
        std::cerr << "Did not run any tests!!!\n";
        return 1;
    }

    std::cout << "\nTime taken: " << elapsed << " seconds " << std::endl;
    std::cout << testSuite.getNumTestsRun() << " test(s) run, " <<
                 testSuite.getNumFailures() << " failed.\n\n";

    if(testSuite.getNumFailures()) {
        std::cerr << ESC_RED << "Unit tests failed!" << ESC_CANCEL << "\n\n";
        return 1; //oops
    }

    std::cout << ESC_GREEN << "\nOK!\n\n" << ESC_CANCEL;
    return 0;
}
