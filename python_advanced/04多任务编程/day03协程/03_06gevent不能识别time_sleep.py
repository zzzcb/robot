import gevent
import time

def work1():
    """任务1"""
    while True:
        print("正在执行work1------------")
        #gevent.sleep(10)# 此时也不会等待IO了，所以 gevent比greenlet 好！
        gevent.sleep(0.5)

def work2():
    """任务1"""
    while True:
        print("正在执行work2----")
        gevent.sleep(0.5)

if __name__ == "__main__":
    g1 = gevent.spawn(work1) 
    g2 = gevent.spawn(work2) 

    # 等待协程执行
    g1.join()
    g2.join()