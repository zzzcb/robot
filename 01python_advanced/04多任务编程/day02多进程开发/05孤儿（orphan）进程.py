"""
Orphan Process:
    a process's parent process has completed,but it is running itself
    执行下面的代码，当kill 了主进程时，子进程a将会被1 接管。
    linux 命令行:
    kill <main process pid>
    然后:ps -ef| grep python  可以看到原先的子进程被1接管。可以只能手动将子进程kill 死。
    
    查看所有孤儿进程的命令: 
    ps -elf | awk '{if ($5 == 1&& $3 !="root") {print $0 }}'  This will show you all the orphan processes running in your system. 
    The output from this command confirms that they are Orphan processes but doesn’t mean that they are all useless, 
    so confirm from some other source also before killing them.

"""
import multiprocessing,time

def process_a():
    while True:
        time.sleep(1)
        print("process_a")

if __name__ == "__main__":
    process_1 = multiprocessing.Process(target=process_a)
    process_1.start()

    print("main process") # 因为process_a 没有执行完,所以main process 依然存在，可以通过kill 将其杀死
