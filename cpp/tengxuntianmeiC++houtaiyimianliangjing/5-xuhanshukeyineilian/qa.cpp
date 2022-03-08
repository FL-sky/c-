// 5.虚函数可以是内联的吗

// 可以。

// 当使用非多态调用时，编译器可选择内联，例如：

#include <cstdio>
struct Base
{
    virtual ~Base() {}
    virtual void Foo() { printf("Base::Foo( )\n"); }
};
struct Derived : Base
{
    virtual void Foo() { printf("Derived::Foo( )\n"); }
};
Base *b = new Derived; // 非static令编译器不能在编译期知道b指向那个类型的对像
int main()
{
    b->Foo();
    //不可能内联
    b->Base::Foo(); //非多态调用，可以内联（但具体是否内联由编泽器决定）delete b;
}

// 许多时候，派生类的虚函数会调用基类的同名函数，这时候不是多态调用，可以内联。