// 1.5.9 说说智能指针及其实现，shared_ptr 线程安全性，原理
// 参考回答

//     1. C++里面的四个智能指针: auto_ptr, shared_ptr, weak_ptr, unique_ptr 其中后三个是c++11支持，
//     并且第一个已经被11弃用。

// 为什么要使用智能指针

//     智能指针的作用是管理一个指针，因为存在以下这种情况：申请的空间在函数结束时忘记释放，造成内存泄漏。
//     使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，
//     当超出了类的作用域是，类会自动调用析构函数，析构函数会自动释放资源。
//     所以智能指针的作用原理就是在函数结束时自动释放内存空间，不需要手动释放内存空间。

// 四种指针分别解决的问题以及各自特性如下：

// （1）auto_ptr（C++98的方案，C++11已经弃用）

//程序实例
#include <bits/stdc++.h>
using namespace std;
void s1()
{
    auto_ptr<string> p1(new string("I reigned loney as a cloud."));
    auto_ptr<string> p2;
    p2 = p1; // auto_ptr不会报错
}
//     采用所有权模式。此时不会报错，p2剥夺了p1的所有权，但是当程序运行时访问p1将会报错。
//     所以auto_ptr的缺点是：存在潜在的内存崩溃问题。

// （2）unique_ptr（替换auto_ptr）

//     unique_ptr实现独占式拥有或严格拥有概念，保证同一时间内只有一个智能指针可以指向该对象。
//     它对于避免资源泄露，例如，以new创建对象后因为发生异常而忘记调用delete时的情形特别有用。

//程序实例
void s2()
{
    auto_ptr<string> p3(new string("I reigned loney as a cloud."));
    auto_ptr<string> p4;
    p4 = p3; //此时不会报错
}
// 采用所有权模式，和上面例子一样。编译器认为P4=P3非法，避免了p3不再指向有效数据的问题。
// 因此，unique_ptr比auto_ptr更安全。
// 另外unique_ptr还有更聪明的地方：当程序试图将一个 unique_ptr 赋值给另一个时，
// 如果源 unique_ptr 是个临时右值，编译器允许这么做；
// 如果源 unique_ptr 将存在一段时间，编译器将禁止这么做，比如以下代码：

//程序实例
void s3()
{
    unique_ptr<string> pu1(new string("hello world"));
    unique_ptr<string> pu2;
    // pu2 = pu1; // #1 not allowed
    unique_ptr<string> pu3;
    pu3 = unique_ptr<string>(new string("You")); // #2 allowed
}
// 其中#1留下悬挂的unique_ptr(pu1)，这可能导致危害。
// 而#2不会留下悬挂的unique_ptr，因为它调用 unique_ptr 的构造函数，
// 该构造函数创建的临时对象在其所有权让给 pu3 后就会被销毁。
// 这种随情况而已的行为表明，unique_ptr 优于允许两种赋值的auto_ptr 。
//  注意：如果确实想执行类似与#1的操作，要安全的重用这种指针，可给它赋新值。
//  C++有一个标准库函数std::move()，让你能够将一个unique_ptr赋给另一个。例如：

//程序实例
void s4()
{
    // unique_ptr<string> ps1, ps2;
    // ps1 = demo("hello");
    // ps2 = move(ps1);
    // ps1 = demo("alexia");
    // cout << *ps2 << *ps1 << endl;
}

// （3）shared_ptr（非常好使）

// shared_ptr实现共享式拥有概念。多个智能指针可以指向相同对象，
// 该对象和其相关资源会在“最后一个引用被销毁”时候释放。
// 从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。
// 可以通过成员函数use_count()来查看资源的所有者个数。
// 除了可以通过new来构造，还可以通过传入auto_ptr, unique_ptr,weak_ptr来构造。
// 当我们调用release()时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。

// shared_ptr 是为了解决 auto_ptr 在对象所有权上的局限性(auto_ptr 是独占的),
// 在使用引用计数的机制上提供了可以共享所有权的智能指针。其成员函数如下：

// use_count    返回引用计数的个数

// unique    返回是否是独占所有权( use_count 为 1)

// swap    交换两个 shared_ptr 对象(即交换所拥有的对象)

// reset    放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少

// get    返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的.
// 如 shared_ptr<int> sp(new int(1)); sp 与 sp.get()是等价的

