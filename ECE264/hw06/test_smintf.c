#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "smintf.h"

int main(int argc, char *argv[]){
	int i = -10;
	
	char* s = smintf("");
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World 123 0xbc\n");
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World %d",123);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World %d", INT_MAX);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World %d", INT_MIN);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World max int in hex %x\n", INT_MAX);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World max int in binary %b\n", INT_MAX);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World min int in hex %x\n", INT_MIN);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello World min int in binary %b\n", INT_MIN);
	fputs(s, stdout);
	free(s);

	for(i = -10; i <=10; i++){
		s = smintf("Hello World %d\n",i);
		fputs(s, stdout);
		free(s);
		
		s = smintf("Hello World in hex %x\n",i);
		fputs(s, stdout);
		free(s);

		s = smintf("Hello World in binary %b\n",i);
		fputs(s, stdout);
		free(s);
	}

	s = smintf("Hello World owes me %$\n", 100.37);
	fputs(s, stdout);
	free(s);

	s = smintf("I owe Hello World %$\n", -100.37);
	fputs(s, stdout);
	free(s);

	s = smintf("How about some more $$ %$\n",1000.99);
	fputs(s, stdout);
	free(s);

	s = smintf("Hello %s World\n", "string time 653");
	fputs(s, stdout);
	free(s);

	s = smintf("Hello %c orld\n", 'w');
	fputs(s, stdout);
	free(s);

	s = smintf("Hello % rogue lone %");
	fputs(s, stdout);
	free(s);

	s = smintf("\n%\n"); 
	fputs(s, stdout);
	free(s);

	s = smintf("Hello actual %%\n");
	fputs(s, stdout);
	free(s);

	s = smintf("Hello unnecessary %z\n");
	fputs(s, stdout);
	free(s);

	s = smintf("Hello combos! %d %x %s %c %$\n", 765421, 765421, "world", 'e', 649.99);
	fputs(s, stdout);
	free(s);

	s = smintf("%%s");
	fputs(s, stdout);
	free(s);

	return EXIT_SUCCESS;
}
