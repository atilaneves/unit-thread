#include "TestCase.hpp"
#include <iostream>

TestCase::TestCase():
    _output(""), _failed(false) {

}

TestCase::~TestCase() {

}

auto TestCase::doTest() -> Tuple{
    setup();
    test();
    shutdown();
    return std::make_tuple(!_failed, _output.str());
}


bool TestCase::verifyTrue(bool condition) {
    return condition || fail();
}


bool TestCase::verifyFalse(bool condition) {
    return !condition || fail();
}


bool TestCase::fail() {
    _failed = true;
    return false;
}
