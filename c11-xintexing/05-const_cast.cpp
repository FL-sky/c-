// const_cast
// 仅用于进行去除const属性的转换，它也是四个强制类型转换运算符中唯一能够去除const属性的运算符。

// *常量对象或者是基本数据类型不允许转化为非常量对象，只能通过指针和引用来修改:*

#include <iostream>
#include <string>
int xmain()
{
    const int n = 5;
    const std::string s = "Inception";
    // std::string t = const_cast<std::string>(s); //错误
    // int k = const_cast<int>(n);                 //错误
    return 0;
}

//*可以利用const_cast转换为同类型的非const 引用或者指针 : *

int ymain()
{
    const int n = 5;
    // const_cast只针对指针，引用,this指针
    int *k = const_cast<int *>(&n);
    *k = 123;
    int &kRef = const_cast<int &>(n);
    kRef = 456;
    printf("&n=%x\tn=%d\n", &n, n);
    printf("k=%x\t*k=%d\n", k, *k);
    printf("&kRef=%x\tkRef=%d\n", &kRef, kRef);
    //_sleep(1);
    printf("&n=%x\t*(&n)=%d\n", &n, *(&n));

    const std::string s = "Inception";
    std::string &t = const_cast<std::string &>(s); //转换成引用
    // int *k = const_cast<int *>(&n);                //转换成指针
    // *k = 6;                                        //转换后指针指向原来的变量
    t = "helloword 19757~~";
    printf("t=%s\n", t.c_str());
    printf("s=%s\n", s.c_str());
    return 0;
}

// *常成员函数中去除this指针的const属性:*

class CTest
{
public:
    CTest() : m_nTest(2) {}

    //常成员函数
    void foo(int nTest) const
    {
        //m_nTest = nTest;错误
        //const_cast<CTest *>(this)->m_nTest = nTest;
        const_cast<CTest *const>(this)->m_nTest = nTest;
    }

public:
    int m_nTest;
};
int main()
{
    //ymain();
    CTest t;
    t.foo(1);
}