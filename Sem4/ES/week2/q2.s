	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000 ;Stack pointer
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
		
Reset_Handler
	LDR R0, =SRC
	LDR R1, =DST
	mov R2, #10
	
	str r2, [r0]
	ldr r3, [r0]
	STR R3, [R1]
STOP
	B STOP

	AREA mydata, DATA, READWRITE
SRC DCD 0x05462975
DST DCD 0x04852695
	END