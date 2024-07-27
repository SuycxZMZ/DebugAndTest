cmake_minimum_required(VERSION 3.15)

project(modernCpp)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGES} -g)

# 配置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)

# 头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
# 加载子目录
add_subdirectory(src)