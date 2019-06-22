#include <stdio.h>

extern char * sub_string(char*, int, int);

int main(){
	printf("Enter a string: ");
	char in_string[256];
	scanf("%s", &in_string);
	printf("Enter the start index: ");
	int startIndex;
	scanf("%d", &startIndex);
	printf("Enter the end index: ");
	int endIndex;
	scanf("%d", &endIndex);
//	sub_string(in_string, startIndex, endIndex);
	char *out_string = sub_string(in_string, startIndex, endIndex);
	printf("The substring of the given string is \'%s\'\n", out_string);
	return 0;
}
