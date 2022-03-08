#include <iostream>
using namespace std;

class A
{ //虚函数示例代码
public:
    virtual void fun() { cout << 1 << endl; }
    virtual void fun2() { cout << 2 << endl; }
};
class B : public A
{
public:
    void fun() { cout << 3 << endl; }
    void fun2() { cout << 4 << endl; }
};

// int main()
// {
//     A *p = new A;
//     p->fun();
//     return 0;
// }

//将上面“虚函数示例代码”添加在这里
int main()
{
    void (*fun)(A *);
    // void (*fun)(A*); 这段定义了一个函数指针名字叫做fun，而且有一个A*类型的参数，
    // 这个函数指针待会儿用来保存从vtbl里取出的函数地址。

    A *p = new B;
    // A* p=new B; new B是向内存（内存分5个区：全局名字空间，自由存储区，寄存器，代码空间，栈）
    // 自由存储区申请一个内存单元的地址然后隐式地保存在一个指针中.然后把这个地址赋值给A类型的指针P。

    long lVptrAddr;
    // long lVptrAddr; 这个long类型的变量待会儿用来保存vptr的值。

    memcpy(&lVptrAddr, p, 4);
    // memcpy(&lVptrAddr,p,4); 前面说了，他们的实例对象里只有vptr指针，
    //  所以我们就放心大胆地把p所指的4bytes内存里的东西复制到lVptrAddr中，
    //  所以复制出来的4bytes内容就是vptr的值，即vtbl的地址。

    //现在有了vtbl的地址了，那么我们现在就取出vtbl第一个slot里的内容。

    memcpy(&fun, reinterpret_cast<long *>(lVptrAddr), 4);
    // memcpy(&fun,reinterpret_cast(lVptrAddr),4); 取出vtbl第一个slot里的内容，并存放在函数指针fun里。
    //  需要注意的是lVptrAddr里面是vtbl的地址，但lVptrAddr不是指针，所以我们要把它先转变成指针类型

    fun(p);
    // fun(p); 这里就调用了刚才取出的函数地址里的函数，也就是调用了B::fun（）这个函数，
    //  也许你发现了为什么会有参数p，其实类成员函数调用时，会有个this指针，这个p就是那个this指针，
    //  只是在一般的调用中编译器自动帮你处理了而已，而在这里则需要自己处理。

    delete p; //释放由p指向的自由空间；
    return 0;
}

// 如果调用B::fun2（）怎么办？那就取出vtbl的第二个slot里的值就行了。

// memcpy(&fun,reinterpret_cast(lVptrAddr+4),4); 为什么是加4呢？///memcpy(&fun, reinterpret_cast<long *>(lVptrAddr+sizeof(int*)), 4);
// 因为一个指针的长度是4bytes(32位机上，64位长度8bytes)，所以加4。
// 或者memcpy(&fun,reinterpret_cast(lVptrAddr)+1,4); 这更符合数组的用法，
// 因为lVptrAddr被转成了long*型别，所以+1就是往后移sizeof(long）的长度。