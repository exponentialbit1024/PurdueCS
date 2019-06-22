@ARM assembly code to perform decimal and hex printing
.section	.data
number:		.word 0
testMsg:	.asciz "t : %d\n"
.section	.text
.global		printd
.global		printx	

division:
	ldr	r1, .Ls_magic_number_10
	smull	r1, r2, r1, r0
	add	r2, r2, r0
	mov	r2, r2, ASR #3
	mov	r1, r0, LSR #31
	add	r0, r2, r1
	bx lr
	.align 4
	.Ls_magic_number_10:	.word 0xCCCCCCCD

modulo:
	mov	r6, r0
	sub	r0, r0, #10
	cmp	r0, #0
	bgt	modulo
	mov	r0, r6
	bx lr

printZi:
	mov	r0, #48
	bl putchar
	bl end

printdMn:
	mov	r0, #50
	bl putchar
	mov	r0, #49
	bl putchar
	mov	r0, #52
	bl putchar
	mov	r0, #55
	bl putchar
	mov	r0, #52
	bl putchar
	mov	r0, #56
	bl putchar
	mov	r0, #51
	bl putchar
	mov	r0, #54
	bl putchar
	mov	r0, #52
	bl putchar
	mov	r0, #56
	bl putchar
	bl end

printd:
	stmfd	sp!, 	{r4,r5,lr}
	cmp	r0, #0
	beq	printZi
	blt	negateInt
	bl normEx
	negateInt:
		mov	r4, r0
		mov	r0, #45
		bl putchar
		cmp	r4, #0x80000000
		beq	printdMn
		mov	r3, $-1
		mul	r4, r4, r3
		mov	r0, r4
		bl normEx
normEx:
	mov	r8, #0

loop9:	cmp	r0, #0
	beq	printEndi
	mov	r6, r0
	bl division
	mov	r5, r0
	mov	r0, r6
	bl modulo
	cmp	r0, #9
	bgt	reduceInt
	push	{r0}
	add	r8,r8,#1
	mov	r0, r5
	bl loop9
	reduceInt:
		sub	r7, r0, #10
		push	{r7}
		add	r8, r8, #1
		mov	r0, r5
	bl loop9

printEndi:
	mov	r7, #0
	loop4:	cmp	r8, r7
		beq	end
		pop	{r0}
		add	r7, r7, #1
		add	r0, r0, #48
		bl	putchar
		b loop4
	bl end

printx:
	stmfd	sp!, 	{r4,r5,lr}
	mov	r5, #0	
	cmp	r0, #0
	beq	printZ

loop2:	cmp	r0, #0
	beq	printEnd
	and	r1, r0, #15
	add	r5, r5, #1
	cmp	r1, #9
	bgt	printHChar
	ble	printDChar
	printHChar:
		add	r4, r1, #87
		bl	stackPusher 
	printDChar:
		add	r4, r1, #48
stackPusher:
	push	{r4}
	cmp	r0, #0
	blt	leftShift
	asr	r0, r0, #4
	bl loop2
	leftShift:
		lsr	r0, r0, #4
	bl loop2

	bl	end		
printEnd:
	mov	r6, #0
	loop3:	cmp	r5, r6
		beq	end
		pop	{r0}
		add	r6, r6, #1
		bl	putchar
		b loop3
	bl end

printZ:
	mov	r0, #48
	bl putchar
	bl end
end:
	ldmfd	sp!,	{r4,r5,lr}
	mov	r0, $0
	bx	lr

