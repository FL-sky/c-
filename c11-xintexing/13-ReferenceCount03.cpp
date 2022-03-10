///最后，我们将该引用计数做一个简易的封装，也就是把引用计数作为一个新的类来使用：

//but BUG特别多,算是改对了吧
#include <bits/stdc++.h>
using namespace std;

void clearValue(vector<void *> &vec);
struct RefValue
{

    RefValue(const char *pszName)
    {
        m_pszName = new char[strlen(pszName) + 1];
        memcpy(m_pszName, pszName, strlen(pszName) + 1);
        m_nCount = 1;
        printf("RefValue::RefValue(const char *pszName)\t\t&%s=%x\n", m_pszName, &m_pszName[0]);
    }
    ~RefValue()
    {

        if (m_pszName != NULL)
        {
            delete m_pszName;
            m_pszName = NULL;
        }
    }

    void AddRef()
    {
        m_nCount++;
    }
    bool Release()
    {
        if (--m_nCount == 0)
        {
            clearValue(vec);
            delete this;
            return true;
        }
        return false;
    }

    char *m_pszName;
    int m_nCount;

    vector<void *> vec;
    void addstar(void *ptr)
    {
        vec.push_back(ptr);
    }
};

class CStudent
{
public:
    CStudent(const char *pszName)
    {
        printf("CStudent::CStudent(const char *pszName)\t\t&%s=%x\n", pszName, &pszName[0]);
        m_pValue = new RefValue(pszName);
        m_pValue->addstar(this);
    }
    CStudent(CStudent &obj)
    {
        m_pValue = obj.m_pValue;
        m_pValue->AddRef();
        m_pValue->addstar(this);
    }

    ~CStudent()
    {
        if (m_pValue != NULL)
            release();
    }

    CStudent &operator=(CStudent &obj)
    {
        if (obj.m_pValue == m_pValue)
        {
            return *this;
        }

        m_pValue->Release(); ///

        m_pValue = obj.m_pValue;
        m_pValue->AddRef();

        return *this;
    }

    void release()
    {
        if (m_pValue->Release() == true)
        {
            //m_pValue = NULL;
        }
    }

    void Show()
    {
        if (m_pValue->m_nCount > 0)
        {
            cout << hex << (int &)m_pValue->m_pszName << "\t" << m_pValue->m_nCount << endl;
        }
    }

    void clearM_pValue()
    {
        m_pValue = NULL;
    }

private:
    RefValue *m_pValue;
};

void clearValue(vector<void *> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        ((CStudent *)vec[i])->clearM_pValue();
    }
    vec.clear();
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
    //stu3.release();

    stu3.Show();

    stu3.release();

    // catch (const char *msg)
    // catch (std::exception &msg)
    // {
    //     cout << msg.what() << endl;
    // }
    return 0;
}

int main()
{ ////try catch 一点用也没有
    try
    {
        main0();
    }
    catch (std::exception &msg)
    {
        cout << msg.what() << endl;
    }
    return 0;
}
// **问题**：

// 上面的做法能在一定程度上解决资源多次重复申请的浪费，但是仍然存在两个核心的问题。

// - 如果对其中某一个类对象中的资源进行了修改，那么所有引用该资源的对象全部会被修改，这显然是错误的。
// - 当前的计数器作用于Student类，在使用时候，需要强行加上引用计数类，这样复用性不好，使用不方便。