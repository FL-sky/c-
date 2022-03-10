#include <iostream>
class Base
{
public:
    int value1;
    int value2;
    float value3;
    //无参默认构造
    Base()
    {
        value1 = 1;
    }
    Base(float f)
    {
        value3 = f;
    }
    //int参数构造
    Base(int value, float f) : Base(f)
    { //委托Base()构造函数
        value2 = 2;
    }
};
int main()
{
    Base b(2, 3.14f);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;
    std::cout << b.value3 << std::endl;
    return 0;
}