//代码示例

#include <iostream>
using namespace std;
class A
{ //虚函数示例代码2
public:
    virtual void fun() { cout << "A::fun" << endl; }
    virtual void fun2() { cout << "A::fun2" << endl; }
};
class B : public A
{
public:
    void fun() { cout << "B::fun" << endl; }
    void fun2() { cout << "B::fun2" << endl; }
}; // end//虚函数示例代码2
int main1()
{
    void (A::*fun)(); //定义一个函数指针
    A *p = new B;
    fun = &A::fun;
    (p->*fun)();
    fun = &A::fun2;
    (p->*fun)();
    delete p;
    return 0;
}

// 误区
// 你能估算出结果吗？如果你估算出的结果是A::fun和A::fun2，哈哈，恭喜恭喜，你中圈套了。
// 其实真正的结果是B::fun和B::fun2，如果你想不通就接着往下看。
// 给个提示，&A::fun和&A::fun2是真正获得了虚函数的地址吗？
// 首先我们回到第二部分，通过段实作代码，得到一个“通用”的获得虚函数地址的方法。

//将上面“虚函数示例代码2”添加在这里
void CallVirtualFun(void *pThis, int index = 0)
{
    void (*funptr)(void *);
    long lVptrAddr;
    memcpy(&lVptrAddr, pThis, 4);
    // memcpy(&funptr, reinterpret_cast<long *>(lVptrAddr) + index, 4);
    memcpy(&funptr, reinterpret_cast<long *>(lVptrAddr + index * sizeof(int *)), 4);
    funptr(pThis); //调用
}
int main2()
{
    A *p = new B;
    CallVirtualFun(p);    //调用虚函数p->fun()
    CallVirtualFun(p, 1); //调用虚函数p->fun2()
    return 0;
}

int main()
{
    main1();
    return 0;
}