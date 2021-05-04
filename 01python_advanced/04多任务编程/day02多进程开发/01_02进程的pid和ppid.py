"""
    os.getpid()
    os.getppid()
"""

# 使用 os  模块
import multiprocessing,time,os

def process_a():
    print("process:a:pid:",os.getpid())
    print("process:a:ppid:",os.getppid())

def process_b():
    print("process:b:pid:",os.getpid())
    print("process:b:ppid:",os.getppid())

if __name__ == "__main__":
    process_1 = multiprocessing.Process(target=process_a)
    process_2 = multiprocessing.Process(target=process_b)
    
    process_1.start()
    process_2.start()
    process_1.join()
    process_2.join()
    print("main:pid:",os.getpid())
    print("main:ppid:",os.getppid())
    print("main process")