#include <cstddef>
#include <iostream>
#include <ostream>
#include <string.h>

using namespace std;

class myString {
private:
  char *_data;
  size_t _size;

public:
  myString() : _data(nullptr), _size(0) {}

  ~myString() { delete[] _data; }

  // 拷贝构造函数
  myString(const myString &other) {
    if (other._data) {
      _size = other._size;
      _data = new char[_size + 1];
      memcpy((void *)_data, (const void *)other._data, _size + 1);
    } else {
      _data = nullptr;
      _size = 0;
    }
  }

  // 赋值操作符
  myString &operator=(const myString &other) {
    if (this != &other) {
      char *new_data = nullptr;
      if (other._data) {
        new_data = new char[other._size + 1];
        memcpy(new_data, other._data, other._size + 1);
      }

      delete[] _data; // 释放旧数据

      _data = new_data; // 赋值新数据
      _size = other._size;
    }
    return *this;
  }

  // 返回字符串大小
  size_t size() const { return _size; }

  // 重载输出操作符
  friend std::ostream &operator<<(std::ostream &os, const myString &s) {
    if (s._data) {
      os << s._data;
    }
    return os;
  }

  // 从C字符串构造
  myString(const char *c) {
    if (!c) {
      _data = nullptr;
      _size = 0;
    } else {
      size_t len = strlen(c);
      _data = new char[len + 1];
      memcpy((void *)_data, (const void *)c, len + 1);
      _size = len;
    }
  }
};

int main() {
  myString s1 = "hello";
  myString s2 = "world";

  myString s3 = s1;
  std::cout << "s1: " << s1 << " s2: " << s2 << " s3: " << s3 << std::endl;

  s2 = s1;
  std::cout << "s2: " << s2 << std::endl;

  return 0;
}