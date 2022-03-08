// 1.3.20 说说什么是虚继承，解决什么问题，如何实现？

// 虚继承是解决C++多重继承问题的一种手段，从不同途径继承来的同一基类，会在子类中存在多份拷贝。
// 这将存在两个问题：其一，浪费存储空间；第二，存在二义性问题，通常可以将派生类对象的地址赋值给基类对象，
// 实现的具体方式是，将基类指针指向继承类（继承类有基类的拷贝）中的基类对象的地址，但是多重继承可能存在一个基类的多份拷贝，这就出现了二义性。
// 虚继承可以解决多种继承前面提到的两个问题

#include <bits/stdc++.h>
using namespace std;
class A
{
public:
    int _a;
};
class B : virtual public A
{
public:
    int _b;
};
class C : virtual public A
{
public:
    int _c;
};
class D : public B, public C
{
public:
    int _d;
};
//菱形继承和菱形虚继承的对象模型
int main()
{
    typedef long long ll;
    D d;
    d.B::_a = 1;
    d.C::_a = 2;
    d._b = 3;
    d._c = 4;
    d._d = 5;
    printf("sizeof(D)=%d\tsizeof(d)=%d\n", sizeof(D), sizeof(d));
    vector<ll> v;
    v.push_back(ll(&d.A::_a));
    v.push_back(ll(&d.B::_a));
    v.push_back(ll(&d.C::_a));
    v.push_back(ll(&d._b));
    v.push_back(ll(&d._c));
    v.push_back(ll(&d._d));
    set<ll> st;
    for (int i = 0; i < v.size(); i++)
    {
        printf("%x\t", v[i]);
        st.insert(v[i]);
    }
    printf("\nsize=%d\n", st.size());
    for (set<ll>::iterator it = st.begin(); it != st.end(); it++)
    {
        printf("%x\t", *it);
    }

    return 0;
}