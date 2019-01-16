
from socket import *
import time
from threading import Thread

serverPort = 12001

# SOCK_STREAM 建立 TCP 连接
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
serverSocket.bind(('', serverPort))
serverSocket.listen(4)

print('server is ready')

def thread_func(connectionSocket, addr):
  # 对于每个到来的 client, 创建一个新的 connection socket
  # 建立 TCP 连接
  # connectionSocket, addr = serverSocket.accept()
  print('create a thread')

  try:
    message = connectionSocket.recv(2048)

    fileName = message.split()[1].decode()
    f = open(fileName[1:])
    outputData = f.readlines()

    connectionSocket.send('HTTP/1.1 200 OK\n'.encode())
    connectionSocket.send('Content-Type: text/html\n'.encode())

    for i in range(0, len(outputData)):
      connectionSocket.send(outputData[i].encode())
    connectionSocket.close()
    print(addr, time.time(), '-->')

  except IOError:
    connectionSocket.send('404 not found'.encode())

  connectionSocket.close()

while True:
  connectionSocket, addr = serverSocket.accept()
  print(addr, time.time(), '<--')
  thread = Thread(target=thread_func, args=(connectionSocket, addr))
  thread.start()





