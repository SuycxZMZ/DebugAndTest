#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>

const int BUFFER_SIZE = 10;
std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;

/**
 * @brief 生产者
 * */
void producer() 
{
    for (int i = 0; i < 1000; ++i) {
        // 加锁生产
        {
            std::unique_lock<std::mutex> lock(mtx);
            // 如果buffer满了，就释放锁，让消费者再消费一会，当前线程继续阻塞
            cv.wait(lock, [](){return buffer.size() < BUFFER_SIZE;});
            // wait成功返回，可以生产了
            buffer.push(i);
        }
        // 通知阻塞在wait上的消费者线程
        cv.notify_all();
        std::cout << "producer : " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

/**
 * @brief 消费者
 * */
void consumer() 
{
    for (int i = 0; i < 500; ++i) {
        // 加锁取货物
        int ret = -1;
        {
            std::unique_lock<std::mutex> lock(mtx);
            // 等待buffer非空，条件满足之后上锁取货
            cv.wait(lock, [](){return !buffer.empty();});
            // 已经从wait返回，说明buffer非空且已经拿到了锁
            ret = buffer.front();
            buffer.pop();
        }
        cv.notify_all();
        std::cout << "consumer : " << ret << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(2));
    }
}

int main() 
{
    std::thread t1(producer);
    std::thread t2(consumer);
    std::thread t3(consumer);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
