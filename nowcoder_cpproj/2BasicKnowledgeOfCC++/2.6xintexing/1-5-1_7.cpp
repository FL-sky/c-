// 7.基于范围的for循环

//     如果要用 for 循环语句遍历一个数组或者容器，只能套用如下结构：

// for(表达式 1; 表达式 2; 表达式 3){
//     //循环体
// }
//程序实例
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
int main()
{
    char arc[] = "www.123.com";
    int i;
    // for循环遍历普通数组
    for (i = 0; i < strlen(arc); i++)
    {
        cout << arc[i];
    }
    cout << endl;
    vector<char> myvector(arc, arc + 3);
    vector<char>::iterator iter;
    // for循环遍历 vector 容器
    for (iter = myvector.begin(); iter != myvector.end(); ++iter)
    {
        cout << *iter;
    }
    return 0;
}
/*
    程序运行结果：
    www.123.com
    www
*/