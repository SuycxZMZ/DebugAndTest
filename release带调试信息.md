# 调试不带调试信息的程序

一般release版本开启最大优化 O2或O3， -DNDEBUG选项是禁用断言用的

debug版本包含，但是比较慢，占用空间也比较大

如果想都要，那么编译为 RelWithDebInfo 提供优化和调试信息同样加上选项 -O2 -g -DNDEBUG

但是包含调试信息，可能软件被破解，且代码已经被优化过，可能执行流程与原本的不太一样

## 设置默认的构建类型为RelWithDebInfo

    if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
    endif()

可以通过将调试信息与可执行文件分离来实现这一点。这样，可以在上线时发布优化后的可执行文件，并在需要调试时使用调试信息文件。这通常通过使用objcopy工具来实现，该工具可以将调试信息从可执行文件中分离出来并存储到一个单独的文件中。

使用objcopy分离调试信息

    objcopy --only-keep-debug bin/main bin/main.debug

    objcopy --strip-debug bin/main

    objcopy --add-gnu-debuglink=bin/main.debug bin/main

objcopy --only-keep-debug bin/main bin/main.debug：从可执行文件main中提取调试信息并保存到main.debug文件中。

objcopy --strip-debug bin/main：从可执行文件main中删除调试信息。

objcopy --add-gnu-debuglink=bin/main.debug bin/main：将调试信息文件链接回可执行文件main，以便调试器知道在哪里找到调试信息。

## 运行时调试

在一个终端中
    ./bin/main
另一个终端调试：gdb会自动查找和加载与可执行文件关联的调试信息文件（bin/main.debug），因为使用了objcopy --add-gnu-debuglink命令将调试信息文件链接回了可执行文件。

    gdb ./bin/main

直接调试的话就 gdb ./bin/main

如果没有链接调试信息，则在gdb开启文件之后 显示指定
    (gdb) symbol-file bin/main.debug