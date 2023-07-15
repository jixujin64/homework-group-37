# *Project3: implement length extension attack for SM3, SHA256, etc.

## sm3/sha-256长度扩展攻击
在SM3/SHA-256中，长度扩展攻击是指攻击者可以在不知道消息的内容的情况下，构造出一个具有相同哈希值的继承消息。
这是因为使用了Merkle–Damgård结构，将消息分块处理。攻击者可以通过对已知哈希值的消息添加一些额外数据，再重新计算哈希值，从而构造出一个新的继承消息。<br>
<img width="399" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/9fa2d0e3-a2f3-44b7-a06e-53c40c6e2e3c">

MD结构的主要特点是： <br>
1.分块处理：将输入消息分成固定大小的块，通常是 512 位或 1024 位。 <br>
2.压缩函数：每个块通过一个压缩函数进行处理，该函数将当前块和前一个块的哈希值作为输入，输出一个新的哈希值。 <br>
3.迭代计算：将压缩函数的输出作为下一个块的输入，并重复这个过程，直到处理完所有块。 <br>
4.初始向量：第一个块的哈希值称为初始向量，通常是一个固定的值。 <br>
这个结构的优点是可以处理任意长度的输入消息。 <br>

## SM3的长度扩展攻击
### 攻击思路：
1.随机选取一个消息m1（this is sm3 length extension attack），事实上不需要知其内容，只需要知道长度。填充后m1||padding，利用sm3算法求其哈希值hash(m1)，记为h1； <br>
2.对另一个消息m2（Let's construct a forgery attack），计算hash(m1||padding||m2),记为h2； <br>
3.以h1的8个字为SM3算法的初始向量ABCDEFGH,计算hash(m3)，记为h3； <br>
4.比较h1和h3，如果相等，则伪造成功。 <br>

### 实现环境
#### 软件环境：
IDLE (Python 3.10 64-bit)
#### 硬件环境：
处理器	11th Gen Intel(R) Core(TM) i5-11300H @ 3.10GHz   2.61 GHz
  机带 RAM	16.0 GB (15.7 GB 可用)

### 代码实现效果
<img width="411" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/ab81059d-29a7-40c7-8780-85b305ecb3bc">

