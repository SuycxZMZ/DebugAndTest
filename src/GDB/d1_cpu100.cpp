#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

int generateRandomNumber();

void threadFunc1() {
    long long cnt = 0;
    while (1) {
        std::cout << "thread1:" << cnt++ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int allsum(vector<int>& nums, int start) {
    for (int n : nums) start += n;
    return start;
}

void threadFunc2() {
    vector<int> vec(10000);
    for (int i = 0; i < 10000; ++i) {
        vec[i] = generateRandomNumber();
    }
    while (1) {
        vec[generateRandomNumber()] = generateRandomNumber();
        std::cout << "thread2:" << allsum(vec, 0) << endl;
    }
}


// 全局随机数生成器和分布对象
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis;

// 初始化分布对象的函数
void initializeRandomNumberGenerator(int min, int max) {
    dis = std::uniform_int_distribution<>(min, max);
}

// 生成[min, max]区间内的随机整数
int generateRandomNumber() {
    return dis(gen);
}

int main() {

    initializeRandomNumberGenerator(0, 2000);

    // std::thread t1(threadFunc1);
    std::thread t2(threadFunc2);

    // t1.join();
    t2.join();


    return 0;
}