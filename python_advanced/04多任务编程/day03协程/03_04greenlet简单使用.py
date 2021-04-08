import greenlet
import time

def work1():
    """任务1"""
    while True:
        print("正在执行work1------------")
        target2.switch()
        #time.sleep(10) # 会等待IO才能切换,greenlet 不太好
        time.sleep(0.5)

def work2():
    """任务1"""
    while True:
        print("正在执行work2----")
        target1.switch()
        time.sleep(0.5)

if __name__ == "__main__":
    target1 = greenlet.greenlet(work1)
    target2 = greenlet.greenlet(work2)

    target1.switch() # switch to target1