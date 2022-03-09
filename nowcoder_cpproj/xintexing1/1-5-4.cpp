// 1.5.4 简述 C++ 右值引用与转移语义
// 参考回答

// 1.右值引用

// 一般来说，不能取地址的表达式，就是右值引用，能取地址的，就是左值。
#include <bits/stdc++.h>
using namespace std;

class A
{
};
void s0()
{
    // A &r = A();
    // cannot bind non-const lvalue reference of type 'A&' to an rvalue of type 'A'
    //  A &r = A();
}

// error,A()是无名变量，是右值 A && r = A(); //ok,r是右值引用
//  1.转移语义

// move 本意为 "移动"，但该函数并不能移动任何数据，它的功能很简单，就是将某个左值强制转化为右值。
// 基于 move() 函数特殊的功能，其常用于实现移动语义。

// 答案解析

// 1.右值引用

//     C++98/03 标准中就有引用，使用 "&" 表示。但此种引用方式有一个缺陷，
//     即正常情况下只能操作 C++ 中的左值，无法对右值添加引用。举个例子：
void s1()
{
    int num = 10;
    int &b = num; //正确 int &c = 10; //错误
}
// 如上所示，编译器允许我们为 num 左值建立一个引用，但不可以为 10 这个右值建立引用。
// 因此，C++98/03 标准中的引用又称为左值引用。

// 注意：虽然 C++98/03 标准不支持为右值建立非常量左值引用，但允许使用常量左值引用操作右值。
// 也就是说，常量左值引用既可以操作左值，也可以操作右值，例如：
void s2()
{
    int num = 10;
    const int &b = num;
    const int &c = 10;
}
// 我们知道，右值往往是没有名称的，因此要使用它只能借助引用的方式。
// 这就产生一个问题，实际开发中我们可能需要对右值进行修改（实现移动语义时就需要），
// 显然左值引用的方式是行不通的。

// 为此，C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。

// 注意：和声明左值引用一样，右值引用也必须立即进行初始化操作，且只能使用右值进行初始化，比如：
void s3()
{
    int num = 10; // int && a = num;  //右值引用不能初始化为左值 int && a = 10;
                  //  和常量左值引用不同的是，右值引用还可以对右值进行修改。例如：

    int &&a = 10;
    a = 100;
    cout << a << endl; /*    程序运行结果：           100  */
    // 另外值得一提的是，C++ 语法上是支持定义常量右值引用的，例如：
    {
        const int &&a = 10; //编译器不会报错
    }
    // 但这种定义出来的右值引用并无实际用处。一方面，右值引用主要用于移动语义和完美转发，
    // 其中前者需要有修改右值的权限；其次，常量右值引用的作用就是引用一个不可修改的右值，
    // 这项工作完全可以交给常量左值引用完成。
}
// 1.move语义

//程序实例
#include <iostream>
using namespace std;
class first
{
public:
    first() : num(new int(0))
    {
        cout << "construct!" << endl;
    } //移动构造函数
    first(first &&d) : num(d.num)
    {
        d.num = NULL;
        cout << "first move construct!" << endl;
    }

public: //这里应该是 private，使用 public 是为了更方便说明问题
    int *num;
};
class second
{
public:
    second() : fir() {} //用 first 类的移动构造函数初始化 fir
    second(second &&sec) : fir(move(sec.fir))
    {
        cout << "second move construct" << endl;
    }

public: //这里也应该是 private，使用 public 是为了更方便说明问题
    first fir;
};
int main()
{
    second oth;
    second oth2 = move(oth);
    //
    // cout << *oth.fir.num << endl; //程序报运行时错误
    return 0;
} /*      程序运行结果：   construct!  first move construct!  second move construct */