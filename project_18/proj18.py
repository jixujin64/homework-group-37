from bitcoinlib.transactions import Transaction, Input, Output
from bitcoinlib.keys import PrivateKey, P2PKH_Address

# 创建一个输出地址 - 替换为自己的测试网络地址
output_address = P2PKH_Address('n3LHh2xVeTEALjM4iZdiZHX8jC7qEdGMb4')

# 创建一个输入交易
input_transaction_hash = '1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef'
input_transaction_index = 0
input_transaction_value = 10000 # 以聪为单位（1 BTC = 100000000 聪）

# 创建一个新交易
transaction = Transaction()

# 添加输入到交易中
transaction.add_input(Input(input_transaction_hash, input_transaction_index))

# 添加输出到交易中
transaction.add_output(Output(output_address, input_transaction_value))

# 签名交易
private_key = PrivateKey('[您的私钥]')
transaction.sign(private_key)

# 序列化交易
serialized_tx = transaction.serialize()

# 解析序列化的交易数据
parsed_tx_data = []
for byte in serialized_tx:
    parsed_tx_data.append(format(byte, '02x'))

# 显示解析后的交易数据
for i, data in enumerate(parsed_tx_data):
    print(f"字节 {i}: {data}")
