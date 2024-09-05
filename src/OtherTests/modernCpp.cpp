//
// Created by yuan su on 24-4-24.
//
//======================================================================
using namespace std;
#include <iostream>
#include <functional>
namespace example1
{
    // foo.h
    #ifdef __cplusplus
    extern "C" {
    #endif

    int add(int x, int y);

    #ifdef __cplusplus
    }
    #endif

    // foo.c
    int add(int x, int y) {
        return x+y;
    }

    void test_exmaple()
    {
        [out = std::ref(std::cout << "Result from C code: " << add(1, 2))](){
            out.get() << ".\n";
        }();
    }
}
//======================================================================
// nullptr_example
#include <iostream>
#include <type_traits>

namespace exmaple2
{
    void foo(char *);
    void foo(int);
    void foo(char *) {
        std::cout << "foo(char*) is called" << std::endl;
    }
    void foo(int i) {
        std::cout << "foo(int) is called" << std::endl;
    }
    void test_exmaple()
    {
        if (std::is_same<decltype(NULL), decltype(0)>::value)
            std::cout << "NULL == 0" << std::endl;
        if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
            std::cout << "NULL == (void *)0" << std::endl;
        if (std::is_same<decltype(NULL), std::nullptr_t>::value)
            std::cout << "NULL == nullptr" << std::endl;

        foo(0);          // 调用 foo(int)
        // foo(NULL);    // 该行不能通过编译
        foo(nullptr);    // 调用 foo(char*)
    }
}
//======================================================================
// constexpr_example
#include <iostream>

namespace exmaple3
{
    #define LEN 10

    int len_foo() {
        int i = 2;
        return i;
    }
    constexpr int len_foo_constexpr() {
        return 5;
    }

    constexpr int fibonacci(const int n) {
        return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
    }
    void test_example()
    {
        char arr_1[10];                      // 合法
        char arr_2[LEN];                     // 合法

        int len = 10;
        // char arr_3[len];                  // 非法

        const int len_2 = len + 1;
        constexpr int len_2_constexpr = 1 + 2 + 3;
        // char arr_4[len_2];                // 非法
        char arr_4[len_2_constexpr];         // 合法

        // char arr_5[len_foo()+5];          // 非法
        char arr_6[len_foo_constexpr() + 1]; // 合法

        std::cout << fibonacci(10) << std::endl;
        // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    }
}

//======================================================================
// initializer_list_example,结构化绑定
#include <initializer_list>
#include <vector>
#include <iostream>
#include <tuple>

namespace example4
{
    class MagicFoo {
        public:
        std::vector<int> vec;
        MagicFoo(std::initializer_list<int> list) {
            for (std::initializer_list<int>::iterator it = list.begin();
                it != list.end(); ++it)
                vec.push_back(*it);
        }

        public:
        void foo(std::initializer_list<int> list) {
            for (std::initializer_list<int>::iterator it = list.begin();
                it != list.end(); ++it) vec.push_back(*it);
        }
    };

    std::tuple<int, double, std::string> f()
    {
        return std::make_tuple(1, 2.3, "456");
    }

    void test_example()
    {
        // after C++11
        MagicFoo magicFoo = {1, 2, 3, 4, 5};
        magicFoo.foo({6,7,8,9});
        std::cout << "magicFoo: ";
        for (std::vector<int>::iterator it = magicFoo.vec.begin();
            it != magicFoo.vec.end(); ++it)
            std::cout << *it << ' ';
        cout << endl;
        auto [x, y, z] = f();
        std::cout << x << ", " << y << ", " << z << std::endl;
    }
}

//======================================================================
//enumeration class_example
namespace example5
{
    enum class new_enum : unsigned int
    {
        value1,
        value2,
        value3 = 100,
        value4 = 100
    };

    template<typename T>
    std::ostream& operator<<(
        typename std::enable_if<std::is_enum<T>::value,
            std::ostream>::type& stream, const T& e)
    {
        return stream << static_cast<typename std::underlying_type<T>::type>(e);
    }

