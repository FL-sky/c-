// 2.成员变量默认初始化

// 好处：构建一个类的对象不需要用构造函数初始化成员变量。

//程序实例
#include <iostream>
using namespace std;
class B
{
public:
    int m = 1234; //成员变量有一个初始值
    int n;
};
int main()
{
    B b;
    cout << b.m << endl;
    return 0;
}