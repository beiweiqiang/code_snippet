/**
 * stat 程序
 * ./stat file
 * 展示 file 的信息
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  char * pathname = argv[1];
  struct stat sb;

  if (stat(pathname, &sb) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }

  printf("file size: %lld bytes\n", (long long) sb.st_size);
  printf("blocks allocated: %lld \n", (long long) sb.st_blocks);
  printf("reference count: %ld \n", (long) sb.st_nlink);
  printf("inode number: %ld \n", (long) sb.st_ino);

  return 0;
}
