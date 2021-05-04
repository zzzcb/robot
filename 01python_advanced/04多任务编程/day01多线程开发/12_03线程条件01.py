from threading import Thread, Condition
import time
""" 
Adding a max size on the queue.Producer should not put data in the queue if the queue is full.
"""
import random

queue = []
MAX_NUM = 5
condition =Condition()

class ProducerThread(Thread):
    def run(self):
        nums = range(5) 
        global queue
        while True:
            condition.acquire()
            if len(queue) == MAX_NUM:
                print("queue is full. producer is waiting.")
                condition.wait() # auto release 
                print("space in queue,consumer notified the producer.")

            num = random.choice(nums) 
            queue.append(num)
            print("生产后:Queue:", queue)
            condition.notify() 
            condition.release() 
            time.sleep(1)


class ConsumerThread(Thread):
    def run(self):
        global queue
        while True:
            condition.acquire()
            if not queue:
                print("Nothing in queue, consumer is waiting")
                condition.notify()
                condition.wait() # wait producer. wait() blocks the consumer and also releases the lock associated with the condition. 
                print("Producer added something to queue and notified the consumer")

            num = queue.pop(0)
            print("消费之后:Queue:", queue)
            condition.release()
            time.sleep(2)


ProducerThread().start()
ConsumerThread().start()


"""
生产后:Queue: [1]
消费之后:Queue: []
生产后:Queue: [3]
生产后:Queue: [3, 2]
消费之后:Queue: [2]
生产后:Queue: [2, 4]
消费之后:Queue: [4]
生产后:Queue: [4, 4]
生产后:Queue: [4, 4, 0]
消费之后:Queue: [4, 0]
生产后:Queue: [4, 0, 0]
生产后:Queue: [4, 0, 0, 1]
消费之后:Queue: [0, 0, 1]
生产后:Queue: [0, 0, 1, 2]
生产后:Queue: [0, 0, 1, 2, 0]
消费之后:Queue: [0, 1, 2, 0]
生产后:Queue: [0, 1, 2, 0, 1]
queue is full. producer is waiting.
消费之后:Queue: [1, 2, 0, 1]
消费之后:Queue: [2, 0, 1]
消费之后:Queue: [0, 1]
消费之后:Queue: [1]
消费之后:Queue: []
Nothing in queue, consumer is waiting
space in queue,consumer notified the producer.
生产后:Queue: [3]
Producer added something to queue and notified the consumer
消费之后:Queue: []
生产后:Queue: [3]
消费之后:Queue: []
生产后:Queue: [3]
生产后:Queue: [3, 3]
消费之后:Queue: [3]
生产后:Queue: [3, 2]
生产后:Queue: [3, 2, 0]
消费之后:Queue: [2, 0]
生产后:Queue: [2, 0, 1]
生产后:Queue: [2, 0, 1, 2]
消费之后:Queue: [0, 1, 2]
生产后:Queue: [0, 1, 2, 0]
生产后:Queue: [0, 1, 2, 0, 0]
消费之后:Queue: [1, 2, 0, 0]
生产后:Queue: [1, 2, 0, 0, 4]
queue is full. producer is waiting.
消费之后:Queue: [2, 0, 0, 4]
消费之后:Queue: [0, 0, 4]
消费之后:Queue: [0, 4]
消费之后:Queue: [4]
消费之后:Queue: []
Nothing in queue, consumer is waiting
space in queue,consumer notified the producer.
生产后:Queue: [2]
Producer added something to queue and notified the consumer
消费之后:Queue: []
生产后:Queue: [4]
生产后:Queue: [4, 0]
消费之后:Queue: [0]
生产后:Queue: [0, 0]
消费之后:Queue: [0]
生产后:Queue: [0, 2]
生产后:Queue: [0, 2, 1]
消费之后:Queue: [2, 1]
生产后:Queue: [2, 1, 2]
生产后:Queue: [2, 1, 2, 1]
消费之后:Queue: [1, 2, 1]
"""

