/**
 * @file c20_Coroutines.cpp
 * @author suycx
 * @brief co_await：用于在协程中挂起等待某个值。
 *        co_yield：用于在协程中生成一个值并挂起。
 *        co_return：用于在协程中返回一个值并完成。
 *        并发打印 1 -- 1000
 * @version 0.1
 * @date 2024-07-30
 * 
 */
#include <iostream>
#include <coroutine>

// Custom generator type
// 用于包装协程的生成器功能
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    Generator(handle_type h) : coro(h) {}
    handle_type coro;

    ~Generator() {
        if (coro) coro.destroy();
    }

    struct promise_type {
        int current_value;

        auto get_return_object() {
            return Generator{handle_type::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    bool move_next() {
        coro.resume();
        return !coro.done();
    }

    int current_value() const {
        return coro.promise().current_value;
    }
};

// Coroutine function that generates numbers from 1 to 1000
// 每次调用co_yield时，协程会挂起并返回一个值
Generator generate_numbers(const char* name, int start) {
    for (int i = start; i <= 1000; i += 2) {
        std::cout << name << ": " << i << "\n";
        co_yield i;
    }
}

int main() {
    auto gen1 = generate_numbers("Coroutine 1", 1);
    auto gen2 = generate_numbers("Coroutine 2", 2);

    bool move_next1 = true;
    bool move_next2 = true;

    // 使用 move_next() 交替恢复两个协程并检查是否完成。
    while (move_next1 || move_next2) {
        if (move_next1) {
            move_next1 = gen1.move_next();
        }
        if (move_next2) {
            move_next2 = gen2.move_next();
        }
    }

    return 0;
}

