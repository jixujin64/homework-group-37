# *Project9: AES / SM4 software implementation
## AES的软件实现
### 实现环境：
软件环境：visual studio 2022

硬件环境：处理器	11th Gen Intel(R) Core(TM) i5-11300H @ 3.10GHz   2.61 GHz  机带 RAM	16.0 GB (15.7 GB 可用)


### 实现过程
注意:

1.字节替换使用查找表的方法

2.最后一轮无列混合


<img width="338" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/8d33c992-9d6d-454d-9d9f-2b9a0b2d7ad1">



运行效果：

<img width="252" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/a6c620b5-cebe-42c2-9d49-595dc6272efa">

## SM4的软件实现
SM4加解密过程主要包括以下步骤：

密钥扩展：将128位的密钥扩展为32个轮密钥。通过密钥扩展算法，根据初始密钥计算出每一轮需要使用的子密钥。

加密过程：
a. 初始置换：将输入的128位数据按照一定规则进行初步的置换操作。

b. 轮函数迭代：对初始置换后的数据进行32轮的迭代处理。每一轮包括四个基本操作：字节替代（Substitution）、行移位（Shift Rows）、列混淆（Mix Columns）和轮密钥加（Add Round Key）。

c. 末尾置换：在最后一轮迭代结束后，对数据进行末尾置换操作。

解密过程：

a. 加密和解密使用相同的轮密钥，但使用顺序相反。

b. 解密过程与加密过程类似，只是在轮密钥的使用顺序上有所调整。

运行效果：

<img width="491" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/24e33afb-f3e4-439b-8017-6c854f204217">



## 参考资料：
[1] https://zhuanlan.zhihu.com/p/360393988
