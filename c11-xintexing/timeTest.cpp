////https://blog.csdn.net/qq_33263769/article/details/88988461
#include <iostream>
#include <thread>
using namespace std;

int g_nData = 0;

void foo()
{
    for (int i = 0; i < 10000000; i++)
    {
        g_nData++;
    }
}

int main()
{
    std::thread t(foo);

    for (int i = 0; i < 100000; i++)
    {
        g_nData++;
    }

    t.join();

    std::cout << g_nData << std::endl;

    return 0;
}

// 同时:时间片的交替20ms

// 线程1:
//     008E42D9    mov     eax, dwond ptr [g_nData (090E390h)]     寄存器eax=内存中g_nData数值
//     008E42DE    add     eax,1                                   寄存器eax++
//     008E42E1    mov     dword ptr [g_nData (090E390h)],eax      内存中g_nData数值=寄存器eax
// 线程2:

//     00904A4F    mov     eax, dwond ptr [g_nData (090E390h)]
//     00904A54    add     eax,1
//     00904A57    mov     dword ptr [g_nData (090E390h)],eax

// 原因分析：
// 1.     /*
// 2.     *                 1 int eax = g_nDataMemory;
// 3.     *
// 4.     *   g_nData++ ==> 2 eax++
// 5.     *
// 6.     *                 3 g_nDataMemory = eax;
// 7.     */
// 8.
// 9. CPU
// 10.     (1)线程1：执行到了第二步
// 11.     eax = 1000;
// 12.    （2）线程1时间片耗尽，切换到线程2
// 13.     线程2：执行到了第三步
// 14.     g_nDataMemory = 1050
// 15.     (3)线程2时间片耗尽，切回到线程1
// 16.     g_nDataMemory = 1000;
// 17.
// 18.     lock xxxx = xxxxx;