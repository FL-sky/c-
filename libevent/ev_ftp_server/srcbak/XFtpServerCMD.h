#pragma once
#include "XFtpTask.h"
class XFtpServerCMD : public XFtpTask
{
public:
    virtual bool Init();
    virtual void Read(struct bufferevent* bev);
    virtual void Event(struct bufferevent* bev, short what);
    XFtpServerCMD();
    ~XFtpServerCMD();

private:
};
