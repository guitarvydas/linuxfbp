#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

int main (int argc, char **argv) {
  char buff[MAX];
  fprintf (stdout, "\n");
  while (NULL != fgets(buff, MAX, stdin)) {
    fprintf (stdout, "%s", buff);
  }
  exit(0);
}

  
  
