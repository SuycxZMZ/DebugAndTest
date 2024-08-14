#include <iostream>
#include <cstring>

using namespace std;

class ccString {
private:
    char* _data;
    int _length;
public:
    ccString() : _data(nullptr), _length(0) {} // 默认构造

    ccString(const ccString& other) {          // 拷贝构造，深拷贝
        _length = other._length;
        if (other._data) {
            _data = new char[_length + 1];     // 重新分配内存
            std::strcpy(_data, other._data);
        } else {
            _data = nullptr;
        }
    }

    ccString(const char* str) {                // 接收一个 c 风格字符串
        if (str) {
            _length = std::strlen(str);
            _data = new char[_length + 1];     // 内存分配
            std::strcpy(_data, str);
        } else {
            _data = nullptr;
            _length = 0;
        }
    }

    // 赋值运算符
    ccString& operator= (const ccString& other) {
        if (this == &other) return *this; // 防止自我赋值
        
        delete[] _data; // 释放已有内存
        _length = other._length;
        if (other._data) {
            _data = new char[_length + 1];
            std::strcpy(_data, other._data);
        } else {
            _data = nullptr;
        }

        return *this;
    }

    ~ccString() {
        delete[] _data;
    }

    ssize_t size() {
        return _length;
    }

    const char* c_str() const {
        return _data;
    }

    friend std::ostream& operator<< (std::ostream& os, const ccString& str) {
        if (str._data) {
            os << str._data;
        }
        return os;
    }

    void display() const {
        if (_data) {
            std::cout << "stringaddr : " << (void*)_data << ":" << _data << std::endl;
        } else {
            std::cout << "empty , nullptr !!! " << std::endl; 
        }
    }
};

int main() {
    ccString str1("hello 1");
    ccString str2 = str1;
    str1.display();
    str2.display();

    str2 = "hello test3 test c++ string";
    str2.display();

    return 0;
}