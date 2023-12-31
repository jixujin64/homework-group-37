# *Project5: Impl Merkle Tree following RFC6962
## 1.背景知识
### Merkle Tree的介绍
默克尔树是一种典型的二叉树结构，由一个根节点、一组中间节点和一组叶节点组成。Merkle Tree通常也被称作Hash Tree，顾名思义，就是存储hash值的一棵树。
Merkle树的叶子是数据块(例如，文件或者文件的集合)的hash值。非叶节点是其对应子节点串联字符串的hash。<br>
默克尔树的主要特点是使用哈希函数将大量数据块逐层递归地组织在一起，最终形成一个唯一的根哈希值。这个根哈希值可以用来验证数据的完整性，即使树中的某个数据块发生了改变，根哈希值也会不同

<img width="654" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/fd57b1f4-2ae4-4a3d-9109-f34e3111f9fb">

### Merkle Tree的操作及实现
##### ① 默克尔树的构建
默克尔树的构建过程如下：<br>
1.将要构建默克尔树的数据分割成固定大小的数据块。<br>
2.对每个块进行哈希计算，得到块的哈希值。<br>
3.不断将相邻的两个块的哈希值合并为一个新的哈希值，直到只剩下一个哈希值。<br>
4.最后得到的唯一哈希值即为默克尔树的根root哈希值。<br>
创建Merkle Tree是O(n)复杂度(这里指O(n)次hash运算)，n是数据块的大小。得到Merkle Tree的树高是log(n)+1。
##### ② 检索
默克尔树的检索通常用于验证某个数据块是否属于给定的数据集，或者验证整个数据集是否完整和一致。
通过比较根节点的哈希值，可以快速判断数据集是否被篡改。如果根节点的哈希值与预期的哈希值不一致，那么数据集可能已被篡改。
从根节点开始，根据节点哈希值和目标哈希值的比较，沿着树的路径向下移动，直到找到目标节点或到达叶子节点。
##### ③ 插入和删除

## 2.代码实现
①定义结构体：创建一个结构体来表示默克尔树的节点。节点应包括一个指向左子节点和右子节点的指针，以及一个保存哈希值的变量。以及还有一个表示树的结构体<br>
<img width="336" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/2fc47007-2372-4542-bf17-1c3754b2243a">
<br>
②哈希函数使用sha256，直接调用cryptopp库里的函数<br>
<img width="369" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/d8365080-706c-4ac5-8904-9299d0d653be"><br>
③创建树<br>
<img width="423" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/bfccdfa1-3058-490f-a1f9-f84c32d551ff">  <br>
④插入结点<br>
<img width="335" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/3f787cd8-1be5-4186-af62-0e9bcbcf1693"><br>
⑤删除结点<br>
<img width="380" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/44d8566f-509e-40a8-bb67-2242a6567105"><br>
⑥更新结点<br>
<img width="313" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/c20aa3c0-beb9-412f-a469-0e4692634614"><br>
⑦检索结点<br>
<img width="371" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/d1f0b29f-542d-40b8-b07c-00928503179d"><br>
## 3.实验环境
##### 软件环境：
vs 2022
##### 硬件环境：
处理器	11th Gen Intel(R) Core(TM) i5-11300H @ 3.10GHz   2.61 GHz   机带 RAM	16.0 GB (15.7 GB 可用)

## 4.效果：
叶子数据：char* leaves[] = {"abcd","acdew","yuhgdcd"，"576vdsj","cdsieydjk","e8hcdjsk","scidsozcerz","12738dsj","jinjixu123","202100150107","jjiuhb887","ji9jwk8"};<br>
<img width="824" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/b66cff1e-a897-433c-98fa-c544e3e2f853">

## 5.参考资料
[1] https://en.wikipedia.org/wiki/Merkle_tree<br>
[2] Merkle Tree学习: https://www.cnblogs.com/fengzhiwu/p/5524324.html<br>
[3] https://www.rfc-editor.org/rfc/rfc6962<br>
