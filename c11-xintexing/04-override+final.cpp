#include <iostream>

//override final default delete
//对于类的用法final
//对于虚函数final

class Base
{
public:
    virtual void foo() final {} //final 不可再被重写
    Base() = default;           //保留原有默认的构造函数
    //Base() = delete;            //不让编译器产生默认构造
    Base(int n)
    {
    }
};
class Subclass final : public Base //final 截止。不可再被继承
{
public:
    /////void foo() {}
    //void foo() override{}; //override 显式 重写
    //virtual void foo(){};
};

// class Subclass2 : public Subclass
// {
// public:
// };

int main()
{
    Base b;
    return 0;
}
