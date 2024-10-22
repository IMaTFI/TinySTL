#include<iostream>
#include<chrono>
#include<memory>
#include<algorithm>
#include<vector>

#include"allocator.h"

int main(){
    tinystl::allocator<std::string> as;
    auto p = as.allocate(10);
    as.construct(p, 100, 's');
    std::cout<<*p<<std::endl;
    std::cout<<sizeof(std::string)<<std::endl;
    as.deallocate(p);
    return 0;
}