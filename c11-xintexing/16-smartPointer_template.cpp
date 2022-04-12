//为智能指针添加模板

#include <iostream>
#include <cstring>

using namespace std;

//智能指针：
// 1. 用起来像指针
// 2. 会自己对资源进行释放

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
        m_nSex = 1;
    }

private:
    char *m_pszBuf;
    int m_nSex;
};

//
template <typename T>
class CSmartPtr;
//

template <typename T>
class CRefCount
{
    friend class CSmartPtr<T>; ///有什么用

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

//致命问题， CSmartPtr中表示的类型是固定的，是CStudent, 需要添加模板
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
        m_pRef->Release();
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

class CTest
{
public:
    CTest()
    {

        while (false)
            ;
    }
};

int main(int argc, char *argv[])
{
    CStudent *pStu = new CStudent();

    // CRefCount<CStudent> ref(pStu);

    CSmartPtr<CStudent> sp1(pStu);
    CSmartPtr<CStudent> sp2(new CStudent()); //拷贝构造???
    CSmartPtr<CStudent> sp3(sp2);
    CSmartPtr<CStudent> sp4;
    sp4 = sp2;
    // sp2 = sp1; //运算符重载

    //
    CSmartPtr<CTest> sp5(new CTest);

    CSmartPtr<int> pi(new int(10));
    cout << *pi << endl;
    return 0;
}