    void test_example()
    {
        if (new_enum::value3 == new_enum::value4)
        {
            // 枚举类型后面使用了冒号及类型关键字来指定枚举中枚举值的类型，
            // 这使得我们能够为枚举赋值（未指定时将默认使用 int）
            // 会输出
            std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
        }

        std::cout << new_enum::value3 << std::endl;
    }
}

//======================================================================
// Lambda_example, 函数对象包装器, std::function_example
// 语法 ：
/*
    [捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型
    {
        // 函数体
    }
*/

// 说明
//*********************

// 所谓捕获列表，其实可以理解为参数的一种类型，
// Lambda 表达式内部函数体在默认情况下是不能够使用函数体外部的变量的，
// 这时候捕获列表可以起到传递外部数据的作用。根据传递的行为，捕获列表也分为以下几种：
// 按值，按引用，隐式捕获，表达式捕获

//*********************
#include <iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move
#include <functional>
namespace example6
{
    // 1,按值
    void lambda_value_capture()
    {
        int value = 1;
        auto copy_value = [value] () {
            return value;
        };
        value = 100;
        auto stored_value = copy_value();
        std::cout << "lambda_value_capture " << "stored_value = " << stored_value << std::endl;
        // 这时, stored_value == 1, 而 value == 100.
        // 因为 copy_value 在创建时就保存了一份 value 的拷贝
    }
    // 2,引用
    void lambda_reference_capture()
    {
        int value = 1;
        auto copy_value = [&value] {
            return value;
        };
        value = 100;
        auto stored_value = copy_value();
        std::cout << "lambda_reference_capture " << "stored_value = " << stored_value << std::endl;
        // 这时, stored_value == 100, value == 100.
        // 因为 copy_value 保存的是引用
    }
    // 3, [&] 引用捕获, 让编译器自行推导引用列表
    // [=] 值捕获, 让编译器自行推导值捕获列表

    // 4, 表达式捕获
    /*
        上面提到的值捕获、引用捕获都是已经在外层作用域声明的变量，
        因此这些捕获方式捕获的均为左值，而不能捕获右值。
        C++14 给与了我们方便，允许捕获的成员用任意的表达式进行初始化，
        这就允许了右值的捕获， 被声明的捕获变量类型会根据表达式进行判断，判断方式与使用 auto 本质上是相同的：
    */
    void lambda_expression_capture()
    {
        // important 是一个独占指针，是不能够被 "=" 值捕获到，这时候我们可以将其转移为右值，在表达式中初始化
        auto important = std::make_unique<int>(1);
        auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
            return x+y+v1+(*v2);
        };
        std::cout << "lambda_expression_capture : " << add(3,4) << std::endl;
    }
    // 5,泛型Lambda
    // 从 C++14 开始，Lambda 函数的形式参数可以使用 auto 关键字来产生意义上的泛型
    void template_lambda()
    {
        auto add = [](auto x, auto y) {
            return x+y;
        };
        add(1, 2);
        add(1.1, 2.2);
        cout << "template_lambda : 1 + 2 = " << add(1, 2) << "  |||  1.1 + 2.2 = " << add(1.1, 2.2) << endl;
    }

    //6, 函数对象包装器
    // Lambda 表达式的本质是一个和函数对象类型相似的类类型（称为闭包类型）的对象（称为闭包对象），
    // 当 Lambda 表达式的捕获列表为空时，闭包对象还能够转换为函数指针值进行传递

    using foo = void(int); // 定义函数类型
    void functional(foo f)
    {
        // 参数列表中定义的函数类型 foo 被视为退化后的函数指针类型 foo*
        f(1); // 通过函数指针调用函数
    }
    void functor_example()
    {
        auto f = [](int value) {
            std::cout << "functor_example : " << value << std::endl;
        };
        functional(f); // 传递闭包对象，隐式转换为 foo* 类型的函数指针值
        cout << "lambda 表达式调用 : ";
        f(1); // lambda 表达式调用
    }

    // 7,
    // C++11 std::function 是一种通用、多态的函数封装，
    // 它的实例可以对任何可以调用的目标实体进行存储、复制和调用操作，
    // 它也是对 C++ 中现有的可调用实体的一种类型安全的包裹（相对来说，函数指针的调用不是类型安全的），
    // 换句话说，就是函数的容器。当我们有了函数的容器之后便能够更加方便的将函数、函数指针作为对象进行处理。
    int foo2(int para)
    {
        return para;
    }
    void function_example()
    {
        // std::function 包装了一个返回值为 int, 参数为 int 的函数
        std::function<int(int)> func = foo2;

        int important = 10;
        std::function<int(int)> func2 = [&](int value) -> int {
            return 1+value+important;
        };
        cout << "function example : " << endl;
        std::cout << func(10) << std::endl;
        std::cout << func2(10) << std::endl;
    }

