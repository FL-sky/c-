

// 1.3.3 简述一下 C++ 的重载和重写，以及它们的区别
// 参考回答

// 重写

// 是指派生类中存在重新定义的函数。其函数名，参数列表，返回值类型，所有都必须同基类中被重写的函数一致。只有函数体不同（花括号内），派生类对象调用时会调用派生类的重写函数，不会调用被重写函数。重写的基类中被重写的函数必须有virtual修饰。

// 示例如下：

#include <bits/stdc++.h>
using namespace std;
class A
{
public:
    virtual void fun() { cout << "A"; }
};
class B : public A
{
public:
    virtual void fun() { cout << "B"; }
};
int main(void)
{
    A *a = new B();
    a->fun(); //输出B，A类中的fun在B类中重写
    return 0;
}