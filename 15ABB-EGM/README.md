## RobotStudio Configuration

要使用ABB EGM需要有689-1 External Guided Motion模块
控制面板-配置-主题-Communication-Transmission Protocal下配置好UDP协议的地址和端口
EGMSensor needs to be defined under **Configuration Editor** - **Communication** - **Transmission Protocol.** The parameters are: 

| Name        | Type           | Serial Port  | Remote Adress   | Remote port number   |
| ----------- |:--------------:| ------------:| ---------------:| --------------------:|
| EGMSensor   | UDPUC          | N/A          | Computers IP	| 6510				   |
