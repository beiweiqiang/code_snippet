/**
 * 简单的 Producer/Consumer 模型
 * buffer 只能存一个值
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include "mythreads.h"

int buffer;
int count = 0;

void put(int value) {
  assert(count == 0);
  count = 1;
  buffer = value;
}

int get() {
  assert(count == 1);
  count = 0;
  return buffer;
}

int loops;
pthread_cond_t fill, empty;
pthread_mutex_t mutex;

void *producer(void * arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);
    while (count == 1) {
      // 等一个 empty 信号
      Pthread_cond_wait(&empty, &mutex);
    }
    put(i);
    // 发送一个 fill 信号
    Pthread_cond_signal(&fill);
    Pthread_mutex_unlock(&mutex);
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);
    while (count == 0) {
      Pthread_cond_wait(&fill, &mutex);
    }
    int tmp = get();
    Pthread_cond_signal(&empty);
    Pthread_mutex_unlock(&mutex);
    printf("%d \n", tmp);
  }
}

int main(void) {
  return 0;
}
