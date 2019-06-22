#include <stdio.h>

extern int myprintf(const char * format, ...);
int main(){
	int a = -2147483648;
	int b = 20;
	char *subFormat = "Hello World Hi";
	myprintf("Hello World %d %s\n", a,subFormat);
	return 0;
}
