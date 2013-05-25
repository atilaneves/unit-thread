#ifndef TESTCASE_HPP_
#define TESTCASE_HPP_

#include "TypeTraits.hpp"
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <tuple>

class TestCase {
public:

    using Tuple = std::tuple<bool, std::string>;

    TestCase();
    virtual ~TestCase();
    Tuple doTest();

protected:

    std::ostringstream _output;

    template<typename T, typename U>
    bool verifyEqual(const T t, const U u) { return t == u || fail(); }

    template<typename C1, typename C2,
             //         typename std::enable_if<true>::type>
             typename std::enable_if<HasBeginEnd<C1>::value && HasBeginEnd<C2>::value>::type>
    bool verifyEqual(const C1& c1, const C2& c2, const C1& c12) {
        return std::equal(std::begin(c1), std::end(c1), std::begin(c2));
    }

    template<typename T, typename U>
    bool verifyNotEqual(const T t, const U u) { return t != u || fail(); }

    template<typename T>
    bool verifyNull(const T* t) { return t == nullptr || fail(); }

    template<typename T>
    bool verifyNotNull(const T* t) { return t != nullptr || fail(); }

    template<typename C>
    bool verifyIn(const C& container, const typename C::value_type& obj) {
        return std::find(container.cbegin(), container.cend(), obj) != container.end() || fail();
    }

    template<typename C>
    bool verifyNotIn(const C& container, const typename C::value_type& obj) {
        return std::find(container.cbegin(), container.cend(), obj) == container.cend() || fail();
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


#endif
