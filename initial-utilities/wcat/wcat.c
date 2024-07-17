#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    char *fname = argv[i];
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("wcat: cannot open file\n");
        exit(1);
    }
    while(1) {
      int ch = fgetc(file);
      if (ch == EOF)
          break;
      putchar(ch);
    }
  }

  exit(0);
}
