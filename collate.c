#include <stdio.h>
#include <stdlib.h>

#define MAX 1025

void usage() {
  fprintf (stderr, "usage: collate\n");
  exit (1);
}

#define NPIPES 2

int main (int argc, char **argv) {
  char portArray[NPIPES][MAX];
  FILE *mf, *df;
  int *fldarray;
  int i, parmcnt;
  mf = fdopen(3, "r");
  df = fdopen(4, "r");
  if (mf == NULL || df == NULL || argc < 2) {
    usage();
  }
  parmcnt = argc - 1;
  fldarray = (int*)calloc(parmcnt, sizeof(int));
  for (i = 0; i < parmcnt ; i += 1) {
    fldarray[i] = atoi(argv[i]);
  }
  while (NULL != fgets(portArray[0], MAX, mf)) {
    fprintf (stdout, "%s", master);
  }
  while (NULL != fgets(portArray[1], MAX, df)) {
    fprintf (stdout, "%s", detail);
  }
  fclose(mf);
  fclose(df);
  exit(0);
}

