cmake_minimum_required(VERSION 3.10)
project(number_game VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 如果是Windows，添加WIN32定义
if(WIN32)
    add_definitions(-DWIN32)
    if(MINGW)
        # MinGW下使用UTF-8编码
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=utf-8")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=utf-8")
    elseif(MSVC)
        # MSVC下使用UTF-8编码
        add_compile_options(/utf-8)
    endif()
endif()

# 设置输出可执行文件名称
set(EXECUTABLE_NAME "90-b2")

# 添加源文件
set(SOURCES
    pullze_main.cpp
    pullze_base.cpp
    pullze_console.cpp
    pullze_tools.cpp
    cmd_console_tools.cpp
)

# 添加头文件
set(HEADERS
    pullze.h
    cmd_console_tools.h
)

# 创建可执行文件
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

# 设置包含目录
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 为cmd_console_tools.cpp单独设置GBK编码
set_source_files_properties(cmd_console_tools.cpp PROPERTIES COMPILE_FLAGS "-fexec-charset=GBK -finput-charset=GBK")

# 如果是Windows，链接必要的库
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE winmm)
endif()

# 设置输出目录
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 安装规则
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin) 