/**
 * 并发队列
 * 有两个 lock, 分别用于 enqueue 和 dequeue,
 * 使得这两个操作可以并发执行
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

typedef struct __node_t {
  int value;
  struct __node_t *next;
} node_t;

typedef struct __queue_t {
  node_t *head;
  node_t *tail;
  pthread_mutex_t headLock;
  pthread_mutex_t tailLock;
} queue_t;

void queue_init(queue_t * q) {
  node_t *tmp = malloc(sizeof(node_t));
  tmp->next = NULL;
  // 队列内先存入一个 dummy node
  q->head = q->tail = tmp;
  // headLock 不是指针, 所以要使用 &q->headLock, 而不是 q->headLock
  pthread_mutex_init(&q->headLock, NULL);
  pthread_mutex_init(&q->tailLock, NULL);
}

void queue_enqueue(queue_t *q, int value) {
  // malloc 不需要在 lock 范围内
  node_t *tmp = malloc(sizeof(node_t));
  assert(tmp != NULL);
  tmp->value = value;
  tmp->next = NULL;

  pthread_mutex_lock(&q->tailLock);
  q->tail->next = tmp;
  q->tail = tmp;
  pthread_mutex_unlock(&q->tailLock);
}

// *value 用于存放出队的 node_t 的值
int queue_dequeue(queue_t *q, int * value) {
  pthread_mutex_lock(&q->headLock);
  node_t *tmp = q->head;
  node_t *newHead = tmp->next;
  if (newHead == NULL) {
    pthread_mutex_unlock(&q->headLock);
    return -1;
  }
  *value = newHead->value;
  q->head = newHead;
  pthread_mutex_unlock(&q->headLock);
  free(tmp);
  return 0;
}

int main(void) {
  return 0;
}
