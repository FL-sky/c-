///static_cast用于基类与派生类的转换过程中，但是没有运行时类型检查。

#include <iostream>
#include <string>

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
    virtual void foo()
    {
        std::cout << "CSon::void foo()" << std::endl;
    }
};

int main()
{
    CFather *pFather = nullptr;
    CSon *pSon = nullptr;

    //pFather = pSon;
    //pFather = static_cast<CFather*>(pSon);

    //pSon = pFather;
    //pSon = static_cast<CSon *>(pFather);

    //父类转子类.(丕安全)
    //pson = pFather;
    pSon = static_cast<CSon *>(pFather); //不安全.,.没有提供运行时的检测

    //子类转父类(安全)..
    pFather = pSon;
    pFather = static_cast<CFather *>(pSon);

    return 0;
}