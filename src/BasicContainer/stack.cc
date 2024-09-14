#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class myStack {
private:
  T *_data;
  size_t _size;
  size_t _cap;
  size_t _back_idx;

  void expand() {
    size_t newCap = (_cap == 0) ? 1 : _cap * 2;
    T *newData = new T[newCap];
    for (size_t i = 0; i < _size; ++i) {
      newData[i] = _data[i];
    }

    delete[] _data;
    _data = newData;
    _cap = newCap;
    _back_idx = _size - 1;
  }

public:
  myStack() : _data(nullptr), _size(0), _cap(0), _back_idx(0) {}
  ~myStack() { delete[] _data; }
  void push(const T &val) {
    if (_size >= _cap) {
      expand();
    }
    if (_size == 0) {
      _back_idx = 0;
    } else {
      _back_idx = (_back_idx + 1) % _cap;
    }
    _data[_back_idx] = val;
    ++_size;
  }

  void pop() {
    if (_size == 0) {
      throw std::out_of_range("dequeue out of range");
    }
    _back_idx = (_back_idx - 1) % _cap;
    --_size;
  }

  T Peek() const {
    if (_size == 0) {
      throw std::out_of_range("Peek out of range");
    }
    return _data[_back_idx];
  }

  size_t size() const { return _size; }
  size_t empty() const { return _size == 0; }
};

int main() {
  myStack<int> st;
  for (int i = 0; i < 10; ++i) {
    st.push(i);
  }
  std::cout << "----------------- test queue -----------------" << std::endl;
  for (int i = 0; i < 5; ++i) {
    std::cout << st.Peek() << " ";
    st.pop();
  }
  std::cout << std::endl;

  return 0;
}