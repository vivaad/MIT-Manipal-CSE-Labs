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
    LDR R0, =NUM1          ; Load address of first packed BCD number
    LDR R1, [R0]           ; Load first number
    LDR R0, =NUM2          ; Load address of second packed BCD number
    LDR R2, [R0]           ; Load second number
    
    MOV R3, #0             ; Initialize result
    MOV R4, #8             ; Counter for 8 BCD digits
    MOV R5, #0             ; Carry flag

add_loop
    ; Extract rightmost digits from both numbers
    AND R6, R1, #0xF       ; Extract digit from first number
    AND R7, R2, #0xF       ; Extract digit from second number
    
    ; Add digits and previous carry
    ADD R8, R6, R7         ; Add the digits
    ADD R8, R8, R5         ; Add previous carry
    MOV R5, #0             ; Reset carry flag
    
    ; Check if sum > 9 (needs adjustment)
    CMP R8, #9             ; Compare with 9
    BLS no_adjust          ; If sum <= 9, no adjustment needed
    SUB R8, R8, #10        ; Subtract 10 from sum
    MOV R5, #1             ; Set carry flag
    
no_adjust
    ; Pack result digit
    ORR R3, R3, R8         ; Add digit to result
    
    ; Shift numbers right for next digits
    LSR R1, R1, #4         ; Shift first number right
    LSR R2, R2, #4         ; Shift second number right
    
    ; Shift result left for next digit unless it's the last iteration
    SUBS R4, R4, #1        ; Decrement counter
    BEQ store_result       ; If counter = 0, store result
    LSL R3, R3, #4         ; Shift result left for next digit
    B add_loop             ; Continue loop

store_result
    ; Check final carry
    CMP R5, #1             ; Check if there's a final carry
    BNE finish             ; If no carry, finish
    LSL R3, R3, #4         ; Make space for carry digit
    ORR R3, R3, #1         ; Add carry digit
    
finish
    LDR R0, =RESULT        ; Load result address
    STR R3, [R0]           ; Store final result

STOP
    B STOP

    AREA mydata, DATA, READWRITE
NUM1    DCD 0x12345678     ; First packed BCD number (12345678)
NUM2    DCD 0x11111111     ; Second packed BCD number (11111111)
RESULT  DCD 0              ; Storage for result

    END