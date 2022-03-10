//windows的线程使用：

// #include <iostream>
// #include <windows.h>

// using namespace std;

// //线程回调函数
// DWORD WINAPI ThreadProc(LPVOID lpParameter)
// {
//     std::cout << "hello world" << std::endl;
//     return 1;
// }

// int main()
// {
//     DWORD dwThreadID = 0;
//     HANDLE hThread = CreateThread(
//         NULL,
//         0,          //默认栈大小
//         ThreadProc, //线程回调函数 函数指针
//         NULL,       //参数
//         0,          //或者CREATE_SUSPENDED  表示是否暂停
//         &dwThreadID //线程
//     );

//     WaitForSingleObject(hThread, INFINITE);

//     return 0;
// }

// //c11中的线程：

#include <iostream>
#include <thread>

using namespace std;

void foo()
{
    std::cout << "hello world" << std::endl;
}

int main()
{
    //std::thread t(foo);
    thread t([]
             { cout << "hello bilibili~" << endl; });
    t.join();

    return 0;
}