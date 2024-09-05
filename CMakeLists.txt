cmake_minimum_required(VERSION 3.15)

project(modernCpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# 设置默认的构建类型为RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# 根据构建类型设置编译选项
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2 -DNDEBUG")

# 配置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)

# 加载子目录
add_subdirectory(src)
