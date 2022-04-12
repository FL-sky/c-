// 前言
// 今日的C++不再是个单纯的“带类的C”语言，它已经发展成为一个多种次语言所组成的语言集合，其中泛型编程与基于它的STL是C++发展中最为出彩的那部分。
// 在面向对象C++编程中，多态是OO三大特性之一，这种多态称为<运行期多态，也称为动态多态>；
// 在泛型编程中，多态基于template(模板)的具现化与函数的重载解析，这种多态在编译期进行，因此称为<编译期多态或静态多态>。
// 在本文中，我们将了解：

// 1.什么是运行期多态
// 2.什么是编译期多态
// 3.它们的优缺点在哪

// 运行期多态
// 运行期多态的设计思想要归结到类继承体系的设计上去。
// 对于有相关功能的对象集合，我们总希望能够抽象出它们共有的功能集合，在基类中将这些功能声明为虚接口（虚函数），然后由子类继承基类去重写这些虚接口，以实现子类特有的具体功能。
// 典型地我们会举下面这个例子：

// [2-1.png]

#include <bits/stdc++.h>
using namespace std;
class Animal
{
public:
    virtual void shout() = 0;
};
class Dog : public Animal
{
public:
    virtual void shout() { cout << "汪汪！" << endl; }
};
class Cat : public Animal
{
public:
    virtual void shout() { cout << "喵喵~" << endl; }
};
class Bird : public Animal
{
public:
    virtual void shout() { cout << "叽喳!" << endl; }
};

int main1()
{
    Animal *anim1 = new Dog;
    Animal *anim2 = new Cat;
    Animal *anim3 = new Bird;

    //藉由指针（或引用）调用的接口，在运行期确定指针（或引用）所指对象的真正类型，调用该类型对应的接口
    anim1->shout();
    anim2->shout();
    anim3->shout();

    // delete 对象
    // ...
    return 0;
}

// 运行期多态的实现依赖于虚函数机制。当某个类声明了虚函数时，编译器将为该类对象安插一个虚函数表指针，并为该类设置一张唯一的虚函数表，虚函数表中存放的是该类虚函数地址。
// 运行期间通过虚函数表指针与虚函数表去确定该类虚函数的真正实现。

// 运行期多态的优势还在于它使处理异质对象集合称为可能：

//我们有个动物园，里面有一堆动物
int main()
{
    vector<Animal *> anims;

    Animal *anim1 = new Dog;
    Animal *anim2 = new Cat;
    Animal *anim3 = new Bird;
    Animal *anim4 = new Dog;
    Animal *anim5 = new Cat;
    Animal *anim6 = new Bird;

    //处理异质类集合
    anims.push_back(anim1);
    anims.push_back(anim2);
    anims.push_back(anim3);
    anims.push_back(anim4);
    anims.push_back(anim5);
    anims.push_back(anim6);

    for (auto &i : anims)
    {
        i->shout();
    }
    // delete对象
    //...
    return 0;
}
// 总结：运行期多态通过虚函数发生于运行期