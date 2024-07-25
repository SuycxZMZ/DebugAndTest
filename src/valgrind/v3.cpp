#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> array(100, 0);
    vector<int> array2(1000, 0);
    array[1000] = 1;  // 越界写入
    array2[10000] = 1;
    cout << "array[100] = " << array[1000] << endl;
    cout << "array[10000] = " << array[10000] << endl;
    // delete[] array;
    return 0;
}
