#ifndef UTILITY_H
#define UTILITY_H

#include"type_traits.h"

namespace tinystl{

template<typename T>
typename tinystl::remove_reference<T>::type&& move(T &&t){
    return static_cast<typename tinystl::remove_reference<T>::type&&>(t);
}

template<typename T>
T&& forward(typename tinystl::remove_reference<T>::type& t){
    return static_cast<T&&>(t);
}

template<typename T>
T&& forward(typename tinystl::remove_reference<T>::type&& t){
    return static_cast<T&&>(t);
}

}

#endif