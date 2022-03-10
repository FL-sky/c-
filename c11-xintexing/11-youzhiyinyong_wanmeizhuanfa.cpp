#include <bits/stdc++.h>
using namespace std;

// #### （4）完美转发

// 前面我们提到了，一个声明的右值引用其实是一个左值。这就为我们进行参数转发（传递）造成了问题：

/*void reference(int &v)
{
    std::cout << "左值" << std::endl;
}
void reference(int &&v)
{
    std::cout << "右值" << std::endl;
}
template <typename T>
void pass(T &&v)
{
    std::cout << "普通传参:";
    reference(v); // 始终调用 reference(int &)
}
int main()
{
    std::cout << "传递右值:" << std::endl;
    pass(1); // 1是右值, 但输出左值

    std::cout << "传递左值:" << std::endl;
    int v = 1;
    pass(v); // v是左引用, 输出左值

    return 0;
}*/

// 对于 `pass(1)` 来说，虽然传递的是右值，但由于 `v` 是一个引用，所以同时也是左值。因此 `reference(v)` 会调用 `reference(int&)`，输出『左值』。
// 而对于`pass(v)`而言，`v`是一个左值，为什么会成功传递给 `pass(T&&)` 呢？

// 这是基于**引用坍缩规则**的：在传统 C++ 中，我们不能够对一个引用类型继续进行引用，但 C++ 由于右值引用的出现而放宽了这一做法，从而产生了引用坍缩规则，允许我们对引用进行引用，既能左引用，又能右引用。
// 但是却遵循如下规则：

// | 函数形参类型 | 实参参数类型 | 推导后函数形参类型 |
// | ------------ | ------------ | ------------------ |
// | T&           | 左引用       | T&                 |
// | T&           | 右引用       | T&                 |
// | T&&          | 左引用       | T&                 |
// | T&&          | 右引用       | T&&                |

// 因此，模板函数中使用 `T&&` 不一定能进行右值引用，当传入左值时，此函数的引用将被推导为左值。
// 更准确的讲，**无论模板参数是什么类型的引用，当且仅当实参类型为右引用时，模板参数才能被推导为右引用类型**。这才使得 `v` 作为左值的成功传递。

// 完美转发就是基于上述规律产生的。所谓完美转发，就是为了让我们在传递参数的时候，保持原来的参数类型（左引用保持左引用，右引用保持右引用）。
// 为了解决这个问题，我们应该使用 `std::forward` 来进行参数的转发（传递）：

void reference(int &v)
{
    std::cout << "左值引用" << std::endl;
}
void reference(int &&v)
{
    std::cout << "右值引用" << std::endl;
}
template <typename T>
void pass(T &&v)
{
    std::cout << "普通传参:";
    reference(v);
    std::cout << "std::move 传参:";
    reference(std::move(v));
    std::cout << "std::forward 传参:";
    reference(std::forward<T>(v));
    printf("--------->");
    reference(static_cast<T>(v));
}
int main()
{
    std::cout << "传递右值:" << std::endl;
    pass(1);

    std::cout << "传递左值:" << std::endl;
    int v = 1;
    pass(v);

    return 0;
}

// 输出结果为：

// ```txt
// 传递右值:
// 普通传参:左值引用
// std::move 传参:右值引用
// std::forward 传参:右值引用
// 传递左值:
// 普通传参:左值引用
// std::move 传参:右值引用
// std::forward 传参:左值引用
// ```

// 无论传递参数为左值还是右值，普通传参都会将参数作为左值进行转发，所以 `std::move` 总会接受到一个左值，从而转发调用了`reference(int&&)` 输出右值引用。

// 唯独 `std::forward` 即没有造成任何多余的拷贝，同时**完美转发**(传递)了函数的实参给了内部调用的其他函数。

// > 这里 `std::forward` 和 `std::move` 一样，没有做任何事情，`std::move` 单纯的将左值转化为右值，`std::forward` 也只是单纯的将参数做了一个类型的转换，
// 从是实现来看，`std::forward(v)` 和 `static_cast(v)` 是完全一样的。