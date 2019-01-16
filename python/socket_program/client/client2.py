import asyncio
import requests
import time
import concurrent.futures

num_requests = 1000

startTime = time.time()
print('nums:', num_requests, 'start:', startTime)


async def main():
  with concurrent.futures.ThreadPoolExecutor(max_workers=1000) as executor:
    loop = asyncio.get_event_loop()
    futures = [
      loop.run_in_executor(
        executor,
        requests.get,
        'http://localhost:12001/index.html'
      )
      for i in range(num_requests)
    ]
    for response in await asyncio.gather(*futures):
      pass


loop = asyncio.get_event_loop()
loop.run_until_complete(main())

endTime = time.time()
print('end:', endTime)
print('spend:', endTime - startTime)
