// 编译期多态
// 对模板参数而言，多态是通过模板具现化和函数重载解析实现的。以不同的模板参数具现化导致调用不同的函数，这就是所谓的编译期多态。
// 相比较于运行期多态，实现编译期多态的类之间并不需要成为一个继承体系，它们之间可以没有什么关系，但约束是它们都有相同的隐式接口。我们将上面的例子改写为:

#include <bits/stdc++.h>
using namespace std;
class Animal
{
public:
    void shout() { cout << "发出动物的叫声" << endl; };
};
class Dog
{
public:
    void shout() { cout << "汪汪！" << endl; }
};
class Cat
{
public:
    void shout() { cout << "喵喵~" << endl; }
};
class Bird
{
public:
    void shout() { cout << "叽喳!" << endl; }
};
template <typename T>
void animalShout(T &t)
{
    t.shout();
}
int main()
{
    Animal anim;
    Dog dog;
    Cat cat;
    Bird bird;

    animalShout(anim);
    animalShout(dog);
    animalShout(cat);
    animalShout(bird);

    getchar();
}

// 在编译之前，函数模板中t.shout()调用的是哪个接口并不确定。
// 在编译期间，编译器推断出模板参数，因此确定调用的shout是哪个具体类型的接口。
// 不同的推断结果调用不同的函数，这就是编译器多态。这类似于重载函数在编译器进行推导，以确定哪一个函数被调用。