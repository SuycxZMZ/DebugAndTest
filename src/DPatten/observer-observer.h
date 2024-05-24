#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "observer.h"

class MyObserver : public IObserver
{
public:
    explicit MyObserver(const std::string &str) : m_name(str) {}
    void Update(int message) override {
        std::cout << m_name << " recv message:" << message << std::endl;
    }
private:
    std::string m_name;
};