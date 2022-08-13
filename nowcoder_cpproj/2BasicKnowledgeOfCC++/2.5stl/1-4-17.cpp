// 1.4.17 说说 push_back 和 emplace_back 的区别
// 参考回答

//     如果要将一个临时变量push到容器的末尾，push_back()需要先构造临时对象，
//     再将这个对象拷贝到容器的末尾，而emplace_back()则直接在容器的末尾构造对象，这样就省去了拷贝的过程。

// 答案解析

//     参考代码：

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int gouzao, kaobeigouzao;
class A
{
public:
    A(int i)
    {
        str = to_string(i);
        // cout << "构造函数" << endl;
        gouzao++;
    }
    ~A() {}
    A(const A &other) : str(other.str)
    {
        // cout << "拷贝构造" << endl;
        kaobeigouzao++;
    }

public:
    string str;
};
int main()
{
    gouzao = kaobeigouzao = 0;
    vector<A> vec;
    vec.reserve(10);
    // for (int i = 0; i < 10; i++)
    // {
    //     vec.push_back(A(i)); //调用了10次构造函数和10次拷贝构造函数,
    //                          // vec.emplace_back(i);  //调用了10次构造函数一次拷贝构造函数都没有调用过
    // }
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    printf("%d %d\n", gouzao, kaobeigouzao);
    vector<A> v2;
    v2.reserve(10);
    gouzao = kaobeigouzao = 0;
    for (int i = 0; i < 10; i++)
    {
        v2.emplace_back(i);
    }
    printf("%d %d\n", gouzao, kaobeigouzao);
    return 0;
}