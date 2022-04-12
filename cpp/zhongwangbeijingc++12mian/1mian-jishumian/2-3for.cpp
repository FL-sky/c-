// 区间 for 迭代
// 终于，C++11 引入了基于范围的迭代写法，我们拥有了能够写出像 Python 一样简洁的循环语句，
// 我们可以进一步简化前面的例子：
#include <iostream>
#include <vector>
#include <algorithm>
int main1()
{
    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end())
        *itr = 4;
    for (auto element : vec)
        std::cout << element << std::endl; // read only
    for (auto &element : vec)
    {
        element += 1;
        // writeable
    }
    for (auto element : vec)
        std::cout << element << std::endl; // read only
}

//------- for_each
// template <typename InputIterator, typename Function>
// Function for_each(InputIterator beg, InputIterator end, Function f)
// {
//     while (beg != end)
//         f(*beg++);
// }
// 能看懂吧！！！

// for_each example
#include <iostream>  // std::cout
#include <algorithm> // std::for_each
#include <vector>    // std::vector

void myfunction(int i)
{ // function:
    std::cout << ' ' << i;
}

struct myclass
{ // function object type:
    void operator()(int i) { std::cout << ' ' << i; }
} myobject;

int main()
{
    std::vector<int> myvector;
    myvector.push_back(10);
    myvector.push_back(20);
    myvector.push_back(30);

    std::cout << "myvector contains:";
    for_each(myvector.begin(), myvector.end(), myfunction);
    std::cout << '\n';

    // or:
    std::cout << "myvector contains:";
    for_each(myvector.begin(), myvector.end(), myobject);
    std::cout << '\n';

    return 0;
}

// 结果：
// myvector contains : 10 20 30 myvector contains : 10 20 30
