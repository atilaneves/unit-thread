#ifndef OUTPUT_H
#define OUTPUT_H

#include <ostream>
#include <vector>

template<typename T>
std::ostream & operator<<(std::ostream &os, const std::vector<T>& vector) {
    os << "{";
    for(const auto& t: vector) {
        os << t << ", ";
    }
    os << "}";
    return os;
}


#endif // OUTPUT_H
