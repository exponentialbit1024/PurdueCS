#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int allocations = 5;

int main() {
  printf("\n---- Running test2 ---\n");
  
  // test performs a few large allocations, beyond 2MB.
  // this means more chunks must be requested from the OS.
  int i;
  for ( i = 0; i < allocations; i++ ) {
    char * p1 = (char *) malloc(1500000);
    *p1 = 100;
    print_list();
  }
  exit( 0 );
}
