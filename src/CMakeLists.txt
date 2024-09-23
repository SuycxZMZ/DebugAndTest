# 遍历源文件列表
file(GLOB SOURCE_FILES "*.cpp"
  ./Leetcode/*.cpp
  ./DPatten/*.cpp
  ./ThreadCommunication/*.cpp
  ./ACM_INOUT/*.cpp
  ./Mem/*.cpp
  ./GDB/*.cpp
  ./BasicContainer/*.cc
  ./HW0717/*.cc)
    
# 编译每个源文件为可执行文件
foreach(source_file ${SOURCE_FILES})
    # 提取文件名（不含路径和扩展名）
    get_filename_component(executable_name ${source_file} NAME_WE)
    # 添加可执行文件
    add_executable(${executable_name} ${source_file})
    # 指定链接文件
    target_link_libraries(${executable_name} pthread)
endforeach()