    void test_example()
    {
        lambda_value_capture();
        lambda_reference_capture();
        lambda_expression_capture();
        template_lambda();
        functor_example();
        function_example();
    }

}

//======================================================================
// rvalue_reference : 右值引用, move语义
namespace example7
{
    //1, 左值 右值
    void reference(std::string& str) {
        std::cout << "左值" << std::endl;
    }
    void reference(std::string&& str) {
        std::cout << "右值" << std::endl;
    }
    void test_example1()
    {
        std::string lv1 = "string,"; // lv1 是一个左值
        // std::string&& r1 = lv1; // 非法, 右值引用不能引用左值
        std::string&& rv1 = std::move(lv1); // 合法, std::move可以将左值转移为右值
        std::cout << rv1 << std::endl; // string,

        const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
        // lv2 += "Test"; // 非法, 常量引用无法被修改
        std::cout << lv2 << std::endl; // string,string,

        std::string&& rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
        rv2 += "Test"; // 合法, 非常量引用能够修改临时变量
        std::cout << rv2 << std::endl; // string,string,string,Test

        reference(rv2); // 输出左值
    }

    //2, 移动 拷贝
    class A {
    public:
        int *pointer;
        A():pointer(new int(1)) {
            std::cout << "构造" << pointer << std::endl;
        }
        A(A& a):pointer(new int(*a.pointer)) {
            std::cout << "拷贝" << pointer << std::endl;
        } // 无意义的对象拷贝
        A(A&& a):pointer(a.pointer) {
            a.pointer = nullptr;
            std::cout << "移动" << pointer << std::endl;
        }
        ~A(){
            std::cout << "析构" << pointer << std::endl;
            delete pointer;
        }
    };
    // 防止编译器优化
    A return_rvalue(bool test)
    {
        A a,b;
        if(test) return a; // 等价于 static_cast<A&&>(a);
        else return b;     // 等价于 static_cast<A&&>(b);
    }
    void test_example2()
    {
        A obj = return_rvalue(false);
        std::cout << "obj:" << std::endl;
        std::cout << obj.pointer << std::endl;
        std::cout << *obj.pointer << std::endl;
    }

    // 3, 完美转发
    // 一个声明的右值引用其实是一个左值。这就为我们进行参数转发（传递）造成了问题
    void reference(int& v) {
        std::cout << "左值" << std::endl;
    }
    void reference(int&& v) {
        std::cout << "右值" << std::endl;
    }
    template <typename T>
    void pass(T&& v) {
        std::cout << "普通传参:";
        reference(v); // 始终调用 reference(int&)
    }
    void test_example3()
    {
        std::cout << "传递右值:" << std::endl;
        pass(1); // 1是右值, 但输出是左值

        std::cout << "传递左值:" << std::endl;
        int l = 1;
        pass(l); // l 是左值, 输出左值
    }
    // forward
    // 无论传递参数为左值还是右值，普通传参都会将参数作为左值进行转发；
    // 由于类似的原因，std::move 总会接受到一个左值，从而转发调用了reference(int&&) 输出右值引用
    // 唯独 std::forward 即没有造成任何多余的拷贝，同时完美转发(传递)了函数的实参给了内部调用的其他函数。
    // std::forward 和 std::move 一样，没有做任何事情，
    // std::move 单纯的将左值转化为右值， std::forward 也只是单纯的将参数做了一个类型的转换，
    // 从现象上来看， std::forward<T>(v) 和 static_cast<T&&>(v) 是完全一样的
    // 为什么在使用循环语句的过程中，auto&& 是最安全的方式？ 因为当 auto 被推导为不同的左右引用时，与 && 的坍缩组合是完美转发。
    template <typename T>
    void pass2(T&& v) {
        std::cout << "              普通传参: ";
        reference(v);
        std::cout << "       std::move 传参: ";
        reference(std::move(v));
        std::cout << "    std::forward 传参: ";
        reference(std::forward<T>(v));
        std::cout << "static_cast<T&&> 传参: ";
        reference(static_cast<T&&>(v));
    }
    void test_example4()
    {
        std::cout << "传递右值:" << std::endl;
        pass2(1);

        std::cout << "传递左值:" << std::endl;
        int v = 1;
        pass2(v);
    }


