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

    return 0;
}