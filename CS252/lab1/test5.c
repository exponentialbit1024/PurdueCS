#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int main() {

  printf("\n---- Running test5 ----\n");
  //allocate three blocks of memory 
  //(the third is just used as a boundary)
  char * mem1 = malloc(8);
  char * mem2 = malloc(8);
  malloc(8);
  printf("\n---- ALLOCATE ----\n");
  print_list();
  free(mem1);
  free(mem2);
  printf("\n---- FREE AND COALESCE RIGHT ----\n");
  print_list();

  exit(0);
}

