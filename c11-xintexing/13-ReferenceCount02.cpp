#include <bits/stdc++.h>
using namespace std;

//增加一个变量，记录**资源使用的次数**。

class CStudent
{
public:
    CStudent(const char *pszName);
    CStudent(CStudent &obj);

    ~CStudent();

    CStudent &operator=(CStudent &obj);

    void release();

    void Show()
    {
        if (*m_pCount > 0)
        {
            cout << hex << (int &)m_pszName << m_pszName << endl;
        }
    }

private:
    char *m_pszName;
    int *m_pCount; ////
};

CStudent::CStudent(const char *pszName)
{
    m_pszName = new char[256];
    m_pCount = new int;

    strcpy(m_pszName, pszName);

    *m_pCount = 1;
}

CStudent::CStudent(CStudent &obj)
{
    m_pszName = obj.m_pszName;

    m_pCount = obj.m_pCount;
    (*m_pCount)++;
}

CStudent::~CStudent()
{
    release();
}

CStudent &CStudent::operator=(CStudent &obj)
{
    if (obj.m_pszName == m_pszName)
    {
        return *this;
    }

    if (--(*m_pCount) == 0)
    {
        delete m_pszName;
        m_pszName = NULL;
        delete m_pCount;
    }

    m_pszName = obj.m_pszName;
    m_pCount = obj.m_pCount;

    (*m_pCount)++;

    return *this;
}

void CStudent::release()
{
    if (m_pszName != NULL && --*m_pCount == 0)
    {
        delete m_pszName;
        m_pszName = NULL;

        delete m_pCount;
        //m_pCount = NULL;
    }
}

int main(int argc, char *argv[])
{
    CStudent stu1("zhang san");

    CStudent stu2("li si");

    CStudent stu3 = stu2;

    stu1.Show();
    stu2.Show();
    stu3.Show();

    stu2.release();
    stu3.release();

    stu3.Show();

    return 0;
}