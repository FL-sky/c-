// 1.5.12 简述一下 C++ 11 中 auto 的具体用法
// 参考回答

//     auto用于定义变量，编译器可以自动判断变量的类型。auto主要有以下几种用法：

// 1.auto的基本使用方法

// （1）基本使用语法如下
#include <bits/stdc++.h>
using namespace std;
template <typename T>
void s1(T value)
{
    auto name = value; // name 是变量的名字，value 是变量的初始值
}
// 注意：auto 仅仅是一个占位符，在编译器期间它会被真正的类型所替代。
// 或者说，C++ 中的变量必须是有明确类型的，只是这个类型是由编译器自己推导出来的。

// （2）程序实例如下
void s2()
{
    auto n = 10;
    auto f = 12.8;
    auto p = &n;
    auto url = "www.123.com";
}
// a. 第 1 行中，10 是一个整数，默认是 int 类型，所以推导出变量 n 的类型是 int。
// b. 第 2 行中，12.8 是一个小数，默认是 double 类型，所以推导出变量 f 的类型是 double。
// c. 第 3 行中，&n 的结果是一个 int* 类型的指针，所以推导出变量 f 的类型是 int*。
// d. 第 4 行中，由双引号""包围起来的字符串是 const char* 类型，
// 所以推导出变量 url 的类型是 const char*，也即一个常量指针。

// 1.auto和 const 的结合使用

// （1） auto 与 const 结合的用法

//     a. 当类型不为引用时，auto 的推导结果将不保留表达式的 const 属性；

//     b. 当类型为引用时，auto 的推导结果将保留表达式的 const 属性。

// （2）程序实例如下
void s3()
{
    int x = 0;
    const auto n = x;   // n 为 const int ，auto 被推导为 int
    auto f = n;         // f 为 const int，auto 被推导为 int（const 属性被抛弃）
    const auto &r1 = x; // r1 为 const int& 类型，auto 被推导为 int
    auto &r2 = r1;      // r1 为 const int& 类型，auto 被推导为 const int 类型
}
// a. 第 2 行代码中，n 为 const int，auto 被推导为 int。
// b. 第 3 行代码中，n 为 const int 类型，但是 auto 却被推导为 int 类型，
// 这说明当=右边的表达式带有 const 属性时，auto 不会    使用 const 属性，而是直接推导出 non-const 类型。
// c. 第 4 行代码中，auto 被推导为 int 类型，这个很容易理解，不再赘述。
// d. 第 5 行代码中，r1 是 const int & 类型，auto 也被推导为 const int 类型，
// 这说明当 const 和引用结合时，auto 的推导将保留    表达式的 const 类型。

// 1.使用auto定义迭代器

//     在使用 stl 容器的时候，需要使用迭代器来遍历容器里面的元素；
//     不同容器的迭代器有不同的类型，在定义迭代器时必须指明。
//     而迭代器的类型有时候比较复杂，请看下面的例子：

// #include <vector>
// using namespace std;
int main1()
{
    vector<vector<int>> v;
    // vector< vector<int> >::iterator i = v.begin();
    auto i = v.begin();
    //使用 auto 代替具体的类型,该句比上一句简洁,
    // 根据表达式 v.begin() 的类型（begin() 函数的返回值类型）来推导出变量i的类型
    return 0;
}
// 1.用于泛型编程

//     auto 的另一个应用就是当我们不知道变量是什么类型，或者不希望指明具体类型的时候，
//     比如泛型编程中。请看下面例子：

// #include <iostream>
// using namespace std;
class A
{
public:
    static int get(void)
    {
        return 100;
    }
};
class B
{
public:
    static const char *get(void)
    {
        return "www.123.com";
    }
};
template <typename T>
void func(void)
{
    auto val = T::get();
    cout << val << endl;
}
int main(void)
{
    func<A>();
    func<B>();
    return 0;
}

/*
    运行结果：
        100
        www.123.com
*/
// 本例中的模板函数 func() 会调用所有类的静态函数 get()，并对它的返回值做统一处理，
// 但是 get() 的返回值类型并不一样，而且不能自动转换。
// 这种要求在以前的 C++ 版本中实现起来非常的麻烦，需要额外增加一个模板参数，
// 并在调用时手动给该模板参数赋值，用以指明变量 val 的类型。
// 但是有了 auto 类型自动推导，编译器就根据 get() 的返回值自己推导出 val 变量的类型，
// 就不用再增加一个模板参数了。