/**
 * @SuycxZMZ
 * @brief 观察者模式
 * 解决的问题：观察者模式可以有效支持组件解耦，避免循环依赖。
 * 经常看到一些对象调用其他对象的方法：因为实现复杂的任务通常需要几个对象一起合作完成，
 * 为了该目标，对象A为了调用对象B的方法，就必须知道对象B的存在及其接口。
 * 最简单的办法是让A.cpp包含（include）B.h，然后直接调用B class方法。
 * 但这样做，A中引入了B class，导致A和B编译时依赖，迫使两个类紧耦合。
 * 后果是，A class通用性减弱。如果A还调用了C class、D class，那么对A的改变会影响这三个紧耦合的类。
 * 而且，编译时紧耦合会导致用户不能在运行时给系统动态添加新的依赖。
 * 
 * 概念：
 * 观察者模式的意图定义为：对象间的一种一对多的依赖关系，
 * 当一个对象的状态发生改变时，所有依赖它的对象都得到通知并被自动更新。
 * 
 * 典型观察者模式有两个概念：主题（Subject），观察者（Observer），也称为发布者，订阅者。
 * 主要工作是将Subject对Object的编译时依赖，转化为对接口类的依赖，从而实现解耦。
 * 
 * 观察者模式的优势：主题（Subject）无需耦合某个具体的观察者（如MyObserver），
 * 而只需要知道其抽象接口IObserver即可。观察者对象需要事先在具体的主题（MySubject）中订阅关注的事件，
 * 当主题自身状态发生改变时，可Notify通知订阅了特定事件的所有观察者。
 * 整个过程中，MySubject跟MyObserver没有编译时依赖，也没有耦合。
 * 
 * 观察者模式的缺点：性能损耗，即在函数调用前遍历观察者列表的开销。
 * 另外，在销毁观察者对象前，必须取消订阅此观察者对象，否则通知一个已销毁的观察者可能导致程序崩溃。
*/

#include "observer-observer.h"
#include "observer-subject.h"
#include "observer.h"

int main()
{

    // 构造三个观察者对象
    MyObserver observer1("observer1");
    MyObserver observer2("observer2");
    MyObserver observer3("observer3");
    // 构造一个主题对象
    MySubject subject;

    // 注册观察者对象关注的事件
    subject.Subscribe(MySubject::ADD, &observer1);
    subject.Subscribe(MySubject::ADD, &observer2);
    subject.Subscribe(MySubject::REMOVE, &observer2);
    subject.Subscribe(MySubject::REMOVE, &observer3);

    // 通知订阅特定事件的观察者
    subject.Notify(MySubject::ADD);
    subject.Notify(MySubject::REMOVE);

    return 0;
}