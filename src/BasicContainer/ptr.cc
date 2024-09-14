#include <cstddef>

template <typename T>
class sPtr {
private:
  T *_ptr;
  size_t *_cnt;

public:
  sPtr() : _ptr(nullptr), _cnt(new size_t(0)) {}
  explicit sPtr(T *p) : _ptr(p), _cnt(new size_t(1)) {}

  // 拷贝构造
  sPtr(const sPtr &other) : _ptr(other._ptr), _cnt(other._cnt) {
    if (_ptr) {
      (*_cnt)++;
    }
  }

  // 拷贝赋值
  sPtr &operator=(const sPtr &other) {
    if (this != &other) {
      release();
      _ptr = other._ptr;
      _cnt = other._cnt;
      if (_ptr) {
        (*_cnt)++;
      }
    }
    return *this;
  }
  // 移动构造
  sPtr(sPtr &&other) : _ptr(other._ptr), _cnt(other._cnt) {
    other._ptr = nullptr;
    other._cnt = nullptr;
  }

  // 移动赋值
  sPtr &operator=(sPtr &&other) {
    if (this != &other) {
      release();
      _ptr = other._ptr;
      _cnt = other._cnt;
      other._cnt = nullptr;
      other._ptr = nullptr;
    }
    return *this;
  }
  // 析构
  ~sPtr() {
    release();
  }
  // 箭头
  T *operator->() const {
    return _ptr;
  }
  // 星号
  T &operator*() const {
    return *_ptr;
  }
private:
  void release() {
    if (_ptr) {
      (*_cnt)--;
      if (*_cnt == 0) {
        delete _ptr;
        delete _cnt;
      }
      _ptr = nullptr;
      _cnt = nullptr;
    }
  }
};

int main() { return 0; }