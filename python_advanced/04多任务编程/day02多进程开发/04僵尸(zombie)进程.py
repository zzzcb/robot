"""
Zombie Process:[通常是child process],标志是Linux下 Z+
    a process has completed,but has an entry in process table!
    下面的程序 process a 就会变为僵尸进程，因为它执行完毕。 但是，main process 并没有将它从process table中清理出来
    然后，Linux命令行:ps -ef | grep python
"""
import multiprocessing,time 

def process_a():
    time.sleep(1)
    print("process_a")

def process_b():
    while True:
        time.sleep(1)
        print("process_b")

if __name__ == "__main__":
    process_1 = multiprocessing.Process(target=process_a)
    process_2 = multiprocessing.Process(target=process_b)

    process_1.start()
    process_2.start()

    print("main process")