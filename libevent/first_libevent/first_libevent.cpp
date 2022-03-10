//https://www.cnblogs.com/coversky/p/14913806.html
//https://zhuanlan.zhihu.com/p/351692546
//https://www.bilibili.com/video/BV1yy4y147mu?p=9
//https://blog.csdn.net/qq_42608626/article/details/98783114

#include <iostream>
#include<event2/event.h>
using namespace std;
int main()
{
#ifdef _WIN32
    //初始化socket库
    WSADATA wver;
    WSAStartup(MAKEWORD(2, 2), &wver);

#endif
    cout << "test libevent\n";

    //
    event_base* base = event_base_new();
    if (base) {
        cout << "event_base_new success!" << endl;
    }
    return 0;
}

