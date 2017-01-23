#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "hw02.h"

int main(int argc, char* argv[]) {
	
	//check for all bases from 2 to 36
	for(int base = 2; base <= 36; base++) {
			
		//check for boundary extreme values
		print_integer(INT_MAX,base,"");
		print_integer(INT_MIN,base,"");
		
		//check for normal and negative integers for some arbitary range
		for(int i = -10; i <= 10; i++) {
			print_integer(i,base,"");
		}
		printf("\n");
	}

	//check for supplied prefixes and certain regular expressions
	print_integer(666,16,"0x");
	print_integer(666,10,"$");
	print_integer(-666,10,"$");
	return EXIT_SUCCESS;
}
