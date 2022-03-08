// 1.3.12 简述一下 C++ 中的多态
// 由于派生类重写基类方法，然后用基类引用指向派生类对象，调用方法时候会进行动态绑定，这就是多态。 多态分为静态多态和动态多态：

// 1.静态多态：编译器在编译期间完成的，编译器会根据实参类型来推断该调用哪个函数，如果有对应的函数，就调用，没有则在编译时报错。

// 比如一个简单的加法函数：

#include <bits/stdc++.h>
using namespace std;

int Add(int a, int b) // 1
{
    printf("int Add\n");
    return a + b;
}

char Add(char a, char b) // 2
{
    printf("char Add\n");
    return a + b;
}

int s1()
{
    cout << Add(666, 888) << endl; // 1
    cout << Add('1', '2');         // 2
    return 0;
}

int s2()
{
    cout << Add('1', '2') << endl; // 2
    cout << Add(666, 888) << endl; // 1
    return 0;
}

// 2.动态多态：其实要实现动态多态，需要几个条件——即动态绑定条件：

// i.虚函数。基类中必须有虚函数，在派生类中必须重写虚函数。

// ii.通过基类类型的指针或引用来调用虚函数。

// 说到这，得插播一条概念：
// 重写——也就是基类中有一个虚函数，而在派生类中也要重写一个原型（返回值、名字、参数）都相同的虚函数。
// 不过协变例外。
// 协变是重写的特例，基类中返回值是基类类型的引用或指针，在派生类中，返回值为派生类类型的引用或指针。

//协变测试函数
#include <iostream>
using namespace std;

class Base
{
public:
    virtual Base *FunTest()
    {
        cout << "victory" << endl;
        return this;
    }
};

class Derived : public Base
{
public:
    virtual Derived *FunTest()
    {
        cout << "yeah" << endl;
        return this;
    }
};

int main()
{
    Base b;
    Derived d;

    b.FunTest();
    d.FunTest();

    return 0;
}