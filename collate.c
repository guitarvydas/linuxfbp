#include <stdio.h>
#include <stdlib.h>

#define MAX 1025

void usage() {
  fprintf (stderr, "usage: collate fields\n");
  exit (1);
}

#define NPIPES 2

void copy (char *dest, char *src, int len) {
  int i;
  for (i = 0 ; i < len; i += 1) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
}

int compareTo (char *a, char *b, int len) {
  // return -1 if a < b, 1 if a > b, 0 if a == b (string compare with length)
  int i;
  for (i = 0 ; i < len ; i += 1) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

char *receive (char *buff, int len, FILE *f) {
  char *p = fgets(buff, len, f);
  return p;
}

void sendOutput(char *buff) {
  fprintf (stdout, "%s", buff);
}

int main (int argc, char **argv) {
  char pArray[NPIPES][MAX];
  FILE *inportArray[NPIPES];
  int *fldarray, firstPipe;
  int i, j, parmct, totlen, no, count, low;
  char *hold, *p;
  if (argc <= 1) {
    usage();
  }
  firstPipe = 3;
  for (i = 0 ; i < NPIPES ; i += 1) {
    inportArray[i] = fdopen(firstPipe + i, "r");
    if (inportArray[i] == NULL) {
      usage();
    }
  }
  parmct = argc - 1;
  fldarray = (int*)calloc(parmct, sizeof(int));
  for (i = 0, j = 1; j <= parmct ; i += 1, j += 1) {
    fldarray[i] = atoi(argv[j]);
  }
  totlen = 0;
  for (i = 0; i < parmct; i += 1) {
    totlen += fldarray[i];
  }
  no = NPIPES;
  count = no;
  for (i = 0; i < no ; i += 1) {
    if (NULL == receive(pArray[i], MAX, inportArray[i])) {
      pArray[i][0] = '\0';
      count -= 1;
    } else {
      // "IP" already in pArray[i]
    }
  }
  hold = (char *)malloc(totlen + 1);
  while (1) {
    for (i = 0; i < totlen ; i += 1) {
      hold[i] = 0x7f;  // maximum ASCII value
    }
    hold[totlen] = '\0';
    low = 0;
    for (i = 0; i < no ; i += 1) {
      if (pArray[i][0] != '\0') {
	if (compareTo(pArray[i], hold, totlen) < 0) {
	  copy(hold, pArray[i], totlen);
	  low = i;
	}
      }
    }
    sendOutput(pArray[low]);
    p = receive(pArray[low], MAX, inportArray[low]);
    if (p == NULL) {
      count -= 1;
    }
    if (count == 0) {
      break;
    }
  }
  for (i = 0 ; i < NPIPES ; i += 1) {
    fclose(inportArray[i]);
  }
  exit(0);
}

