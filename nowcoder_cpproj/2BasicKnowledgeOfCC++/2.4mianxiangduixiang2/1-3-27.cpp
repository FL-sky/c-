#include <bits/stdc++.h>
using namespace std;

// 1.3.27 说说类方法和数据的权限有哪几种

// 参考回答

// 1.C++通过 public、protected、private 三个关键字来控制成员变量和成员函数的访问权限，它们分别表示公有的、受保护的、私有的，被称为成员访问限定符。

// 关键字      权限
// public      可以被任意实体访问
// protected   只允许子类及本类的成员函数访问
// private     只允许本类的成员函数访问

// 2.下面介绍一个例子。

// 父类：

class Person
{
public:
    Person(const string &name, int age) : m_name(name), m_age(age) {}
    void ShowInfo()
    {
        cout << "姓名：" << m_name << endl;
        cout << "年龄：" << m_age << endl;
    }

protected:
    string m_name; //姓名
private:
    int m_age; //年龄
};
// 子类：

class Teacher : public Person
{
public:
    Teacher(const string &name, int age, const string &title)
        : Person(name, age), m_title(title)
    {
    }

    void ShowTeacherInfo()
    {
        ShowInfo();                         //正确，public属性子类可见
        cout << "姓名：" << m_name << endl; //正确，protected属性子类可见
        cout << "年龄：" << m_age << endl;  //错误，private属性子类不可见

        cout << "职称：" << m_title << endl; //正确，本类中可见自己的所有成员
    }

private:
    string m_title; //职称
};

// 调用方：

void test()
{
    Person person("张三", 22);
    person.ShowInfo();             // public属性,对外部可见
    cout << person.m_name << endl; // protected属性,对外部不可见
    cout << person.m_age << endl;  // private属性,对外部不可见
}