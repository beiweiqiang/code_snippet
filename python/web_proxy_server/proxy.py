from socket import *
import time
import sys

if len(sys.argv) <=1:
  print('python3.6 proxy.py server_ip')
  sys.exit(2)

serverPort = 12001

tcpServerSocket = socket(AF_INET, SOCK_STREAM)
tcpServerSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
tcpServerSocket.bind(('', serverPort))

# todo ?
tcpServerSocket.listen(1)

while True:
  print('ready to serve...')
  tcpClientSocket, address = tcpServerSocket.accept()
  print('received a connection from:', address)
  msg = tcpClientSocket.recv(4096)
  filename = msg.split()[1].decode().partition('/')[2]
  fileExist = "false"
  filetouse = '/' + filename

  try:
    f = open(filetouse[1:], 'r')
    outputData = f.readlines()
    fileExist = "true"
    for i in range(0, len(outputData)):
      tcpClientSocket.send(outputData[i].encode())
    tcpClientSocket.close()
    print('proxy.py', '41', '->', 'cache from local')

  except IOError:
    if fileExist == 'false':
      c = socket(AF_INET, SOCK_STREAM)
      hostname = filename
      print('proxy.py', '46', hostname)
      try:
        c.connect((hostname, 80))
        send_str = 'GET / HTTP/1.1\r\n' + 'Host: ' + hostname + '\r\n\r\n'
        print('proxy.py', '50', '->', send_str)
        c.sendall(send_str.encode())
        buffer = c.recv(4096)
        tcpClientSocket.sendall(buffer)
        # fileobj = c.makefile('r', None)
        # fileobj.write('GET / HTTP/1.1\r\n' + 'Host: ' + 'www.example.org' + '\r\n\r\n')
        # buffer = fileobj.readlines()
        tmpFile = open(filename, 'w')
        tmpFile.writelines(buffer.decode())
        tmpFile.close()
      except error:
        print('illegal request')
  else:
    print('file not found')
  tcpClientSocket.close()



















