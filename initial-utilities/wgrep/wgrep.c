#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_line(char *line, FILE *fp, int max_len) {
  char ch;
  int pos = 0;
  while (pos < max_len - 1) {
    ch = fgetc(fp);
    if (ch == EOF) return EOF;
    if (ch == '\n') break;
    line[pos] = ch;
    pos++;
  }
  line[pos] = '\0';
  return pos;
}

void process_file(FILE *fp, char *needle) {
  char *buf = malloc(sizeof(char) * 10240);
  if (buf == NULL) {
      printf("wgrep: cannot allocate memory\n");
      exit(1);
  }
  size_t n_len = strlen(needle);
  int l_len = 0;
  while ((l_len = read_line(buf, fp, 10240)) != EOF) {
    int should_print = 0;
    for (size_t i = 0; i < l_len - n_len + 1; i++) {
      int is_eq = 1;
      if (n_len > l_len) { break; }
      for (size_t j = 0; j < n_len; j++) {
        if (needle[j] != buf[i + j]) {
          is_eq = 0;
          break;
        }
      }
      if (is_eq) {
        should_print = 1;
        break;
      }
    }
    if (should_print) {
      printf("%s\n", buf);
    }

  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  };
  char *needle = argv[1];

  if (argc == 2) {
    process_file(stdin, needle);
  } else {
    for (int i = 2; i < argc; i++) {
      FILE *fp = fopen(argv[i], "r");
      if (fp == NULL) {
          printf("wgrep: cannot open file\n");
          exit(1);
      }
      process_file(fp, needle);
      fclose(fp);
    }
  }
  
}