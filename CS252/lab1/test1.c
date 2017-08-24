#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int allocations = 65535;

int main() {
  printf("\n---- Running test1 ---\n");
  
  //test performs many small allocations, up to 2MB
  int i;
  for ( i = 0; i < allocations; i++ ) {
    char * p1 = (char *) malloc(15 );
    *p1 = 100;
  }
  print_list();
  exit( 0 );
}

