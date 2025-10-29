	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	; Vector table
	DCD 0x10001000          ; Reset vector address
	DCD Reset_Handler       ; Reset handler address
	ALIGN

	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler	

Reset_Handler
	; Initialize registers with values
	mov r1, #1
	mov r2, #6
	mov r3, #4
	mov r4, #7
	mov r5, #9
	mov r6, #3
	mov r7, #2
	mov r8, #5
	mov r9, #8
	mov r10, #10
	
	; Store values in memory (stack) using STM
	stmia r13!, {r1-r10}
	
	; r0 holds stack top
	mov r0, r13 
	
	; r2 holds the number of elements in stack
	mov r2, #10 
	
	; Initialize outer loop counter (r8)
	mov r8, #0
	
ol
	; Check if outer loop is done (r8 == r2)
	cmp r8, r2
	beq exit
	
	; r1 points to the stack top
	mov r1, r0
	; r3 points to the stack top minus 4 bytes
	mov r3, r0
	sub r3, #4
	
	; r9 is for inner loop counter (initialize to outer loop + 1)
	add r9, r8, #1
	
il
	; Compare inner loop counter to the number of elements in stack
	cmp r9, r2
	beq exin
	
	; Increment inner loop counter (r9)
	add r9, r9, #1
	
	; Load value from stack (r1 points to current element)
	ldmdb r1!, {r4}
	ldmdb r3!, {r5}
	
	; Compare if current element (r5) is less than the next element (r4)
	cmp r5, r4
	blt il
	
	; Swap elements if needed
	stmdb r1!, {r5}
	stmdb r3!, {r4}
	
	; Repeat inner loop
	b il

exin
	; Move the stack pointer down by 4 bytes after each outer loop iteration
	sub r0, r0, #4
	; Increment outer loop counter
	add r8, r8, #1
	; Repeat outer loop
	b ol
	
exit
	; Restore the values back into registers
	ldmdb r13!, {r1-r10}
	
stop
	; Infinite loop to stop the program
	b stop

	AREA mydata, DATA, READWRITE
	END
