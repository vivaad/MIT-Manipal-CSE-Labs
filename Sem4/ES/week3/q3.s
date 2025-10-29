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
    LDR   R0, =DIVIDEND    
    LDR   R1, =DIVISOR     
    LDR   R2, [R0]         
    LDR   R3, [R1]         

    MOV   R4, #0           ; clear r4 for quotient
CHECK_LOOP
    CMP   R2, R3           ; Compare dividend/remainder (R2) with divisor (R3)
    BLT   DONE             ; If dividend < divisor, we're done
    SUB   R2, R2, R3       
    ADD   R4, R4, #1       
    B     CHECK_LOOP       ; Repeat until dividend < divisor

DONE
    LDR   R5, =QUOTIENT
    STR   R4, [R5]
    LDR   R5, =REMAINDER
    STR   R2, [R5]

STOP
    B STOP                 

DIVIDEND DCD 100           
DIVISOR  DCD 7             

    AREA mydata, DATA, READWRITE
QUOTIENT  DCD 0            
REMAINDER DCD 0           

    END