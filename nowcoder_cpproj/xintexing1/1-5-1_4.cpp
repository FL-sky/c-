// 4.decltype    求表达式的类型

//     decltype 是 C++11 新增的一个关键字，它和 auto 的功能一样，都用来在编译时期进行自动类型推导。

// (1)为什么要有decltype

//     因为 auto 并不适用于所有的自动类型推导场景，在某些特殊情况下 auto 用起来非常不方便，
// 甚至压根无法使用，所以 decltype 关键字也被引入到 C++11 中。

//     auto 和 decltype 关键字都可以自动推导出变量的类型，但它们的用法是有区别的：

// auto varname = value; decltype(exp) varname = value;
//     其中，varname 表示变量名，value 表示赋给变量的值，exp 表示一个表达式。

//     auto 根据"="右边的初始值 value 推导出变量的类型，
// 而 decltype 根据 exp 表达式推导出变量的类型，跟"="右边的 value 没有关系。

//     另外，auto 要求变量必须初始化，而 decltype 不要求。
// 这很容易理解，auto 是根据变量的初始值来推导出变量类型的，
// 如果不初始化，变量的类型也就无法推导了。decltype 可以写成下面的形式：

// decltype(exp) varname;

// (2)代码示例

// decltype 用法举例
void s1()
{
    int a = 0;
    decltype(a) b = 1;      // b 被推导成了 int
    decltype(10.8) x = 5.5; // x 被推导成了 double
    decltype(x + 100) y;    // y 被推导成了 double
}
