// 3.auto关键字

//     用于定义变量，编译器可以自动判断的类型（前提：定义一个变量时对其进行初始化）。

//程序实例
#include <vector>
using namespace std;
int main()
{
    vector<vector<int>> v;
    vector<vector<int>>::iterator i = v.begin();
    return 0;
}
// 可以看出来，定义迭代器 i 的时候，类型书写比较冗长，容易出错。
// 然而有了 auto 类型推导，我们大可不必这样，只写一个 auto 即可。