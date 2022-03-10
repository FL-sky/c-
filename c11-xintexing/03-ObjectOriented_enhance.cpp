#include <iostream>
class Base
{
public:
    int value1;
    int value2;

    //无参默认构造
    Base()
    {
        value1 = 1;
    }
    //int参数构造
    Base(int value) : Base()
    { //委托Base()构造函数
        value2 = 2;
    }
};

//继承构造
class SubClass : public Base
{
public:
    //直接使用父类的构造
    using Base::Base;
};

int main()
{
    SubClass s(1);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;

    return 0;
}