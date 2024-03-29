#include "XThreadPool.h"
#include "XThread.h"
#include <thread>
#include <iostream>
#include "XTask.h"
using namespace std; ///这种文件中就可以using?

//分发线程
void XThreadPool::Dispatch(XTask *task)
{
    //轮询
    if (!task)
        return;
    int tid = (lastThread + 1) % threadCount;
    lastThread = tid;
    XThread *t = threads[tid];

    t->addTask(task);
    //激活线程
    t->Activate();
}

//初始化所有线程并启动线程
void XThreadPool::Init(int threadCount)
{
    this->threadCount = threadCount;
    this->lastThread = -1;
    for (int i = 0; i < threadCount; i++)
    {

        XThread *t = new XThread();
        t->id = i;
        cout << "Create thread " << i << endl;
        //启动线程
        t->Start();
        threads.push_back(t);
        this_thread::sleep_for(10ms);
    }
}

// XThreadPool::XThreadPool()
// {
// }

// XThreadPool::~XThreadPool()
// {
// }
