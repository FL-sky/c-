#include "XFtpServerCMD.h"
#include <iostream>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <string.h>
using namespace std;

void XFtpServerCMD::Read(struct bufferevent* bev)
{

    char data[1024] = { 0 };
    for (;;)
    {
        int len = bufferevent_read(bev, data, sizeof(data) - 1);
        if (len <= 0)
        {
            break;
        }
        data[len] = '\0';
        cout << "Recv CMD:" << data << flush;
    }
}

void XFtpServerCMD::Event(struct bufferevent* bev, short what)
{

    if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT))
    {
        cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT" << endl;
        bufferevent_free(bev);
        delete this;
    }
}

bool XFtpServerCMD::Init()
{
    cout << "XFtpServerCMD::Init()" << endl;

    bufferevent* bev = bufferevent_socket_new(base, sock, BEV_OPT_CLOSE_ON_FREE);

    this->SetCallback(bev);

    timeval rt = { 60, 0 };
    bufferevent_set_timeouts(bev, &rt, 0);

    string msg = "220 Welcome to libevent XFtpServer\r\n";
    bufferevent_write(bev, msg.c_str(), msg.size());

    return true;
}

XFtpServerCMD::XFtpServerCMD()
{
}
XFtpServerCMD::~XFtpServerCMD()
{
}
