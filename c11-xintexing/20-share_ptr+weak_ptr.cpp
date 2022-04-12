#include <bits/stdc++.h>
using namespace std;

// # shared_ptr与weak_ptr

// shared_ptr是带引用计数的智能指针：

// **1. 构造**

// 其初始化多了一种写法：std::make_shared<int>

void foo_construct1()
{
    int *p = new int(3);

    std::shared_ptr<int> sptr(p);
    std::shared_ptr<int> sptr2(new int(4));
    std::shared_ptr<int> sptr3 = sptr2;
    std::shared_ptr<int> sptr4 = std::make_shared<int>(5);
}

//这里显然可以看到有引用计数的存在。
//
//通过修改上面例子种的sptr3的作用域，可以发现，出了块作用域之后，shared_ptr对应的引用计数的值减少了。
void foo_construct2()
{
    int *p = new int(3);

    std::shared_ptr<int> sptr(p);
    std::shared_ptr<int> sptr2(new int(4));
    {
        std::shared_ptr<int> sptr3 = sptr2;
    }

    std::shared_ptr<int> sptr4 = std::make_shared<int>(5);
}

void foo_construct3()
{
    int *p = nullptr;
    {
        p = new int(3);

        std::shared_ptr<int> sptr(p);
        std::shared_ptr<int> sptr2(new int(4));
        {
            std::shared_ptr<int> sptr3 = sptr2;
        }
    } ///出了作用域后，p被销毁
    std::shared_ptr<int> sptr4 = std::make_shared<int>(5);
}

//**2. 注意事项： * *
//
// 1. 如果用同一个指针去初始化两个shared_ptr时，则引用计数仍然会出错：

void foo_test()
{
    int *p = new int(3);

    {
        std::shared_ptr<int> sptr(p);

        {
            std::shared_ptr<int> sptr2(p);
        }
    }
} //异常
//显然出了最里面的作用域之后，sptr2对象就已经释放了，此时，对于sptr2来说，p的引用计数为0，所有p被释放，但是实际上sptr还存在，所以再释放sptr时，就会0xc0000005.

// 2. shared_ptr最大的问题是存在循环引用的问题：
//
//如果两个类的原始指针的循环使用，那么会出现重复释放的问题：

class CPerson;
class CSon;
/// <summary>
/// 循环引用问题
/// </summary>
class CPerson;
class CSon;

class Cperson
{
public:
    Cperson()
    {
    }

    void Set(std::shared_ptr<CSon> pSon)
    {
        m_pSon = pSon;
    }

    ~Cperson()
    {
    }

    std::weak_ptr<CSon> m_pSon;
};

class CSon
{
public:
    CSon()
    {
    }

    void Set(std::shared_ptr<Cperson> pParent)
    {
        m_pParent = pParent;
    }

    ~CSon()
    {
    }

    std::shared_ptr<Cperson> m_pParent;
};

void testShared0()
{
    CSon *pSon = new CSon();
    Cperson *pPer = new Cperson();

    {
        std::shared_ptr<Cperson> shared_Parent(pPer);
        std::shared_ptr<CSon> shared_Son(pSon);

        shared_Parent->Set(shared_Son);
        shared_Son->Set(shared_Parent);

        printf("pSon : use_count = %d\r\n", shared_Son.use_count());
        printf("pPer : use_count = %d\r\n", shared_Parent.use_count());
    }
}

void testShared1()
{
    //循环的引用，会出现析构异常
    //解决方法，改一个为弱指针。
    {
        std::shared_ptr<Cperson> shared_Parent(new Cperson());
        std::shared_ptr<CSon> shared_Son(new CSon());

        shared_Parent->Set(shared_Son);
        shared_Son->Set(shared_Parent);

        printf("pSon : use_count = %d\r\n", shared_Son.use_count());
        printf("pPer : use_count = %d\r\n", shared_Parent.use_count());
    }
}

void testWeak()
{
    struct po
    {
        int x, y;
        po(int x = 0, int y = 0) : x(x), y(y) {}
    };

    std::shared_ptr<po> sharedPtr(new po(-1, -2));
    std::weak_ptr<po> weakPtr(sharedPtr);

    printf("sharedPtr_Count = %d, weakPtr_Count = %d, Value = %d \r\n", sharedPtr.use_count(), weakPtr.use_count(), *sharedPtr);
    //当weakPtr为空或者对应的shared_ptr不再有内部指针时，expired返回为true.
    if (!weakPtr.expired())
    {
        std::shared_ptr<po> sharedPtr2 = weakPtr.lock();
        printf("sharedPtr_Count = %d, weakPtr_Count = %d, Value = %d \r\n", sharedPtr.use_count(), weakPtr.use_count(), *sharedPtr);
        *sharedPtr2 = 5;
    }

    printf("sharedPtr_Count = %d, weakPtr_Count = %d, Value = %d \r\n", sharedPtr.use_count(), weakPtr.use_count(), *sharedPtr);
}

int main()
{
    // foo_construct3();
    // testShared1();
    testWeak();
    return 0;
}
