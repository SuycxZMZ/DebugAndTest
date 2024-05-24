#ifndef THREADGUARD_H
#define THREADGUARD_H

#include <thread>
#include <functional>

class threadGuard {
public:
    template<typename Function, typename... Args>
    explicit threadGuard(Function&& func, Args&&... args) {
        // 使用 std::forward 将参数完美转发给线程函数
        thread_ = std::thread(std::forward<Function>(func), std::forward<Args>(args)...);
    }       

    ~threadGuard() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    // 防止拷贝和移动
    threadGuard(const threadGuard&) = delete;
    threadGuard& operator=(const threadGuard&) = delete;
    threadGuard(threadGuard&&) = delete;
    threadGuard& operator=(threadGuard&&) = delete;
private:
    std::thread thread_;
};

#endif // THREADGUARD_H