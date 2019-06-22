#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int main() {

  printf("\n---- Running test7 ---\n");
  // allocate three blocks of memory 
  // (the fourth is just used as a boundary)
  char * mem1 = malloc(8);
  char * mem2 = malloc(8);
  char * mem3 = malloc(8);
  malloc(8);
  printf("\n---- ALLOCATE ----\n");
  print_list();
  free(mem1);
  free(mem3);
  free(mem2);
  printf("\n---- FREE AND COALESCE BOTH SIDES ----\n");
  print_list();

  exit(0);
}

