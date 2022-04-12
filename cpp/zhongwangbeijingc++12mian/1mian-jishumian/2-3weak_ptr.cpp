// 如果你仔细思考 std::shared_ptr 就会发现依然存在着资源无法释放的问题。看下面这个例子：
#include <memory>
#include <iostream>
struct A;
struct B;
struct A
{
    std::shared_ptr<B> pointer;
    ~A()
    {
        std::cout << "A 被销毁" << std::endl;
    }
};
struct B
{
    std::shared_ptr<A> pointer;
    ~B()
    {
        std::cout << "B 被销毁" << std::endl;
    }
};
void main1()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;
}

int main()
{
    main();
    return 0;
}
