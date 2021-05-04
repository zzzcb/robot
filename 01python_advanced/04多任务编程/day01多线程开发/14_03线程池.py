from concurrent.futures import ThreadPoolExecutor
import math 
from time import sleep


def my_log(n):
    val = math.log(n)
    sleep(1)
    return val

if __name__ == '__main__':
    values = [1,10,100,1000] 
    with ThreadPoolExecutor(max_workers = 3) as executor:
        thread = executor.map(my_log, values) # map 用于执行相同的任务，submit执行不同的任务

    for result in thread:
        print(round(result,2))
"""
    This example shows the use of the Executor.map function has been displayed. 
    We know in Python, a map function is used to apply a certain function to every element within iterables. 
    Here we have mapped all the elements of the iterator values to the function named my_log(argument) and 
    have submitted these as independent jobs to the ThreadPoolExecutor.
"""