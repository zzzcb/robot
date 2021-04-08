import multiprocessing,time

def write_file01(lock):
    lock.acquire()
    with open("./zcb.txt","a+",encoding="utf8") as f:
        for i in range(100):
            f.write(f"hello world{i},from 01\n")
    lock.release()

def write_file02(lock):
    lock.acquire()
    with open("./zcb.txt","a+",encoding="utf8") as f:
        for i in range(100):
            f.write(f"hello world{i},from 02\n")
    lock.release()

if __name__ == "__main__":
    import os,sys 
    os.chdir(os.path.dirname(sys.argv[0]))
    lock = multiprocessing.Lock()
    p1 = multiprocessing.Process(target=write_file01,args=(lock,))
    p2 = multiprocessing.Process(target=write_file02,args=(lock,))

    p1.start()
    p2.start()
