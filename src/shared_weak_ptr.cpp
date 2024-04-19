#include <iostream>
#include <memory>
#include <thread>
#include <functional>
using namespace std;

/*
shared_ptr : 改变引用计数
weak_ptr : 不改变引用计数，只是一个观察者，不能使用资源，没有 * ->的重载

shared_ptr 的循环引用问题 资源无法释放，造成内存泄漏
*/ 
namespace cyc_Ref
{
    class A;
    class B
    {
    public:
        B() { cout << "B()" << endl; }
        ~B(){ cout << "~B()" << endl;}
        shared_ptr<A> _mptr2A;
    };

    class A
    {
    public:
        A() { cout << "A()" << endl; }
        ~A() { cout << "~A()" << endl; }
        shared_ptr<B> _mptr2B;
    };
    void test()
    {
        shared_ptr<A> ptrA(new A());
        shared_ptr<B> ptrB(new B());
        ptrA->_mptr2B = ptrB;
        ptrB->_mptr2A = ptrA;
        cout << ptrB.use_count() << endl;
    }
}
/*
shared_ptr : 改变引用计数
weak_ptr : 不改变引用计数，只是一个观察者，不能使用资源，没有 * ->的重载
解决循环引用 : 定义的时候使用弱指针， 使用的时候用强指针
*/ 
namespace okcyc_Ref
{
    class A;
    class B
    {
    public:
        B() { cout << "B()" << endl; }
        ~B(){ cout << "~B()" << endl;}
        void func()
        {
            cout << "a good func ,other class can use" << endl;
        }
        weak_ptr<A> _mptr2A;
    };

    class A
    {
    public:
        A() { cout << "A()" << endl; }
        ~A() { cout << "~A()" << endl; }
        void func_B()
        {
            shared_ptr<B> pB = _mptr2B.lock();
            if (nullptr != pB) pB->func();
        }
        weak_ptr<B> _mptr2B;
    };
    void test()
    {
        shared_ptr<A> ptrA(new A());
        shared_ptr<B> ptrB(new B());
        ptrA->_mptr2B = ptrB;
        ptrB->_mptr2A = ptrA;
        cout << ptrB.use_count() << endl;
        ptrA->func_B();
    }
}

/*
shared_ptr : 改变引用计数
weak_ptr : 不改变引用计数，只是一个观察者，不能使用资源，没有 * ->的重载
解决循环引用 : 定义的时候使用弱指针， 使用的时候用强指针

智能指针多线程访问的线程安全问题
*/ 
namespace thread_Ref
{
    class A;
    class B
    {
    public:
        B() { cout << "B()" << endl; }
        ~B(){ cout << "~B()" << endl;}
        void func()
        {
            cout << "a good func ,other class can use" << endl;
        }
        // weak_ptr<A> _mptr2A;
    };

    class A
    {
    public:
        A() { cout << "A()" << endl; }
        ~A() { cout << "~A()" << endl; }
        // void func_B()
        // {
        //     shared_ptr<B> pB = _mptr2B.lock();
        //     if (nullptr != pB) pB->func();
        // }
        // weak_ptr<B> _mptr2B;
    };
    void handler01(B* pb)
    {
        pb->func();
    }
    void handler02(weak_ptr<B> pb)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        shared_ptr<B> spb = pb.lock();
        if (nullptr != spb) spb->func();
        else
            cout << "resource relise" << endl; 
    }
    void test_notsafe()
    {
        B* pb = new B();
        thread t1(handler01, pb);
        pb->func();
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        delete pb;
        t1.join();
    }
    void test_safe()
    {
        {
            shared_ptr<B> pb(new B());
            thread t1(handler02, weak_ptr<B>(pb));
            t1.detach();
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main()
{
    cyc_Ref::test();
    // okcyc_Ref::test();
    // thread_Ref::test_safe();

    // 自定义删除器
    // unique_ptr<FILE, function<void(FILE* )>> ptr1(fopen("test.cpp", "w"), 
    //                                               [](FILE* f)->void
    //                                               { 
    //                                                 cout << "close file" << endl;
    //                                                 fclose(f); 
    //                                               });
    return 0;
}