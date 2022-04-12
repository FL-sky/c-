#include <bits/stdc++.h>
using namespace std;

class Base
{
    virtual void dummy() {}
};
class Derived : public Base
{
};

int main()
{
    Base *b1 = new Base;
    Base *b2 = new Derived;

    Derived *b3 = dynamic_cast<Derived *>(b1); //  转换失败，返回 NULL
    printf("b3=%x\n", b3);
    Derived *b4 = dynamic_cast<Derived *>(b2); // 转换成功
    printf("b4=%x\n", b4);

    Derived &b5 = dynamic_cast<Derived &>(*b1); // 转换失败（抛出异常）
    printf("b5=%x\n", &b5);
    Derived &b6 = dynamic_cast<Derived &>(*b2); // 转换成功
    printf("b6=%x\n", &b6);
    return 0;
}