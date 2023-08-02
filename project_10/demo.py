from ecdsa import PrivateKey, hash256
import time

start=time.time()
e = int.from_bytes(hash256(b'my secret'), 'big') # 私钥
z = int.from_bytes(hash256(b'my message'), 'big')  # 加密的数据
print('e:',e)
print('z:',z)
pk = PrivateKey(e)
sig = pk.sign(z)
print("sig:",sig)
res = pk.point.verify(z, sig)
print('res:',res)
end=time.time()
print("用时：",end-start,"s")
