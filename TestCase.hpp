#ifndef TESTCASE_HPP_
#define TESTCASE_HPP_

#include <functional>
#include <algorithm>
#include <iostream>


class TestCase {
public:

    TestCase();
    virtual ~TestCase();
    bool doTest();

protected:

    template<typename T, typename U>
    bool verifyEqual(const T t, const U u) { return t == u ? true : fail(); }

    template<typename T, typename U>
    bool verifyNotEqual(const T t, const U u) { return t != u ? true : fail(); }

    template<typename T>
    bool verifyNull(const T* t) { return t == nullptr ? true : fail(); }

    template<typename T>
    bool verifyNotNull(const T* t) { return t != nullptr ? true : fail(); }

    template<typename C>
    bool verifyIn(const C& container, const typename C::value_type& obj) {
        return std::find(container.cbegin(), container.cend(), obj) != container.end() ? true : fail(); 
    }

    template<typename C>
    bool verifyNotIn(const C& container, const typename C::value_type& obj) {
        return std::find(container.cbegin(), container.cend(), obj) == container.cend() ? true : fail(); 
    }

    bool verifyTrue(bool condition);
    bool verifyFalse(bool condition);

    virtual void test() = 0;
    virtual void setup()    { }
    virtual void shutdown() { }

private:

    bool _failed;

    bool fail();
};

typedef std::function<TestCase*()> TestCaseCreator;

#endif
