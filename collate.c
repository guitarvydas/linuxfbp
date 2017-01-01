#include <stdio.h>
#include <stdlib.h>

#define MAX 1025

void usage() {
  fprintf (stderr, "usage: collate\n");
  exit (1);
}

int main (int argc, char **argv) {
  char master[MAX];
  char detail[MAX];
  FILE *mf, *df;
  mf = fdopen(3, "r");
  df = fdopen(4, "r");
  if (mf == NULL || df == NULL) {
    usage();
  }
  while (NULL != fgets(master, MAX, mf)) {
    fprintf (stdout, "%s", master);
  }
  while (NULL != fgets(detail, MAX, df)) {
    fprintf (stdout, "%s", detail);
  }
  fclose(mf);
  fclose(df);
  exit(0);
}

