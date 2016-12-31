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
  fprintf (stderr, "mf=%lx df=%lx\n", (unsigned long int)mf, (unsigned long int)df);
  if (mf == NULL || df == NULL) {
    usage();
  }
  while (NULL != fgets(master, MAX, mf)) {
    fprintf (stdout, "%s", master);
    fflush(stdout);
  }
  while (NULL != fgets(detail, MAX, df)) {
    fprintf (stdout, "%s", detail);
    fflush(stdout);
  }
  fflush(mf);
  fclose(mf);
  fflush(df);
  fclose(df);
  exit(0);
}

