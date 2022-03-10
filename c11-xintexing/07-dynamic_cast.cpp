// 用于具有**虚函数的基类**与**派生类**之间的**指针或引用**的转换。

// - ##### 基类必须具备虚函数

//   原因：dynamic_cast是**运行时类型检查**，需要运行时类型信息(RTTI)，而这个信息是存储与类的**虚函数表**关系紧密，只有一个类定义了虚函数，才会有虚函数表。

// - ##### 运行时检查，转型不成功则返回一个空指针

// - ##### 非必要不要使用dynamic_cast，有额外的函数开销

// 常见的转换方式：

// - 基类指针或引用转派生类指针（**必须使用**dynamic_cast）

// - 派生类指针或引用转基类指针（可以使用dynamic_cast,但是**更推荐使用static_cast**）

#include <iostream>
#include <string>

//基类与派生类之间的转换

class CFather
{
public:
    CFather()
    {
        m_nTest = 3;
    }

    virtual void foo()
    {
        std::cout << "CFather()::void foo()" << std::endl;
    }

    int m_nTest;
};

class CSon : public CFather
{
public:
    virtual void foo()
    {
        std::cout << "CSon::void foo()" << std::endl;
    }
    int m_nSon;
};

int main0()
{
    CFather f;
    CSon s;
    CFather *pFather = &f;
    CSon *pSon = &s;

    //向下转换，父类转子类（不安全）
    //pSon = pFather;
    pSon = dynamic_cast<CSon *>(pFather); //运行时的检测,返回空
    //pSon->foo(); //运行时，pSon为NULL

    //pFather = static_cast<CFather* >(&s); //向上转换，子类转父类，安全
    pFather = dynamic_cast<CFather *>(&s); //子类转父类也可以通过dynamic_cast，但不是必须的
    pSon = dynamic_cast<CSon *>(pFather);  //运行时的检测,可以通过类型检测
    pSon->foo();
    return 0;
}

int main()
{
    CFather f;
    CSon s;
    CFather *pFather = &f;
    CSon *pSon = &s;

    //使用dynamic_cast前提:
    //必须要有虚函数

    //向上转换,子类转父类安全
    pFather = static_cast<CFather *>(pSon); ///
    //pFather = dynamic_cast<CFather*>(pSon);//不推荐使用，不需要额外的检查，避免开销

    //向下转换，父类转子类不安全
    //有种语法能检测出这种转换是丕安全的. dynamic_cast
    //在运行时刻检测转换是否安全

    // dynamic_cast能够在运行的时刻，检测出被转换的指针的类型（依赖RTTI)
    //有额外的开销，一般而言只有在向下转换时才必须使用
    pSon = dynamic_cast<CSon *>(pFather);
    if (pSon != nullptr)
    {
        pSon->m_nSon = 123;
        std::cout << pSon->m_nSon << std::endl;
    }

    //具有多态类类型的向下转换时必须使用，其余情况可以不用

    return 0;
}