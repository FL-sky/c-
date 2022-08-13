//内联函数示例
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
void s1()
{
    int a = 1;
    MAX(a, "Hello"); //错误地比较int和字符串，没有参数类型检查
}
inline int add(int a, int b)
{
    return (a + b);
}

inline void f1(int a, int b)
{
    if (a > b)
        swap(a, b);
    while (a < b)
    {
        a += b / 2 + 1;
    }
    switch (a == b)
    {
    case 1:
        printf("%d==%d", a, b);
        break;
    case 0:
        printf("%d>%d", a, b);
        break;
    }
}

int main(void)
{
    int a;
    a = add(1, 2);
    printf("a+b=%d\n", a);
    int b = a * a;
    f1(a, b);
    return 0;
}