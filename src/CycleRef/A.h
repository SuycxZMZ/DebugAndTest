// A.h
#ifndef CLASSA_H  
#define CLASSA_H  
#include <iostream>
#include "B.h"  // 包含ClassB的头文件  

using namespace std;

class ClassA {  
public:  
    void aFunc() {
        cout << "A Func" << endl;
    }
private:
    ClassB* b;  // ClassA包含对ClassB的引用  
    // 其他成员... 
    int a; 
};  
  
#endif