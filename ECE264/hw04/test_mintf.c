#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include "mintf.h"

int main(int argc, char* argv[]){
	
	int i = -10;

	mintf("");

	mintf("Hello World 123 0xbc\n");

	mintf("Hello World %d",123);
	mintf("Hello World %d", INT_MIN);
	mintf("Hello World %d\n", INT_MAX);
	for(i = -10; i <=10; i++){
		mintf("Hello World %d\n", i);
		mintf("Hello World in hex %x\n", i);
		mintf("Hello World in binary %b\n", i);
	}
	mintf("%d in hex is %x\n", i,i);
	mintf("%d in binary is %b\n",i,i);
	mintf("%x in binary is %b\n",i,i);
	
	mintf("Hello World owes me %$\n",100.37);
	mintf("I owe Hello World %$\n",-100.37);
	mintf("How about some more $$ %$", 1000.99);

	mintf("Hello %s World\n", "string time 653");
	mintf("Hello %c orld\n", 'w');

	mintf("Hello % rogue lone %");
	mintf("\n%\n");

	mintf("Hello actual %%\n");
	mintf("Hello unnecessary %z\n");

	mintf("Hello combos! %d %x %s %c %$\n", 765421, 765421, "world", 'e', 649.99);
	mintf("%%s");
	return EXIT_SUCCESS;
}
