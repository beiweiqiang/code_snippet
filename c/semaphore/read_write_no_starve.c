/**
 * 多个 readers, 一个 writer
 * 如何避免 writer 的 starve 状态 ?
 * 当一个 writer 想要进行处理, 会等待目前正在 process 的 readers 完成,
 * 但是后来想要获得 lock 的 readers 会被阻塞直到 writer 完成
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

//
// Your code goes in the structure and functions below
//

typedef struct __rwlock_t {
  sem_t lock;
  sem_t write_lock;
  int readers;
  int writers;
} rwlock_t;

void rwlock_init(rwlock_t *rw) {
  rw->readers = 0;
  rw->writers = 0;
  sem_init(&rw->lock, 0, 1);
  sem_init(&rw->write_lock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  while (rw->writers > 0) {
    sem_wait(&rw->write_lock);
  }
  rw->readers++;
  printf("readers: %d \n", rw->readers);
  sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  rw->readers--;
  printf("readers: %d \n", rw->readers);
  if (rw->readers == 0) {
    sem_post(&rw->write_lock);
  }
  sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  sem_wait(&rw->write_lock);
  rw->writers++;
  printf("writers: %d \n", rw->writers);
  sem_post(&rw->lock);
}

void rwlock_release_writelock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  sem_post(&rw->write_lock);
  rw->writers--;
  printf("writers: %d \n", rw->writers);
  sem_post(&rw->lock);
}

//
// Don't change the code below (just use it!)
// 

int loops;
int value = 0;

rwlock_t lock;

void *reader(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    rwlock_acquire_readlock(&lock);
    printf("read %d\n", value);
    rwlock_release_readlock(&lock);
  }
  return NULL;
}

void *writer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    rwlock_acquire_writelock(&lock);
    value++;
    printf("write %d\n", value);
    rwlock_release_writelock(&lock);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  assert(argc == 4);
  int num_readers = atoi(argv[1]);
  int num_writers = atoi(argv[2]);
  loops = atoi(argv[3]);

  pthread_t pr[num_readers], pw[num_writers];

  rwlock_init(&lock);

  printf("begin\n");

  int i;
  for (i = 0; i < num_readers; i++)
    pthread_create(&pr[i], NULL, reader, NULL);
  for (i = 0; i < num_writers; i++)
    pthread_create(&pw[i], NULL, writer, NULL);

  for (i = 0; i < num_readers; i++)
    pthread_join(pr[i], NULL);
  for (i = 0; i < num_writers; i++)
    pthread_join(pw[i], NULL);

  printf("end: value %d\n", value);

  return 0;
}

