#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "MyMalloc.h"

int main() {
  const char * str = "\n---- Running test0 ---\n";
  write(1, str, strlen(str));

  //simple test that does nothing requiring malloc()
  int i = 2;
  int j = 3;
  int k = i + j;

  //print_list();

  exit(0);
}
