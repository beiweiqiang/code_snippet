/**
 * 并发链表
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

typedef struct __node_t {
  int key;
  struct __node_t * next;
} node_t;

typedef struct __list_t {
  node_t *head;
  pthread_mutex_t lock;
} list_t;

void list_init(list_t *l) {
  l->head = NULL;
  pthread_mutex_init(&l->lock, NULL);
}

void list_insert(list_t *l, int key) {
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    return;
  }
  new->key = key;

  pthread_mutex_lock(&l->lock);
  new->next = l->head;
  l->head = new;
  pthread_mutex_unlock(&l->lock);
}

// 如果返回 0 则找到该元素, -1 则找不到
int list_lookup(list_t *l, int key) {
  int rv = -1;
  pthread_mutex_lock(&l->lock);
  node_t *cur = l->head;
  while (cur) {
    if (cur->key == key) {
      rv = 0;
      // break 跳出 while 循环
      break;
    }
    cur = cur->next;
  }
  pthread_mutex_unlock(&l->lock);
  return rv;
}

int main(void) {
  return 0;
}
