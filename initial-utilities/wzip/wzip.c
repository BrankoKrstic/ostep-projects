#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(FILE* fp) {
  char cur_ch = fgetc(fp);
  unsigned int char_count = 1;

  while (cur_ch != EOF){
    char new = fgetc(fp);
    if (new == cur_ch) {
      char_count++;
    } else {
      fwrite(&char_count, sizeof(char_count), 1, stdout);
      fwrite(&cur_ch, sizeof(cur_ch), 1, stdout);
      cur_ch = new;
      char_count = 1;
    }
  }
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  };
  
  int first_run = 1;
  char cur_ch;
  unsigned int char_count = 1;
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
        printf("wzip: cannot open file\n");
        exit(1);
    }

    if (first_run) {
      first_run = 0;
      cur_ch = fgetc(fp);
    }
    while (1) {
      char new = fgetc(fp);
      if (new == EOF) {
        break;
      }if (new == cur_ch) {
        char_count++;
      } else {
        fwrite(&char_count, sizeof(char_count), 1, stdout);
        fwrite(&cur_ch, sizeof(cur_ch), 1, stdout);
        cur_ch = new;
        char_count = 1;
      }
    }
    fclose(fp);
  }
  fwrite(&char_count, sizeof(char_count), 1, stdout);
  fwrite(&cur_ch, sizeof(cur_ch), 1, stdout);
}