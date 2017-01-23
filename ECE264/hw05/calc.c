#include "calc.h"

// forward declarations for helper functions in this file
int _parse_integer(const char* s);
void _find_base(const char** start, int* base);
void _find_sign(const char** start, int* sign);


int calculate(const char* lhs_str, const char operator, const char* rhs_str) {
	int lhs_int = _parse_integer(lhs_str);
	int rhs_int = _parse_integer(rhs_str);
	switch(operator) {
		case '*':
			return lhs_int * rhs_int;
		case '/':
			return lhs_int / rhs_int;
		case '+':
			return lhs_int + rhs_int;
		case '-':
			return lhs_int - rhs_int;
		case '%':
			return lhs_int % rhs_int;
		default:
			return 0;
	}
}

int _parse_integer(const char* s) {
	const char* start = s; // address of first digit after "0x", "0b", or "-"

	int sign  = 0;   // 1 if positive, -1 if negative
	_find_sign(&start, &sign);

	int base  = 0;   // 10 for decimal, 16 for hexadecimal, 2 for binary
	_find_base(&start, &base);

	int value = 0;   // This will be the return value from this function
	int i = 0;
	while(start[i] != '\0') {
		value *= base;
		value += start[i] - (start[i] <= '9' ? '0' : 'a' - 10);
		i++;
	}

	return value * sign;
}

void _find_sign(const char** start, int* sign) {
	if((*start)[0] == '-') {
		*sign = -1;  // found minus sign, so mark as negative
		*start += 1; // advance start to just after the '-'
	}
	else {
		*sign = 1;   // No minus sign, so mark this as positive
	}
}

void _find_base(const char** start, int* base) {
	if((*start)[0] == '0' && (*start)[1] == 'x') {
		*base = 16;  // hexadecimal
		*start += 2; // advance start to just after the "0x"
	}
	else if((*start)[0] == '0' && (*start)[1] == 'b') {
		*base = 2;   // binary
		*start += 2; // advance start to just after the "0b"
	}
	else {
		*base = 10;  // decimal
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
