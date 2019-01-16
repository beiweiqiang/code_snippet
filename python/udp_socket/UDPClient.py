
from socket import *

serverName = '144.34.132.119'
serverPort = 12000

# AF_INET 说明是 IPv4, SOCK_DGRAM 说明是 UDP
clientSocket = socket(AF_INET, SOCK_DGRAM)
message = input('Input low case:')
clientSocket.sendto(message.encode(), (serverName, serverPort))
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())
clientSocket.close()

