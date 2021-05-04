使用 greenlet 可以实现协程

Greenlet是python的一个C扩展，来源于Stackless python，旨在提供可自行调度的‘微线程’，即协程。generator实现的协程在yield value时只能将value返回给调用者(caller)。 而在greenlet中，target.switch（value）可以切换到指定的协程（target）， 然后yield value。greenlet用switch来表示协程的切换，从一个协程切换到另一个协程需要显式指定。

为了更好使用协程来完成多任务，python中的greenlet模块对其封装，从而使得切换任务变的
更加简单

安装：pip install greenlet 

不是重点，不直接用，一般使用的是gevent

