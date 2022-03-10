//vs2019

#include <bits/stdc++.h>
using namespace std;

//**1.auto_ptr的构造及所有权的转移**
int main0()
{
    //通过指针进行构造
    std::auto_ptr<int> aptr(new int(3));

    printf("aptr %p : %d\r\n", aptr.get(), *aptr);

    //这样会编译出错，因为auto_ptr的构造有关键字explicit
    //explicit关键字表示调用构造函数时不能使用隐式赋值，而必须是显示调用
    //std::auto_ptr<int> aptr2 = new int(3);

    //可以用其他的auto_ptr指针进行初始化
    std::auto_ptr<int> aptr2 = aptr;
    printf("aptr2 %p : %d\r\n", aptr2.get(), *aptr2);

    //但是这么内存访问出错，直接0xc05,因为aptr已经释放了其所有权。
    //*aptr = 4;
    printf("aptr %p\r\n", aptr.get());

    return 0;
}

//**2.auto_ptr析构及资源的自动释放**
void foo_release0()
{
    //释放
    int *pNew = new int(3);
    {
        std::auto_ptr<int> aptr(pNew);
    }
}
//- 这里显然，当出了块作用域之后，aptr对象会自动调用析构，然后在析构中会自动的delete其内部指针，也就是出了这个作用域后，其内部指针就被释放了。

//- 当然上面这种写法是不推荐的，因为我们这里本质上就是希望不去管理指针的释放工作，上面的写法就又需要程序员自己操心指针的问题，也就是使用 * *智能指针要避免出现指针的直接使用 * *！

//================
//在这里可以在使用前调用release，从而放弃其内部指针的使用权，但是同样这么做违背了智能指针的初衷。
void foo_release1()
{
    //释放
    int *pNew = new int(3);
    {
        std::auto_ptr<int> aptr(pNew);
        int *p = aptr.release(); ///只是放弃了内部指针的所有权，并没有将其释放
    }
}

//**3.分配新的指针所有权 * *
//
//可以调用reset来重新分配指针的所有权，reset中会先释放原来的内部指针的内存，然后分配新的内部指针。
void foo_reset2()
{
    //释放
    int *pNew = new int(3);
    int *p = new int(5);
    {
        std::auto_ptr<int> aptr(pNew);
        aptr.reset(p); //pNew被释放掉了
    }
}

//**4.=运算符的使用**

void foo_assign()
{
    std::auto_ptr<int> p1;
    std::auto_ptr<int> p2;

    p1 = std::auto_ptr<int>(new int(3));
    *p1 = 4;
    p2 = p1; ///p1被释放掉了，为空!
}

//#### auto_ptr存在的问题
//
//为什么11标准会不让使用auto_ptr，原因是其使用有问题。
//
//** 1. 作为参数传递会存在问题。 * *
//
//因为有拷贝构造和赋值的情况下，会释放原有的对象的内部指针，所以当有函数使用的是auto_ptr时，调用后会导致原来的内部指针释放。

void foo_test(std::auto_ptr<int> p)
{
    printf("%d\r\n", *p);
}

int tmain1()
{
    std::auto_ptr<int> p1 = std::auto_ptr<int>(new int(3));
    foo_test(p1);

    //这里的调用就会出错，因为拷贝构造函数的存在，p1实际上已经释放了其内部指针的所有权了
    printf("%d\r\n", *p1);

    return 0;
}

//**2. 不能使用vector数组 * *
//
//因为数组的实现，所以这么定义会出错：

void foo_ary()
{
    std::vector<std::auto_ptr<int>> Ary;
    std::auto_ptr<int> p(new int(3));
    Ary.push_back(p);

    printf("%d\r\n", *p);
}

int main()
{
    {
        //int* p = new int(3);
        //auto_ptr<int>aptr1(p);
        //auto_ptr<int>aptr2(p);
        //两次析构会崩溃
    } {
        auto_ptr<int> aptr1(new int(3));
        auto_ptr<int> aptr2(new int(111));
        aptr2 = aptr1;
        //aptr1为空
    }
    foo_reset2();
    foo_assign();
    tmain1();
    foo_ary();
    return 0;
}
