/*
 * A "tee" (named dot, not to clash with linux tee) which takes
 * an integer on the command line for the # of incoming pipes.
 * Sends all output to stdout.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 1024
#define MAXFDS 10

void usage(void) {
  fprintf (stderr, "usage: dot n (where n > 0 and n <= %d)\n", MAXFDS);
  exit(1);
}

int main (int argc, char **argv) {
  char buff[MAX];
  int nfds, nfiles, i, fd;
  char *r;
  FILE *files[MAXFDS];
  if (argc != 2) usage();
  nfds = atoi(argv[1]);
  if (nfds < 1 || nfds > MAXFDS) usage();
  for (i = 0; i < MAXFDS; i += 1) {
    files[i] = NULL;
  }
  nfiles = nfds;
  for (fd = 3, i = 0; i < nfds ; i += 1, fd += 1) {
    files[i] = fdopen(fd, "r");
    if (files[i] == NULL) { // error or skip
      fprintf(stderr, "can't fdopen %d as file[%d]\n", fd, i);
      exit(1);
    }
  }
  while (nfds > 0) {
    for (i = 0; i < nfiles && nfds > 0; i += 1) {
      if (files[i] != NULL) {
	r = fgets(buff, MAX, files[i]);
	if (r == NULL) {
	  fclose(files[i]);
	  files[i] = NULL;
	  nfds -= 1;
	} else {
	  fprintf(stdout, "%s", buff);
	}
      }
    }
  }
  fclose(stdout);
  exit(0);
}

  
  
