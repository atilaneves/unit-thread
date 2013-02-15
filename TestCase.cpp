#include "TestCase.hpp"

TestCase::TestCase():
    _failed(false) {

}

TestCase::~TestCase() {

}

bool TestCase::doTest() {
    setup();
    test();
    shutdown();
    return !_failed;
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
