import multiprocessing,time,os

def copy_work():
    print("拷贝中....",os.getpid())
    time.sleep(3)

if __name__ == '__main__':
    # 创建进程池
    # Pool(3) 表示创建容量为3个进程的进程池
    pool = multiprocessing.Pool(3)
    for i in range(10):
        # 利用进程池同步拷贝文件，进程池中的进程会必须等上一个进程退出才能执行下一个进程
        pool.apply(copy_work)# 阻塞在这

    print("执行完毕")
    pool.close() # 关闭进程池，不再接收新的任务

