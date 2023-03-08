// Wybieram wariant z funkcjami posix
#include <stdio.h>
#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
    return 1;
  }
  const char *input_filename = argv[1];
  const char *output_filename = argv[2];

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

  char buf[1]; // Change me to whatever buffer size you like
  int n;
  int read_bytes = sizeof(buf);
  fseek(input, 0, SEEK_END);
  long input_size = ftell(input);
  rewind(input);

  fseek(output, input_size, SEEK_SET);

  while ((n = fread(buf, sizeof(buf[0]), ARR_LEN(buf), input)) > 0) {
    typeof(buf[0]) mirror[ARR_LEN(buf)];
    for (int j = 0; j < n; j++) {
      mirror[n - 1 - j] = buf[j];
    }
    fseek(output, -n, SEEK_CUR);
    fwrite(mirror, sizeof(mirror[0]), n, output);
    fseek(output, -n, SEEK_CUR);
  }

  fclose(input);
  fclose(output);
  return 0;
}