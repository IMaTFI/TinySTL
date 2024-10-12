cmake_minimum_required(VERSION 3.10)
project(TinySTL VERSION 1.0)

# 设置 C++ 标准版本
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件搜索路径
include_directories(TinySTL)

# 添加可执行文件
add_executable(
    main
    test/main.cpp
)