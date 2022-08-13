// 1.3.19 简述一下什么是常函数，有什么作用

// 类的成员函数后面加 const，表明这个函数不会对这个类对象的数据成员（准确地说是非静态数据成员）作任何改变。
// 在设计类的时候，一个原则就是对于不改变数据成员的成员函数都要在后面加const，而对于改变数据成员的成员函数不能加 const。
// 所以 const 关键字对成员函数的行为作了更明确的限定：
// 有 const 修饰的成员函数（指 const 放在函数参数表的后面，而不是在函数前面或者参数表内），只能读取数据成员，不能改变数据成员；
// 没有 const 修饰的成员函数，对数据成员则是可读可写的。除此之外，在类的成员函数后面加 const 还有什么好处呢？
// 那就是常量（即 const）对象可以调用 const 成员函数，而不能调用非const修饰的函数。
// 正如非const类型的数据可以给const类型的变量赋值一样，反之则不成立。

#include <iostream>
using namespace std;

class CStu
{
public:
    int a;
    CStu()
    {
        a = 12;
    }

    void Show() const
    {
        // a = 13; //常函数不能修改数据成员
        cout << a << "I am show()" << endl;
    }
};

int main()
{
    CStu st;
    st.Show();
    system("pause");
    return 0;
}