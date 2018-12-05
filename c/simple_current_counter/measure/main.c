/**
 * 多线程测量 simple current counter 的效果
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>

typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  c->value++;
  pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  c->value--;
  pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  int rc = c->value;
  pthread_mutex_unlock(&c->lock);
  return rc;
}

void * thread_handler(void * args) {
  counter_t * c = (counter_t *) args;
  increment(c);
  printf("thread: %d \n", get(c));
}

int main(void) {
  pthread_t thr;
  size_t i;
  counter_t c;
  init(&c);

  for (i = 0; i < 100; i++) {
    pthread_create(&thr, NULL, thread_handler, (void *) &c);
  }
  pthread_join(thr, NULL);

  printf("%d \n", get(&c));

  return 0;
}