    void test_example()
    {
        test_example1();
        cout << "===== test_example2 : =====" << endl;
        test_example2();
        cout << "===== 转发右值引用 =====" << endl;
        test_example3();
        cout << "===== forward =====" << endl;
        test_example4();
    }
} // namespace
//======================================================================
// tuple_example
// std::make_tuple: 构造元组
// std::get: 获得元组某个位置的值
// std::tie: 元组拆包
#include <tuple>
namespace example8
{
    auto get_student(int id)
    {
        // 返回类型被推断为 std::tuple<double, char, std::string>

        if (id == 0)
            return std::make_tuple(3.8, 'A', "张三");
        if (id == 1)
            return std::make_tuple(2.9, 'C', "李四");
        if (id == 2)
            return std::make_tuple(1.7, 'D', "王五");
        return std::make_tuple(0.0, 'D', "null");
        // 如果只写 0 会出现推断错误, 编译失败
    }

    void test_example1()
    {
        auto student = get_student(0);
        std::cout << "ID: 0, "
        << "GPA: " << std::get<0>(student) << ", "
        << "成绩: " << std::get<1>(student) << ", "
        << "姓名: " << std::get<2>(student) << '\n';

        double gpa;
        char grade;
        std::string name;

        // 元组进行拆包
        std::tie(gpa, grade, name) = get_student(1);
        std::cout << "ID: 1, "
        << "GPA: " << gpa << ", "
        << "成绩: " << grade << ", "
        << "姓名: " << name << '\n';
    }

    void test_example()
    {
        test_example1();
    }

} // namespace example8
//======================================================================
// 智能指针
#include <memory>
namespace example9
{
    void foo(std::shared_ptr<int> i) {
        (*i)++;
    }
    void test_example1()
    {
        // auto pointer = new int(10); // illegal, no direct assignment
        // Constructed a std::shared_ptr
        auto pointer = std::make_shared<int>(10);
        foo(pointer);
        std::cout << *pointer << std::endl; // 11
        // The shared_ptr will be destructed before leaving the scope
    }
    void test_example2()
    {
        auto pointer = std::make_shared<int>(10);
        auto pointer2 = pointer; // 引用计数+1
        auto pointer3 = pointer; // 引用计数+1
        int *p = pointer.get();  // 这样不会增加引用计数
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 3
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

        pointer2.reset();
        std::cout << "reset pointer2:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 2
        std::cout << "pointer2.use_count() = "
                << pointer2.use_count() << std::endl;           // pointer2 已 reset; 0
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2
        pointer3.reset();
        std::cout << "reset pointer3:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 1
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
        std::cout << "pointer3.use_count() = "
        << pointer3.use_count() << std::endl;           // pointer3 已 reset; 0
    }

    // unique_ptr
    struct Foo {
        Foo() { std::cout << "Foo::Foo" << std::endl; }
        ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
        void foo() { std::cout << "Foo::foo" << std::endl; }
    };

    void f(const Foo &) {
        std::cout << "f(const Foo&)" << std::endl;
    }

    void test_example3()
    {
        std::unique_ptr<Foo> p1(std::make_unique<Foo>());
        // p1 不空, 输出
        if (p1) p1->foo();
        {
            std::unique_ptr<Foo> p2(std::move(p1));
            // p2 不空, 输出
            f(*p2);
            // p2 不空, 输出
            if(p2) p2->foo();
            // p1 为空, 无输出
            if(p1) p1->foo();
            p1 = std::move(p2);
            // p2 为空, 无输出
            if(p2) p2->foo();
            std::cout << "p2 被销毁" << std::endl;
        }
        // p1 不空, 输出
        if (p1) p1->foo();
        // Foo 的实例会在离开作用域时被销毁
    }

