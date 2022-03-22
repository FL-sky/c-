// 2.27 请你说说什么是守护进程，如何实现？
// 参考回答

// 1.守护进程：守护进程是运行在后台的一种生存期长的特殊进程。它独立于控制终端，处理一些系统级别任务。

// 2.如何实现：

// （1）创建子进程，终止父进程。方法是调用fork() 产生一个子进程，然后使父进程退出。

// （2）调用setsid() 创建一个新会话。

// （3）将当前目录更改为根目录。使用fork() 创建的子进程也继承了父进程的当前工作目录。

// （4）重设文件权限掩码。文件权限掩码是指屏蔽掉文件权限中的对应位。

// （5）关闭不再需要的文件描述符。子进程从父进程继承打开的文件描述符。

// 答案解析

// 实现代码如下：

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAXFILE 65535

int main()
{ //第一步:创建进程
    int pid = fork();
    if (pid > 0)
        exit(0); //结束父进程
    else if (pid < 0)
    {
        printf("fork error!\n");
        exit(1); // fork失败，退出
    }            //第二步:子进程成为新的会话组长和进程组长,并与控制终端分离
    setsid();    //第三步:改变工作目录到
    chdir("/");  //第四步:重设文件创建掩模
    umask(0);    //第五步:关闭打开的文件描述符
    for (int i = 0; i < MAXFILE; ++i)
        close(i);
    sleep(2);
}
return 0;
}