#include<stdio.h>
#include "hw02.h"

void print_integer(int n, int radix, char* prefix){
	unsigned int tempn;
	int conv = 0;
	int prefidx = 0;
	char final_num[33];
	int count = 0;
	if(n < 0){
		tempn = -n;
		fputc('-', stdout);
	}
	else{
		tempn = n;
	}
	while(prefix[prefidx] != '\0'){
		fputc(prefix[prefidx], stdout);
		prefidx++;
	}
	while(tempn >= radix){
		conv = tempn % radix;
		tempn = tempn / radix;
		final_num[count] = conv;
		count++;
	}
	final_num[count] = tempn;
	while(count >= 0){
		if(final_num[count] > 9){
			fputc(final_num[count] - 10 + 'a', stdout);
		}
		else{
			fputc('0'+ final_num[count], stdout);
		}
		count--;
	}
}
