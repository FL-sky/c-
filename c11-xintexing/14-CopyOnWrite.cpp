///**写时拷贝**(COW copy on write)，在所有需要改变值的地方，重新分配内存。

// Student.cpp : Defines the entry point for the console application.
//

#include <bits/stdc++.h>
using namespace std;

struct RefValue
{

    RefValue(const char *pszName);
    ~RefValue();

    void AddRef();
    void Release();

    char *m_pszName;
    int m_nCount;
};

RefValue::RefValue(const char *pszName)
{
    m_pszName = new char[256];

    strcpy(m_pszName, pszName);
    m_nCount = 1;
}

RefValue::~RefValue()
{
    if (m_pszName != NULL)
    {
        delete m_pszName;
        m_pszName = NULL;
    }
}

void RefValue::AddRef()
{
    m_nCount++;
}

void RefValue::Release()
{
    if (--m_nCount == 0)
    {
        delete this;
    }
}

class CStudent
{
public:
    CStudent(const char *pszName);
    CStudent(CStudent &obj);

    void SetName(const char *pszName);

    ~CStudent();

    CStudent &operator=(CStudent &obj);

    void release();

    void Show()
    {
        if (m_pValue->m_nCount > 0)
        {
            cout << hex << (int &)m_pValue->m_pszName << m_pValue->m_pszName << endl;
        }
    }

private:
    RefValue *m_pValue;
};

void CStudent::SetName(const char *pszName)
{
    m_pValue->Release();
    m_pValue = new RefValue(pszName);
}

CStudent::CStudent(const char *pszName)
{
    m_pValue = new RefValue(pszName);
}

CStudent::CStudent(CStudent &obj)
{
    m_pValue = obj.m_pValue;
    m_pValue->AddRef();
}

CStudent::~CStudent()
{
    release();
}

CStudent &CStudent::operator=(CStudent &obj)
{
    if (obj.m_pValue == m_pValue)
    {
        return *this;
    }

    m_pValue->Release();

    m_pValue = obj.m_pValue;
    m_pValue->AddRef();

    return *this;
}

void CStudent::release()
{
    m_pValue->Release();
}

int main(int argc, char *argv[])
{
    CStudent stu1("zhang san");

    CStudent stu2("li si");

    CStudent stu3 = stu2;

    stu2.Show();
    stu3.Show();

    stu2.SetName("li si2");

    stu2.Show();
    stu3.Show();

    //加入以下句子，调式运行会出错
    // stu2.release();
    // stu3.release();
    return 0;
}