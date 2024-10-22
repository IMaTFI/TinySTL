#ifndef ITERATOR_H
#define ITERATOR_H

#include<cstddef>

namespace tinystl{

// 五种迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag, public output_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

// 迭代器类型，所有自定义的迭代器都应继承这个类
template<typename Category,
         typename T,
         typename Distance = ptrdiff_t,
         typename Pointer = T*,
         typename Reference = T&>
struct iterator{
    using iterator_category = Category;
    using value_type = T;
    using difference_type = Distance;
    using pointer = Pointer;
    using reference = Reference;
};


// iterator_traits
template<typename Iterator>
struct iterator_traits{
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::typename;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
};

// 针对native pointer的偏特化
template<typename T>
struct iterator_traits<T*>{
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&; 
};

// 针对native pointer-to-const的偏特化
template<typename T>
struct iterator_traits<const T*>
{
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T*;
    using reference = const T&; 
};

template<typename Iterator>
auto iterator_category(const Iterator&)
->typename iterator_traits<Iterator>::iterator_category
{
    return iterator_traits<Iterator>::iterator_category();
}

// // 为什么要返回空指针？应用场景是什么？
// template<typename Iterator>
// auto value_type(const Iterator&)->typename iterator_traits<Iterator>::value_type*{
//     return static_cast<iterator_traits<Iterator>::value_type>(0);
// }

// template<typename Iterator>
// auto difference_type(const Iterator&)->typename iterator_traits<Iterator>::difference_type*{
//     return static_cast<iterator_traits<Iterator>::difference_type>(0);
// }


// 以下函数用于计算迭代器的距离

template<typename InputIterator>
auto __distance(InputIterator begin, InputIterator end, input_iterator_tag)
->typename iterator_traits<InputIterator>::difference_type
{
    using difference_type = typename iterator_traits<InputIterator>::difference_type;
    difference_type i = 0;
    while(begin != end)
    {
        ++begin;
        ++i;
    }
    return i;
}

template<typename RandomAccessIterator>
auto __distance(RandomAccessIterator begin, RandomAccessIterator end, random_access_iterator_tag)
->typename iterator_traits<RandomAccessIterator>::difference_type
{
    return end - begin;
}

// 将模板参数命名为能支持此操作的最低要求
template<typename InputIterator>
auto distance(InputIterator begin, InputIterator end)
->typename iterator_traits<InputIterator>::difference_type
{
    return __distance(begin, end, iterator_category(begin));
}


// 以下函数用于实现advance

template<typename InputIterator, typename Distance>
auto __advance(InputIterator &it, Distance n, input_iterator_tag)->void
{
    while(--n) ++it;
}

template<typename BidirectionalIterator, typename Distance>
auto __advance(BidirectionalIterator &it, Distance n, bidirectional_iterator_tag)->void
{
    if(n >= 0) while(--n) ++it;
    else while(++n) --it;
}

template<typename RandomAccessIterator, typename Distance>
auto __advance(RandomAccessIterator &it, Distance n, random_access_iterator_tag)->void
{
    it += n;
}

template<typename InputIterator, typename Distance>
auto advance(InputIterator &it, Distance n)->void
{
    __advance(it, n, iterator_category(it));
}

}

#endif