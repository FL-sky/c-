// 9.无序容器（哈希表）

// 用法和功能同map一模一样，区别在于哈希表的效率更高。

// (1) 无序容器具有以下 2 个特点：

//     a. 无序容器内部存储的键值对是无序的，各键值对的存储位置取决于该键值对中的键，

//     b. 和关联式容器相比，无序容器擅长通过指定键查找对应的值（平均时间复杂度为 O(1)）；
//     但对于使用迭代器遍历容器中存储的元素，无序容器的执行效率则不如关联式容器。

// (2) 和关联式容器一样，无序容器只是一类容器的统称，其包含有 4 个具体容器，
// 分别为 unordered_map、unordered_multimap、unordered_set 以及 unordered_multiset。
// 功能如下表：

// 无序容器                    功能

// unordered_map           存储键值对 <key, value> 类型的元素，其中各个键值对键的值不允许重复，
//                         且该容器中存储的键值对是无序的。

// unordered_multimap      和 unordered_map 唯一的区别在于，该容器允许存储多个键相同的键值对。

// unordered_set           不再以键值对的形式存储数据，而是直接存储数据元素本身（当然也可以理解为，
//                         该容器存储的全部都是键 key 和值 value 相等的键值对，正因为它们相等，
//                         因此只存储 value 即可）。另外，该容器存储的元素不能重复，
//                         且容器内部存储的元素也是无序的。

// unordered_multiset      和 unordered_set 唯一的区别在于，该容器允许存储值相同的元素。

// (3) 程序实例（以 unordered_map 容器为例）

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main()
{
    //创建并初始化一个 unordered_map 容器，其存储的 <string,string> 类型的键值对
    std::unordered_map<std::string, std::string> my_uMap{
        {"教程1", "www.123.com"},
        {"教程2", "www.234.com"},
        {"教程3", "www.345.com"}};
    //查找指定键对应的值，效率比关联式容器高
    string str = my_uMap.at("教程2");
    cout << "str = " << str << endl;

    // string str = my_uMap.at("C语言教程");
    ///注意：如果不存在 key ，该方法将给出运行时错误。

    // printf("%d\n", my_uMap.size());
    // string rt = my_uMap["111"];
    // printf("%d\n", my_uMap.size());//size+1

    //使用迭代器遍历哈希容器，效率不如关联式容器
    for (auto iter = my_uMap.begin(); iter != my_uMap.end(); ++iter)
    {
        // pair 类型键值对分为 2 部分
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}

/*
    程序运行结果：
      教程1 www.123.com
      教程2 www.234.com
      教程3 www.345.com
*/