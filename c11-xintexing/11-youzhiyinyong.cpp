#include <bits/stdc++.h>
using namespace std;

////https://zhuanlan.zhihu.com/p/335994370
//一文读懂C++右值引用和std::move

// #### （2）右值引用和左值引用

// 需要拿到一个将亡值，就需要用到右值引用的申明：`T &&`，其中 `T` 是类型。右值引用的声明让这个临时值的生命周期得以延长、只要变量还活着，那么将亡值将继续存活。

// C++11 提供了 `std::move` 这个方法将左值参数无条件的转换为右值，有了它我们就能够方便的获得一个右值临时对象，例如：

void reference(std::string &str)
{
    std::cout << "左值" << std::endl;
}
void reference(std::string &&str)
{
    std::cout << "右值" << std::endl;
}

int main()
{
    std::string lv1 = "string,"; // lv1 是一个左值
    //std::string &&r1 = s1;                   // 非法, s1 在全局上下文中没有声明
    //string &&ts = lv1;                       // 非法, 无法将右值引用绑定到左值C/C++(1768) std::string lv1 lv1 是一个左值
    std::string &&rv1 = std::move(lv1);        // 合法, std::move 可以将左值转移为右值
    std::cout << "rv1 = " << rv1 << std::endl; // string,

    const std::string &lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
    // lv2 += "Test";                   // 非法, 引用的右值无法被修改
    std::cout << "lv2 = " << lv2 << std::endl; // string,string

    std::string &&rv2 = lv1 + lv2;             // 合法, 右值引用延长临时对象的生命周期
    rv2 += "string";                           // 合法, 非常量引用能够修改临时变量
    std::cout << "rv2 = " << rv2 << std::endl; // string,string,string,
    int a = 1, b = 2;
    const int &x = a + b;
    //int &y = a + b; //不合法，非常量引用的初始值必须为左值
    reference(rv2); // 输出左值

    return 0;
}