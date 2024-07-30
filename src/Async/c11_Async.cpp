/**
 * @file c11_Async.cpp
 * @author suycx
 * @brief 现代C++的基本异步API测试
 * @version 0.1
 * @date 2024-07-30
 * 
 */
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void asyncWork_1(std::promise<int> prom) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    prom.set_value(42); // Set the result of the work
}

int asyncWork() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    return 42; // Return the result of the work
}

void test_future_promise() {
    // Create a promise and get its future
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    // Start a thread to perform the asynchronous work
    std::thread t(asyncWork_1, std::move(prom));

    // Do other work while waiting for the result
    std::cout << "Waiting for the result..." << std::endl;

    // Get the result (this will block until the result is ready)
    int result = fut.get();
    std::cout << "The result is: " << result << std::endl;

    // Join the thread
    t.join();
}

void test_future_async() {
    // Launch asynchronous work using std::async
    // std::launch::async: 任务会在一个新的线程中立即启动。
    // std::launch::deferred: 任务会延迟到std::future::get()或者std::future::wait()被调用时才开始执行。
    // 默认策略: 系统在运行时自动选择策略
    std::future<int> fut = std::async(std::launch::async, asyncWork);

    // Do other work while waiting for the result
    std::cout << "Waiting for the result..." << std::endl;

    // Get the result (this will block until the result is ready)
    int result = fut.get();
    std::cout << "The result is: " << result << std::endl;
}

int main() {
    std::cout << " ---------------- test future -- promise ---------------- \n";
    test_future_promise();

    std::cout << " ---------------- test future -- Async   ---------------- \n";
    test_future_async();
    return 0;
}
