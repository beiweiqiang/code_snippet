/**
 * 优化后的 current counter:
 * 一个 global lock, 多个 local lock
 * 一个 global counter, 多个 local counter
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#define NUMCPUS 4

typedef struct __counter_t {
  int global;
  pthread_mutex_t glock;
  int local[NUMCPUS];
  pthread_mutex_t llock[NUMCPUS];
  int threshold;
} counter_t;

void init(counter_t *c, int threshold) {
  c->threshold = threshold;
  c->global = 0;
  pthread_mutex_init(&c->glock, NULL);
  int i;
  for(i = 0; i < NUMCPUS; i++) {
    c->local[NUMCPUS] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

void update(counter_t *c, int threadID) {
  int cpu = threadID % NUMCPUS;
  pthread_mutex_lock(&c->llock[cpu]);
  c->local[cpu] += 1;
  if (c->local[cpu] >= c->threshold) {
    pthread_mutex_lock(&c->glock);
    c->global += c->local[cpu];
    pthread_mutex_unlock(&c->glock);
    c->local[cpu] = 0;
  }
  pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) {
  pthread_mutex_lock(&c->glock);
  int val = c->global;
  pthread_mutex_unlock(&c->glock);
  return val;
}

void * thread_handler(void * args) {
  counter_t * c = (counter_t *) args;
  update(c, (int) pthread_self());
}

int main(void) {
  pthread_t thr;
  size_t i;
  counter_t c;
  init(&c, 5);
  clock_t begin = clock();

  for (i = 0; i < 10000; i++) {
    pthread_create(&thr, NULL, thread_handler, (void *) &c);
  }
  pthread_join(thr, NULL);

  printf("%d \n", get(&c));
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%lf s", time_spent); // 1.276220 s

  return 0;
}

