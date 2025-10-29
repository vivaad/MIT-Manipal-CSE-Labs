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
    LDR R0, =NUM1          
    LDR R1, =NUM2         
    LDR R2, [R0]           
    LDR R3, [R1]           
    SUB R4, R2, R3         
    LDR R5, =RESULT        
    STR R4, [R5]           

STOP 
    B STOP                 

NUM1 DCD 20                
NUM2 DCD 10               

    AREA mydata, DATA, READWRITE
RESULT DCD 0               
    END