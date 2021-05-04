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
    process_1.daemon = True
    process_2.daemon = True

    process_1.start()
    process_2.start()

    print("main process")
