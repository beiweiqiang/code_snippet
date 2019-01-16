from socket import *

serverPort = 12000

# SOCK_STREAM 建立 TCP 连接
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))

# 参数 1 指定最多进行排队的 connection 个数为 1
serverSocket.listen(1)

print('server is ready')

while True:
  # 对于每个到来的 client, 创建一个新的 connection socket
  connectionSocket, addr = serverSocket.accept()
  print(addr)
  message = connectionSocket.recv(2048)
  print(message.decode())
  modifiedMessage = message.upper()
  connectionSocket.send(modifiedMessage)
  connectionSocket.close()
