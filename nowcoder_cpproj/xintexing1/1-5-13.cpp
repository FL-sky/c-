// 1.5.13 简述一下 C++11 中的可变参数模板新特性
// 参考回答

//     可变参数模板(variadic template)使得编程者能够创建这样的模板函数和模板类，
//     即可接受可变数量的参数。例如要编写一个函数，它可接受任意数量的参数，
//     参数的类型只需是cout能显示的即可，并将参数显示为用逗号分隔的列表。
#include <bits/stdc++.h>
using namespace std;
void show_list() {} //递归终止函数
template <typename T, typename... Args>
void show_list(T &&value, Args &&...args) /// 为什么是&&
{
    cout << value << endl;
    show_list(args...);
}
int main()
{
    int n = 14;
    double x = 2.71828;
    std::string mr = "Mr.String objects!";
    show_list(n, x);
    show_list(x * x, '!', 7, mr); //这里的目标是定义show_list()
    return 0;
}
/*
    运行结果：
      14, 2.71828
      7.38905， !, 7, Mr.String objects!
*/
// 要创建可变参数模板，需要理解几个要点：

// （1）模板参数包（parameter pack）；

// （2）函数参数包；

// （3）展开（unpack）参数包；

// （4）递归。