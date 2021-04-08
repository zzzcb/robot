import multiprocessing,time,random

def write_queue(queue):
    try:
        while True:
            ele = random.randint(1,10)
            queue.put(ele,timeout=3)
            print("put to queue:",ele)
            time.sleep(5)
    except:
        print("超过3s没人取数据,write_queue进程结束")

def read_queue(queue):
    try:
        while True:
            ret = queue.get(timeout=3)
            print("get from queue:",ret)
            time.sleep(1)
    except:
        print("超过3s没人放数据,read_queue进程结束")

if __name__ == "__main__":
    queue = multiprocessing.Manager().Queue(10)
    pool = multiprocessing.Pool(3)
    pool.apply_async(write_queue,(queue,)) # no block
    pool.apply_async(read_queue,(queue,)) # no block

    pool.close()
    pool.join()
    print("执行完毕")