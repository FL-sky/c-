// 1.重载

// 我们在平时写代码中会用到几个函数但是他们的实现功能相同，但是有些细节却不同。例如：交换两个数的值其中包括（int, float,char,double)这些个类型。在C语言中我们是利用不同的函数名来加以区分。这样的代码不美观而且给程序猿也带来了很多的不便。于是在C++中人们提出了用一个函数名定义多个函数，也就是所谓的函数重载。函数重载是指同一可访问区内被声明的几个具有不同参数列（参数的类型，个数，顺序不同）的同名函数，根据参数列表确定调用哪个函数，重载不关心函数返回类型。

#include <bits/stdc++.h>
using namespace std;
class A
{
    void fun(){};
    void fun(int i){};
    void fun(int i, int j){};
    void fun1(int i, int j){};
};