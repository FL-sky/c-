#include <bits/stdc++.h>
using namespace std;

//代码示例
#include <iostream>
using namespace std;

void testfunc(int a, int *b, int &c)
{ //形参a值发生了改变，但是没有影响实参i的值；但形参*b、c的值发生了改变，影响到了实参*j、k的值
    a += 1;
    (*b) += 1;
    c += 1;
    printf("a= %d, b= %d, c= %d\n", a, *b, c); // a= 2, b= 2, c= 2
}
int main()
{
    int i = 1;
    int a = 1;
    int *j = &a;
    int k = 1;
    testfunc(i, j, k);
    printf("i= %d, j= %d, k= %d\n", i, *j, k); // i= 1, j= 2, k= 2
    return 0;
}