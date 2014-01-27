#ifndef MACROS_HPP_
#define MACROS_HPP_
#endif

#include "output.hpp"


#define REGISTER_TEST(path, klass) \
    namespace { \
        bool result_##klass = TestCaseFactory::getInstance().registerTest((#path"/"#klass), \
                                                                          testCaseCreator<klass>); \
    }

#define HIDDEN_TEST(path, klass) \
    namespace { \
        bool result_##klass = TestCaseFactory::getInstance().registerTest((#path"/"#klass), \
                                                                          testCaseCreator<klass>, \
                                                                          true); \
    }


#define UTEST(path, klass) \
    namespace { \
        struct klass: public TestCase { \
            virtual void test() override; \
        }; \
        REGISTER_TEST(path, klass) \
    } \
    void klass::test()


#define UTHIDDEN(path, klass) \
    namespace { \
        struct klass: public TestCase { \
            virtual void test() override; \
        }; \
        HIDDEN_TEST(path, klass) \
    } \
    void klass::test()


#define UTCHILD(path, klass, parent) \
        class klass; \
        REGISTER_TEST(path, klass) \
        class klass: public parent

#define UTHIDDEN_CHILD(path, klass, parent) \
        class klass; \
        HIDDEN_TEST(path, klass) \
        class klass: public parent


#define UTCLASS(path, klass) UTCHILD(path, klass, TestCase)
#define UTHIDDEN_CLASS(path, klass) UTHIDDEN_CHILD(path, klass, TestCase)

#define checkEqual(value, expected) \
    { \
        if(!verifyEqual((value), (expected))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value '" #value "' (" << (value) << \
                ") is not the expected '" #expected "' (" << (expected) << ")" << std::endl; \
    }


#define checkNotEqual(value, expected)    \
    { \
        if(!verifyNotEqual((value), (expected))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value "' (" << (value) << \
                ") is equal to the expected '" #expected "' (" << (expected) << ")" <<std::endl; \
    }


#define checkNull(value) \
    { \
        if(!verifyNull((value)))                        \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                      " Value " #value " is not null " << std::endl; \
    }


#define checkNotNull(value) \
    { \
        if(!verifyNotNull((value))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                      " Value " #value " is null " << std::endl; \
    }


#define checkIn(container, value) \
    { \
        if(!verifyIn((container), (value))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value " not in container " << #container << std::endl; \
    }


#define checkNotIn(container, value) \
    { \
        if(!verifyNotIn((container), (value))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value " in container " << #container << std::endl; \
    }


#define checkTrue(value) \
    { \
        if(!verifyTrue((value))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is not true" << std::endl; \
    }


#define checkFalse(value) \
    { \
        if(!verifyFalse((value))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is not false" << std::endl; \
    }
