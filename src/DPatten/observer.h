#pragma once

#include <map>
#include <vector>

class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void Update(int message) = 0; // 更新
};

/**
 * @brief 主题，用于观察者订阅关注的特定消息
 *        主题能为多个不同的消息类型注册并发出通知，这样观察者只需要订阅关心的特定消息即可。
 *        比如，对于一个表示一堆元素的主题，当添加或删除元素时，
 *        观察者可以选择订阅关注的“添加或删除元素”消息。
*/
class ISubject
{
public:
    ISubject() {}
    virtual ~ISubject() {}
    // 观察者订阅指定类型事件
    virtual void Subscribe(int message, IObserver* observer) = 0;
    // 观察者取消订阅指定类型事件   
    virtual void UnSubscribe(int message, IObserver* observer) = 0;

    // 通知观察者
    virtual void Notify(int message) = 0;
protected:
    // 观察者列表
    using ObserverList = std::vector<IObserver*>;
    // (消息类型 观察者)，用于观察者订阅关注的特定消息
    using ObserverMap = std::map<int, ObserverList>;
    ObserverMap m_observers;
};