//linux
#include <event2/event.h>
#include <signal.h>
#include <iostream>
using namespace std;
int main()
{
#ifdef _WIN32
    //初始化socket库
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#else
    //忽略管道信号，发送数据给已关闭的socket
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        return 1;
#endif

    //创建配置上下文
    event_config *conf = event_config_new();

    //显示支持的网络模式
    const char **methods = event_get_supported_methods();
    cout << "supported_methods:" << endl;
    for (int i = 0; methods[i] != NULL; i++)
    {
        cout << methods[i] << endl;
    }

    //初始化配置libevent上下文
    event_base *base = event_base_new_with_config(conf);
    event_config_free(conf);
    if (!base)
        cerr << "event_base_new_with_config failed!" << endl;
    else
        cout << "event_base_new_with_config success!" << endl;
    event_base_free(base);

    return 0;
}