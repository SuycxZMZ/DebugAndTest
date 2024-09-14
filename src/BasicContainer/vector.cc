#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>
class myVector {
private:
  T * _data;
  size_t _size;
  size_t _cap;
private:
  void expand() {
    _cap = (_cap == 0) ? 1 : _cap * 2;
    T *newData = new T[_cap];
    for (size_t i = 0; i < _size; ++i) {
      newData[i] = _data[i];
    }
    delete[] _data;
    _data = newData;
  }

public:
  myVector() : _data(nullptr), _size(0), _cap(0) {}
  ~myVector() { delete[] _data; }
  size_t size() { return _size; }
  size_t capacity() { return _cap; }
  void push_back(const T& val) {
    if (_size >= _cap) {
      expand();
    }
    _data[_size++] = val;
  }

  void pop_back() {
    if (_size > 0) {
      --_size;
    }
  }

  T &operator[](size_t idx) {
    if (idx < _size) {
      return _data[idx];
    }
    throw std::out_of_range("idx out of range");
  }

};


int main() {

  myVector<int> vec;
  for (int i = 0; i < 10; ++i) vec.push_back(i);
  std::cout << "----------------- test vector -----------------" << std::endl;
  for (int i = 0; i < 10; ++i) {
    cout << vec[i] << " ";
  }
  std::cout << std::endl;

  for (int i = 0; i < 5; ++i)
    vec.pop_back();
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  
  
  return 0;
}