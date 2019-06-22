#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int allocations =10000;

int main() {

  printf("\n---- Running test4 ---\n");
  //this test requests many small blocks, and then frees every other block.
  //this should result in NO coalescing
  char * ptrs[15410];
  int i;
  for (i = 0; i < allocations; i++ ) {
    char * p1 = (char *) malloc(100 );
    ptrs[i] = p1;
    *p1 = 100;
  }
  print_list();
  for(i = 0; i<allocations; i = i+2){
    free(ptrs[i]);
  }
  print_list();
  exit( 0 );
}

