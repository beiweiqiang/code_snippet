/**
 * 测量运行时间
 */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>

int main(void) {
  clock_t begin = clock();
  for (int i = 0; i < 10000000; ++i) ;
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%lf s", time_spent);
  return 0;
}
