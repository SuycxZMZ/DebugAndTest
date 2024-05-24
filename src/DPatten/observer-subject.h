#pragma once

#include "observer.h"
#include <algorithm>

class MySubject : public ISubject {
public:
    // 消息类型
    enum Message {
        ADD,
        REMOVE,
    };

    // 订阅消息
    void Subscribe(int message, IObserver *observer) {
        if (observer) {
            auto it = m_observers.find(message);
            if (it == m_observers.end()) {
                ObserverList list;
                list.emplace_back(observer);
                m_observers[message] = list;
            } else {
                it->second.emplace_back(observer);
            }
        }
    }

    // 取消订阅消息
    void UnSubscribe(int message, IObserver *observer) {
        auto it = m_observers.find(message);
        if (it != m_observers.end()) {
            it->second.erase(std::remove_if(it->second.begin(), it->second.end(), [observer](IObserver *obs) {
                return observer == obs;
            }), it->second.end());
        }
    }

    // 通知订阅消息的所有观察者
    void Notify(int message) {
        auto it = m_observers.find(message);
        if (it != m_observers.end() && !it->second.empty()) {
            for (auto observer : it->second) {
                observer->Update(message);
            }
        }
    }
};