#include <bits/stdc++.h>
using namespace std;

template <typename _Tx, typename _Ty>
void Multiply(_Tx x, _Ty y)
{
    // std::cout << x * y << endl;
    //若不使用auto变量来声明v，那这个函数就难定义啦，不到编译的时候，谁知道x*y的真正类型是什么呢
    //然而事实上可以如上面写
    auto v = x * y;
    std::cout << v << endl;
}

template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y) -> decltype(x * y)
{
    return x * y;
}

template <typename _Tx, typename _Ty>
auto multiply0(_Tx x, _Ty y) // c++11 cannot
{
    return x * y;
}

int main1()
{
    Multiply(5, 6.9);
    cout << multiply(5, 6.9) << endl;
    cout << multiply0(5, 6.9) << endl;
    return 0;
}

///注意事项

// auto 变量必须在定义时初始化，这类似于const关键字。
// 定义在一个auto序列的变量必须始终推导成同一类型。例如：
void s1()
{
    auto a4 = 10, a5 = 20, a6 = 30; //正确
    // auto b4 = 10, b5 = 20.0, b6 = 'a'; //错误,没有推导为同一类型
}

void s2()
{
    // 如果初始化表达式是引用，则去除引用语义。
    {
        int a = 10;
        int &b = a;

        auto c = b;  // c的类型为int而非int&（去除引用）
        auto &d = b; //此时c的类型才为int&

        c = 100; // a =10;
        d = 100; // a =100;
    }

    // 如果初始化表达式为const或volatile（或者两者兼有），则除去const/volatile语义。
    {
        const int a1 = 10;
        auto b1 = a1;       // b1的类型为int而非const int（去除const）
        const auto c1 = a1; //此时c1的类型为const int
        b1 = 100;           //合法
        // c1 = 100;           //非法
    }
    //如果auto关键字带上&号，则不去除const语意。
    {
        const int a2 = 10;
        auto &b2 = a2; //因为auto带上&，故不去除const，b2类型为const int
        // b2 = 10;       //非法
    }
    // 初始化表达式为数组时，auto关键字推导类型为指针
    {
        int a3[3] = {1, 2, 3};
        auto b3 = a3;
        cout << typeid(b3).name() << endl;
    }
    // 若表达式为数组且auto带上&，则推导类型为数组类型
    {
        int a7[3] = {1, 2, 3};
        auto &b7 = a7;
        cout << typeid(b7).name() << endl;
    }
    //     时刻要注意auto并不是一个真正的类型。
    // auto仅仅是一个占位符，它并不是一个真正的类型，不能使用一些以类型为操作数的操作符，如sizeof或者typeid。
    {
        // cout << sizeof(auto) << endl;        //错误
        // cout << typeid(auto).name() << endl; //错误
    }
}
// 函数或者模板参数不能被声明为auto

// void func(auto a) //错误
// {
//     //...
// }
int main()
{
    s2();
    return 0;
}