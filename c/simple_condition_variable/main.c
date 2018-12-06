/**
 *
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include "mythreads.h"

/**
 * 为什么需要 done 变量 ?
 * 存在情况: 父线程创建了子线程以后, 子线程马上运行, 发送 signal 但是没有 sleep 的线程, 然后子线程结束,
 * 接着父线程运行, 没有 done 作为判断依据, 父线程直接调用 wait() 进入 sleep
 */
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
  Pthread_mutex_lock(&m);
  done = 1;
  Pthread_cond_signal(&c);
  Pthread_mutex_unlock(&m);
}

void *child(void * arg) {
  printf("child \n");
  thr_exit();
  return NULL;
}


/**
 * 为什么需要 lock ?
 * 存在情况: while 判断 done 为 0, 进入语句块, 准备执行 wait() 之前, 线程切换到子线程运行,
 * 子线程执行 signal 并没有 sleep 的线程, 子线程结束, 返回父线程
 * 父线程然后调用 wait() 进入 sleep
 * 
 * 如果想要去掉 lock, 需要考虑运行过程中, 可能会发生 context switch 的情况
 */
void thr_join() {
  Pthread_mutex_lock(&m);
  while (done == 0) {
    Pthread_cond_wait(&c, &m);
  }
  Pthread_mutex_unlock(&m);
}

int main(void) {
  printf("begin \n");
  pthread_t p;
  Pthread_create(&p, NULL, child, NULL);
  thr_join();
  printf("end\n");
  return 0;
}
