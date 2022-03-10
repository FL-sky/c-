#pragma once
#include "XFtpTask.h"
class XFtpUSER :
    public XFtpTask
{
    //½âÎöĞ­Òé
    virtual void Parse(std::string type, std::string msg);
};

