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
	ldr r0, =message
	bl printf

	ldr r0, =stringHold
	ldr r1, =totString
	bl scanf
	
	ldr r0, =message2
	bl printf

	ldr r0, =intHold
	ldr r1, =startIndex
	bl scanf
	
	ldr r0, =message3
	bl printf	
	
	ldr r0, =intHold
	ldr r1, =endIndex
	bl scanf

	ldr r0, =totString
	ldr r1, =startIndex
	ldr r1, [r1]
	ldr r2, =endIndex
	ldr r2, [r2]
	bl sub_string
	mov r1, r0
	ldr r0, =message4
	bl printf

	mov r0, $0
	bl fflush
	mov r7, $1
	svc $0
	.end
