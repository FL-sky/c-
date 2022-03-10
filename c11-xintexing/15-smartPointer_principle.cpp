//智能指针
#include <bits/stdc++.h>
using namespace std;

//智能指针:
// 1.用起来像指针
// 2．会自己对资源进行释放

class CStudent
{
public:
    CStudent()
    {
        while (false)
            ;
    }

    void test()
    {
        cout << "CStudent" << endl;
        m_nSex = 1; ///
    }

private:
    char *m_pszBuf;
    int m_nSex;
};

//创建一个类，利用该类的构造和析构（进出作用域自动被编译器调用)的机制
//来解决资源自动释放的问题
//智能指针雏形 需要管理资源
class CSmartPtr
{
public:
    //一定要是一个堆对象
    CSmartPtr(CStudent *pobj)
    {
        m_pobj = pobj;
    }
    ~CSmartPtr()
    {
        if (m_pobj != nullptr)
        {
            delete m_pobj;
        }
    }

    //CSmartPtr &operator=(CSmartPtr &) = delete;
    //CSmartPtr(CSmartPtr &) = delete; //不可拷贝构造

    CSmartPtr &operator=(CSmartPtr &sp)
    {
        if (m_pobj != nullptr)
        {
            delete m_pobj;
        }
        m_pobj = sp.m_pobj;
        sp.m_pobj = nullptr;
        return *this;
    }

    //需要想办法让其对象用起来像是一个指针

    //像一个指针的写法
    CStudent *operator->()
    {
        return m_pobj;
    }
    CStudent &operator*()
    {
        return *m_pobj;
    }
    //bool
    operator bool()
    {
        return m_pobj != nullptr;
    }
    //& 取地址
    //...
private:
    CStudent *m_pobj; //将资源放入贺能指针类史.箕理起来
};

int main()
{
    //这里可以完成资源的自动释放
    CSmartPtr sp(new CStudent());
    //CSmartPtr sp = new CStudent();
    //但是，用起来不像是一个指针
    CSmartPtr sp3(new CStudent());

    //解决多次析构销毁的方法
    //1．不允许=号运算符重载，拷贝构造
    //2．使用拷贝移动       auto_ptr 98
    //3. 结合前面的引用计数以及写时拷贝     新的智能指针的写法

    //sp3 = sp;
    //
    sp->test();
    (*sp).test();
    if (sp)
    {
        sp->test();
    }
    return 0;
}