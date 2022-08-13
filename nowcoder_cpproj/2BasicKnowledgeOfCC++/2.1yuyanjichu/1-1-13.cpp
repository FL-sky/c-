#include <bits/stdc++.h>
using namespace std;
// 1.1.13 说说什么是野指针，怎么产生的，如何避免
//  参考回答

// 概念：野指针就是指针指向的位置是不可知的（随机的、不正确的、没有明确限制的）

// 产生原因：释放内存后指针不及时置空（野指针），依然指向了该内存，那么可能出现非法访问的错误。
// 这些我们都要注意避免。

// 避免办法：

// （1）初始化置NULL

// （2）申请内存后判空

// （3）指针释放后置NULL

// （4）使用智能指针

// 答案解析

// 产生原因：释放内存后指针不及时置空（野指针），依然指向了该内存，那么可能出现非法访问的错误。
// 这些我们都要注意避免。如：

void f1()
{
    char *p = (char *)malloc(sizeof(char) * 100);
    strcpy(p, "Douya");
    free(p); // p所指向的内存被释放，但是p所指的地址仍然不变
    // ...
    if (p != NULL)
    {                               //没有起到防错作用
        strcpy(p, "hello, Douya!"); //出错
    }
}
// 避免办法：

// （1）初始化置NULL

// （2）申请内存后判空

// （3）指针释放后置NULL
void f2(int n)
{
    int *p = NULL;                      //初始化置NULL
    p = (int *)malloc(sizeof(int) * n); //申请n个int内存空间
    assert(p != NULL);                  //判空，防错设计
    p = (int *)realloc(p, 25);          //重新分配内存, p 所指向的内存块会被释放并分配一个新的内存地址
    free(p);
    p = NULL; //释放后置空

    int *p1 = NULL;                     //初始化置NULL
    p1 = (int *)calloc(n, sizeof(int)); //申请n个int内存空间同时初始化为0
    assert(p1 != NULL);                 //判空，防错设计
    free(p1);
    p1 = NULL; //释放后置空

    int *p2 = NULL;     //初始化置NULL
    p2 = new int[n];    //申请n个int内存空间
    assert(p2 != NULL); //判空，防错设计
    delete[] p2;
    p2 = nullptr; //释放后置空
}

int main()
{
    int n = 10;
    int *p = NULL;                      //初始化置NULL
    p = (int *)malloc(sizeof(int) * n); //申请n个int内存空间
    assert(p != NULL);                  //判空，防错设计
    free(p);
    int nn = 25;
    p = NULL;                  //如果已经释放p，且不置NULL，会出错
    p = (int *)realloc(p, nn); //重新分配内存, p 所指向的内存块会被释放并分配一个新的内存地址
    for (int i = 0; i < nn; i++)
    {
        printf("%d ", p[i]);
    }
    p = NULL; //释放后置空
    return 0;
}