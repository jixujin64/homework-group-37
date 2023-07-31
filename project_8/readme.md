# *Project8: AES impl with ARM instruction
## 背景
针对AES对称加密算法，ARM架构提供了专门的指令扩展，称为AES指令集扩展。ARM的AES指令集扩展为处理AES算法提供了硬件加速支持，通过在处理器中引入新的AES指令，可以有效地执行加密和解密操作，提高数据处理速度和效率。使用ARM的AES指令集扩展，可以在特定的ARM处理器上利用硬件加速来执行AES算法，而无需依赖软件实现。这些指令包括AES加密（AESE）指令和AES解密（AESD）指令。

AES的加密：

1.密钥扩展(Key Expansion)：
首先根据选择的AES密钥长度（128位、192位或256位），执行密钥扩展算法生成扩展密钥。密钥扩展使用特定的算法，如Rijndael算法，根据初始密钥生成一系列轮密钥（Round Keys）。

2轮密钥加(Round Key Addition)：将输入数据与第一个轮密钥进行异或操作。

3.轮函数(SubBytes、ShiftRows、MixColumns和AddRoundKey)：
这是AES的核心处理步骤，通过一系列操作对数据进行混淆和替换：
①SubBytes：使用S-Box字节替换表将输入字节映射到一个新的字节，唯一的非线性部件。

②ShiftRows：对输入的字节进行行移位操作，改变其顺序。

③MixColumns：列混合，将每一列的数据进行线性变换。

④AddRoundKey：将轮密钥与处理后的数据进行异或操作。


重复执行轮函数：
注意最后一轮：在最后一轮中，省略MixColumns步骤。
## 实现：

因为我的电脑是x86指令集，无法直接运行ARM指令集，所以仅给出伪代码

伪代码：
```
; 寄存器定义
.data
input_block:    .byte 16         ; 输入数据块
output_block:   .byte 16         ; 输出数据块
key:            .byte 16         ; 密钥
state:          .byte 16         ; 当前状态
.text
.global aes_encrypt               ; 全局可见的AES加密函数
aes_encrypt:
    ; 导入输入数据块和密钥到寄存器
    ldr r0, =input_block
    ldr r1, =key
    vld1.8 {d0}, [r0]             ; 输入数据块
    vld1.8 {d1}, [r1]             ; 密钥
    ; 初始轮密钥加
    vadd.i8 q0, q0, q1
    ; 主循环（9次）
    mov r2, #9                    ; 轮数
aes_rounds:
    ; SubBytes 步骤
    vtbl.8 d2, {d0}, d2           ; 使用查找表进行字节替换
    ; ShiftRows 步骤
    vrev32.8 q0, q0               ; 交换字节顺序
    ; MixColumns 步骤
    vmov.8 q1, #0x02              ; 用于 MixColumns 的常数
    vmull.b8 q0, d0, q1           ; 混合列乘法
    vmull.b8 q0, d1, q1
    vmull.b8 q0, d2, q1
    vmull.b8 q0, d3, q1
    ; AddRoundKey 步骤
    vld1.8 {d1}, [r1]             ; 轮密钥
    vadd.i8 q0, q0, q1
    ; 更新循环计数器
    subs r2, r2, #1
    bne aes_rounds
    ; 最后一轮（无 MixColumns 步骤）
    ; SubBytes 步骤
    vtbl.8 d2, {d0}, d2
    ; ShiftRows 步骤
    vrev32.8 q0, q0
    ; AddRoundKey 步骤
    vadd.i8 q0, q0, q1
    ; 导出加密后的数据块
    ldr r0, =output_block
    vst1.8 {d0}, [r0]
    bx lr                          ; 返回

```
## 参考资料：
[1] http://skypacer210.github.io/2013/12/22/aes-acceleration-in-arm/
