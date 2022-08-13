#include <bits/stdc++.h>
using namespace std;

// 参考回答

// 定义不同 指针函数本质是一个函数，其返回值为指针。 函数指针本质是一个指针，其指向一个函数。

// 写法不同

// 指针函数：int *fun(int x,int y);
// 函数指针：int (*fun)(int x,int y);
// 用法不同

// 用法参考答案解析

//指针函数示例
typedef struct _Data
{
    int a;
    int b;
} Data;
//指针函数
Data *f(int a, int b)
{
    Data *data = new Data;
    //...
    return data;
}
int s1()
{
    //调用指针函数
    Data *myData = f(4, 5);
    // Data *myData = static_cast<Data *>(f(4, 5));
    myData = static_cast<Data *>(f(4, 5));
    //...
    cout << myData->a << " " << myData->b << endl;
}

//函数指针示例
int add(int x, int y)
{
    return x + y;
}
//函数指针
int (*fun)(int x, int y);

void s2()
{
    //赋值
    fun = add;
    //调用
    cout << "(*fun)(1,2) = " << (*fun)(1, 2);
    //输出结果
    //(*fun)(1,2) =  3
}

int main()
{
    s1();
    s2();
    return 0;
}