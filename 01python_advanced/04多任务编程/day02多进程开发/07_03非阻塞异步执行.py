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
    queue = multiprocessing.Queue(10)
    write_process = multiprocessing.Process(target=write_queue,args=(queue,))
    read_process = multiprocessing.Process(target=read_queue,args=(queue,))

    write_process.start()
    read_process.start()
   