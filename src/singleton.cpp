#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

#include "threadGuard.h"

/*懒汉式单例模式的特点是在第一次请求时才创建对象，避免了程序启动时的资源浪费，但需要注意在多线程环境下的线程安全性*/
/**
 * @SuycxZMZ
 * @brief 静态局部变量 懒汉单例模式
 * @details 静态局部变量在函数首次调用时被初始化，并且在整个程序生命周期内保持存在。
 *          由于静态局部变量在 C++ 中具有线程安全的保证，
 *          因此无需显式使用互斥锁或原子操作来保护实例的创建过程。
 */
class Singleton
{
public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }
    ~Singleton()
    {
        std::cout << "Singleton destroyed" << std::endl;
    }
    void log(const std::string &msg)
    {
        std::cout << msg << std::endl;
    }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton()
    {
        std::cout << "Singleton created" << std::endl;
    }
};
#define LOG_SINGLETON_STATIC(logMsgFmt, ...)                        \
    do                                                              \
    {                                                               \
        Singleton &instance = Singleton::getInstance();             \
        char buffer[1024];                                          \
        snprintf(buffer, sizeof(buffer), logMsgFmt, ##__VA_ARGS__); \
        instance.log(std::string(buffer));                          \
    } while (0)

/**
 * @SuycxZMZ
 * @brief new 方法创建，饿汉模式
 * @details 特点：实现简单，线程安全，但可能造成内存浪费
 *          适用情况: 单例对象在程序运行过程中频繁被调用,
 *          饿汉式是最简单的一种单例模式实现方式，它在程序启动时就创建了单例对象，因此也被称为“急切创建”方式。
 *          这种方式的优点是实现简单且线程安全，因为这种方式在单例对象被使用之前就已经创建好了，
 *          因此不存在多线程环境下的竞争问题，但是缺点是如果该对象很少被使用，会造成内存浪费。
 *          饿汉式单例模式的实现方式一般是将单例模式定义为静态成员变量，并在类定义中就初始化它，
 *          这样单例对象就会在类装载的时候进行创建，在整个程序结束时按序销毁。
 */
class Singleton2
{
public:
    static Singleton2 *getInstance();
    void log(const std::string &msg) { std::cout << msg << std::endl; }
    ~Singleton2() { std::cout << "Singleton2 destroyed" << std::endl; }

private:
    Singleton2() { std::cout << "Singleton2 created" << std::endl; }
    Singleton2(const Singleton2 &) {}
    Singleton2 &operator=(const Singleton2 &) {}

private:
    static Singleton2 *m_instance;
};
Singleton2 *Singleton2::m_instance = new Singleton2();
Singleton2 *Singleton2::getInstance() { return m_instance; }

#define LOG_SINGLETON_STATIC2(logMsgFmt, ...)                       \
    do                                                              \
    {                                                               \
        Singleton2 *instance = Singleton2::getInstance();           \
        char buffer[1024];                                          \
        snprintf(buffer, sizeof(buffer), logMsgFmt, ##__VA_ARGS__); \
        instance->log(std::string(buffer));                         \
    } while (0);

/**
 * @SuycxZMZ
 * @brief new 方法创建 懒汉模式
 * @details 它在第一次访问单例对象时才进行创建
 *          延迟创建对象实例，避免了不必要的资源消耗，但是在多线程环境中线程不安全，需要加锁保证线程安全。
 *          不是线程安全的原因：竞态1 if (m_instance == nullptr)
 *                           竞态2 m_instance = new Singleton3();
 *
 *          由于多线程的关系，可能当我们在分配内存好了以后，还没来得急初始化成员变量，就进行线程切换，
 *          另外一个线程拿到所有权后，由于内存已经分配了，但是变量初始化还没进行，因此“使用成员变量”的相关值会发生不一致现象。
 *
 *          适用情况: 单例对象的创建和初始化过程比较耗时，而且在程序运行过程中可能并不总是需要使用该对象，
 *          对资源敏感时也不叫使用，如果线程安全没什么要求，也可以用。
 */
class Singleton3
{
public:
    static Singleton3 *getInstance()
    {
        if (m_instance == nullptr)
        {
            // 1, operator new  2, placement new
            m_instance = new Singleton3();
        }
        return m_instance;
    }

private:
    Singleton3() { std::cout << "Singleton3 created" << std::endl; }
    Singleton3(const Singleton3 &) {}
    Singleton3 &operator=(const Singleton3 &) {}
    static Singleton3 *m_instance;
};
Singleton3 *Singleton3::m_instance = nullptr;

/**
 * @SuycxZMZ
 * @brief new 懒汉 双锁
 * @details C++中的双检锁（Double-Checked Locking）实现单例模式是一种在多线程环境下延迟创建单例对象的方式，
 *          通过使用双重检查来提高性能。
 */
class Singleton4
{
public:
    static Singleton4 *getInstance()
    {
        if (m_instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr)
            {
                m_instance = new Singleton4();
            }
        }
        return m_instance;
    }
    void log(const std::string &msg) { std::cout << msg << std::endl; }

private:
    Singleton4() { std::cout << "Singleton4 created" << std::endl; }
    Singleton4(const Singleton4 &) {}
    Singleton4 &operator=(const Singleton4 &) {}
    static Singleton4 *m_instance;
    static std::mutex m_mutex;
};
Singleton4 *Singleton4::m_instance = nullptr;
std::mutex Singleton4::m_mutex;
#define LOG_SINGLETON_STATIC4(logMsgFmt, ...)                       \
    do                                                              \
    {                                                               \
        Singleton4 *instance = Singleton4::getInstance();           \
        char buffer[1024];                                          \
        snprintf(buffer, sizeof(buffer), logMsgFmt, ##__VA_ARGS__); \
        instance->log(std::string(buffer));                         \
    } while (0);


void testSingleton()
{
    for (int i = 0; i < 100; ++i)
    {
        LOG_SINGLETON_STATIC("say hello %d times thread:%llu line:%d", i, std::this_thread::get_id(), __LINE__);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        LOG_SINGLETON_STATIC2("say hello %d times thread:%llu line:%d", i, std::this_thread::get_id(), __LINE__);
    }
}

int main()
{
    testSingleton();
    threadGuard t1(testSingleton);
    threadGuard t2(testSingleton);
    return 0;
}