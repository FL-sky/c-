#include <bits/stdc++.h>
using namespace std;

int Foo(int a, int b)
{
    return a + b;
}

int main()
{
    // lambda表达式就是匿名函数(没有名字的函数)

    //[]捕获列表()参数列表->返回值
    int c = [](int a, int b) -> int
    {
        //函数体
        return a + b;
    }(1, 2);
    //c = Foo(1,2);

    auto f = [](int a, int b) -> int
    {
        //函数体
        return a + b;
    };
    c = f(1, 2);
    cout << c << endl;

    //函数式编程 多线程 并发
    int c2 = [](int n)
    {
        return [n](int x)
        {
            return n + x;
        }(1);
    }(2);
    cout << c2 << endl;

    auto g = [](int n)
    {
        return [n](int x)
        {
            return n + x;
        };
    };

    int c3 = g(1)(2);

    cout << c << endl;

    return 0;
}