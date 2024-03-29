//智能指针的循环引用

#include <bits/stdc++.h>
using namespace std;

//智能指针：
// 1. 用起来像指针
// 2. 会自己对资源进行释放

class CStudent
{
public:
    CStudent() {}

    void test()
    {
        cout << "CStudent" << endl;
        m_nSex = 1;
    }

private:
    char *m_pszBuf;
    int m_nSex;
};

template <typename T>
class CSmartPtr;

template <typename T>
class CRefCount
{
    friend class CSmartPtr<T>;

public:
    CRefCount(T *pStu)
    {
        m_pObj = pStu;
        m_nCount = 1;
    }

    ~CRefCount()
    {
        delete m_pObj;
        m_pObj = NULL;
    }

    void AddRef()
    {
        m_nCount++;
    }

    void Release()
    {
        if (--m_nCount == 0)
        {
            //这么写就表示自己一定要是一个堆对象
            delete this;
        }
    }

private:
    T *m_pObj;
    int m_nCount;
};

template <typename T>
class CSmartPtr
{
public:
    CSmartPtr()
    {
        m_pRef = NULL;
    }

    CSmartPtr(T *pStu)
    {
        m_pRef = new CRefCount<T>(pStu);
    }

    ~CSmartPtr()
    {
        if (m_pRef != NULL)
        {
            m_pRef->Release();
        }
    }

    CSmartPtr(CSmartPtr &obj)
    {
        m_pRef = obj.m_pRef;
        m_pRef->AddRef();
    }

    CSmartPtr &operator=(CSmartPtr &obj)
    {
        if (m_pRef == obj.m_pRef)
        {
            return *this;
        }

        if (m_pRef != NULL)
        {
            m_pRef->Release();
        }

        m_pRef = obj.m_pRef;
        m_pRef->AddRef();

        return *this;
    }

    void test2()
    {
        cout << "test2" << endl;
    }

    T *operator->()
    {
        return m_pRef->m_pObj;
    }

    T **operator&()
    {
        return &m_pRef->m_pObj;
    }

    T &operator*()
    {
        return *m_pRef->m_pObj;
    }

    operator T *()
    {
        return m_pRef->m_pObj;
    }

private:
    CRefCount<T> *m_pRef;
};

class B;

class A
{

public:
    A() {}
    CSmartPtr<B> m_b;
};

class B
{

public:
    B() {}
    CSmartPtr<A> m_a;
};

int main()
{
    {
        CSmartPtr<A> a = new A;
        CSmartPtr<B> b = new B;
        a->m_b = b;
        b->m_a = a;
    }

    return 0;
}