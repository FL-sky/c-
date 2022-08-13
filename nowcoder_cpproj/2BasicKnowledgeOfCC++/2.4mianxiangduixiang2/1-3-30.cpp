// 1.3.30 简述一下虚析构函数，什么作用
// 参考回答

// 1.虚析构函数，是将基类的析构函数声明为virtual，举例如下：

class TimeKeeper
{
public:
    TimeKeeper() {}
    virtual ~TimeKeeper() {}
};
// 2.虚析构函数的主要作用是防止内存泄露。

// 定义一个基类的指针p，在delete p时，如果基类的析构函数是虚函数，这时只会看p所赋值的对象，
// 如果p赋值的对象是派生类的对象，就会调用派生类的析构函数（毫无疑问，在这之前也会先调用基类的构造函数，在调用派生类的构造函数，然后调用派生类的析构函数，基类的析构函数，所谓先构造的后释放）；
// 如果p赋值的对象是基类的对象，就会调用基类的析构函数，这样就不会造成内存泄露。

// 如果基类的析构函数不是虚函数，在delete p时，调用析构函数时，只会看指针的数据类型，而不会去看赋值的对象，这样就会造成内存泄露。

// 答案解析

// 我们创建一个TimeKeeper基类和一些及其它的派生类作为不同的计时方法

// class TimeKeeper
// {
// public:
//     TimeKeeper() {}
//     ~TimeKeeper() {} //非virtual的
// };

//都继承与TimeKeeper
// class AtomicClock : public TimeKeeper
// {
// };
// class WaterClock : public TimeKeeper
// {
// };
// class WristWatch : public TimeKeeper
// {
// };

// 如果客户想要在程序中使用时间，不想操作时间如何计算等细节，这时候我们可以设计factory（工厂）函数，让函数返回指针指向一个计时对象。
// 该函数返回一个基类指针，这个基类指针是指向于派生类对象的

// TimeKeeper *getTimeKeeper()
// {
//     //返回一个指针，指向一个TimeKeeper派生类的动态分配对象
// }
// // 因为函数返回的对象存在于堆中，因此为了在不使用时我们需要使用释放该对象（delete）

// TimeKeeper *ptk = getTimeKeeper();
// delete ptk;
// 此处基类的析构函数是非virtual的，因此通过一个基类指针删除派生类对象是错误的

//     解决办法： 将基类的析构函数改为virtual就正确了

// class TimeKeeper
// {
// public:
//     TimeKeeper() {}
//     virtual ~TimeKeeper() {}
// };
// 声明为virtual之后，通过基类指针删除派生类对象就会释放整个对象（基类 + 派生类）