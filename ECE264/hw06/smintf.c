#include<stdlib.h>
#include<stdarg.h>
#include "smintf.h"

int strlength(const char* string){
	int len = 0;
	while(string[len] != '\0'){
		len++;
	}
	len++;
	return(len);
}

void convert(char* returnStr,int num, int base, char *prefix){
	unsigned int tempn;
	int conv = 0;
	int prefidx = 0;
	char final_num[33];
	int count = 0;
	int ptrCtr = 0;

	if(num < 0){
		tempn = -num;
		returnStr[ptrCtr] = '-';
		ptrCtr++;
	}
	else{
		tempn = num;
	}
	
	while(prefix[prefidx] != '\0'){
		returnStr[ptrCtr] = prefix[prefidx];
		ptrCtr++;
		prefidx++;
	}

	while(tempn >= base){
		conv = tempn % base;
		tempn = tempn / base;
		final_num[count] = conv;
		count++;
	}
	final_num[count] = tempn;

	while(count >= 0){
		if(final_num[count] > 9){
			returnStr[ptrCtr] = final_num[count] - 10 + 'a';
			ptrCtr++;
		}
		else{
			returnStr[ptrCtr] = '0' + final_num[count];
			ptrCtr++;
		}
		count--;
	}
	returnStr[ptrCtr] = '\0';
}

int sizecounter(const char* format, va_list args){
	int counter = 0;
	int final_size = 0;
	int i = 0;
	char interimStr[33];
	int decimal = 0;
	int wholedec = 0;
	char *s;

	while(format[counter] != '\0'){
		if(format[counter] == '%'){
			if(format[counter+1] != '\0'){
				switch(format[counter+1]){
					case 'd':
						i = va_arg(args, int);
						convert(interimStr, i, 10,"");
						for(int j = 0; interimStr[j] != '\0'; j++){
							final_size += sizeof(char);
						}
						counter++;
						break;
					case 'x':
						i = va_arg(args, int);
						convert(interimStr, i, 16, "0x");
						for(int j = 0; interimStr[j] != '\0'; j++){
							final_size += sizeof(char);
						}
						counter++;
						break;
					case 'b':
						i = va_arg(args, int);
						convert(interimStr, i, 2, "0b");
						for(int j = 0; interimStr[j] != '\0'; j++){
							final_size += sizeof(char);
						}
						counter++;
						break;
					case '$':
						i = va_arg(args, double) * 100;
						if(i < 0){
							i = -i;
							final_size += sizeof(char);
						}
						decimal = i % 100;
						wholedec = (i - decimal) / 100;
						convert(interimStr, wholedec, 10, "$");
						for(int j = 0; interimStr[j] != '\0';j++){
							final_size += sizeof(char);
						}
						final_size += sizeof(char);
						convert(interimStr, decimal, 10,"");
						for(int k = 0; interimStr[k] != '\0'; k++){
							final_size += sizeof(char);
						}
						counter++;
						break;
					case 's':
						s = va_arg(args, char *);
						for(int j = 0; s[j] != '\0'; j++){
							final_size += sizeof(char);
						}
						counter++;
						break;
					case 'c':
						i = va_arg(args, int);
						final_size += sizeof(char);
						counter++;
						break;
					case '%':
						final_size += sizeof(char);
						counter++;
						break;
					default:
						final_size += sizeof(char);
						break;
				}
				counter++;
			}
		}
		counter++;	
	}
	final_size += sizeof(char);
	return(final_size);
}

char* smintf(const char* format, ...){
	va_list args, argc1;
	va_start(args, format);
	va_copy(argc1, args);
	int mallSize = sizecounter(format, argc1);
	char *final_str = malloc(mallSize+strlength(format)*sizeof(*final_str));
	int counter = 0;
	int strcounter = 0;
	int i = 0;
	char interimStr[33];
	int decimal = 0;
	int wholedec = 0;
	char *s;

	while(format[counter] != '\0'){
		if(format[counter] == '%'){
			if(format[counter+1] != '\0'){
				switch(format[counter+1]){
					case 'd':
						i = va_arg(args, int);
						convert(interimStr, i, 10, "");
						for(int j = 0; interimStr[j] != '\0'; j++){
							final_str[strcounter] = interimStr[j];
							strcounter++;
						}
						counter++;
						break;
					case 'x':
						i = va_arg(args, int);
						convert(interimStr, i, 16, "0x");
						for(int j = 0; interimStr[j] != '\0'; j++){
							final_str[strcounter] = interimStr[j];
							strcounter++;
						}
						counter++;
						break;
					case 'b':
						i = va_arg(args, int);
						convert(interimStr, i, 2, "0b");
						for(int j = 0; interimStr[j] != '\0'; j++){
							final_str[strcounter] = interimStr[j];
							strcounter++;
						}
						counter++;
						break;
					case '$':
						i = va_arg(args, double) * 100;
						if(i < 0){
							i = -i;
							final_str[strcounter] = '-';
							strcounter++;
						}
						decimal = i % 100;
						wholedec = (i - decimal) / 100;
						convert(interimStr, wholedec, 10, "$");
						for(int j = 0; interimStr[j] != '\0';j++){
							final_str[strcounter] = interimStr[j];
							strcounter++;
						}
						final_str[strcounter] = '.';
						strcounter++;
						convert(interimStr, decimal, 10,"");
						for(int k = 0; interimStr[k] != '\0'; k++){
							final_str[strcounter] = interimStr[k];
							strcounter++;
						}
						counter++;
						break;
					case 's':
						s = va_arg(args, char *);
						for(int j = 0; s[j] != '\0';j++){
							final_str[strcounter] = s[j];
							strcounter++;
						}
						counter++;
						break;	
					case 'c':
						i = va_arg(args, int);
						final_str[strcounter] = i;
						strcounter++;
						counter++;
						break;
					case '%':
						final_str[strcounter] = '%';
						strcounter++;
						counter++;
						break;
					default:
						final_str[strcounter] = '%';
						strcounter++;
						break;
				}
				counter++;
			}
		}
		final_str[strcounter] = format[counter];
		counter++;
		strcounter++;
	}
	final_str[strcounter] = '\0';
	va_end(args);
	return(final_str);
}	