    void test_example()
    {
        test_example1();
        test_example2();
        cout << "test unique_ptr : " << endl;
        test_example3();
    }
} // namespace example9
//======================================================================
// https://github.com/changkun/modern-cpp-tutorial/blob/master/book/zh-cn/07-thread.md
// 并发与并行，std::thread
#include <thread>
#include <mutex>
#include <future>
namespace example10
{
    // thread_test
    void test_thread()
    {
        std::thread t([](){
            std::cout << "hello test c++ thread" << std::endl;
        });
        t.join();
    }

    // mutex_test
    int v = 1;
    void critical_section(int change_v)
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);

        // 执行竞争操作
        v = change_v;

        // 离开此作用域后 mtx 会被释放
    }
    void test_mutex()
    {
        std::thread t1(critical_section, 2), t2(critical_section, 3);
        t1.join();
        t2.join();

        std::cout << v << std::endl;
    }

    // test_unique_lock
    // 而 std::unique_lock 则是相对于 std::lock_guard 出现的，std::unique_lock 更加灵活，
    // std::unique_lock 的对象会以独占所有权（没有其他的 unique_lock 对象同时拥有某个 mutex 对象的所有权）
    // 的方式管理 mutex 对象上的上锁和解锁的操作。所以在并发编程中，推荐使用 std::unique_lock。

    // std::lock_guard 不能显式的调用 lock 和 unlock，
    // 而 std::unique_lock 可以在声明后的任意位置调用， 可以缩小锁的作用范围，提供更高的并发度。

    // 如果你用到了条件变量 std::condition_variable::wait 则必须使用 std::unique_lock 作为参数。
    void critical_section2(int change_v)
    {
        static std::mutex mtx2;
        std::unique_lock<std::mutex> lock(mtx2);
        // 执行竞争操作
        v = change_v;
        std::cout << v << std::endl;
        // 将锁进行释放
        lock.unlock();

        // 在此期间，任何人都可以抢夺 v 的持有权

        // 开始另一组竞争操作，再次加锁
        lock.lock();
        v += 1;
        std::cout << v << std::endl;
    }
    void test_unique_lock()
    {
        v = 1;
        std::thread t1(critical_section2, 2), t2(critical_section2, 3);
        t1.join();
        t2.join();
    }

    // future 简单实现异步调用
    void test_future()
    {
        // 将一个返回值为7的 lambda 表达式封装到 task 中
        // std::packaged_task 的模板参数为要封装函数的类型
        std::packaged_task<int()> task([](){return 7;});
        // 获得 task 的期物
        std::future<int> result = task.get_future(); // 在一个线程中执行 task
        std::thread(std::move(task)).detach();
        std::cout << "waiting..." << endl;
        result.wait(); // 在此设置屏障，阻塞到期物的完成
        // 输出执行结果
        std::cout << "done!" << std:: endl << "future result is "
        << result.get() << std::endl;
    }

    void test_example()
    {
        test_thread();
        cout << "test_mutex : " << endl;
        test_mutex();
        cout << "test_unique_lock : " << endl;
        test_unique_lock();
        cout << "test_future : " << endl;
        test_future();
    }
} // namespace example10
//======================================================================
// std::condition_variable, atomic
// 条件变量 std::condition_variable 是为了解决死锁而生，当互斥操作不够用而引入的。
// 比如，线程可能需要等待某个条件为真才能继续执行， 而一个忙等待循环中可能会导致所有其他线程都无法进入临界区使得条件为真时，就会发生死锁。
// 所以，condition_variable 实例被创建出现主要就是用于唤醒等待线程从而避免死锁。
// std::condition_variable的 notify_one() 用于唤醒一个线程； notify_all() 则是通知所有线程。
// 下面是一个生产者和消费者模型的例子

#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <atomic>

namespace example11
{
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;  // 通知信号

    // 生产者
    auto producer = []() {
        for (int i = 0; ; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all(); // 此处也可以使用 notify_one
        }
    };
    // 消费者
    auto consumer = []() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified) {  // 避免虚假唤醒
                cv.wait(lock);
            }
            // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
            lock.unlock();
            // 消费者慢于生产者
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            lock.lock();
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    void test_condition()
    {
        // 分别在不同的线程中运行
        std::thread p(producer);
        std::thread cs[2];
        for (int i = 0; i < 2; ++i) {
            cs[i] = std::thread(consumer);
        }
        p.join();
        for (int i = 0; i < 2; ++i) {
            cs[i].join();
        }
    }

    // atomic
    struct A {
        float x;
        int y;
        // long long z;
    };

    void test_atomic()
    {
        std::atomic<A> a;
        std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    }

    void test_example()
    {
        cout << "test std::condition_variable :  " << endl;
        // test_condition();
        cout << "test atomic :" << endl;
        test_atomic();
    }
} // namespace example11

