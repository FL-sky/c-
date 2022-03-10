#include <bits/stdc++.h>
using namespace std;

class CInt
{
public:
    operator int()
    {
        return m_nInt;
    }
    int m_nInt;
};

int zhuanhuan01()
{
    int n = 5;
    float f = 10.0f;
    double dbl = 1.0;
    //本质上发生了隐式转换
    //f = n;
    //static_cast
    //f = static_cast<float>(n);

    //低风险的转换:
    //整型与浮点型
    n = static_cast<int>(dbl);

    //字符与整型
    char ch = 'a';
    n = static_cast<int>(ch);

    //void*指针的转换
    void *p = nullptr;
    int *pN = static_cast<int *>(p);

    //转换运算符的方式
    CInt nobj;
    //int kk = nobj;
    int k = static_cast<int>(nobj);

    //高风险的转换:
    int kk;
    char *p;
    //整型与指针类型转换
    // p = kk;
    //char* k = static_cast<char*>(kk);

    int *pK;
    // char *k = pK;
    ///k = static_cast<ghar*>(pK);

    return 0;
}
