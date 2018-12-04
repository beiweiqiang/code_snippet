/**
 * 并发 hash table, 基于 current linked list
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#define BUCKETS (101)

//----- current linked list -----
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

// 返回 -1 则插入不成功, 返回 0 则成功
int list_insert(list_t *l, int key) {
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    return -1;
  }
  new->key = key;

  pthread_mutex_lock(&l->lock);
  new->next = l->head;
  l->head = new;
  pthread_mutex_unlock(&l->lock);
  return 0;
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
//----- current linked list -----

typedef struct __hash_t {
  list_t lists[BUCKETS];
} hash_t;

void hash_init(hash_t *h) {
  int i;
  for(i = 0; i < BUCKETS; i++) {
    list_init(&h->lists[i]);
  }
}

int hash_insert(hash_t *h, int key) {
  int bucket = key % BUCKETS;
  return list_insert(&h->lists[bucket], key);
}

int hash_lookup(hash_t *h, int key) {
  int bucket = key % BUCKETS;
  return list_lookup(&h->lists[bucket], key);
}

int main(void) {
  return 0;
}
