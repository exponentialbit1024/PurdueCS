#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int allocations =10000;

int main() {

  printf("\n---- Running test10 ----\n");
  char * ptrs[15410];
  int i;
  for (i = 0; i < allocations; i++ ) {
    char * p1 = (char *) malloc(100 );
    ptrs[i] = p1;
    *p1 = 100;
  }
  printf("\n---- AFTER ALLOCATIONS ----\n");
  print_list();
  for(i = 0; i < allocations; i = i+2){
    free(ptrs[i]);
  }
  printf("\n---- AFTER FREES ----\n");
  print_list();
  for (i = 0; i < allocations; i++ ) {
    char * p1 = (char *) malloc(100 );
    ptrs[i] = p1;
    *p1 = 100;
  }
  printf("\n---- AFTER MORE ALLOCATIONS ----\n");
  print_list();
  exit( 0 );
}

