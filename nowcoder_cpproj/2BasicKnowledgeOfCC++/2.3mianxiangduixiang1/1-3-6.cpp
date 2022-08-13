// 1.3.6 说说构造函数有几种，分别什么作用
// 参考答案

// C++中的构造函数可以分为4类：默认构造函数、初始化构造函数、拷贝构造函数、移动构造函数。

// 1.默认构造函数和初始化构造函数。 在定义类的对象的时候，完成对象的初始化工作。
#include <bits/stdc++.h>
using namespace std;
class Student
{
public: //默认构造函数
    Student()
    {
        num = 1001;
        age = 18;
    } //初始化构造函数
    Student(int n, int a) : num(n), age(a) {}

private:
    int num;
    int age;
};
int main()
{               //用默认构造函数初始化对象S1
    Student s1; //用初始化构造函数初始化对象S2
    Student s2(1002, 18);
    return 0;
}
// 有了有参的构造了，编译器就不提供默认的构造函数。

// 2.拷贝构造函数

class Test
{
    int i;
    int *p;

public:
    Test(int ai, int value)
    {
        i = ai;
        p = new int(value);
    }
    ~Test() { delete p; }
    Test(const Test &t)
    {
        this->i = t.i;
        this->p = new int(*t.p);
    }
}; //复制构造函数用于复制本类的对象
int main(int argc, char *argv[])
{
    Test t1(1, 2);
    Test t2(t1); //将对象t1复制给t2。注意复制和赋值的概念不同
    return 0;
}
// 赋值构造函数默认实现的是值拷贝（浅拷贝）。

// 3.移动构造函数。用于将其他类型的变量，隐式转换为本类对象。下面的转换构造函数，将int类型的r转换为Student类型的对象，对象的age为r，num为1004.
// void s1()
// {
//     Student(int r)
//     {
//         int num = 1004;
//         int age = r;
//     }
// }//这真的是移动构造吗