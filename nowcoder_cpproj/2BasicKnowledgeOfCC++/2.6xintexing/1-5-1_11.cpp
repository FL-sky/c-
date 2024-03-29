// 11.Lambda匿名函数

// 所谓匿名函数，简单地理解就是没有名称的函数，又常被称为 lambda 函数或者 lambda 表达式。

// （1）定义

//     lambda 匿名函数很简单，可以套用如下的语法格式：

//         [外部变量访问方式说明符] (参数) mutable noexcept/throw() -> 返回值类型 { 函数体; };

// 其中各部分的含义分别为：

// a. [外部变量方位方式说明符]     [ ] 方括号用于向编译器表明当前是一个 lambda 表达式，其不能被省略。
// 在方括号内部，可以注明当前 lambda 函数的函数体中可以使用哪些“外部变量”。

//     所谓外部变量，指的是和当前 lambda 表达式位于同一作用域内的所有局部变量。

// b. (参数)     和普通函数的定义一样，lambda 匿名函数也可以接收外部传递的多个参数。
// 和普通函数不同的是，如果不需要传递参数，可以连同 () 小括号一起省略；

// c. mutable     此关键字可以省略，如果使用则之前的 () 小括号将不能省略（参数个数可以为 0）。
// 默认情况下，对于以值传递方式引入的外部变量，不允许在 lambda 表达式内部修改它们的值
// （可以理解为这部分变量都是 const 常量）。而如果想修改它们，就必须使用 mutable 关键字。

//     注意:对于以值传递方式引入的外部变量，lambda 表达式修改的是拷贝的那一份，并不会修改真正的外部变量；

// d. noexcept/throw()     可以省略，如果使用，在之前的 () 小括号将不能省略（参数个数可以为 0）。
// 默认情况下，lambda 函数的函数体中可以抛出任何类型的异常。
// 而标注 noexcept 关键字，则表示函数体内不会抛出任何异常；
// 使用 throw() 可以指定 lambda 函数内部可以抛出的异常类型。

// e. -> 返回值类型     指明 lambda 匿名函数的返回值类型。
// 值得一提的是，如果 lambda 函数体内只有一个 return 语句，或者该函数返回 void，
// 则编译器可以自行推断出返回值类型，此情况下可以直接省略"-> 返回值类型"。

// f. 函数体     和普通函数一样，lambda 匿名函数包含的内部代码都放置在函数体中。
// 该函数体内除了可以使用指定传递进来的参数之外，还可以使用指定的外部变量以及全局范围内的所有全局变量。

// （2）程序实例

#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int num[4] = {4, 2, 3, 1};
    //对 a 数组中的元素进行排序
    sort(num, num + 4, [=](int x, int y) -> bool
         { return x < y; });
    for (int n : num)
    {
        cout << n << " ";
    }
    return 0;
}

/*    程序运行结果：
          1 2 3 4
*/