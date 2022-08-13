// 2.32 进程通信中的管道实现原理是什么？
// 参考回答

// 操作系统在内核中开辟一块缓冲区（称为管道）用于通信。管道是一种两个进程间进行单向通信的机制。
// 因为这种单向性，管道又称为半双工管道，所以其使用是有一定的局限性的。
// 半双工是指数据只能由一个进程流向另一个进程（一个管道负责读，一个管道负责写）；
// 如果是全双工通信，需要建立两个管道。
// 管道分为无名管道和命名管道，无名管道只能用于具有亲缘关系的进程直接的通信（父子进程或者兄弟进程），可以看作一种特殊的文件，管道本质是一种文件；命名管道可以允许无亲缘关系进程间的通信。

// 管道原型如下：

// ＃include <unistd.h>   int pipe(int fd[2]);
// pipe()函数创建的管道处于一个进程中间，因此一个进程在由 pipe()创建管道后，一般再使用fork() 建立一个子进程，然后通过管道实现父子进程间的通信。
// 管道两端可分别用描述字fd[0]以及fd[1]来描述。注意管道的两端的任务是固定的，即一端只能用于读，由描述字fd[0]表示，称其为管道读端；
// 另 一端则只能用于写，由描述字fd[1]来表示，称其为管道写端。
// 如果试图从管道写端读取数据，或者向管道读端写入数据都将发生错误。一般文件的 I/O 函数都可以用于管道，如close()、read()、write()等。

// 具体步骤如下：

// 1.父进程调用pipe开辟管道,得到两个文件描述符指向管道的两端。

// 2.父进程调用fork创建子进程,那么子进程也有两个文件描述符指向同一管道。

// 3.父进程关闭管道读端,子进程关闭管道写端。父进程可以往管道里写,子进程可以从管道里读,管道是用环形队列实现的,数据从写端流入从读端流出,这样就实现了进程间通信。

// 答案解析

// 给出实现的代码，实现父子进程间的管道通信

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT 0
#define OUTPUT 1
int main()
{ //创建管道
    int fd[2];
    pipe(fd); //创建子进程
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("fork error!\n");
        exit(-1);
    }
    else if (pid == 0)
    {                                             //执行子进程
        printf("Child process is starting...\n"); //子进程向父进程写数据，关闭管道的读端
        close(fd[INPUT]);
        write(fd[OUTPUT], "hello douya!", strlen("hello douya!"));
        exit(0);
    }
    else
    {                                                 //执行父进程
        printf("Parent process is starting......\n"); //父进程从管道读取子进程写的数据 ，关闭管道的写端
        close(fd[OUTPUT]);
        char buf[255];
        int output = read(fd[INPUT], buf, sizeof(buf));
        printf("%d bytes of data from child process: %s\n", output, buf);
    }
    return 0;
}