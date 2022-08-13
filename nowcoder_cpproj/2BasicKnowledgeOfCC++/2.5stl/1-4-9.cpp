// 以下是两个接口的源代码：
// void resize(size_type new_size)
// {
//     resize(new_size, T());
// }
// void resize(size_type new_size, const T &x)
// {
//     if (new_size < size())
//         erase(begin() + new_size, end()); // erase区间范围以外的数据，确保区间以外的数据无效
//     else
//         insert(end(), new_size - size(), x); // 填补区间范围内空缺的数据，确保区间内的数据有效
// }
#include <iostream>
#include <vector>
using namespace std;
int s1()
{
    vector<int> a;
    cout << "initial capacity:" << a.capacity() << endl;
    cout << "initial size:" << a.size() << endl; /*resize改变capacity和size*/
    a.resize(20);
    cout << "resize capacity:" << a.capacity() << endl;
    cout << "resize size:" << a.size() << endl;
    vector<int> b; /*reserve改变capacity,不改变resize*/
    b.reserve(100);
    cout << "reserve capacity:" << b.capacity() << endl;
    cout << "reserve size:" << b.size() << endl;
    return 0;
}
/*
运行结果：
initial capacity:0
initial size:0
resize capacity:20
resize size:20
reserve capacity:100
reserve size:0
*/

int main()
{
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> w = v;
    w.resize(5);
    for (int i = 0, ui = 5; i < ui; i++)
    {
        printf("%3d", w[i]);
    }
    printf("\nw.capacity()=%d\n", w.capacity());
    //
    w = v;
    w.resize(15);
    for (int i = 0, ui = 15; i < ui; i++)
    {
        printf("%3d", w[i]);
    }
    printf("\nw.capacity()=%d\n", w.capacity());
    return 0;
}

//   注意：如果n大于当前的vector的容量(是容量，并非vector的size)，将会引起自动内存分配。
//   所以现有的pointer,references,iterators将会失效。而内存的重新配置会很耗时间。