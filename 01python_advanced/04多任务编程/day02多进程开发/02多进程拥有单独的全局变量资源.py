import multiprocessing,time 

num = 0

def process_a():
    global num
    num += 1
    print("process_a:",num)

def process_b():
    global num
    num += 2
    print("process_b:",num)


if __name__ == "__main__":
    process_1 = multiprocessing.Process(target=process_a)
    process_2 = multiprocessing.Process(target=process_b)

    process_1.start()
    process_2.start()

    process_1.join()
    process_2.join()
    print("main process:",num)



