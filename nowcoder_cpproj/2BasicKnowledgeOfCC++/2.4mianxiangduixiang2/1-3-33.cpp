// 1.3.33仿函数了解吗？有什么作用
// 参考回答

// 1.仿函数（functor）又称为函数对象（function object）是一个能行使函数功能的类。
// 仿函数的语法几乎和我们普通的函数调用一样，不过作为仿函数的类，都必须重载operator()运算符，举个例子：
#include <bits/stdc++.h>
using namespace std;
class Func
{
public:
    void operator()(const string &str) const
    {
        cout << str << endl;
    }
};
void s1()
{
    Func myFunc;
    myFunc("helloworld!");
}

// >>>helloworld!

// 1.仿函数既能想普通函数一样传入给定数量的参数，还能存储或者处理更多我们需要的有用信息。我们可以举个例子：

// 假设有一个vector<string>，你的任务是统计长度小于5的string的个数，如果使用count_if函数的话，你的代码可能长成这样：

bool LengthIsLessThanFive(const string &str)
{
    return str.length() < 5;
}
void s2()
{
    vector<string> vec = {"3f2", "f3tg3g", "fc2f", "ggg34f43", "32", "f343"};
    int res = count_if(vec.begin(), vec.end(), LengthIsLessThanFive);
    printf("res=%d\n", res);
}

// 其中count_if函数的第三个参数是一个函数指针，返回一个bool类型的值。一般的，如果需要将特定的阈值长度也传入的话，我们可能将函数写成这样：

bool LenthIsLessThan(const string &str, int len)
{
    return str.length() < len;
}
// 这个函数看起来比前面一个版本更具有一般性，但是他不能满足count_if函数的参数要求：count_if要求的是unary function（仅带有一个参数）作为它的最后一个参数。
// 如果我们使用仿函数，是不是就豁然开朗了呢：

class ShorterThan
{
public:
    // https://blog.csdn.net/guoyunfei123/article/details/89003369
    // C++ explicit关键字详解
    explicit ShorterThan(int maxLength) : length(maxLength) {}
    bool operator()(const string &str) const
    {
        return str.length() < length;
    }

private:
    const int length;
};

int main()
{
    s1();
    s2();
    return 0;
}