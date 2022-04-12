#include <bits/stdc++.h>
using namespace std;

class CRefCount
{
public:
    CRefCount()
    {
        m_nUsedCount = 1;
        m_nWeakCount = 1;
    }

    void incUsed()
    {
        m_nUsedCount++;
    }

    int decUsed()
    {
        m_nUsedCount--;
        return m_nUsedCount;
    }

    void incWeak()
    {
        m_nWeakCount++;
    }

    int decWeak()
    {
        m_nWeakCount--;

        return m_nWeakCount;
    }

    int getUsed()
    {
        return m_nUsedCount;
    }

private:
    int m_nUsedCount; //强指针引用次数
    int m_nWeakCount; //弱指针引用次数
};

template <typename T>
class CMySmartPtrBase
{
public:
    CMySmartPtrBase(){};
    ~CMySmartPtrBase(){};

    void mydestroy()
    {
        delete m_Ptr;
    }

    void myrelease()
    {
        if (this->m_pRef != nullptr && this->m_pRef->decWeak() == 0)
        {
            delete m_pRef;
        }
    }

protected:
    T *m_Ptr;
    CRefCount *m_pRef;
};

// #define mydestroy() \
//     ;               \
//     this->mydestroy();
// #define myrelease() \
//     ;               \
//     this->myrelease();
//#define x.m_pRef x.m_pRef
//#define m_pRef this->m_pRef
//#define x.m_Ptr x.m_Ptr
//#define m_Ptr this->m_Ptr
//强指针类型
template <typename T>
class CMyWeakPtr;

template <typename T>
class CStrongPtr : public CMySmartPtrBase<T>
{
    friend class CMyWeakPtr<T>;

public:
    CStrongPtr()
    {
        this->m_Ptr = nullptr;
        this->m_pRef = nullptr;
    }

    explicit CStrongPtr(T *p)
    {
        this->m_Ptr = p;
        this->m_pRef = new CRefCount;
    }

    CStrongPtr(CStrongPtr<T> &obj)
    {

        this->m_Ptr = obj.m_Ptr;
        obj.m_pRef->incUsed();
        this->m_pRef = obj.m_pRef;
    }

    CStrongPtr<T> &operator=(CStrongPtr<T> &obj)
    {

        if (this->m_pRef != nullptr && this->m_pRef->decUsed() == 0)
        {

            // mydestroy();
            // myrelease();
            this->mydestroy();
            this->myrelease();
        }

        this->m_Ptr = obj.m_Ptr;
        obj.m_pRef->incUsed();
        this->m_pRef = obj.m_pRef;

        return *this;
    }

    CStrongPtr(CMyWeakPtr<T> &obj)
    {
        this->m_Ptr = obj.m_Ptr;
        obj.m_pRef->incUsed();
        this->m_pRef = obj.m_pRef;
    }

    ~CStrongPtr()
    {
        if ((this->m_pRef) != nullptr && (this->m_pRef)->decUsed() == 0)
        {
            this->mydestroy();
            this->myrelease();
            // mydestroy();
            // myrelease();
        }
    }

    T &operator*()
    {
        return *this->m_Ptr;
    }

    T *operator->()
    {
        return this->m_Ptr;
    }

    T *get()
    {
        return this->m_Ptr;
    }
};

//强指针类型
template <typename T>
class CMyWeakPtr : public CMySmartPtrBase<T>
{
public:
    friend class CStrongPtr<T>;

    CMyWeakPtr()
    {
        this->m_Ptr = nullptr;
        this->m_pRef = nullptr;
    }

    CMyWeakPtr(CStrongPtr<T> &obj)
    {
        // myrelease();

        this->m_Ptr = obj.m_Ptr;
        obj.m_pRef->incWeak();
        this->m_pRef = obj.m_pRef;
    }

    CMyWeakPtr<T> &operator=(CStrongPtr<T> &obj)
    {
        // myrelease();
        this->myrelease();
        this->m_Ptr = obj.m_Ptr;
        obj.m_pRef->incWeak();
        this->m_pRef = obj.m_pRef;

        return *this;
    }

    CMyWeakPtr(CMyWeakPtr<T> &obj)
    {

        this->m_Ptr = obj.m_Ptr;
        obj.m_pRef->incWeak();
        this->m_pRef = obj.m_pRef;
    }

    ~CMyWeakPtr()
    {
        // myrelease();
        this->myrelease();
    }

    CStrongPtr<T> &lock()
    {
        if (this->m_pRef == nullptr)
        {
            return CStrongPtr<T>();
        }

        return CStrongPtr<T>(*this);
    }

    bool IsExpried()
    {
        if (this->m_pRef == nullptr)
        {
            return true;
        }

        return this->m_pRef->getUsed() == 0;
    }
};

//--

class CSon;

class CTest
{
public:
    // void set(CStrongPtr<CSon> p2)
    // {
    //     m_p1 = p2;
    // }

    void set(CStrongPtr<CSon> &p2)
    {
        m_p1 = p2;
    }

    CStrongPtr<CSon> m_p1;
};

class CSon
{
public:
    // void set(CStrongPtr<CTest> p2)
    // {
    //     m_p1 = p2;
    // }
    void set(CStrongPtr<CTest> &p2)
    {
        m_p1 = p2;
    }

    CMyWeakPtr<CTest> m_p1;
};

void foo()
{
    int x;
    {
        CTest *father = new CTest();
        CSon *son = new CSon();

        CStrongPtr<CTest> ptrFather(father);
        CStrongPtr<CSon> ptrSon(son);

        father->set(ptrSon);
        son->set(ptrFather);
        x = 1 + 2;
    }
    int y = x * x;
}

int main()
{

    foo();

    return 0;
}