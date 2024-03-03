#include <iostream>
#include <memory>
using namespace std;

// 模拟引用计数类
template <typename T>
class RefCnt
{
public:
    RefCnt(T* _mptr = nullptr) : mptr(_mptr)
    {
        if (mptr != nullptr) mcnt = 1;
    }
    void addRef() { mcnt++; }
    int delRef() { return --mcnt; }
private:
    T* mptr;
    int mcnt;
};

// 模拟智能指针类
template <typename T>
class CSmart_ptr
{
public: 
    CSmart_ptr(T* _mptr = nullptr) : mptr(_mptr)
    {
        mpRefCnt = new RefCnt<T> (mptr);
    }
    // 深拷贝构造
    // 智能指针模仿裸指针，深拷贝不能用
    // CSmart_ptr(const CSmart_ptr<T>& src)
    // {
    //     mptr = new T(*src.mptr);
    // }
    CSmart_ptr(const CSmart_ptr<T>& src) : mptr(src.mptr), mpRefCnt(src.mpRefCnt)
    {
        if (mptr != nullptr) mpRefCnt->addRef();
    }
    // 拷贝赋值
    CSmart_ptr<T>& operator= (const CSmart_ptr<T>& src)
    {
        if (this == &src) return *this;
        if (0 == mpRefCnt->delRef())
        {
            delete mptr;
        }

        mptr = src.mptr;
        mpRefCnt = src.mpRefCnt;
        mpRefCnt->addRef();
        return *this;
    }
    ~CSmart_ptr() 
    { 
        if (0 == mpRefCnt->delRef())
        {
            delete mptr; 
            mptr = nullptr;
            cout << "~CSmart_ptr: Last" << endl;
        }
        // cout << "~CSmart_ptr" << endl;
    }
    T& operator* () { return *mptr; }
    T* operator-> () { return mptr; }
private:
    T* mptr;
    RefCnt<T>* mpRefCnt; // 指向引用计数对象的指针
};

int main()
{
    // shared_ptr<int> ptr1 = make_shared<int>(20);
    CSmart_ptr<int> ptr1(new int);
    // 如果不加引用计数，则是浅拷贝，mptr 成员指向的内存空间释放了两次
    CSmart_ptr<int> ptr2(ptr1);  
    CSmart_ptr<int> ptr3;
    ptr3 = ptr2;
    *ptr3 = 30;
    cout << "p1, p2, p3 : " << *ptr1 << ' ' << *ptr2 << ' ' << *ptr3 << ' ' << endl;
    *ptr1 = 10;
    cout << "p1, p2, p3 : " << *ptr1 << ' ' << *ptr2 << ' ' << *ptr3 << ' ' << endl;
    return 0;
}