#include "XFtpFactory.h"
#include "XFtpServerCMD.h"
#include "XFtpUSER.h"
#include"XFtpLIST.h"
#include"XFtpPORT.h"
XTask *XFtpFactory::CreateTask()
{
    XFtpServerCMD *x = new XFtpServerCMD();

    //注册ftp消息处理对象
    x->Reg("USER", new XFtpUSER());
    x->Reg("PORT", new XFtpPORT());
    XFtpLIST* list = new XFtpLIST();
    x->Reg("PWD", list);
    x->Reg("LIST", list);//同一个对象里面处理多个事件
    return x;
}