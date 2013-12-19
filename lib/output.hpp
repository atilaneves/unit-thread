#ifndef OUTPUT_H
#define OUTPUT_H

#include <ostream>
#include <vector>
#include <string>
#include <sstream>

namespace unit_thread_output {
    template<typename T>
    std::string convert(const T& t) {
        return std::to_string(t);
    }

    template<>
    std::string convert(const uint8_t& t);

    template<>
    std::string convert(const std::string& s);
}



template<typename T>
std::ostream & operator<<(std::ostream &os, const std::vector<T>& vector) {
    os << "{";
    bool first = true;
    for(const auto& t: vector) {
        if(!first) os << ", ";
        first = false;
        os << unit_thread_output::convert(t);
    }
    os << "}";
    return os;
}


#endif // OUTPUT_H
