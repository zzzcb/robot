import multiprocessing,time,random

def write_queue(queue):
    while True:
        ele = random.randint(1,10)
        queue.put(ele)
        print("put to queue:",ele)
        time.sleep(1)

def read_queue(queue):
    while True:
        ret = queue.get()
        print("get from queue:",ret)
        time.sleep(2)



if __name__ == "__main__":
    queue = multiprocessing.Manager().Queue(10)
    pool =  multiprocessing.Pool(3)
    pool.apply_async(write_queue,(queue,)) # no block
    pool.apply_async(read_queue,(queue,)) # no block
  
    pool.close()
    pool.join()
    print("执行完毕")