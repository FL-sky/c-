#include <bits/stdc++.h>
using namespace std;
// 1.1.12 nullptr调用成员函数可以吗？为什么？
// 参考回答

// 能。

// 原因：因为在编译时对象就绑定了函数地址，和指针空不空没关系。
//给出实例
class animal
{
public:
    void sleep() { cout << "animal sleep" << endl; }
    void breathe() { cout << "animal breathe haha" << endl; }
};
class fish : public animal
{
public:
    void breathe() { cout << "fish bubble" << endl; }
};

void s0()
{

    animal *pAn = nullptr;
    pAn->breathe(); // 输出：animal breathe haha
    fish *pFish = nullptr;
    pFish->breathe(); // 输出：fish bubble
}
void s1()
{

    animal *pAn = NULL;
    pAn->breathe(); // 输出：animal breathe haha
    fish *pFish = NULL;
    pFish->breathe(); // 输出：fish bubble
}
int main()
{
    s0();
    puts("\n---------------\n");
    s1();
    int x = -5;
    cout << x % 7 << endl;
    return 0;
}

// 原因：因为在编译时对象就绑定了函数地址，和指针空不空没关系。
// pAn->breathe();编译的时候，函数的地址就和指针pAn绑定了；调用breath(*this), this就等于pAn。
// 由于函数中没有需要解引用this的地方，所以函数运行不会出错，
// 但是若用到this，因为this=nullptr，运行出错。