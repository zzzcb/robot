import multiprocessing,time,os

def copy_work():
    print("拷贝中....",os.getpid())
    time.sleep(3)

if __name__ == '__main__':
    # 创建进程池
    # Pool(3) 表示创建容量为3个进程的进程池
    pool = multiprocessing.Pool(3)
    for i in range(10):
        pool.apply_async(copy_work)# 不会阻塞在这

    pool.close() # 关闭pool，不再接收新的任务
    pool.join()
    print("执行完毕")