"""
Orphan Process:
    a process's parent process has completed,but it is running itself
    执行下面的代码，子进程a,b不是被1 接管，而是被其他的一个进程号接管。不懂~
    linux 命令行:
    kill <main process pid>
    然后:ps -ef| grep python
"""
import multiprocessing,time 

def process_a():
    while True: 
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