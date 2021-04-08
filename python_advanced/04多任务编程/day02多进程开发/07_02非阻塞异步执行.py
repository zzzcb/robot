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
    queue = multiprocessing.Queue(10)
    write_process = multiprocessing.Process(target=write_queue,args=(queue,))
    read_process = multiprocessing.Process(target=read_queue,args=(queue,))

    write_process.start()
    read_process.start()
   