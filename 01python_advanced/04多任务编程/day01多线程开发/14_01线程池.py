from concurrent.futures import ThreadPoolExecutor
from time import sleep

def count_number_of_words(sentence):
    number_of_words = len(sentence.split())
    sleep(1)
    print(f"Number of words in the sentence :\n{sentence}:{number_of_words}")

def count_number_of_characters(sentence):
    number_of_characters = len(sentence)
    sleep(1)
    print(f"Number of characters in the sentence :\n{sentence}:{number_of_characters}")

if __name__ == "__main__":
    sentence = "Python is very niu bi."
    executor = ThreadPoolExecutor(4)
    thread1 = executor.submit(count_number_of_words, (sentence))
    thread2 = executor.submit(count_number_of_characters, (sentence))
    print(f"Thread 1 executed ? :{thread1.done()}")
    print(f"Thread 2 executed ? :{thread2.done()}")
    sleep(2)
    print(f"Thread 1 executed ? :{thread1.done()}")
    print(f"Thread 2 executed ? :{thread2.done()}")
    
""" code explanation:
In the above example, a Thread Pool Executor has been created with 4 threads. 
Then two tasks which are signified by the functions count_number_of_words and count_number_of_characters, 
respectively, will wait for 1 second each before executing the functions and displaying the result. 
The tasks do not complete in the first one-second interval, so the call to the done() function returns a False value. After the task is executed and the respective print statements are displayed, then again, when the done() function is called, it returns a true value.
"""
