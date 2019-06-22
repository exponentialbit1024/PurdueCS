@ARM assembly substringmain program
.section	.data
message:	.asciz "Enter a string: "
message2:	.asciz "Enter the start index: "
message3:	.asciz "Enter the end index: "
message4:	.asciz "The substring of the given string is \'%s\'\n"
stringHold:	.asciz "%s"
substrHold:	.asciz "%s"
intHold:	.asciz "%d"
startIndex:	.word 0 
endIndex:	.word 0
totString:	.space 100
outString:	.space 100
testMsg:	.asciz "Test number is %d.\n"
.section	.text
.global 	main
main:
	ldr r0, =message	@load the input messages
	bl printf		@branch to printf function

	ldr r0, =stringHold	@load asciz word into register to store
	ldr r1, =totString	@load final string to prompt user =, into regiseter
	bl scanf		@branch to scanf
	
	ldr r0, =message2	@second prompt message into r0 for passing as function parameter to printf
	bl printf		@branch to printf

	ldr r0, =intHold	@load r0 with message prompt to pass to scanf as parameter
	ldr r1, =startIndex	@pass second parameter to hold the value
	bl scanf
	
	ldr r0, =message3	@pass message as parameter to printf via r0
	bl printf		@branch to printf
	
	ldr r0, =intHold	@repeat procedure to store endIndex
	ldr r1, =endIndex
	bl scanf

	ldr r0, =totString	@load input string as parameter for sub_string function
	ldr r1, =startIndex	@load start_index as second parameter
	ldr r1, [r1]		@deference r1 parameter to pass to sub_string
	ldr r2, =endIndex	@load end_index as third parameter
	ldr r2, [r2]		@deference r2 parameter to pass to sub_string
	bl sub_string		@branch to sub_string subroutine
	mov r1, r0		@copy r0 to r1, to hold print message for passing to printf
	ldr r0, =message4	@pass final print message to printf
	bl printf

	mov r0, $0		@reset stack pointers
	bl fflush
	mov r7, $1
	svc $0
	.end