// （4）weak_ptr

//     weak_ptr 是一种不控制对象生命周期的智能指针, 它指向一个 shared_ptr 管理的对象。
//     进行该对象的内存管理的是那个强引用的 shared_ptr。
//     weak_ptr只是提供了对管理对象的一个访问手段。
//     weak_ptr 设计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作，
//     它只可以从一个 shared_ptr 或另一个 weak_ptr 对象构造,
//     它的构造和析构不会引起引用记数的增加或减少。
//     **weak_ptr是用来解决shared_ptr相互引用时的死锁问题**，
//     如果说两个shared_ptr相互引用，那么这两个指针的引用计数永远不可能下降为0，资源永远不会释放。
//     它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，
//     shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。

//程序实例
class B;
class A
{
public:
    shared_ptr<B> pb_;
    ~A()
    {
        cout << "A delete\n";
    }
};
class B
{
public:
    shared_ptr<A> pa_;
    ~B()
    {
        cout << "B delete\n";
    }
};
void fun()
{
    shared_ptr<B> pb(new B());
    shared_ptr<A> pa(new A());
    pb->pa_ = pa;
    pa->pb_ = pb;
    cout << pb.use_count() << endl;
    cout << pa.use_count() << endl;
}
int main1()
{
    fun();
    return 0;
}
// 可以看到fun函数中pa ，pb之间互相引用，两个资源的引用计数为2，当要跳出函数时，
// 智能指针pa，pb析构时两个资源引用计数会减一，但是两者引用计数还是为1，
// 导致跳出函数时资源没有被释放（A B的析构函数没有被调用），
// 如果把其中一个改为weak_ptr就可以了，我们把类A里面的shared_ptr pb_;
// 改为weak_ptr pb; 运行结果如下，这样的话，资源B的引用开始就只有1，
// 当pb析构时，B的计数变为0，B得到释放，B释放的同时也会使A的计数减一，
// 同时pa析构时使A的计数减一，那么A的计数为0，A得到释放。

// 注意：我们不能通过weak_ptr直接访问对象的方法，比如B对象中有一个方法print()，
// 我们不能这样访问，pa->pb->print(); 英文pb是一个weak_ptr，应该先把它转化为shared_ptr，
// 如：shared_ptr p = pa->pb_.lock(); p->print();

// 1.线程安全性

//     多线程环境下，调用不同shared_ptr实例的成员函数是不需要额外的同步手段的，
//     即使这些shared_ptr拥有的是同样的对象。但是如果多线程访问（有写操作）同一个shared_ptr，
//     则需要同步，否则就会有race condition 发生。
//     也可以使用 shared_ptr overloads of atomic functions来防止race condition的发生。

//     多个线程同时读同一个shared_ptr对象是线程安全的，
//     但是如果是多个线程对同一个shared_ptr对象进行读和写，则需要加锁。

//     多线程读写shared_ptr所指向的同一个对象，不管是相同的shared_ptr对象，
//     还是不同的shared_ptr对象，也需要加锁保护。例子如下：

//程序实例
#include <thread>
#include <mutex>
shared_ptr<long> global_instance = make_shared<long>(0);
std::mutex g_i_mutex;

void thread_fcn()
{
    // std::lock_guard<std::mutex> lock(g_i_mutex);

    // shared_ptr<long> local = global_instance;

    for (int i = 0; i < 100000000; i++)
    {
        *global_instance = *global_instance + 1;
        //*local = *local + 1;
    }
}

int main(int argc, char **argv)
{
    thread thread1(thread_fcn);
    thread thread2(thread_fcn);

    thread1.join();
    thread2.join();

    cout << "*global_instance is " << *global_instance << endl;

    return 0;
}
// 在线程函数thread_fcn的for循环中，2个线程同时对global_instance进行加1的操作。
// 这就是典型的非线程安全的场景，最后的结果是未定的，运行结果如下：

//         *global_instance is 197240539

// 如果使用的是每个线程的局部shared_ptr对象local，因为这些local指向相同的对象，
// 因此结果也是未定的，运行结果如下：            *global_instance is 160285803

// 因此，这种情况下必须加锁，将thread_fcn中的第一行代码的注释去掉之后，
// 不管是使用global_instance，还是使用local，得到的结果都是：

//         *global_instance is 200000000