#ifndef TYPETRAITS_H
#define TYPETRAITS_H


#include <type_traits>
#include <vector>
#include <list>
#include <map>

template<typename T>
struct HasBeginEnd {
    static const bool value = false;
};

template<typename T, typename A>
struct HasBeginEnd<std::vector<T, A>> {
    static const bool value = true;
};

template<typename T, typename A>
struct HasBeginEnd<std::list<T, A>> {
    static const bool value = true;
};

template<typename K, typename T, typename C, typename A>
struct HasBeginEnd<std::map<K, T, C, A>> {
    static const bool value = false;
};


#endif // TYPETRAITS_H
