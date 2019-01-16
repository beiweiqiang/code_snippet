from socket import *

serverName = '144.34.132.119'
serverPort = 12000

# SOCK_STREAM 代表是 TCP socket
clientSocket = socket(AF_INET, SOCK_STREAM)

# 建立 TCP 连接
clientSocket.connect((serverName, serverPort))
sentence = input('input low case: ')

# 通过 socket 直接发送, 不用带 destination address
clientSocket.send(sentence.encode())
modifiedSentence = clientSocket.recv(1024)
print(modifiedSentence.decode())
clientSocket.close()
