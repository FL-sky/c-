// 1.3.16 简述一下移动构造函数，什么库用到了这个函数？
// C++11中新增了移动构造函数。与拷贝类似，移动也使用一个对象的值设置另一个对象的值。但是，又与拷贝不同的是，移动实现的是对象值真实的转移（源对象到目的对象）：源对象将丢失其内容，其内容将被目的对象占有。移动操作的发生的时候，是当移动值的对象是未命名的对象的时候。这里未命名的对象就是那些临时变量，甚至都不会有名称。典型的未命名对象就是函数的返回值或者类型转换的对象。使用临时对象的值初始化另一个对象值，不会要求对对象的复制：因为临时对象不会有其它使用，因而，它的值可以被移动到目的对象。做到这些，就要使用移动构造函数和移动赋值：当使用一个临时变量对对象进行构造初始化的时候，调用移动构造函数。类似的，使用未命名的变量的值赋给一个对象时，调用移动赋值操作。

// 移动操作的概念对对象管理它们使用的存储空间很有用的，诸如对象使用new和delete分配内存的时候。在这类对象中，拷贝和移动是不同的操作：从A拷贝到B意味着，B分配了新内存，A的整个内容被拷贝到为B分配的新内存上。 而从A移动到B意味着分配给A的内存转移给了B，没有分配新的内存，它仅仅包含简单地拷贝指针。 看下面的例子：

// 移动构造函数和赋值
#include <iostream>
#include <string>
using namespace std;

class Example6
{
    string *ptr;

public:
    Example6(const string &str) : ptr(new string(str)) {}
    ~Example6() { delete ptr; }
    // 移动构造函数，参数x不能是const Pointer&& x，
    // 因为要改变x的成员数据的值；
    // C++98不支持，C++0x（C++11）支持
    Example6(Example6 &&x) : ptr(x.ptr)
    {
        x.ptr = nullptr;
    }
    // move assignment
    Example6 &operator=(Example6 &&x)
    {
        delete ptr;
        ptr = x.ptr;
        x.ptr = nullptr;
        return *this;
    }
    // access content:
    const string &content() const { return *ptr; }
    // addition:
    Example6 operator+(const Example6 &rhs)
    {
        return Example6(content() + rhs.content());
    }
};
int main()
{
    Example6 foo("Exam"); // 构造函数
    // Example6 bar = Example6("ple"); // 拷贝构造函数
    Example6 bar(move(foo)); // 移动构造函数
                             // 调用move之后，foo变为一个右值引用变量，
                             // 此时，foo所指向的字符串已经被"掏空"，
                             // 所以此时不能再调用foo
    bar = bar + bar;         // 移动赋值，在这儿"="号右边的加法操作，
                             // 产生一个临时值，即一个右值
                             // 所以此时调用移动赋值语句
    cout << "foo's content: " << foo.content() << '\n';
    return 0;
}

// 执行结果：

// foo's content: Example