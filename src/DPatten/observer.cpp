/**
 * @file observer.cpp 定义了一种一对多的依赖关系，当一个对象的状态发生变化时，
                      所有依赖于它的对象都会收到通知并自动更新。
                      这个模式常用于实现事件处理系统、发布-订阅系统等。
 * @author Suycx
 * @brief
 * @version 0.1
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

// 1. 观察者接口
class Observer {
public:
  virtual void update(float temperature) = 0;
  virtual ~Observer() {}
};

// 2. 被观察者接口
class Subject {
public:
  virtual void attach(std::shared_ptr<Observer> observer) = 0;
  virtual void detach(std::shared_ptr<Observer> observer) = 0;
  virtual void notify() = 0;
  virtual ~Subject() {}
};

// 3. 具体被观察者类（天气站）
class WeatherStation : public Subject {
private:
  std::vector<std::shared_ptr<Observer>> observers;
  float temperature;

public:
  void attach(std::shared_ptr<Observer> observer) override {
    observers.emplace_back(observer);
  }

  void detach(std::shared_ptr<Observer> observer) override {
    observers.erase(std::remove_if(observers.begin(), observers.end(),
                                   [&](const std::shared_ptr<Observer> &o) {
                                     return o == observer;
                                   }),
                    observers.end());
  }

  void notify() override {
    for (auto &observer : observers) {
      if (observer) {
        observer->update(temperature);
      }
    }
  }

  void setTemperature(float temp) {
    temperature = temp;
    std::cout << "WeatherStation: Temperature updated to " << temperature
              << "°C" << std::endl;
    notify();
  }
};

// 4. 具体观察者类（显示器）
class Display : public Observer {
private:
  std::string name;

public:
  Display(const std::string &displayName) : name(displayName) {}

  void update(float temperature) override {
    std::cout << name
              << " Display: Received temperature update: " << temperature
              << "°C" << std::endl;
  }
};

// 5. 客户端代码
int main() {
  // 创建被观察者对象
  std::shared_ptr<WeatherStation> weatherStation =
      std::make_shared<WeatherStation>();

  // 创建观察者对象
  std::shared_ptr<Observer> display1 = std::make_shared<Display>("Phone");
  std::shared_ptr<Observer> display2 = std::make_shared<Display>("Computer");

  // 注册观察者
  weatherStation->attach(display1);
  weatherStation->attach(display2);

  // 更新温度
  weatherStation->setTemperature(25.0f);
  weatherStation->setTemperature(30.5f);

  // 移除一个观察者
  weatherStation->detach(display1);

  // 再次更新温度
  weatherStation->setTemperature(28.0f);

  return 0;
}
