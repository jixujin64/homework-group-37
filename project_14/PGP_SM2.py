import base64
import binascii
import time
from gmssl import sm2, func
from gmssl.sm4 import CryptSM4, SM4_ENCRYPT, SM4_DECRYPT

key = b'375butlj26hvv313'
value = b'101' #  bytes类型
iv = b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00' #  bytes类型
crypt_sm4 = CryptSM4()

private_key = '00D9AB0B828FF68872F21A837FC303668428DEA11DCD1B24429D0C99E24EED83D5'
public_key = 'B9C906E04E9C91F7BA880429273747D7EF5DDEB0BB2FF6317EB00BEF331A83081A6994B8993F3F5D6EADDDB81872266C87C018FB4162F5AF347B483E24620207'
sm2_crypt = sm2.CryptSM2(
    public_key=public_key, private_key=private_key)


def PGP_Enc(message,k):
    global iv,crypt_sm4,sm2_crypt
    enc_data = sm2_crypt.encrypt(k)
    crypt_sm4.set_key(k, SM4_ENCRYPT)
    encrypt_value = crypt_sm4.crypt_cbc(iv , message)
    return encrypt_value,enc_data

def PGP_Dec(encrypt_value,enc_data):
    global crypt_sm4,sm2_crypt
    k =sm2_crypt.decrypt(enc_data)
    crypt_sm4.set_key(k, SM4_DECRYPT)
    decrypt_value = crypt_sm4.crypt_ecb(encrypt_value)
    return decrypt_value,k

message=b'123456789'
start=time.time()
encrypt_value,enc_data=PGP_Enc(message,key)
print("encrypt_value",encrypt_value)
print("enc_data",enc_data)
decrypt_value,k=PGP_Dec(encrypt_value,enc_data)
print("decrypt_value",decrypt_value)
print("k",k)
end=time.time()
print("用时：",end-start,"s")
    
