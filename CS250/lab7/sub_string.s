@ARM assembly main substring program
.section	.data
number:		.word 0
substr:		.space 100
testMsg:	.asciz "Test number is %d.\n"
.section	.text
.global		sub_string	

sub_string:
	sub	r3, r2, r1	@get length of the subtring required
	add	r0, r0, r1	@point r0 to the correct starting point in the in_string for the substring
	sub	r0, r0, $1	@subtract 1 for proper looping
	ldr	r6, =substr	@load memory pointer to store the substring
	ldr	r5, =number	@load a 0 bit to act as loop counter
	ldr	r5, [r5]	@deference r5 (loop counter) to use for cmp instruction
	mov	r7, lr		@save the current lr position of the stack
loop:
	cmp	r3, r5		@check if the loop has completed running for length times
	blt	end		@exit the loop if it has completed
	ldrb	r4, [r0], #1	@load one byte of the in_string where r0 currently points
	strb	r4, [r6]	@store that byte in the new substring
	add	r6, r6, $1	@move the substring pointer to the next free byte
	add	r5, r5, $1	@update the counter
	BL loop

end:
	ldr	r6, =substr	@move the substring pointer to the start of the substring
	mov 	r0, r6		@move it to r0 to pass it as a return parameter
	mov	lr, r7		@move the lr to previously saved address to resume proper execution of the code
	bx	lr		@branch exit to the main
