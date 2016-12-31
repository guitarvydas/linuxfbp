#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

int main (int argc, char **argv) {
  char buff[MAX];
  while (NULL != fgets(buff, MAX, stdin)) {
    fprintf (stdout, "%s", buff);
    fflush (stdout);
  }
  exit(0);
}

  
  
