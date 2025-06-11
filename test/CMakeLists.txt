cmake_minimum_required(VERSION 3.10)
project(CCT_TEST)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(test-cct test-cct.cpp ../cmd_console_tools.cpp)

# 包含头文件目录
target_include_directories(test-cct PRIVATE ${CMAKE_SOURCE_DIR}/..)

# 链接Windows库
if(WIN32)
    target_link_libraries(test-cct PRIVATE winmm)
endif()


