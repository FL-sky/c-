// 5.智能指针 shared_ptr

//     和 unique_ptr、weak_ptr 不同之处在于，多个 shared_ptr 智能指针可以共同使用同一块堆内存。
//     并且，由于该类型智能指针在实现上采用的是引用计数机制，
//     即便有一个 shared_ptr 指针放弃了堆内存的“使用权”（引用计数减 1），
//     也不会影响其他指向同一堆内存的 shared_ptr 指针（只有引用计数为 0 时，堆内存才会被自动释放）。

#include <iostream>
#include <memory>
using namespace std;
int main()
{ //构建 2 个智能指针
    std::shared_ptr<int> p1(new int(10));
    std::shared_ptr<int> p2(p1); //输出 p2 指向的数据
    cout << *p2 << endl;
    p1.reset(); //引用计数减 1,p1为空指针
    if (p1)
    {
        cout << "p1 is not empty 不为空" << endl;
    }
    else
    {
        cout << "p1 is empty 为空" << endl;
    }                    //以上操作，并不会影响 p2
    cout << *p2 << endl; //判断当前和 p2 同指向的智能指针有多少个
    cout << p2.use_count() << endl;
    return 0;
} /*      程序运行结果：          10  p1 为空  10  1  */