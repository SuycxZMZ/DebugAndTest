#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 10;
std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;

void producer() 
{
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return buffer.size() < BUFFER_SIZE; });
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;
        lock.unlock();
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer() 
{
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !buffer.empty(); });
        int val = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << val << std::endl;
        lock.unlock();
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}

int main() 
{
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
