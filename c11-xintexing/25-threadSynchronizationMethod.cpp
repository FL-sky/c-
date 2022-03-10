#include <bits/stdc++.h>
using namespace std;

// # 线程同步的方法

// - 原子操作：

// ​    是指线程在访问资源时能够确保所有其他线程都不在同一时间内访问相同的资源。

// 1.   while(InterlockedExchange((LPLONG)&pDlg->m_bEnter,TRUE) == TRUE)
// 2.   {
// 3. 	    Sleep(10);
// 4.   }
// 5.
// 6.   for (int i = 0; i < 10000000; i++)
// 7.   {
// 8. 	    pDlg->m_nCount++;
// 9.   }
// 10.
// 11.  InterlockedExchange((LPLONG)&pDlg->m_bEnter,FALSE);

///总结：windows中，互锁函数家族只能在单值上运行，无法使线程进入等待状态，但是速度最快。

#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>
using namespace std;

long long g_nData = 0;

//原子操作
/*
会议室： 甲公司 乙公司

保安/买一把锁：

线程1：
   对会议室进行加锁（同一把锁）

   甲公司开会（独占会议室）

   对会议室进行解锁

线程2：
   对会议室进行加锁（同一把锁）

   乙公司开会（独占会议室）
   
   对会议室进行解锁

*/

void foo()
{
    for (int i = 0; i < 100000; i++)
    {
        //++操作对应的汇编代码不止一行
        //g_nData++;
        //使用InterlockedAdd，可以使得g_nData++操作是原子操作
        //lock xadd   dword ptr[ecx], eax

        // InterlockedAdd((LONG*)&g_nData, 1);
        //g_nData = g_nData * 5;

        InterlockedAdd((long *)&g_nData, 1);
    }
}

int main()
{
    std::thread t(foo);

    for (int i = 0; i < 100000; i++)
    {
        //g_nData++;
        InterlockedAdd((LONG *)&g_nData, 1);
    }

    t.join();

    std::cout << g_nData << std::endl;

    return 0;
}