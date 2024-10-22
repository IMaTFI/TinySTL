// 定义construct和destroy

#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include"utility.h"

namespace tinystl{

template<typename T, typename ...Args>
auto construct(T *ptr, Args &&...args)->void{
    ::new(ptr) T(tinystl::forward<Args>(args)...);
}

template<typename T>
auto destroy_one(T *ptr, std::true_type)->void{}

template<typename T>
auto destroy_one(T *ptr, std::false_type)->void{
    ptr->~T();
}

template<typename T>
auto destroy(T *ptr)->void{
    destroy_one(ptr, std::is_trivially_destructible<T>());
}



}

#endif