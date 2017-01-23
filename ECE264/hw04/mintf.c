#include<stdio.h>
#include<stdarg.h>
#include "mintf.h"

//function to print characters in desired format
void print_integer(int n , int radix, char* prefix){
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
			fputc('0' + final_num[count], stdout);
		}
		count--;
	}
}

//function to get the length of string to prevent outputting unnecessary post string garbage
int strlength(const char * string){
	int len = 0;
	while(string[len] != '\0'){
		len++;
	}
	return(len);
}

void mintf(const char* format, ...){
	va_list arg;
	va_start(arg, format);
	int i = 0;		//integer to store paramters from va_arg
	int counter = 0;		//counter to loop over the paramter string
	char *s;		//string variable to print %s case string
	int substringcounter = 0;		//loop over %s string
	int wholedec = 0;		//decimal before the period in %$ case
	int decimal = 0;	//decimal after the period in %$ case

	while(format[counter] != '\0'){
		if(format[counter] == '%'){
			if(format[counter+1] != '\0'){	//check for subsequent end of string
			//cases corresponding to the hw for different format strings
				switch(format[counter+1]){
					case 'd':
						i = va_arg(arg, int);
						print_integer(i,10,"");
						counter++;
						break;
					case 'x':
						i = va_arg(arg, int);
						print_integer(i,16,"0x");
						counter++;
						break;
					case 'b':
						i = va_arg(arg, int);
						print_integer(i,2,"0b");
						counter++;
						break;
					case '$':
						i = va_arg(arg, double) * 100;
						if(i < 0){
							i = -i; 
							fputc('-', stdout);
						}
						//slice the incoming double to print only 2 digits after period
						decimal = i % 100;
						wholedec =  (i - decimal) / 100;
						print_integer(wholedec,10,"$");
						fputc('.', stdout);
						print_integer(decimal,10,"");
						counter++;
						break;
					case 's':
						s = va_arg(arg, char*);
						while(s[substringcounter] != '\0'){
							fputc(s[substringcounter], stdout);
							substringcounter++;
						}
						counter++;
						break;
					case 'c':
						i = va_arg(arg, int);
						fputc(i, stdout);
						counter++;
						break;
					case '%':
						fputc('%', stdout);
						counter++;
						break;
					default:
						fputc('%', stdout);
						break;
				}
				counter++;
			}
		}
		//in some cases, the counter++ exceeds the string length, and to prevent that, this condition is necessary
		if(counter < strlength(format)){
			fputc(format[counter], stdout);
		}
		counter++;
	}
	va_end(arg);
}	
