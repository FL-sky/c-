// 1.4.7 说一下STL中迭代器的作用，有指针为何还要迭代器？
// 参考回答

// 1.迭代器的作用

// （1）用于指向顺序容器和关联容器中的元素

// （2）通过迭代器可以读取它指向的元素

// （3）通过非const迭代器还可以修改其指向的元素

// 2.迭代器和指针的区别

//     迭代器不是指针，是类模板，表现的像指针。他只是模拟了指针的一些功能，
//     重载了指针的一些操作符，-->、++、--等。
//     迭代器封装了指针，是一个”可遍历STL（ Standard Template Library）容器内全部或部分元素”的对象，
//     本质是封装了原生指针，是指针概念的一种提升，提供了比指针更高级的行为，相当于一种智能指针，
//     他可以根据不同类型的数据结构来实现不同的++，--等操作。

//     迭代器返回的是对象引用而不是对象的值，所以cout只能输出迭代器使用取值后的值而不能直接输出其自身。

// 3.迭代器产生的原因

//     Iterator类的访问方式就是把不同集合类的访问逻辑抽象出来，
//     使得不用暴露集合内部的结构而达到循环遍历集合的效果。

// 答案解析

// 1.迭代器

//     Iterator（迭代器）模式又称游标（Cursor）模式，用于提供一种方法顺序访问一个聚合对象中各个元素,
//     而又不需暴露该对象的内部表示。
//     或者这样说可能更容易理解：Iterator模式是运用于聚合对象的一种模式，
//     通过运用该模式，使得我们可以在不知道对象内部表示的情况下，
//     按照一定顺序（由iterator提供的方法）访问聚合对象中的各个元素。
//      由于Iterator模式的以上特性：与聚合对象耦合，在一定程度上限制了它的广泛运用，
//      一般仅用于底层聚合支持类，如STL的list、vector、stack等容器类及ostream_iterator等扩展Iterator。

//     2. 迭代器示例：

#include <vector>
#include <iostream>
using namespace std;
int main()
{
    vector<int> v; //一个存放int元素的数组，一开始里面没有元素
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    vector<int>::const_iterator i;         //常量迭代器
    for (i = v.begin(); i != v.end(); ++i) // v.begin()表示v第一个元素迭代器指针，++i指向下一个元素
        cout << *i << ",";                 //*i表示迭代器指向的元素
    cout << endl;
    vector<int>::reverse_iterator r; //反向迭代器
    for (r = v.rbegin(); r != v.rend(); r++)
        cout << *r << ",";
    cout << endl;
    vector<int>::iterator j; //非常量迭代器
    for (j = v.begin(); j != v.end(); j++)
        *j = 100;
    for (i = v.begin(); i != v.end(); i++)
        cout << *i << ",";
    return 0;
} /*      运行结果：   1,2,3,4,   4,3,2,1,   100,100,100,100, */