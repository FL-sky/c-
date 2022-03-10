#include "XFtpTask.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include<iostream>
using namespace std;
//�ظ�cmd��Ϣ
void XFtpTask::ResCMD(std::string msg) {
    if (!cmdTask||!cmdTask->bev) {
        return;
    }
    cout << "ResCMD:" << msg << endl;
    if (msg[msg.size() - 1] != '\n'){
        msg += "\r\n";
    }
    bufferevent_write(cmdTask->bev, msg.c_str(), msg.size());
}


void XFtpTask::SetCallback(struct bufferevent *bev)
{
    bufferevent_setcb(bev, ReadCB, WriteCB, EventCB, this);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void XFtpTask::ReadCB(bufferevent *bev, void *arg)
{
    XFtpTask *t = (XFtpTask *)arg;
    t->Read(bev);
}
void XFtpTask::WriteCB(bufferevent *bev, void *arg)
{
    XFtpTask *t = (XFtpTask *)arg;
    t->Write(bev);
}

void XFtpTask::EventCB(bufferevent *bev, short what, void *arg)
{
    XFtpTask *t = (XFtpTask *)arg;
    t->Event(bev, what);
}