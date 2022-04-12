#include <bits/stdc++.h>
using namespace std;

int main0()
{
    int t = 10;
    //按值捕获,捕获的是声明匿名函数时,捕获列表参数的值
    auto f = [t]()
    {
        std ::cout << t << std ::endl;
    };

    f();
    //按引用捕获
    auto f2 = [&t]()
    {
        std::cout << t << std::endl;
        t = 13;
    };
    t = 11;
    f2();
    std::cout << t << std ::endl;

    int a, b, c, d;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    //按值捕获所有的变量
    [=]()
    { cout << a << " + " << b << endl; }();
    //按引用捕获所有的变量
    [&]()
    { cout << a++ << " + " << b++ << endl; }();
    //按照值和引用的方式捕获变量
    [a, b, &c, &d]()
    {
        cout << a << " + " << b << endl;
        cout << c++ << " + " << d++ << endl;
    }();

    return 0;
}

int main()
{
    // Create a vector object that contains 10 elements.
    vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }

    // Count the number of even numbers in the vector by
    // using the for_each function and a lambda.
    int evenCount = 0;
    for_each(v.begin(), v.end(), [&evenCount](int n)
             {
                 cout << n;

                 if (n % 2 == 0)
                 {
                     cout << " is even " << endl;
                     ++evenCount;
                 }
                 else
                 {
                     cout << " is odd " << endl;
                 }
             });

    // Print the count of even numbers to the console.
    cout << "There are " << evenCount
         << " even numbers in the vector." << endl;
}
//cmd chcp
//gbk 编码方式