//======================================================================
// std::promise
// std::promise 是 C++11 标准库中提供的异步编程工具之一，
// 它通常与 std::future 一起使用，用来实现线程间的异步通信。
// promise 提供了一个承诺（promise），表示在某个时间点一定会有一个值或一个异常被设置。

// promise 可以在一个线程中设置一个值，而另一个线程中可以通过 std::future 来访问这个值。
// 通常的做法是，创建一个 promise 对象，然后通过 promise 对象获取一个 future 对象，
// 将 future 对象传递到另一个线程中去，另一个线程将值或异常设置到 promise 对象中，随后原线程可以通过 future 对象来获取值或异常。

// 注意std::promise对象只能使用一次。

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
namespace example12
{
    // 异步求和
    void Accumulate(std::vector<int>::iterator first,
    std::vector<int>::iterator last,
    std::promise<int> accumulate_promise)
    {
        int sum = std::accumulate(first, last, 0);
        accumulate_promise.set_value(sum);  // Notify future
    }

    // 线程1设置值
    void Do_work1(std::promise<int> &barrier)
    {
        //为了突出效果，可以使线程休眠5s
        std::this_thread::sleep_for(std::chrono::seconds(3));
        int iVal = 233;
        std::cout << "传入数据(int)：" << iVal << std::endl;
        barrier.set_value(iVal); // 设置共享状态的值, 此处和线程new_work_thread保持同步.

    }

    // 线程2获取值
    void Do_work2(std::future<int> &fun)
    {
        //阻塞函数，直到收到相关联的std::promise对象传入的数据
        auto iVal = fun.get();		//iVal = 233
        std::cout << "收到数据(int)：" << iVal << std::endl;
    }

    void test_example()
    {
        // 演示如何使用promise<int>在线程之间传输结果
        std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
        std::promise<int> accumulate_promise; // 主线程生成一个 std::promise<int> 对象.
        std::future<int> accumulate_future = accumulate_promise.get_future(); // 和 future 关联.
        std::thread work_thread(Accumulate, numbers.begin(), numbers.end(),
            std::move(accumulate_promise)); // 求和

        // future::get() will wait until the future has a valid result and retrieves it.
        // Calling wait() before get() is not needed
        // accumulate_future.wait();  // wait for result
        std::cout << "result=" << accumulate_future.get() << '\n'; // 异步获取最后的结果
        work_thread.join();  // wait for thread completion

        //演示如何使用promise<int>在线程之间表示状态。
        std::promise<int> barrier; // 生成一个 std::promise<int> 对象.
        std::future<int> barrier_future = barrier.get_future(); // 和 future 关联.
        std::thread new_work1_thread(Do_work1, std::ref(barrier));
        std::thread new_work2_thread(Do_work2, std::ref(barrier_future));

        new_work1_thread.join();
        new_work2_thread.join();
    }
} // namespace example12



int main() {
    cout << "================ test 01 =================" << endl;
    example1::test_exmaple();
    cout << "================ test 02 =================" << endl;
    exmaple2::test_exmaple();
    cout << "================ test 03 =================" << endl;
    exmaple3::test_example();
    cout << "================ test 04 =================" << endl;
    example4::test_example();
    cout << "================ test 05 =================" << endl;
    example5::test_example();
    cout << "================ test 06 =================" << endl;
    example6::test_example();
    cout << "================ test 07 =================" << endl;
    example7::test_example();
    cout << "================ test 08 =================" << endl;
    example8::test_example();
    cout << "================ test 09 =================" << endl;
    example9::test_example();
    cout << "================ test 10 =================" << endl;
    example10::test_example();
    cout << "================ test 11 =================" << endl;
    example11::test_example();
    cout << "================ test 12 =================" << endl;
    example12::test_example();
    return 0;
}