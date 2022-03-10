#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t = 10;
    //按值捕获
    auto f = [t]() mutable
    {
        return ++t;
    };

    auto f2 = [t]() mutable
    {
        return ++t;
    };

    cout << f() << endl;
    cout << f2() << endl;
    cout << f() << endl;
    cout << f2() << endl;
    cout << t << endl;

    return 0;
}