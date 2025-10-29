	AREA RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000         ; The reset vector address (can be a memory address to jump to after reset)
	DCD Reset_Handler      ; Address of the reset handler function
	ALIGN                  

	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
    
    LDR R0,=SRC
	LDR R1,=DST
	MOV R4, #10

LOOP	
	LDR R3, [R0]
	STR R3, [R1]
	ADD R0, #4
	ADD R1, #4
	SUBS R4,#1
	BNE LOOP
	
STOP B STOP
                        

SRC DCD 0,1,2,3,4,5,6,7,8,9

	AREA mydata, DATA, READWRITE
DST DCD 0
	END