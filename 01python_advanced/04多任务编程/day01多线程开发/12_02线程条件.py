from threading import Thread, Condition
import time
import random

condition =Condition()
queue = []

class ProducerThread(Thread):
    def run(self):
        nums = range(5) #Will create the list [0, 1, 2, 3, 4]
        global queue
        while True:
            condition.acquire()
            num = random.choice(nums) #Selects a random number from list [0, 1, 2, 3, 4]
            queue.append(num)
            print("Produced", num)
            condition.notify() # notify consumer. 
            # Once notify() call is made on condition, consumer wakes up. But waking up doesn’t mean it starts executing.
            # notify() does not release the lock. Even after notify(), lock is still held by producer.

            condition.release() # Producer explicitly releases the lock by using condition.release().And consumer starts running again. Now it will find data in queue and no IndexError will be raised.
            time.sleep(random.random())


class ConsumerThread(Thread):
    def run(self):
        global queue
        while True:
            condition.acquire()
            if not queue:
                print("Nothing in queue, consumer is waiting")
                condition.wait() # wait producer. wait() blocks the consumer and also releases the lock associated with the condition. 
                print("Producer added something to queue and notified the consumer")

            num = queue.pop(0)
            print("Consumed", num)
            condition.release()
            time.sleep(random.random())


ProducerThread().start()
ConsumerThread().start()