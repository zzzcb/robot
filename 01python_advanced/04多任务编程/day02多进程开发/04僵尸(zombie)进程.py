"""
Zombie Process:[通常是child process],标志是Linux下 Z+
    a process has completed,but has an entry in process table!
    下面的程序 process a 就会变为僵尸进程，因为它执行完毕。 但是，main process 并没有将它从process table中清理出来
    然后，Linux命令行:ps -aux | grep python
"""
import multiprocessing,time 

def process_a():
    print("process_a")

if __name__ == "__main__":
    process_1 = multiprocessing.Process(target=process_a)

    process_1.start()

    time.sleep(100)
    print("main process")
    
    
# 另外： 
"""
import multiprocessing,time 

def process_b():
    while True:
        time.sleep(1)
        print("process_b")

if __name__ == "__main__":
    process_2 = multiprocessing.Process(target=process_b)
    process_2.start()

    print("main process") # 由于子进程b 没有结束，所以主进程也没有结束。 对于线程也是如此
"""    
    
