import multiprocessing

# 定义消息队列
# 如果不指定队列长度，则默认为最大(和内存有关)，如果指定了消息队列的大小，则消息队列就有上限控制
# 此处的 Queue(3) 指的是放入3条消息
queue = multiprocessing.Queue(3)

# queue.put(值) 向消息队列中放入内容
# put的值几乎可以是任意类型
queue.put(1) # 放入第一个值
queue.put("hello") # 放入第二个值
queue.put([1, 2, 3]) # 放入第三个值

# 打印队列对象
print(queue)

# 此时队列已满，会阻塞 
# queue.put("4") # 此时

# 获取第一个值
value1 = queue.get()
print(value1)
# 获取第二个值
value2 = queue.get()
print(value2)
# 获取第三个值
value3 = queue.get()
print(value3)

# 此时队列已空，会阻塞
# queue.get()