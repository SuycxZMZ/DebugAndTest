// B.h
#ifndef CLASSB_H  
#define CLASSB_H  
#include <iostream>
#include "A.h"  // 包含ClassA的头文件  
  
using namespace std;

class ClassB {  
public:  
    void aFunc() {
        cout << "B Func" << endl;
    }
private:
    ClassA* a;  // ClassB包含对ClassA的引用  
    // 其他成员...  
    int b;
};  
  
#endif