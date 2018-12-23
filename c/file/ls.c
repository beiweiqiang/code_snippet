/**
 * List Files
 * 列举在 directory 中的文件
 * - 如果没有传入参数, 则打印 file names
 * - 如果调用传入 -l, 则需要打印每个 file 的信息, 比如 owner, group, permission...
 * eg: myls -l directory, 如果没有传入 directory, 使用当前处在的目录
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char * argv[]) {
  char buf[256];
  DIR * dir;
  struct dirent *dp;
  struct stat sb;
  int is_detail = 0;

  // 是否展示 file info
  if (argc >= 2 && strcmp("-l", argv[1]) == 0) {
    is_detail = 1;
  }

  if (getcwd(buf, sizeof(buf)) == NULL) {
    perror("getcwd() error");
  }

  if (argc == 1) {
    dir = opendir(buf);
    while ((dp = readdir(dir)) != NULL) {
      printf("%s\n", dp->d_name);
    }
    closedir(dir);
  }

  if (argc == 2) {
    if (is_detail) {
      dir = opendir(buf);
      printf("%10s %4s %4s %s\n", "permission", "uid", "gid", "file");
      while ((dp = readdir(dir)) != NULL) {
        // 拼接文件路径
        char path[1024];
        strcpy(path, buf);
        strcat(path, "/");
        strcat(path, dp->d_name);

        if (stat(path, &sb) == -1) {
          perror("stat fail");
        }

        // 打印 permission bit
        printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
        printf((sb.st_mode & S_IRUSR) ? "r" : "-");
        printf((sb.st_mode & S_IWUSR) ? "w" : "-");
        printf((sb.st_mode & S_IXUSR) ? "x" : "-");
        printf((sb.st_mode & S_IRGRP) ? "r" : "-");
        printf((sb.st_mode & S_IWGRP) ? "w" : "-");
        printf((sb.st_mode & S_IXGRP) ? "x" : "-");
        printf((sb.st_mode & S_IROTH) ? "r" : "-");
        printf((sb.st_mode & S_IWOTH) ? "w" : "-");
        printf((sb.st_mode & S_IXOTH) ? "x " : "- ");

        printf("%4d %4d %s\n", (int) sb.st_uid, (int) sb.st_gid, dp->d_name);
      }
      closedir(dir);
    } else {
      dir = opendir(argv[1]);
      while ((dp = readdir(dir)) != NULL) {
        printf("%s\n", dp->d_name);
      }
      closedir(dir);
    }
  }

  if (argc == 3 && is_detail) {

    dir = opendir(argv[2]);
    while ((dp = readdir(dir)) != NULL) {
      // 拼接文件路径
      char path[1024];
      strcpy(path, argv[2]);
      strcat(path, "/");
      strcat(path, dp->d_name);

      if (stat(path, &sb) == -1) {
        perror("stat fail");
      }

      // 打印 permission bit
      printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
      printf((sb.st_mode & S_IRUSR) ? "r" : "-");
      printf((sb.st_mode & S_IWUSR) ? "w" : "-");
      printf((sb.st_mode & S_IXUSR) ? "x" : "-");
      printf((sb.st_mode & S_IRGRP) ? "r" : "-");
      printf((sb.st_mode & S_IWGRP) ? "w" : "-");
      printf((sb.st_mode & S_IXGRP) ? "x" : "-");
      printf((sb.st_mode & S_IROTH) ? "r" : "-");
      printf((sb.st_mode & S_IWOTH) ? "w" : "-");
      printf((sb.st_mode & S_IXOTH) ? "x " : "- ");

      printf("%4d %4d %s\n", (int) sb.st_uid, (int) sb.st_gid, dp->d_name);
    }
    closedir(dir);

  }

  return 0;
}
