#include <iostream>
#include <vector>

using namespace std;

class shadowCopy {
public:
    shadowCopy(int val) {
        data = new int(val);
    }
    ~shadowCopy() {
        delete data;
    }

    void display() {
        cout << "hello addr: " << data << " = " << *data << endl;
    }

    // 默认的拷贝构造，如果不写的话就是是浅拷贝
    // shadowCopy(const shadowCopy& other);
private:
    int* data;
};

class deepCopy {
public:
    deepCopy(int val) {
        data = new int(val);
    }

    void display() {
        cout << "hello addr: " << data << " = " << *data << endl;
    }

    ~deepCopy() {
        delete data;
    }

    // 拷贝构造,深拷贝
    deepCopy(const deepCopy& other) {
        data = new int(*other.data);
    }
private:
    int* data;
};

int main() {
    shadowCopy data1(42);
    data1.display();
    // free(): double free detected in tcache 2
    // shadowCopy data2(data1);
    // data2.display();

    deepCopy data3(43);
    data3.display();
    deepCopy data4(data3);
    data4.display();

    return 0;
}