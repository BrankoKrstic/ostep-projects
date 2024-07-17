#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(FILE* fp) {
  unsigned int count;
  char ch;
  while (!feof(fp)) {
    if (fread(&count, sizeof(count), 1, fp) == 0) continue;

    if(fread(&ch, sizeof(ch), 1, fp) == 0) continue;
    for (unsigned int i = 0; i < count; i++) {
      putc(ch, stdout);
    }
  }
}

int main(int argc, char* argv[]) {
if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  };
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      exit(1);
    }
    process_file(fp);    

    fclose(fp);
  }
}