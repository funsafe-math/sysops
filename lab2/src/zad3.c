#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  const char *directory = ".";
  DIR *dirp = opendir(directory);
  if (!dirp) {
    perror(directory);
    return 1;
  }

  long long sum = 0;
  struct dirent *dir_entry;
  while ((dir_entry = readdir(dirp)) != NULL) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", directory, dir_entry->d_name);

    struct stat path_stat;
    stat(path, &path_stat);
    if (!S_ISDIR(path_stat.st_mode)) {
      printf("%-7ld %s\n", path_stat.st_size, path);
      sum += path_stat.st_size;
    }
  }
  printf("Total size : %lld\n", sum);

  closedir(dirp);

  return 0;
}