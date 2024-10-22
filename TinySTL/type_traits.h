#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

namespace tinystl{

// 利用类模板的部分特化
template<typename T> struct remove_reference {using type = T;};
template<typename T> struct remove_reference<T&> {using type = T;};
template<typename T> struct remove_reference<T&&> {using type = T;};

}

#endif