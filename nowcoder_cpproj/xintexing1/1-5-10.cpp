// 1.5.10 请你回答一下智能指针有没有内存泄露的情况
// 参考回答

//     智能指针有内存泄露的情况发生。

// 1.智能指针发生内存泄露的情况

//     当两个对象同时使用一个shared_ptr成员变量指向对方，会造成循环引用，使引用计数失效，从而导致内存泄露。

// 2.智能指针的内存泄漏如何解决？ 为了解决循环引用导致的内存泄漏，
// 引入了弱指针weak_ptr，weak_ptr的构造函数不会修改引用计数的值，
// 从而不会对对象的内存进行管理，其类似一个普通指针，但是不会指向引用计数的共享内存，
// 但是可以检测到所管理的对象是否已经被释放，从而避免非法访问。

//程序实例
#include <memory>
#include <iostream>
using namespace std;

class Child;
class Parent
{
private:
    std::shared_ptr<Child> ChildPtr;

public:
    void setChild(std::shared_ptr<Child> child)
    {
        this->ChildPtr = child;
    }

    void doSomething()
    {
        if (this->ChildPtr.use_count())
        {
        }
    }

    ~Parent()
    {
    }
};

class Child
{
private:
    std::shared_ptr<Parent> ParentPtr;

public:
    void setPartent(std::shared_ptr<Parent> parent)
    {
        this->ParentPtr = parent;
    }
    void doSomething()
    {
        if (this->ParentPtr.use_count())
        {
        }
    }
    ~Child()
    {
    }
};

int main()
{
    std::weak_ptr<Parent> wpp;
    std::weak_ptr<Child> wpc;
    std::cout << wpp.use_count() << std::endl;
    std::cout << wpc.use_count() << std::endl;
    {
        std::shared_ptr<Parent> p(new Parent);
        std::shared_ptr<Child> c(new Child);
        p->setChild(c);
        c->setPartent(p);
        wpp = p;
        wpc = c;
        std::cout << p.use_count() << std::endl;
        std::cout << c.use_count() << std::endl;
    }
    std::cout << wpp.use_count() << std::endl;
    std::cout << wpc.use_count() << std::endl;
    return 0;
}
/*
    程序运行结果：
        2
        2
        1
        1
*/
// 上述代码中，parent有一个shared_ptr类型的成员指向孩子，
// 而child也有一个shared_ptr类型的成员指向父亲。
// 然后在创建孩子和父亲对象时也使用了智能指针c和p，
// 随后将c和p分别又赋值给child的智能指针成员parent和parent的智能指针成员child。
// 从而形成了一个循环引用。