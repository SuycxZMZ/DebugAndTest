#include <cstdio>

class Actress {
public:
    Actress(int h, int w, int a):height(h),weight(w),age(a){};

    virtual void desc() {
        printf("height:%d weight:%d age:%d\n", height, weight, age);
    }

    virtual void name() = 0;
    // virtual ~Actress() { printf("~Actress\n"); };
    ~Actress() { printf("~Actress\n"); };

    int height; // 身高
    int weight; // 体重
    int age;    // 年龄
};

class Sensei: public Actress {
public:
    Sensei(int h, int w, int a, const char* c):Actress(h, w, a){
        snprintf(cup, sizeof(cup), "%s", c);
    };
    virtual void desc() override {
        printf("height:%d weight:%d age:%d cup:%s\n", height, weight, age, cup);
    }
    virtual void name() override {
        printf("I'm a sensei");
    }

    virtual ~Sensei() { printf("~Sensei\n"); };
private:
    char cup[4];
};

int main() {
    Actress* a3 = new Sensei(170, 50, 20, "36D");
    delete a3;

    return 0;
}