#include <stdio.h>
extern void printx(int);
extern void printd(int);

void printString(int subFormatAd){
	int j = 0;
	char *subFormat = (char *) subFormatAd;
	while(subFormat[j] != '\0'){
		putchar(subFormat[j]);
		j++;
	}
}

int myprintf(const char * format, ...){
	int *p = (int *) &format;
	p++;
	int i = 0;
	while(format[i] != '\0'){
		if(format[i] == '%'){
			if(format[i + 1] != '\0'){
				switch(format[i + 1]){
					case 'd':
						printd(*p);
						break;
					case 's':
						printString(*p);
						break;
					case 'x':
						printx(*p);
						break;
					case 'c':
						putchar(*p);
						break;
					case '%':
						putchar('%');
						break;
				}
			}
			p++;
			i++;
		}else{
			putchar(format[i]);
		}
		i++;
	}
}
