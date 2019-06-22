#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int main() {
  printf("\n---- Running test3 ---\n");
  
  // test attempts a couple allocations with invalid sizes
  char *p1 = (char *) malloc(0);
  if (p1 != NULL) {
    printf("\n---- MALLOC(0) TEST FAILED ---\n");
  } else {
    printf("\n---- MALLOC(0) TEST PASSED ---\n");
  }

  char *p2 = (char *) malloc(150000000);
  int errval = errno;
  if (p2 != NULL || errval != ENOMEM) {
    printf("\n---- MALLOC TOO LARGE TEST FAILED ---\n");
  } else {
    printf("\n---- MALLOC TOO LARGE TEST PASSED ---\n");
  }

    exit(0);
}
