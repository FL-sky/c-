// 1.3.7 只定义析构函数，会自动生成哪些构造函数
// 参考答案

// 只定义了析构函数，编译器将自动为我们生成拷贝构造函数和默认构造函数。

// 默认构造函数和初始化构造函数。 在定义类的对象的时候，完成对象的初始化工作。
#include <bits/stdc++.h>
using namespace std;
class Student
{
public: //默认构造函数
    Student()
    {
        num = 1001;
        age = 18;
    } //初始化构造函数
    Student(int n, int a) : num(n), age(a) {}

private:
    int num;
    int age;
};
int main1()
{               //用默认构造函数初始化对象S1
    Student s1; //用初始化构造函数初始化对象S2
    Student s2(1002, 18);
    return 0;
}
// 有了有参的构造了，编译器就不提供默认的构造函数。

// 拷贝构造函数

class Test
{
    int i;
    int *p;

public:
    Test(int ai, int value)
    {
        i = ai;
        p = new int(value);
    }
    ~Test()
    {
        delete p;
    }
    Test(const Test &t)
    {
        this->i = t.i;
        this->p = new int(*t.p);
    }
};

int main2()
{
    Test t1(1, 2);
    Test t2(t1); //将对象t1复制给t2。注意复制和赋值的概念不同。

    return 0;
}
// 赋值构造函数默认实现的是值拷贝（浅拷贝）。

// 答案解析

// 示例如下：
int id = 0;
class HasPtr
{
public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0)
    {
        i = ++id;
    }
    ~HasPtr()
    {
        cout << "~HasPtr " << i << endl;
        delete ps;
    }

private:
    string *ps;
    int i;
};
// 如果类外面有这样一个函数：

HasPtr f(HasPtr hp)
{
    HasPtr ret = hp;
    ///... 其他操作
    return ret;
}
// 当函数执行完了之后，将会调用hp和ret的析构函数，将hp和ret的成员ps给delete掉，
// 但是由于ret和hp指向了同一个对象，因此该对象的ps成员被delete了两次，这样产生一个未定义的错误，
// 所以说，如果一个类定义了析构函数，那么它要定义自己的拷贝构造函数和默认构造函数。

int main3()
{
    HasPtr a1;
    HasPtr rt = f(a1);
    return 0;
}

int main()
{
    main2();
    return 0;
}