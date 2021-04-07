import concurrent.futures
from time import sleep
numbers = [10,23,54,7,89,100] 
def get_max_number(numbers):
    greatest_num = max(numbers)
    sleep(1)
    print(f"Greatest number is :{greatest_num}")

with concurrent.futures.ThreadPoolExecutor(max_workers = 4) as executor:
    thread = executor.submit(get_max_number, (numbers))
    print(f"Thread 1 executed ? :{thread.done()}")
    sleep(2)
    print(f"Thread 1 executed ? :{thread.done()}")