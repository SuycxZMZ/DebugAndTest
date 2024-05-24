#include <iostream>
#include <string>

/**
 * @brief 抽象产品类
*/
class AbstractProductA {
public:
    virtual ~AbstractProductA() {}
    virtual void Operation() = 0;
};

/**
 * @brief 具体产品类A
*/
class ProductA1 : public AbstractProductA {
public:
    void Operation() override { std::cout << "ProductA1 Operation" << std::endl; }
};
class ProductA2 : public AbstractProductA {
public:
    void Operation() override { std::cout << "ProductA2 Operation" << std::endl; }
};


class AbstractProductB {
public:
    virtual ~AbstractProductB() {}
    virtual void Operation() = 0;
};
/**
 * @brief 具体产品类B
*/
class ProductB1 : public AbstractProductB {
public:
    void Operation() override { std::cout << "ProductB1 Operation" << std::endl; }
};
class ProductB2 : public AbstractProductB {
public:
    void Operation() override { std::cout << "ProductB2 Operation" << std::endl; }
};

/**
 * @brief 抽象工厂类
*/
class AbstractFactory {
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
    virtual ~AbstractFactory() {}
};

/**
 * @brief 具体工厂类
*/
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override { return new ProductA1(); }
    AbstractProductB* createProductB() override { return new ProductB1(); }
};
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override { return new ProductA2(); }
    AbstractProductB* createProductB() override { return new ProductB2(); }
};

int main() {
    AbstractFactory * af1 = new ConcreteFactory1();
    // 工厂1创建产品A
    AbstractProductA * apa1 = af1->createProductA();
    apa1->Operation();
    // 工厂1创建产品B
    AbstractProductB * apb1 = af1->createProductB();
    apb1->Operation();

    // 工厂2创建产品A
    AbstractFactory * af2 = new ConcreteFactory2();
    AbstractProductA * apa2 = af2->createProductA();
    apa2->Operation();
    // 工厂2创建产品B
    AbstractProductB * apb2 = af2->createProductB();
    apb2->Operation();

    delete apa1;
    delete apb1;
    delete apa2;
    delete apb2;
    delete af1;
    delete af2;
    return 0;
}