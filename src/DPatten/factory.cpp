/**
 * @file factory.cpp 提供了一种创建对象的接口，但由子类决定要实例化的类是哪一个。
                     工厂模式让类的实例化推迟到子类。
 * @author Suycx
 * @brief
 * @version 0.1
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <memory>
#include <string>

// 1. 抽象产品类
class Animal {
public:
  virtual void speak() const = 0; // 纯虚函数
  virtual ~Animal() {}
};

// 2. 具体产品类
class Dog : public Animal {
public:
  void speak() const override { std::cout << "Dog: Woof!" << std::endl; }
};

class Cat : public Animal {
public:
  void speak() const override { std::cout << "Cat: Meow!" << std::endl; }
};

// 3. 工厂类
class AnimalFactory {
public:
  // 使用智能指针管理对象生命周期
  static std::unique_ptr<Animal> createAnimal(const std::string &type) {
    if (type == "Dog") {
      return std::make_unique<Dog>();
    } else if (type == "Cat") {
      return std::make_unique<Cat>();
    } else {
      return nullptr;
    }
  }
};

int main() {
  std::string animalType;

  std::cout << "Enter animal type (Dog/Cat): ";
  std::cin >> animalType;

  // 4. 使用工厂创建对象
  std::unique_ptr<Animal> animal = AnimalFactory::createAnimal(animalType);

  if (animal) {
    animal->speak();
  } else {
    std::cout << "Unknown animal type!" << std::endl;
  }

  return 0;
}
