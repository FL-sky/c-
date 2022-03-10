#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <list>

void arr()
{
    puts("------------arr START------------");
    //普通的数组,一旦申请不能再扩增
    int ary[5] = {1, 2, 3, 4, 5};
    //int* pAry = new int[5];

    for (int i = 0; i < sizeof(ary) / sizeof(int); i++)
    {
        std::cout << ary[i] << " ";
    }
    puts("");
    for (auto it : ary)
    {
        std::cout << it + 99 << "\t";
    }
    puts("");
    //容器---动态数组不用指定某大小会根据数组当前的使用情况进行动态的扩容
    //模板类型
    std::vector<int> v; //插入数据
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    puts("");
    //使用迭代器的方式遍历数组
    std::vector<int>::iterator it; //迭代器模板类虫的内部类
    for (it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it << " "; ///* it 来访问模板类的具体的值
    }
    puts("");
    puts("------------arr END------------");
}

void autofunc()
{
    puts("------------autofunc START------------");
    //统一的遍历方式链表
    std::list<std::string> l;
    l.push_back("hello1");
    l.push_back("hello2");
    l.push_back("hello3");
    for (std::list<std::string>::iterator it2 = l.begin(); it2 != l.end(); it2++)
    {
        std::cout << (*it2) /*.c_str()*/ << std::endl; //* it 来访问模板类的具体的值
    }

    /// auto类型推导关键字
    for (auto it2 = l.begin(); it2 != l.end(); it2++)
    {
        std ::cout << (*it2).c_str() << std::endl; //* it来访问模板类的具体的值/ /
    }

    for (std::string str : l)
    {
        std::cout << str.c_str() << std::endl;
    }
    for (auto str : l)
    {
        std::cout << str.c_str() << std::endl;
    }
    puts("------------autofunc END------------");
}

int main()
{
    std::vector<int> nums{1, 2, 4, 8, 16};
    std::list<std ::string> fruits{"orange", "apple", "raspberry"};
    //使用迭代器进行遍历vector
    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
    {
        std::cout << (*it) << std::endl;
    }
    //使用迭代器进行遍历list
    for (std::list<std::string>::iterator it = fruits.begin(); it != fruits.end(); it++)
    {
        std::cout << (*it) << std::endl;
    }
    arr();
    autofunc();
    return 0;
}