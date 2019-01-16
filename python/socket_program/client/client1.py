import requests
import time

num_requests = 1000

startTime = time.time()
print('nums:', num_requests, 'start:', startTime)
responses = [
  requests.get('http://localhost:12001/index.html')
  for i in range(num_requests)
]

endTime = time.time()
print('end:', endTime)
print('spend:', endTime - startTime)
