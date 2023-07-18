# *Project4: do your best to optimize SM3 implementation (software)
## 背景知识
###  sm3算法流程
#### 1.消息填充
SM3的消息扩展步骤是以512位的数据分组作为输入的。因此，我们需要在一开始就把数据长度填充至512位的倍数。数据填充规则和MD5一样，具体步骤如下：<br>
1、先填充一个“1”，后面加上k个“0”。其中k是满足(n+1+k) mod 512 = 448的最小正整数。<br>
2、追加64位的数据长度（bit为单位，大端序存放)<br>
#### 2.分组
将填充后的消息按512比特进行分组，每一组也就是16个字，共n组
#### 3.消息扩展
遵顼某种特定的运算，把每一组的消息块进行扩展，从16个字扩展到132个字
#### 4.迭代压缩
进行n轮的压缩函数CF。由于每一轮的输入都与上一轮的输出有关，所以不能直接并行处理。
### sm3优化思路
1.多线程优化：<br>
压缩函数是最耗时的部分，是优化sm3的关键，这里使用4个线程来并行计算SM3哈希算法。compress函数被传递给每个线程，并在不同的数据块上执行压缩操作。同时，使用互斥锁std::mutex和std::lock_guard，确保在更新V数组时，只有一个线程可以访问。
在sm3Hash函数中，我们创建了4个线程，并分配不同的数据块给每个线程进行并行计算。然后，我们等待所有线程完成计算，然后将结果拼接成最终的哈希值。
2.使用SIMD指令并行处理多个数据块

SIMD（Single Instruction, Multiple Data单指令多数据）指令集是一种通过一条指令同时处理多个数据元素的技术。在优化SM3算法时，可以使用SIMD指令来并行处理多个数据块，提高计算效率。可以使用SIMD指令集中的并行操作指令，如MMX（MultiMedia eXtensions）、SSE（Streaming SIMD Extensions）、AVX（Advanced Vector Extensions）等来加速SM3算法。这些指令集可以同时对多个数据元素执行相同的计算操作，从而减少指令的执行次数和计算的延迟。

在使用SIMD指令优化SM3算法时，可以将数据分成多个块，每个块的大小为SIMD指令集支持的数据元素的个数。然后，对每个数据块使用SIMD指令进行并行计算，最后将计算结果合并得到最终的结果。
### 效果
未优化：<br>
<img width="541" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/c5e39727-a99e-4e82-bedf-14ac921a2085">

多线程：<br>
<img width="606" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/84ed9c64-c926-4c6d-8b6e-6adf552a7d6c">

## 参考资料：
[1] SM3算法流程：https://www.cnblogs.com/11sgXL/p/17006282.html
