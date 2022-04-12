import time
from threading import Thread
from multiprocessing import Process
import random


def f1():
    s = 0
    n = int(random.random()+random.random())*10
    rg = 10000000
    for i in range(rg):
        n = n+i*10
        s = s + n**0.5
    print("s=",s)
    
if __name__ == "__main__":
    t_s_time = time.time()
    l_lst = []
    numT = 12
    for i in range(numT):
        t = Thread(target= f1,)
        t.start()
        l_lst.append(t)
    [i.join() for i in l_lst]
    t_e_time = time.time()
    t_dif_time = t_e_time - t_s_time
    
    print(numT,'个线程执行计算型操作用的时间',t_dif_time)    
    p_s_time = time.time()
    p_lst = []
    for i in range(numT):
        p = Process(target=f1,)
        p.start()
        p_lst.append(p)
    [p.join() for p in p_lst]
    p_e_time = time.time()
    p_time = p_e_time - p_s_time
    print(numT,'个多进程执行计算型操作所用的时间',p_time)
    
    
'''
https://www.cnblogs.com/16795079a/p/10268040.html
总结:计算io操作密集型的代码多线程效率更高,因为线程创建要比进程创建开销少
rg 小，多线程效率高；rg大，多进程效率高
但是计算密集型的代码多 那么进程操作更快,因为多进可以应用多核技术
'''