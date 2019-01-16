from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))

print('server is ready')

while True:
  message, clientAddress = serverSocket.recvfrom(2048)
  print(clientAddress)
  print(message.decode())
  modifiedMessage = message.upper()
  serverSocket.sendto(modifiedMessage, clientAddress)
