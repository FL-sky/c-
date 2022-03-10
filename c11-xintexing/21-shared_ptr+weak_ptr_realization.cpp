#include <memory>
//using namespace std;

// # 深入分析shared_ptr与weak_ptr的实现

//   stl中使用了shared_ptr来管理一个对象的内部指针，并且使用了weak_ptr来防止前面所提到的shared_ptr循环引用的问题。

//   接下来简单的分析shared_ptr和weak_ptr的实现，最后通过自己写代码来模拟shared_ptr和weak_ptr，达到深入学习的目的：

//   测试代码如下：

int main()
{
    std::shared_ptr<int> sptr(new int(3));
    std::shared_ptr<int> sptr2 = sptr;

    std::weak_ptr<int> wptr = sptr;

    if (!wptr.expired())
    {

        std::shared_ptr<int> sptr3 = wptr.lock();
    }
    return 0;
}

// 问题1:
// 为什么会存在强弱指针的计数 ?
// A
// {
//    B对象弱指针(引用次数     1)  weak_ptr_uses_count
// }
// B{
//    A对象智能指针(引用次数    2)  shared_ptr_uses_count
// }

// 问题2:
// 强弱指针计数的用途是什么，具体的代码实现是什么?

// shared_ptr : 对外堤供接口.并无成员变量    表示强指针
//    父类 : _Ptr_base

// weak_ptr : 对外提供接口，并无成员变曼      表示弱指针
//    父类 : _Ptr_base

//------------------------------------------------------------

// _Ptr_base
// {
// 两个成员变曩:
//     _Ty *_Ptr;             //表示智能指针关联的原始的指针，内部指针
//     _Ref_count_base *_Rep; //用于管理智能指针的次数
// }

// 基类 纯虚类
//     _Ref_count_base
// {
//     virtual void _Destroy() _NOEXCEPT = 0;
//     virtual void _Delete_this() _NOEXCEPT = 0;

//     //实际上表达的是当前有多少个强指针在引用内部指针
//     _Atomic_counter_t _uses; //表示强指针使用次数

//     //实际上表达的是当前_Ref_count_base类型的使用次数
//     _Atomic_counter_t _weaks; //表示弱指针使用次数
// }

// 有一个派生类：
// _Ref_count： //真正的计数器对象，使用时，需要将指针强转为父类指针.仅仅使用接口
//     _Ref_count_base
// {
//     //派生类多了一个成员
//     _Ty *_ptr; //表达的是内部指针
// }

//强指针构造，析构，=赋值 拷贝构造等情况下,计数器的变化
//弱指针构造，析构，=赋值 拷贝构造等情况下，计数器的变化
//弱指针提升为强指针时，计数器的变化

//强指针直接构造（拿原始指针构造）时：
//1. 初始化_Ty * _Ptr
//2. 创建_Ref_count对象
//3. _Ref_count_base对象构造时，会分别为_Uses = 1 并且 _Weaks = 1

//------------------------------

// **计数器增减**的规则：

// 初始化及增加的情形：

// - 当创建一个新的shared_ptr时，内部对象计数器和自身的计数器均置1.

// - 当将另外一个shared_ptr赋值给新的shared_ptr时，内部对象计数器+1,自身计数器不变。

// - 当将另外一个shared_ptr赋值给新的weak_ptr时,内部对象计数器不变,自身计数器+1。

// - 当从weak_ptr获取一个shared_ptr时，内部对象计数器+1,自身计数器不变。

// 减少的情形：

// - 当一个shared_ptr析构时，内部对象计数器-1。当内部对象计数器减为0时，则释放内部对象，并将自身计数器-1。

// - 当一个weak_ptr析构时，自身计数器-1。当自身计数器减为0时，则释放自身_Ref_count*对象。

// 那么就可以自己来模拟强弱指针，并修改成模板。