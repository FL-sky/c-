//智能指针
#include <bits/stdc++.h>
using namespace std;

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
    }

private:
    char *m_pszBuf;
    int m_nSex;
};

class CRefCount
{
    friend class CSmartPtr;

    CRefCount(CStudent *pStu)
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
            delete this;
        }
    }

private:
    CStudent *m_pObj;
    int m_nCount;
};

class CSmartPtr
{
public:
    CSmartPtr()
    {
        m_pRef = NULL;
    }

    CSmartPtr(CStudent *pStu)
    {
        m_pRef = new CRefCount(pStu);
    }

    ~CSmartPtr()
    {
        m_pRef->Release();
    }

    CSmartPtr(const CSmartPtr &obj) ///g++下需要const
    {
        //     if (m_pRef != NULL)
        //     {
        //       m_pRef->Release();
        //     }

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

    CStudent *operator->()
    {
        return m_pRef->m_pObj;
    }

    CStudent **operator&()
    {
        return &m_pRef->m_pObj;
    }

    CStudent &operator*()
    {
        return *m_pRef->m_pObj;
    }

    operator CStudent *()
    {
        return m_pRef->m_pObj;
    }

    //   operator CStudent()
    //   {
    //     return *m_pStu;
    //   }

private:
    CRefCount *m_pRef;
};

int main(int argc, char *argv[])
{
    CSmartPtr obj = new CStudent;
    CSmartPtr obj4 = new CStudent;

    CSmartPtr obj2 = obj;

    {
        CSmartPtr obj3;

        obj3 = obj;
        obj3 = obj4;
    }

    //CStudent* pStu = new CStudent;
    //obj.test();

    //pStu ==> obj->
    //pStu->test();

    //obj->->test();
    //pStu->test();

    //   obj->test(); //==> pStu->test();
    //
    //   CStudent** ppStu = &obj;
    //
    //   //(obj).test();
    //   (*obj).test();
    //
    //   CSmartPtr obj2 = obj;
    //
    //   obj2->test();

    return 0;
}