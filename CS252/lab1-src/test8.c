#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"

int main() {

  printf("\n---- Running test8 ---\n");
  print_list();
  char * mem1 = malloc(2097104);
  print_list();
  free(mem1);
  print_list();

  exit( 0 );
}
