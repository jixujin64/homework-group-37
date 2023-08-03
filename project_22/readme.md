## *Project22: research report on MPT
## MPT 介绍
Merkle Patricia Tree（MPT）是一种基于前缀树和默克尔哈希树（Merkle Hash Tree）的数据结构，常用于实现区块链中的状态存储和验证。MPT提供了高效的键值对存储和检索，并具有不可篡改性和快速验证的特点。

MPT的主要思想是将数据按照键在树中进行存储，同时使用哈希算法对数据进行哈希。MPT的每个节点都包含一个状态或者一个子节点，其中叶子节点存储了键值对。

MPT的特点如下：

1.前缀树结构：MPT使用前缀树的结构来存储键值对。通过共享公共前缀，MPT能够高效地存储和检索数据，尤其适用于键之间存在大量相似前缀的情况。

2.默克尔哈希树：MPT使用哈希算法对节点和键值对进行哈希，以确保数据的不可篡改性和完整性。每个节点保存了其子节点的哈希值，因此任何数据的更改都会导致其哈希值的变化，从而可以快速检测到数据的篡改。

3.路径压缩：MPT通过路径压缩技术来减少存储空间。公共前缀的节点可以被压缩成一个节点，减少了存储空间的开销。

4.快速验证：由于每个节点保存了其子节点的哈希值，因此可以通过逐级验证哈希值来验证整个MPT的完整性。这使得快速验证和识别数据是否被篡改成为可能。

MPT常用于以太坊等区块链平台中，用于存储账户状态、交易历史和智能合约代码等信息。它提供了高效、安全的数据组织和验证机制，为区块链的可靠性和安全性做出了重要贡献。


MPT树中的节点：

**空节点(NULL)**- represented as the empty string：
简单的表示空，在代码中是一个空串。

**叶子节点(leaf)** - a 2-item node [ encodedPath, value ]：
表示为 [key,value]的一个键值对，其中key是key的一种特殊十六进制编码(MP编码)， value是value的RLP编码。

**分支节点(branch)** - a 17-item node [ v0 … v15, vt ]：
因为MPT树中的key被编码成一种特殊的16进制的表示，再加上最后的value，所以分支节点是一个 长度为17的list ** ** ， 前16个元素对应着key中的16个可能的十六进制字符 ， 如果有一个[key,value]对在这个分支节点终止，最后一个元素代表一个值 ，即分支节点既可以搜索路径的终止也可以是路径的中间节点。

**扩展节点(extension)** - a 2-item node [ encodedPath, key ]：
也是[key，value]的一个键值对 ，但是这里的 value是其他节点的hash值 ，这个 hash可以被用来查询数据库中的节点。也就是说通过hash链接到其他节点。

因此，有两种[key,value]节点(叶节点和扩展节点):

以太坊中对Key的编码：
在以太坊中，MPT树的key值共有三种不同的编码方式，以满足不同场景的不同需求。

三种编码方式分别为：

1.Raw编码（原生的字符）；

2.Hex编码（扩展的16进制编码）；

3.Hex-Prefix编码（16进制前缀编码）；

**Raw编码**
Raw编码就是原生的key值，不做任何改变。这种编码方式的key，是MPT对外提供接口的默认编码方式。

例如一条key为“cat”，value为“dog”的数据项，其key的Raw编码就是[‘c’, ‘a’, ‘t’]，换成ASCII表示方式就是[63, 61, 74]（Hex）

**Hex编码**
Hex编码就是把一个8位的字节数据用两个十六进制数展示出来，编码时，将8位二进制码重新分组成两个4位的字节，其中一个字节的低4位是原字节的高四位，另一个字节的低4位是原数据的低4位，高4位都补0，然后输出这两个字节对应十六进制数字作为编码。Hex编码后的长度是源数据的2倍。

Exp：

ASCII码：A (65) 二进制码：0100_0001 重新分组：0000_0100 0000_0001 十六进制： 4 1 Hex编码：41

若该Key对应的节点存储的是真实的数据项内容（即该节点是叶子节点），则在末位添加一个ASCII值为16的字符作为terminator；

若该key对应的节点存储的是另外一个节点的哈希索引（即该节点是扩展节点），则不加任何字符；

[‘c’,’a’,’t’] -> [6,3,6,1,7,4,16]

**HP编码**

目的：

区分leaf和extension
把奇数路径变成偶数路径
步骤：

如果有terminator（16）那么就去掉terminator。
根据表格给key加上prefix
|node type  |  path length    |    prefix   | hexchar|
|:---:|:---:|:---:|:---:|
|extension   | even           |    0000   |   0x0|
|extension  |  odd         |    0001  |    0x1|
|leaf     |    even           |    0010     | 0x2|
|leaf      |   odd            |    0011   |   0x3|


如果prefix是0x0或者0x2，加一个padding nibble 0 在prefix后面，所以最终应该是 0x00 和 0x20。原因是为了保证key（path）的长度为偶数。

例子： 末尾的字符“16”说明该节点为叶子结点，并且加上了0x20


[ 0, f, 1, c, b, 8, 16] -> '20 0f 1c b8'

编码转化：

<img width="432" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/122107f7-a30b-4530-9151-0c0830d9f24b">


MPT结构：

