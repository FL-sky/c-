#include "XFtpFactory.h"
#include "XFtpServerCMD.h"
#include "XFtpUSER.h"
#include"XFtpLIST.h"
#include"XFtpPORT.h"
#include"XFtpRETR.h"
#include"XFtpSTOR.h"
XTask *XFtpFactory::CreateTask()
{
    XFtpServerCMD *x = new XFtpServerCMD();

    //ע��ftp��Ϣ��������
    x->Reg("USER", new XFtpUSER());
    x->Reg("PORT", new XFtpPORT());
    XFtpLIST* list = new XFtpLIST();
    x->Reg("PWD", list);
    x->Reg("LIST", list);//ͬһ���������洦������¼�
    x->Reg("CWD", list);
    x->Reg("CDUP", list);
    x->Reg("RETR", new XFtpRETR());
    x->Reg("STOR", new XFtpSTOR());
    return x;
}