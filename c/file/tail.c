/**
 * tail file
 * 打印 file 的最后几行
 * eg: tail -n file, n 是一个数字, 代表要打印最后多少行的内容
 * 首先 seek to 文件的末尾, 然后往回走 n 行
 *
 * **未完待续**
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
  int lines;
  char num[10];

  if (argc < 3) {
    perror("lack of arguments");
  }

  // 提取 -n 数字
  strcpy(num, argv[1] + 1);
  lines = (int) strtol(num, (char **) NULL, 10);

  printf("%d \n", lines);
  int fd = open(argv[2], O_WRONLY);
  off_t end_pos = lseek(fd, 0, SEEK_END);

  return 0;
}
