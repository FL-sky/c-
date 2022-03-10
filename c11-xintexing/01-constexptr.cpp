#include <bits/stdc++.h>
using namespace std;

#define LEN 10
//时期:
//1．编译期cpP --编译器--> exe
//2．运行期双击exe,exe被执行的时期
const int len_foo()
{
    return 5;
}

constexpr int len_foo1(int a, int b)
{
    //a = 5, b = 6;
    return (a ^ b) + 1;
}

constexpr int size()
{
    int a = 2, b = 3, c = 5;
    a = 7;
    // if (rand() % 2)
    //     return a ^ b | c;
    return a + b + c;
}
int main()
{
    //局部变量，在栈上开辟空间, r在编译期间分配的
    char arr_1[10];
    char arr_2[LEN];

    //int len = 5;
    //char arr_3[len]; //编译器在运行期才能确定该变量的大小,从而分配空间
    //char arr_3[len + 5]; //非法
    ///常量表达式
    // char arr_5[len_foo() + 5];//非法
    char arr6[len_foo1(9, 6)];
    printf("%d\n", sizeof(arr6));

    constexpr int sz = size(); //只有当size是一个constexpr函数时//才是一条正确的声明语句
    printf("%d\n", sz);
    //尽管不能使用普通函数作为constexpr变量的初始值，但是正如6.5.2节(第214页)将要介绍的，新标准允许定义一种特殊的constexpr函数。
    ////这种函数应该足够简单以使得编译时就可以计算其结果,这样就能用constexpr函数去初始化constexpr变量了。

    //===========================
    /*
指针和constexpr
必须明确一点，在constexpr声明中如果定义了一个指针，限定符constexpr仅对指针有效，与指针所指的对象无关:

    const int *p = nullptr;         //p是一个指向整型常量的指针
    constexpr int *q = nullptr;     // q是一个指向整数的常量指针

p和q的类型相差甚远，p是一个指向常量的指针，而q是一个常量指针，其中的关键在于constexpr把它所定义的对象置为了顶层const（参见2.4.3节，第57页)。

与其他常量指针类似，constexpr指针既可以指向常量也可以指向一个非常量:

constexpr int *np = nullptr;        //np是一个指向整数的常量指针，其值为空
int j = 0;
constexpr int i = 42;               //i的类型是整型常量
// i和j都必须定义在函数体之外
constexpr const int *p = &i;        //p是常量指针，指向整型常量i
constexpr int *p1 = &j;             //p1是常量指针，指向整数j


*/
    //===========================
    // 练习2.32:下面的代码是否合法?如果非法，请设法将其修改正确。
    // int null = 0, *p = null;

    const int null = 0;
    int *p = null;
    return 0;
}