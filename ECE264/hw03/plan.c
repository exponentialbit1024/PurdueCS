#include<stdio.h>
#include "mintf.h"

int main(int argc, char *argv[]){
	
	//TEST 00	framework test to pass everytime
	//Expect : ""	
	
	//TEST 01: Empty String
	mintf("");
	//Expect: ""
	
	//TEST 02: Test to check printing of a string without any format codes
	mintf("Hello World");
	//Expect: "Hello World"
	
	//TEST 03: Test to check print_integer, but without any format code parsing
	mintf(632);
	//Expect: "632"
	
	//TEST 04: Test to check for '%' parsing success
	mintf("Hello % World");
	//Expect: "Hello %y World"
	
	//TEST 05: Test to check for multiple parameters
	mintf("Hello World", 2, 'c');
	//Expect: "Hello World2c"
	
	//TEST 06: Test to check for %d
	mintf("Hello %d World", 2);
	//Expect: "Hello 2 World"
	
	//TEST 07: Test to check for multiple parameters of %d
	mintf("Hello %d World %d", 2, 3);
	//Expect: "Hello 2 World 3"
	
	//TEST 7.5: Test to check for negative integers for %d
	mintf("Hello %d World", -2);
	//Expect : "Hello -2 World"

	//TEST 08: Test to check for %x
	mintf("Hello %x World", 1020);
	//Expect: "Hello 0x3fc World"
	
	//TEST 09: Test to check for %b
	mintf("Hello %b World", 8);
	//Expect: "Hello 1000 World"
	
	//TEST 10: Test to check for %$
	mintf("Hello %$ World", 35.99);
	//Expect: "Hello $35.99 World"
	
	//TEST 11: Test for -ve %$
	mintf("Hello %$ World", -35.99);
	//Expect: "Hello -$35.99 World"
	
	//TEST 12: Test for %s
	mintf("Hello %s", "world");
	//Expect : "Hello world"
	
	//TEST 13: Test for %c
	mintf("Hello %c orld", 'w');
	//Expect: "Hello w orld"
	
	//TEST 14: Test for %%
	mintf("Hello %% World");
	//Expect : "Hello %% World"
	
	//TEST 15 : Test for rogue %(char)
	mintf("Hello %z World");
	//Expect : "Hello %z World"
	//
	
	//TEST 16: Test for combination of format strings in one
	mintf("Hello %d %x %s", 2, 1020, "world");
	//Expect : Hello 2 0x3fc world"
	
	return EXIT_SUCCESS;
}
