#include <iostream>
using namespace std;

class A
{
public:
    virtual void print() { cout << "This is A" << endl; }
};
class B : public A
{
public:
    void print() { cout << "This is B" << endl; }
};

int main()
{
    //main2
    A a;
    B b;
    A *p1 = &a;
    A *p2 = &b;
    p1->print();
    p2->print();
    return 0;
}

/*
毫无疑问，class A的成员函数print（）已经成了虚函数，那么class B的print（）成了虚函数了吗？
回答是Yes，我们只需在把基类的成员函数设为virtual，其派生类的相应的函数也会自动变为虚函数。所以，class B的print()也成了虚函数。那么对于在派生类的相应函数前是否需要用virtual关键字修饰，那就是你自己的问题了（语法上可加可不加，不加的话编译器会自动加上，但为了阅读方便和规范性，建议加上）。
现在重新运行main2的代码，这样输出的结果就是This is A和This is B了。
现在来消化一下，我作个简单的总结，指向基类的指针在操作它的多态类对象时，会根据不同的类对象，调用其相应的函数，
这个函数就是虚函数。
*/