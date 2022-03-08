// https://baike.baidu.com/item/%E8%99%9A%E5%87%BD%E6%95%B0/2912832?fr=aladdin

/*
 简单地说，那些被virtual关键字修饰的成员函数，就是虚函数。虚函数的作用，用专业术语来解释就是实现多态性（Polymorphism），
 多态性是将接口与实现进行分离；用形象的语言来解释就是实现以共同的方法，但因个体差异，而采用不同的策略。
 下面来看一段简单的代码。
 */

#include <iostream>
using namespace std;
class A
{
public:
    void print()
    {
        cout << "This is A" << endl;
    }
};

class B : public A
{
public:
    void print()
    {
        cout << "This is B" << endl;
    }
};

int main1()
{
    //为了在以后便于区分，我这段main()代码叫做main1
    A a;
    B b;
    a.print();
    b.print();
    return 0;
}

/*
分别是“This is A”、“This is B”。
通过class A和class B的print（）这个接口，可以看出这两个class因个体的差异而采用了不同的策略，
但这并不是多态性行为（使用的是不同类型的指针），没有用到虚函数的功能。现在把main（）处的代码改一改。
*/

int main()
{
    // main2
    A a;
    B b;
    A *p1 = &a;
    A *p2 = &b;
    p1->print();
    p2->print();
    return 0;
}

/*
运行一下看看结果，结果却是两个This is A（错）。
问题来了，p2明明指向的是class B的对象但却是调用的class A的print（）函数，这不是我们所期望的结果，
那么解决这个问题就需要用到虚函数。
*/