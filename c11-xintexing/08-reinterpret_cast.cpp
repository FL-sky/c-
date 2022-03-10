// # reinterpret_cast

// - ##### 用于进行各种不同类型的转换

//   - 不同类型指针之间
//   - 不同类型引用之间
//   - 指针和能容纳指针的整数类型之间的转换

// - ##### 编译期处理,执行的是逐字节复制的操作

// - ##### 类似于显式强转，后果自负

#include <iostream>
#include <string>

using namespace std;

void foo()
{
    cout << "foo()" << endl;
}

int main0()
{
    int nTemp = 0;

    // 指针转整数
    // int nTemp1 = reinterpret_cast<int>(&nTemp);
    long long nTemp1 = reinterpret_cast<long long>(&nTemp);
    cout << hex << nTemp1 << '\n';

    //整数转指针
    int *p1 = reinterpret_cast<int *>(nTemp1);
    cout << *p1 << '\n';

    //将整型转为指针
    unsigned int nTemp2 = 0x00500000;
    int *pTemp = reinterpret_cast<int *>(nTemp2);

    //将一个函数转为一个函数指针并转回
    void (*fp1)() = reinterpret_cast<void (*)()>(foo);
    int (*fp2)() = reinterpret_cast<int (*)()>(fp1);

    cout << dec << fp2() << '\n';
    return 0;
}

class CFather
{
public:
    CFather()
    {
        m_nTest = 3;
    }

    virtual void foo()
    {
        std::cout << "CFather()::void foo()" << std::endl;
    }

    int m_nTest;
};

class CSon : public CFather
{
public:
    virtual void foo()
    {
        std::cout << "CSon::void foo()" << std::endl;
    }
    int m_nSon;
};

int main()
{
    //显式强转
    int n = 1;
    //int* p = (int*)n;

    //用于各种高危险的转换方
    //整型转指针
    int *p = reinterpret_cast<int *>(n);

    //条种类型的指针转换
    char *pCh = reinterpret_cast<char *>(p);

    //父类，子类指针的转换
    CSon *pSon;
    CFather *pFather;
    pSon = reinterpret_cast<CSon *>(pFather); //不存在检查

    return 0;
}