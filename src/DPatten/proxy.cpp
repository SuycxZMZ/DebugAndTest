/**
 * @file proxy.cpp 代理模式（Proxy Design Pattern）是一种结构型设计模式，
                   它为其他对象提供一个代理以控制对这个对象的访问。
                   代理模式在客户端和目标对象之间起到中介的作用，
                   可以在不修改目标对象的情况下，增加目标对象的功能或控制对目标对象的访问。
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

// 1. 抽象接口
class Image {
public:
  virtual void display() const = 0;
  virtual ~Image() {}
};

// 2. 具体实现类
class RealImage : public Image {
private:
  std::string filename;

  void loadFromDisk() const {
    std::cout << "Loading image from disk: " << filename << std::endl;
  }

public:
  RealImage(const std::string &file) : filename(file) { loadFromDisk(); }

  void display() const override {
    std::cout << "Displaying " << filename << std::endl;
  }
};

// 3. 代理类
class ProxyImage : public Image {
private:
  std::string filename;
  mutable std::shared_ptr<RealImage>
      realImage; // 使用shared_ptr管理RealImage的生命周期

public:
  ProxyImage(const std::string &file) : filename(file), realImage(nullptr) {}

  void display() const override {
    if (!realImage) {
      realImage = std::make_shared<RealImage>(filename);
    }
    realImage->display();
  }
};

// 4. 客户端代码
int main() {
  std::shared_ptr<Image> image1 =
      std::make_shared<ProxyImage>("HighResolutionImage1.jpg");
  std::shared_ptr<Image> image2 =
      std::make_shared<ProxyImage>("HighResolutionImage2.jpg");

  std::cout << "Image objects created. Images are not loaded yet.\n\n";

  std::cout << "First call to display image1:\n";
  image1->display(); // 真实图像首次加载

  std::cout << "\nSecond call to display image1:\n";
  image1->display(); // 真实图像已经加载，无需重新加载

  std::cout << "\nFirst call to display image2:\n";
  image2->display(); // 真实图像首次加载

  return 0;
}
