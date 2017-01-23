#include <stdio.h>
#include "calc.h"

int main(int argc, char *argv[]) {
	int result = calculate("1", '+', "1");
	printf("1 + 1 = %d\n", result);

	result = calculate("0xa", '+', "3");
	printf("0xa + 3 = %d\n", result);

	result = calculate("0xa", '*', "3");
	printf("0xa * 3 = %d\n", result);

	result = calculate("0xa", '/', "3");
	printf("0xa / 3 = %d\n", result);

	result = calculate("0xa", '-', "3");
	printf("0xa - 3 = %d\n", result);

	result = calculate("-0b1011", '*', "-0xa0");
	printf("-0b1011 * -0xa0 = %d\n", result);

	result = calculate("0b1011", '+', "0xa0");
	printf("0b1011 + 0xa0 = %d\n", result);

	result = calculate("0", '+', "0x0");
	printf("0 + 0x0 = %d\n", result);
	return 0;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
