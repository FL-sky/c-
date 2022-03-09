// 6.空指针 nullptr（原来NULL）

// nullptr 是 nullptr_t 类型的右值常量，专用于初始化空类型指针。
// nullptr_t 是 C++11 新增加的数据类型，可称为“指针空值类型”。
// 也就是说，nullpter 仅是该类型的一个实例对象（已经定义好，可以直接使用），
// 如果需要我们完全定义出多个同 nullptr 完全一样的实例对象。
// 值得一提的是，nullptr 可以被隐式转换成任意的指针类型。例如：
void s1()
{
    int *a1 = nullptr;
    char *a2 = nullptr;
    double *a3 = nullptr;
}
// 显然，不同类型的指针变量都可以使用 nullptr 来初始化，
// 编译器分别将 nullptr 隐式转换成 int、char 以及 double* 指针类型。
// 另外，通过将指针初始化为 nullptr，可以很好地解决 NULL 遗留的问题，比如：

#include <iostream>
using namespace std;
void isnull(void *c)
{
    cout << "void*c" << endl;
}
void isnull(int n)
{
    cout << "int n" << endl;
}
int main()
{
    isnull(NULL); /// error: call of overloaded 'isnull(NULL)' is ambiguous
    isnull(nullptr);
    return 0;
}

/* ///假的吧
    程序运行结果：
    int n
    void*c
*/