/**
 * Producer/Consumer 模型
 * buffer 能存多个值
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
// 从 ../simple_producer_consumer/mythreads.h 引入
#include "mythreads.h"
#define MAX 100

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
  buffer[fill_ptr] = value;
  fill_ptr = (fill_ptr + 1) % MAX;
  count++;
}

int get() {
  int tmp = buffer[use_ptr];
  use_ptr = (use_ptr + 1) % MAX;
  count--;
  return tmp;
}

int loops;
pthread_cond_t fill, empty;
pthread_mutex_t mutex;

void *producer(void * arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);
    while (count == MAX) {
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
