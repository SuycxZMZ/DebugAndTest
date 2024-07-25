#include <iostream>
#include <cmath>
#include <thread>
#include <vector>

// 定义一个函数执行 CPU 密集型任务
void cpuIntensiveTask() {
    double result = 0.0;
    while (true) {
        for (int i = 0; i < 1000000; i++) {
            result += std::sin(i) * std::cos(i);
        }
    }
}

int main() {
    unsigned int num_threads = 2;
    std::cout << "启动 " << num_threads << " 个线程." << std::endl;

    std::vector<std::thread> threads;

    // 创建多个线程，每个核心一个线程
    for (unsigned int i = 0; i < num_threads; i++) {
        threads.emplace_back(cpuIntensiveTask);
    }

    // 等待所有线程结束 (理论上这些线程不会结束，因为它们处于无限循环中)
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
