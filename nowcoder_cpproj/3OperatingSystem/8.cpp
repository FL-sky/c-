#include <bits/stdc++.h>
using namespace std;
int fun1()
{
    union test
    {
        char c;
        int i;
    };
    test t;
    t.i = 1;
    //如果是大端，则t.c为0x00，则t.c != 1，反之是小端
    cout << (t.c == 1) << endl;
    return (t.c == 1);
}
int main()
{
    fun1();
    return 0;
}