#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 5) {
    fprintf(stderr,
            "Usage: %s <char to find> <char to replace it with> <input file> "
            "<output file>\n",
            argv[0]);
    return 1;
  }
  const char find = argv[1][0];
  const char replace = argv[2][0];
  const char *input_filename = argv[3];
  const char *output_filename = argv[4];

  int input = open(input_filename, O_RDONLY);
  if (input < 0) {
    perror(input_filename);
    return 1;
  }

  int output =
      open(output_filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
  if (output < 0) {
    close(input);
    perror(output_filename);
    return 1;
  }

  char buf[1024]; // Change me to whatever buffer size you like
  int n;
  while ((n = read(input, buf, sizeof(buf))) > 0) {
    for (int i = 0; i < sizeof(buf); i++) {
      if (buf[i] == find)
        buf[i] = replace;
    }
    write(output, buf, n);
  }

  close(input);
  close(output);

  return 0;
}
