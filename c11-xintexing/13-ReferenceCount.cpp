#include <bits/stdc++.h>
using namespace std;

class CStudent
{
public:
    CStudent(const char *pszName); //带参数的构造
    CStudent(CStudent &obj);       ///拷贝构造

    CStudent &operator=(CStudent &obj); ///=运算符重载

    void release();

    void Show()
    {
        cout << hex << (int &)m_pszName << "\t" << m_pszName << endl;
    }

private:
    char *m_pszName;
};

CStudent::CStudent(const char *pszName)
{
    m_pszName = new char[256];

    strcpy(m_pszName, pszName);
}

CStudent::CStudent(CStudent &obj)
{
    m_pszName = obj.m_pszName;

    //strcpy(m_pszName, obj.m_pszName);
}

CStudent &CStudent::operator=(CStudent &obj)
{
    m_pszName = obj.m_pszName;

    return *this;
}

void CStudent::release()
{
    if (m_pszName != NULL)
    {
        delete m_pszName;
        m_pszName = NULL;
    }
}

int main0()
{
    CStudent stu1("zhang san");

    CStudent stu2("li si");

    CStudent stu3 = stu2;

    stu1.Show();
    stu2.Show();
    stu3.Show();

    stu2.release();

    stu3.Show();

    return 0;
}

int main()
{
    main0();
    return 0;
}

// 这样做带来的问题**：

//  但是这样同样存在问题，一旦其中一个对象释放了资源，那么所有的其他对象的资源也被释放了。

//  **解决方法**：增加一个变量，记录**资源使用的次数**。
