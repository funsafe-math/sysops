#include <ftw.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

long long total_size =
    0; // will be put in bss, so initialization is not mandatory, I think

int display_info(const char *fpath, const struct stat *sb, int tflag) {
  if (S_ISDIR(sb->st_mode))
    return 0;
  printf("%-7ld  %s\n", sb->st_size, fpath);
  total_size += sb->st_size;
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <dirname>\n", argv[0]);
    return 1;
  }
  const char *dirpath = argv[1];
  if (ftw(dirpath, display_info, 0) < 0) {
    perror("ftw");
    return 2;
  }
  printf("Total size:  %lld\n", total_size);

  return 0;
}