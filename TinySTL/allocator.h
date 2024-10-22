#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include<cstddef>
#include"construct.h"

namespace tinystl{

template<typename T>
class allocator{
public:
    using value = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    static auto allocate(size_type n=1)->pointer;
    static auto deallocate(pointer ptr, size_type n=0)->void;

    // 只有这样一个难道不够吗？
    // 从性能上考虑，所有调用都是inline
    // 并且都是编译期间可以完成的工作
    template<typename ...Args>
    static auto construct(pointer ptr, Args &&...args)->void;

    static auto destroy(pointer ptr)->void;
};

template<typename T>
auto allocator<T>::allocate(size_type n)->pointer{
    // n为0的情况交由::operator new去考虑
    return static_cast<T*>(::operator new(sizeof(T)*n));
}

template<typename T>
auto allocator<T>::deallocate(T* ptr, size_t n)->void{
    ::operator delete(ptr);
}

template<typename T>
template<typename ...Args>
auto allocator<T>::construct(pointer ptr, Args &&...args)->void{
    tinystl::construct(ptr, tinystl::forward<Args>(args)...);
}

template<typename T>
auto allocator<T>::destroy(pointer ptr)->void{
    tinystl::destroy(ptr);
}


}

#endif