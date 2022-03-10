#include <bits/stdc++.h>
using namespace std;

void foo_constuct()
{
    //这样构造是可以的
    std::unique_ptr<int> p(new int(3));

    //空构造
    std::unique_ptr<int> p4;

    //下面三种写法会报错
    //     std::unique_ptr<int> p2 = p; //需要拷贝构造
    //     std::unique_ptr<int> p3(p);  //需要拷贝构造
    //     p4 = p;                      //需要=运算符重载
    //
} ///因此，这就从根源上杜绝了auto_ptr作为参数传递的写法了

// **2. reset**

//  reset的用法和auto_ptr是一致的：

void foo_reset()
{
    //释放
    int *pNew = new int(3);
    int *p = new int(5);
    {
        std::unique_ptr<int> uptr(pNew);
        uptr.reset(p);
    }
}

//**3.release * *
//
//release与reset一样，也不会释放原来的内部指针，只是简单的将自身置空。

void foo_release()
{
    //释放
    int *pNew = new int(3);
    int *p = NULL;
    {
        std::unique_ptr<int> uptr(pNew);
        p = uptr.release();
    }
}

//4.move * *
//
//但是多了个move的用法：

void foo_move()
{
    int *p = new int(3);

    std::unique_ptr<int> uptr(p);
    std::unique_ptr<int> uptr2 = std::move(uptr); ///之后uptr变为空
    //move等同于剪切操作
}
//因为unique_ptr不能将自身对象内部指针直接赋值给其他unique_ptr，所以这里可以使用std::move()函数，让unique_ptr交出其内部指针的所有权，而自身置空，内部指针不会释放。

//**5.数组 * *
//
//可以采用move的方法来使用数组。
//
//直接使用仍然会报错：

// void foo_ary0()
// {
//     std::vector<std::unique_ptr<int>> Ary;
//     std::unique_ptr<int> p(new int(3));
//     Ary.push_back(p);

//     printf("%d\r\n", *p);
//}

//但是可以采用move的办法，这样就编译通过了：
void foo_ary1()
{
    std::vector<std::unique_ptr<int>> Ary;
    std::unique_ptr<int> uptr(new int(3));
    Ary.push_back(std::move(uptr));

    printf("%d\r\n", *uptr); ///empty
}
int main()
{
    foo_ary1();
    return 0;
}