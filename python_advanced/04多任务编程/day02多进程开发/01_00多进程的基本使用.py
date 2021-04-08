import multiprocessing,time 

def process_a():
    time.sleep(1)
    print("process_a")

def process_b():
    time.sleep(1)
    print("process_b")


if __name__ == "__main__":
    process_1 = multiprocessing.Process(target=process_a)
    process_2 = multiprocessing.Process(target=process_b)
    
    process_1.start()
    process_2.start()
    print("主进程为:",multiprocessing.current_process())
    print("所有的子进程",multiprocessing.active_children())
    process_1.join()
    process_2.join()
    print("main process")
