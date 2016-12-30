#include <stdio.h>
#include <stdlib.h>

#define MAX 1025

void usage() {
  fprintf (stderr, "usage: readfile <fname>\n");
  exit (1);
}

int main (int argc, char **argv) {
  char line[MAX];
  FILE *f;
  if (argc != 2) {
    usage();
  }
  f = fopen(argv[1], "r");
  if (f == NULL) {
    usage();
  }
  while (NULL != fgets(line, MAX, f)) {
    fprintf (stdout, "%s", line);
  }
  fclose(f);
}

