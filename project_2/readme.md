# project2： implement the Rho method of reduced SM3
## 实现环境
#### 软件环境：
visual studio 2022
#### 硬件环境：
处理器	11th Gen Intel(R) Core(TM) i5-11300H @ 3.10GHz   2.61 GHz
机带 RAM	16.0 GB (15.7 GB 可用)


## 实现方式
<img width="273" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/c1e23bf3-b568-4397-8da0-acd0a60430c3">   <br>
SM3的rho攻击是一种与朴素生日攻击不同的攻击方式，它利用了SM3哈希函数中的rho变换特性来构造碰撞。
rho碰撞攻击的基本思想：1.初始化两个变量 x 和 y 为相同的初始值。2.以不同的方式迭代计算 x 和 y 的哈希值，例如通过对 x 和 y 进行不同次数的哈希计算。3.在每次迭代后，比较 x 和 y 的值，如果它们相等，则找到了碰撞点，攻击成功。4.如果 x 和 y 不相等，则继续迭代计算，重复步骤2和3，直到找到碰撞点。
在这里，使用cryptopp库。
## 实现效果

|bits|时间:s|
|:---|:---|
|8|0.017028|
|16|0.102533|
|32|49.69324|


## 部分截图
8bit：<br>
![inage](https://github.com/jixujin64/homework-group-37/blob/main/project_2/8bits.png?raw=true)

16bit:<br>

![image](https://github.com/jixujin64/homework-group-37/blob/main/project_2/16bits.png?raw=true)

32bit: <br>
![image](https://github.com/jixujin64/homework-group-37/blob/main/project_2/32bits.png?raw=true)
## 分析
相对于之前的朴素的基于生日悖论碰撞攻击，rho攻击算法的速度快了很多。