![image](https://github.com/jixujin64/homework-group-37/assets/139337238/af9bf210-b7dd-4db2-b7ae-803d6c61a929)

## 代码实现
*返回根*：

```
def root(self):
        return self._root
```

*返回根的hash值*：
```
def root_hash(self):
        if not self._root:
            return Node.EMPTY_HASH
        elif len(self._root) == 32:
            return self._root
        else:
            return keccak_hash(self._root)
```

*更新结点*：
```
def update(self, encoded_key, encoded_value):
        if self._secure:
            encoded_key = keccak_hash(encoded_key)
        path = NibblePath(encoded_key)
        result = self._update(self._root, path, encoded_value)
        self._root = result
def _update(self, node_ref, path, value):
        if not node_ref:
            return self._store_node(Node.Leaf(path, value))
        node = self._get_node(node_ref)

        if type(node) == Node.Leaf:
            if node.path == path:
                node.data = value
                return self._store_node(node)
            common_prefix = path.common_prefix(node.path)
            path.consume(len(common_prefix))
            node.path.consume(len(common_prefix))
            branch_reference = self._create_branch_node(path, value, node.path, node.data)
            if len(common_prefix) != 0:
                return self._store_node(Node.Extension(common_prefix, branch_reference))
            else:
                return branch_reference

        elif type(node) == Node.Extension:
            if path.starts_with(node.path):
                new_reference = self._update(node.next_ref, path.consume(len(node.path)), value)
                return self._store_node(Node.Extension(node.path, new_reference))

            common_prefix = path.common_prefix(node.path)
            path.consume(len(common_prefix))
            node.path.consume(len(common_prefix))
            branches = [b''] * 16
            branch_value = value if len(path) == 0 else b''

            self._create_branch_leaf(path, value, branches)
            self._create_branch_extension(node.path, node.next_ref, branches)

            branch_reference = self._store_node(Node.Branch(branches, branch_value))
            if len(common_prefix) != 0:
                return self._store_node(Node.Extension(common_prefix, branch_reference))
            else:
                return branch_reference

        elif type(node) == Node.Branch:
            if len(path) == 0:
                return self._store_node(Node.Branch(node.branches, value))

            idx = path.at(0)
            new_reference = self._update(node.branches[idx], path.consume(1), value)

            node.branches[idx] = new_reference

            return self._store_node(node)

```
*删除结点*：
```
def delete(self, encoded_key):
        if self._root is None:
            return
        if self._secure:
            encoded_key = keccak_hash(encoded_key)
        path = NibblePath(encoded_key)
        action, info = self._delete(self._root, path)
        if action == MerklePatriciaTrie._DeleteAction.DELETED: # Trie is empty
            self._root = None
        elif action == MerklePatriciaTrie._DeleteAction.UPDATED:
            new_root = info
            self._root = new_root
        elif action == MerklePatriciaTrie._DeleteAction.USELESS_BRANCH:
            _, new_root = info
            self._root = new_root

def _delete(self, node_ref, path):
        node = self._get_node(node_ref)
        if type(node) == Node.Leaf:
            if path == node.path:
                return MerklePatriciaTrie._DeleteAction.DELETED, None
            else:
                raise KeyError

        elif type(node) == Node.Extension:
            if not path.starts_with(node.path):
                raise KeyError

            action, info = self._delete(node.next_ref, path.consume(len(node.path)))

            if action == MerklePatriciaTrie._DeleteAction.DELETED:
                return action, None
            elif action == MerklePatriciaTrie._DeleteAction.UPDATED:
                child_ref = info
                new_ref = self._store_node(Node.Extension(node.path, child_ref))
                return action, new_ref
            elif action == MerklePatriciaTrie._DeleteAction.USELESS_BRANCH:
                stored_path, stored_ref = info
                child = self._get_node(stored_ref)
                new_node = None
                if type(child) == Node.Leaf:
                    path = NibblePath.combine(node.path, child.path)
                    new_node = Node.Leaf(path, child.data)
                elif type(child) == Node.Extension:
                    path = NibblePath.combine(node.path, child.path)
                    new_node = Node.Extension(path, child.next_ref)
                elif type(child) == Node.Branch:
                    path = NibblePath.combine(node.path, stored_path)
                    new_node = Node.Extension(path, stored_ref)

                new_reference = self._store_node(new_node)
                return MerklePatriciaTrie._DeleteAction.UPDATED, new_reference

```
*查询结点*：
```
 def get(self, encoded_key):
        if not self._root:
            raise KeyError
        if self._secure:
            encoded_key = keccak_hash(encoded_key)
        path = NibblePath(encoded_key)
        result_node = self._get(self._root, path)
        return result_node.data
 def _get_node(self, node_ref):
        raw_node = None
        if len(node_ref) == 32:
            raw_node = self._storage[node_ref]
        else:
            raw_node = node_ref
        return Node.decode(raw_node)

 def _get(self, node_ref, path):
        node = self._get_node(node_ref)
        if len(path) == 0:
            return node

        if type(node) is Node.Leaf:
            if node.path == path:
                return node

        elif type(node) is Node.Extension:
            if path.starts_with(node.path):
                rest_path = path.consume(len(node.path))
                return self._get(node.next_ref, rest_path)

        elif type(node) is Node.Branch:
            branch = node.branches[path.at(0)]
            if len(branch) > 0:
                return self._get(branch, path.consume(1))

        print('not exist in a new mpt.')
        raise KeyError
```



## 参考资料：
[1]. https://zhuanlan.zhihu.com/p/46702178

[2]. https://www.cnblogs.com/whyaza/p/10034128.html

[3]. https://github.com/WangHao-nlp/MPT/tree/main
