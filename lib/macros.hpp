#ifndef MACROS_HPP_
#define MACROS_HPP_
#endif


#define TEST(...) __VA_ARGS__


#define REGISTER_TEST(path, klass) \
    namespace { \
        bool result_##klass = TestCaseFactory::getInstance().registerTest((path), testCaseCreator<klass>); \
    }


#define SIMPLE_TEST(path, klass, code) \
    namespace { \
        struct klass: public TestCase { \
            virtual void test() { \
                code \
            } \
        }; \
    } \
    REGISTER_TEST(#path"/"#klass, klass)


#define checkEqual(value, expected) \
    { \
        if(!verifyEqual((value), (expected))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is not the expected " #expected << std::endl; \
    }


#define checkNotEqual(value, expected)    \
    { \
        if(!verifyNotEqual((value), (expected))) \
            _output << "    " << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is equal to the expected " #expected << std::endl; \
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
