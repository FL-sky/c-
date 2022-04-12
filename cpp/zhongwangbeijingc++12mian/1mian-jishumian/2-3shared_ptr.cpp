// std::make_shared 就能够用来消除显式的使用 new，所以 std::make_shared 会分配创建传入参
// 数中的对象，并返回这个对象类型的 std::shared_ptr 指针。例如：
#include <iostream>

#include <memory>
void foo(std::shared_ptr<int> i)
{
    (*i)++;
}
int main()
{
    // std::shared_ptr<int> p0 = new int(10);
    //不存在从 "int *" 转换到 "std::shared_ptr<int>" 的适当构造函数

    // auto pointer = new int(10); // illegal, no direct assignment
    // Constructed a std::shared_ptr
    {
        auto pointer = std::make_shared<int>(10);
        foo(pointer);
        std::cout << *pointer << std::endl; // 11
        // The shared_ptr will be destructed before leaving the scope
    }
    int *p = nullptr;
    {
        //         std::shared_ptr 可以通过 get() 方法来获取原始指针，通过 reset() 来减少一个引用计数，并
        // 通过 use_count() 来查看一个对象的引用计数。例如：
        auto pointer = std::make_shared<int>(10);
        auto pointer2 = pointer;                                                     // 引用计数 +1
        auto pointer3 = pointer;                                                     // 引用计数 +1
        p = pointer2.get();                                                          // 这样不会增加引用计数
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 3
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3
        pointer2.reset();
        std::cout << "reset pointer2:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 2
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0, pointer2 已 reset
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2
        pointer3.reset();
        std::cout << "reset pointer3:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 1
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 0, pointer3 已 reset

        pointer.reset();
        std::cout << "reset pointer:" << std::endl;
        std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
        std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
        std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;
        // std::cout << *pointer << std::endl; ///wrong
    } //
    std::cout << *p << std::endl;
    return 0;
}