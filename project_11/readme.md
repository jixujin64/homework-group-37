# *Project11: impl sm2 with RFC6979
## 实现背景：
SM2是一种国家商用密码算法，基于椭圆曲线密码体制(ECDSA)。RFC6979是一项规范，描述了一种确定性签名算法，用于产生随机数，以增强ECDSA签名方案的安全性。

实现SM2算法的一般步骤如下：

1.选择椭圆曲线参数：根据SM2标准，选择一条特定的椭圆曲线参数。

2.密钥生成：生成SM2的公钥和私钥。私钥是一个随机数，公钥是由私钥通过椭圆曲线点乘运算得到的点。

3.签名生成：使用RFC6979规范生成确定性随机数，根据RFC6979，使用私钥、消息和其他参数计算出一个固定的随机数，然后用该随机数进行签名。

4.签名验证：验证签名的有效性。使用公钥、消息和签名参数来验证签名的正确性。


## 运行环境：
*软件环境：* win11 IDLE (Python 3.10 64-bit)
*硬件环境：*
处理器	11th Gen Intel(R) Core(TM) i5-11300H @ 3.10GHz   2.61 GHz

机带 RAM	16.0 GB (15.7 GB 可用)


## 实现效果：
<img width="407" alt="image" src="https://github.com/jixujin64/homework-group-37/assets/139337238/0f1b2e41-d059-4bde-9a24-cdc276486621">

runtime：0.613802433013916 s

## 参考资料:
[1] https://www.rfc-editor.org/rfc/rfc6979



