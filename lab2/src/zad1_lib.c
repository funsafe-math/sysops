#include <stdio.h>

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

  FILE *input = fopen(input_filename, "r");
  if (input == NULL) {
    perror(input_filename);
    return 1;
  }

  FILE *output = fopen(output_filename, "w");
  if (output == NULL) {
    fclose(input);
    perror(output_filename);
    return 1;
  }

  int c;
  while ((c = fgetc(input)) != EOF) {
    fputc(c == find ? replace : c, output);
  }

  fclose(input);
  fclose(output);

  return 0;
}
