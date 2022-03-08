// 1.3.5 说说 C 语言如何实现 C++ 语言中的重载

// 参考答案

// c语言中不允许有同名函数，因为编译时函数命名是一样的，不像c++会添加参数类型和返回类型作为函数编译后的名称，进而实现重载。如果要用c语言显现函数重载，可通过以下方式来实现：

// 1.使用函数指针来实现，重载的函数不能使用同名称，只是类似的实现了函数重载功能

// 2.重载函数使用可变参数，方式如打开文件open函数

// 3.gcc有内置函数，程序使用编译函数可以实现函数重载

#include <stdio.h>
void func_int(void *a)
{
    printf("%d\n", *(int *)a); //输出int类型，注意 void * 转化为int
}
void func_double(void *b)
{
    printf("%.2f\n", *(double *)b);
}
typedef void (*ptr)(void *); // typedef申明一个函数指针
void c_func(ptr p, void *param)
{
    p(param); //调用对应函数
}
int main()
{
    int a = 23;
    double b = 23.23;
    c_func(func_int, &a);
    c_func(func_double, &b);
    return 0;
}