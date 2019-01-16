import multiprocessing as mp
import logging
import socket
import time

serverPort = 12001


# logger = mp.log_to_stderr(logging.DEBUG)

def worker(serverSocket):
  while True:
    connectionSocket, addr = serverSocket.accept()
    print(addr, time.time(), '<--')
    # logger.debug("{u} connected".format(u=address))
    # client.send("OK")
    # client.close()
    try:
      message = connectionSocket.recv(2048)

      fileName = message.split()[1].decode()
      f = open(fileName[1:])
      outputData = f.readlines()

      connectionSocket.send('HTTP/1.1 200 OK\n'.encode())
      connectionSocket.send('Content-Type: text/html\n\n'.encode())

      for i in range(0, len(outputData)):
        connectionSocket.send(outputData[i].encode())
      connectionSocket.close()
      print(addr, time.time(), '-->')

    except IOError:
      connectionSocket.send('404 not found'.encode())

    connectionSocket.close()

if __name__ == '__main__':
  num_workers = 20

  serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
  serverSocket.bind(('', serverPort))
  serverSocket.listen(4)

  workers = [mp.Process(target=worker, args=(serverSocket,)) for i in
             range(num_workers)]

  for p in workers:
    p.daemon = True
    p.start()

  while True:
    try:
      time.sleep(10)
    except:
      break
