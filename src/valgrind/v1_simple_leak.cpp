// memory_leak_example.cpp
#include <iostream>

int main() {
    int* p = new int[10]; // 分配内存但未释放
    p[5] = 100;  // 使用分配的内存
    std::cout << "p[5] = " << p[5] << std::endl;
    // 忘记释放内存
    // delete[] p;  // 正确做法是取消注释此行
    return 0;
}
