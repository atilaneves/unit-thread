#include "unit_thread.hpp"
#include <string>
#include <list>
#include <thread>
#include <cassert>

struct Boolean: public TestCase {
    virtual void test() override {
        checkTrue(true);
        checkFalse(false);

        checkTrue(2 > 1);
        checkTrue(1 >= 1);
        checkTrue(2 < 3);
        checkFalse(2 > 3);
        checkFalse(3 >= 4);
    }
};
REGISTER_TEST(equals, Boolean)


UTEST(equals, Numbers) {
    checkEqual(1, 1);
    checkEqual(3.0, 3.0);
    checkNotEqual(2, 3);
    checkNotEqual(2.0, 2.1);
}


UTEST(equals, Strings) {
    checkEqual(std::string("bar"), std::string("bar"));
    checkEqual("baz", "baz");
    checkNotEqual("foo", "barr");
    checkEqual("foo", std::string("foo"));
    checkEqual(std::string("foo"), "foo");
}

struct HiddenTestClass: public TestCase {
    virtual void test() override {
        checkEqual(3, 1 + 2);
    }
};
HIDDEN_TEST(hidden, HiddenTestClass)


UTHIDDEN(hidden, hiddenTestFunction) {
    checkEqual(5, 2 + 3);
}

struct TestObject {
    const int _int;
    const std::string _string;
    TestObject(int i, const std::string& s):_int(i), _string(s) { }
    bool operator==(const TestObject& rhs) const { return _int == rhs._int && _string == rhs._string; }
    bool operator!=(const TestObject& rhs) const { return !(*this == rhs); }
    friend std::ostream& operator<<(std::ostream& ostream, const TestObject& obj);
};

std::ostream& operator<<(std::ostream& ostream, const TestObject& obj) {
    ostream << "i: " << obj._int << ", s: " << obj._string;
    return ostream;
}

struct Objects: public TestCase {
    virtual void test() override {
        checkEqual(TestObject(1, "foo"), TestObject(1, "foo"));
        checkNotEqual(TestObject(1, "foo"), TestObject(2, "foo"));
        checkNotEqual(TestObject(1, "foo"), TestObject(1, "bar"));
    }
};
REGISTER_TEST(equals, Objects)


struct Null: public TestCase {
    virtual void test() override {
        const TestObject* const nullObj = nullptr;
        checkNull(nullObj);
        const TestObject obj(7, "superman");
        checkNotNull(&obj);
    }
};
REGISTER_TEST(standalone, Null)


struct In: public TestCase {
    virtual void test() override {
        std::vector<int> primes{3, 5, 7, 11, 13};
        checkIn(primes, 3);
        checkNotIn(primes, 2);
        checkIn(primes, 11);

        std::list<int> evens{2, 6, 8};
        checkIn(evens, 2);
        checkNotIn(evens, 5);

        std::map<int, double> intToDouble{{1, 2.0}, {2, 4.0}};
        checkIn(intToDouble, std::make_pair(1, 2.0));
        checkNotIn(intToDouble, std::make_pair(1, 3.0));

        std::vector<std::string> strings{"foo", "bar"};
        checkIn(strings, "foo");
        checkNotIn(strings, "baz");
        checkIn(strings, "bar");
    }
};
REGISTER_TEST(containers, In)

struct VectorEquals: public TestCase {
    virtual void test() override {
        std::vector<int> nums1{1, 2, 5};
        std::vector<int> nums2{1, 2, 5};
        std::vector<int> nums3{1, 4, 5};
        checkEqual(nums1, nums2);
        checkEqual(nums2, nums1);
        checkNotEqual(nums1, nums3);
        checkNotEqual(nums2, nums3);
        checkNotEqual(nums3, nums1);
        checkNotEqual(nums3, nums2);
    }
};
REGISTER_TEST(containers, VectorEquals)

struct BeginEnd: public TestCase {
    virtual void test() override {
        checkTrue(HasBeginEnd<std::vector<int>>::value);
        checkFalse(HasBeginEnd<int>::value);
    }
};
REGISTER_TEST(traits, BeginEnd)

struct DirTest: public TestCase {
    virtual void test() override {
        checkTrue(true);
        checkNull(nullptr);
    }
};
REGISTER_TEST(parent/child/grandchild, DirTest)


UTEST(macro/function, funcTest) {
    checkEqual(1 + 3, 4);
}


UTCLASS(macro/klass, classTest) {
    virtual void setup() override {
        checkEqual(1, 1);
    }
    virtual void test() override {
        checkTrue(true);
    }
    virtual void shutdown() override {
        checkNotEqual(9, 8);
    }
};


class TakesAWhile: public TestCase {
    virtual void test() {
        checkEqual(1, 1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        checkNotEqual(1, 2);
    }
};

namespace {
    bool runSlowTests() {
        for(int i = 0; i < 4; ++i) {
            TestCaseFactory::getInstance().registerTest("while/" + std::to_string(i),
                                                        testCaseCreator<TakesAWhile>);
        }
        return true;
    }
    bool resultBogus = runSlowTests();
}
