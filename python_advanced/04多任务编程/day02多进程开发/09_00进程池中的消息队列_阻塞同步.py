import multiprocessing,time,random

def write_queue(queue):
    while True:
        if queue.full():
            print("队列已满")
            break
        ele = random.randint(1,10)
        queue.put(ele)
        print("put to queue:",ele)
        time.sleep(1)

def read_queue(queue):
    while True:
        if queue.empty():
            print("队列已空")
            break
        ret = queue.get()
        print("get from queue:",ret)
        time.sleep(2)



if __name__ == "__main__":
    pool = multiprocessing.Pool(3)
    queue = multiprocessing.Manager().Queue(10)
    pool.apply(write_queue,(queue,)) # block
    pool.apply(read_queue,(queue,)) # block

    pool.close()
    print("执行完毕")