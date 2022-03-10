#include <bits/stdc++.h>
using namespace std;

int test(int n)
{
    cout << n << endl;
    return n;
}

class CTest
{
public:
    CTest() {}
    int MyTest(int n)
    {
        cout << n << endl;
        return n;
    }

    //仿函数
    int operator()(int n)
    {
        cout << n << endl;
        return n;
    }
};

void test2(int a, int b, int c)
{
    cout << a << b << c << endl;
}

int main()
{
    //函数对象包装器
    //为了函数提供了一种容器(封装)
    test(1);
    //支持4种函数的封装
    //1。普通函数
    //2．匿名勇数
    //3. 类的成员函数
    //4．仿函数( 重载了() 运算符的函数)

    //普通函数
    std ::function<int(int)>
        f = test;
    f(123);

    //匿名函数
    std::function<int(int)> f2 = [](int n) -> int
    {
        cout << n << endl;
        return n;
    };
    f2(123);

    ///类的成员函数
    std ::function<int(CTest *, int)> f3 = &CTest ::MyTest; ///注意有默认的this指针
    CTest t;
    f3(&t, 123);

    //仿函数的调用
    t(1234);
    std::function<int(CTest *, int)> f4 = &CTest::operator();
    f4(&t, 12);

    //bind机制
    auto a = std::bind(test2, 1, 2, 3);
    a();

    auto foo2 = std::bind(test2, 1, std::placeholders::_1, 3);
    foo2(1);

    auto foo3 = std::bind(test2, std::placeholders::_2, std::placeholders::_1, 3);
    foo3(5, 7);
    return 0;
}