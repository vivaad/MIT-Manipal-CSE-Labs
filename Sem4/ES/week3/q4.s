	AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000         
    DCD Reset_Handler      
    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =N             
    LDR R1, [R0]           
    ADD R2, R1, #1         ; R2 = N + 1

    MLA R3, R1, R2, R0     ; R3 = (N * (N + 1))
    MOV R4, #2             ; R4 = 2
    SDIV R5, R3, R4        ; R5 = Sum = (N * (N + 1)) / 2

    LDR R6, =SUM           ; Load the address of SUM into R6
    STR R5, [R6]           ; Store the result in SUM

STOP 
    B STOP                 

N DCD 3     

    AREA mydata, DATA, READWRITE
SUM DCD 0  
	
    END