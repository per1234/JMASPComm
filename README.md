JMASPComm Small Pack Communication Protocol

v1.0 for iOS ( 2014.02 )

JungleMetal Software.
support@junglemetal.com

2015.11.01	Kunpeng Zhang<zkppro@gmail.com> modified for arduino


Implement a simple serial communication. Use binary mode with frame CRC check.
Each data length is no more than 256 bytes (including frame header).

+----------------------------------+
| Frame header: 0x023C 2 bytes
+----------------------------------+
| Frame Length: 0xXX 1 byte
+----------------------------------+
| Communication version: 0x10 1 byte
+----------------------------------+
| Data version: 0x10 1 byte
+----------------------------------+
| Data area
| ......
| ......
+----------------------------------+
| CRC: 0xXX 1 byte. 
| included: frame long + communication version + data version + data area
+----------------------------------+


Class Descriptions:

* JMASPComm communication base class
Implement data buffer operations, communication protocol information attributes, basic protocol interpretation, and verification functions.

* JMASPCommReceiver communication protocol receiving class
Implement the receive of communication data

* JMASPCommSender communication protocol sending class
Implement protocol packaging

* JMASPCommCmd communication command generator
Implement the creation of common protocol commands. Inherited from JMACOMMSender.
Applications can directly inherit JMASPCommSender to customize your communication commands.

Other classes

* JMABuffer
The buffer class is responsible for all operations of the buffer. Maximum buffer 255 bytes

* JMARange
Range structure, location, length

* JMACRC8
CRC check calculation function, byte flip function




------------------------------------------------

JMASPComm 小包简单通讯协议

v1.0 for iOS ( 2014.02 )

JungleMetal Software.
support@junglemetal.com

2015.11.01	Kunpeng Zhang<zkppro@gmail.com> modified for arduino


实现一个简单的串行通讯协议。使用二进制方式，带数据帧 CRC 校验。
每个数据帧长度不超过 256 字节（包含帧头）。

+----------------------+
| 帧头: 0x023C  2字节
+----------------------+
| 帧长: 0xXX	1字节
+----------------------+
| 通讯版本: 0x10 1字节 
+----------------------+
| 数据版本: 0x10 1字节
+----------------------+
| 数据区
| ......
| ......
+----------------------+
| CRC: 0xXX 1字节。
| 计算内容：帧长+通讯版本+数据版本+数据区
+----------------------+


类说明：

* JMASPComm 通讯基类 
	实现数据缓存操作，通讯协议信息属性，协议基本解读，校验功能。

* JMASPCommReceiver 通讯协议接收类
	实现通讯数据的接收

* JMASPCommSender 通讯协议发送类
	实现数据协议打包工作

* JMASPCommCmd 通讯命令生成器
	实现常用协议命令的创建。继承自 JMACOMMSender。
	应用可以直接继承 JMACOMMSender 自己定义其他通讯命令实现.


其他辅助类

* JMABuffer
	缓存类，提供缓存的各项操作。最大缓存 255 字节

* JMARange
	范围结构，location, length

* JMACRC8
	CRC 校验计算函数, 字节翻转函数
