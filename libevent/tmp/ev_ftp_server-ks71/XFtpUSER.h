#pragma once
#include "XFtpTask.h"
class XFtpUSER :
    public XFtpTask
{
    //����Э��
    virtual void Parse(std::string type, std::string msg);
};

