# third_ws 主要有 action 通讯,自定义action消息 
# 主要分为: SimpleAction 和 Action 

# SimpleAction 的不足
    1. 在同一个时间内，只能处理一个Goal指令。
    2. 如果在一个Goal指令没有执行完成时，有新的Goal指令到达，将取消当前的Gaol指令，执行新的Goal的。    

# Action 可以解决上述不足 
    其实SimpleAction是Action的简化版本，他将Action的复杂逻辑给隐藏了，给了一个最简易版本给我们使用，这个简易版本的不足就是不可以同时处理多个Goal。这种不足是设计出来的，并不是不可规避的。

    Ros Action State Machine: http://wiki.ros.org/actionlib/DetailedDescription
    参考: http://robot.czxy.com/docs/ros/action/simple/

