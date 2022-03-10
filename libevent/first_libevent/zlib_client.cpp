#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <string.h>
#ifndef _WIN32
#include <signal.h>
#endif
#include <iostream>
using namespace std;

#define FILEPATH "001.txt"
void client_event_cb(struct bufferevent* bev, short what, void* ctx)
{
    cout << "client_event_cb " << what << endl;
    if (what & BEV_EVENT_CONNECTED)
    {
        cout << "BEV_EVENT_CONNECTED" << endl;
        bufferevent_write(bev, FILEPATH, strlen(FILEPATH));
    }
    int arr[] = { BEV_EVENT_READING, BEV_EVENT_WRITING, BEV_EVENT_EOF, BEV_EVENT_ERROR,
                 BEV_EVENT_TIMEOUT, BEV_EVENT_CONNECTED };
    for (int i = 0; i < 6; i++)
    {
        if (what & arr[i])
        {
            cout << " [" << i << "] ";
        }
    }
}
void Client(event_base* base)
{
    cout << "begin Client" << endl;
    //���ӷ����
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(5001);
    evutil_inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr.s_addr);
    bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    // ֻ���¼��ص�, ����ȷ�����ӳɹ�

    bufferevent_enable(bev, EV_READ | EV_WRITE);
    bufferevent_setcb(bev, 0, 0, client_event_cb, 0);
    bufferevent_socket_connect(bev, (sockaddr*)&sin, sizeof(sin));

    //�����ļ���
    //���ջظ�ȷ��OK
}