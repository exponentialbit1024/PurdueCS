
#include <stdlib.h>
#include <stdio.h>
#include "MyMalloc.h"



int
main( int argc, char **argv )
{

  printf("\n---- Running test1 ---\n");

  printf("Before any allocation\n");
  print_list();

  //test designed to coalesce from both sides of a block
  int * mem1 = (int *) malloc( 8 );
  *mem1 = 10;

  printf("mem1 = malloc(8)\n");
  print_list();

  int * mem2 = (int *) malloc( 8 );
  *mem2 = 11;
  
  printf("mem2 = malloc(8)\n");
  print_list();

  int * mem3 = (int *) malloc( 8 );
  *mem3 = 12;

  printf("mem3 = malloc(8)\n");
  print_list();

  free(mem2);
  printf("free(mem2))\n");
  print_list();

  free(mem1);
  printf("free(mem1))\n");
  print_list();

  exit(0);
}
