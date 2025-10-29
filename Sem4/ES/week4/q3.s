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
    LDR R0, =HEX_NUM      ; Load address of hexadecimal number
    LDR R1, [R0]          ; Load the hexadecimal number
    MOV R2, #0            ; Initialize packed BCD result
    MOV R3, #0            ; Initialize digit position counter
    MOV R4, #10           ; Divisor (10 for decimal conversion)

convert_loop
    ; Divide current number by 10
    MOV R5, #0            ; Initialize remainder
    MOV R6, #16           ; Initialize bit counter for division
    
divide_loop
    LSL R5, R5, #1        ; Shift remainder left
    LSL R1, R1, #1        ; Shift dividend left
    BCC no_add            ; If carry is not set, skip addition
    ADD R5, R5, #1        ; Add carry to remainder
no_add
    CMP R5, R4            ; Compare remainder with divisor
    BCC continue_div      ; If less than divisor, continue
    SUB R5, R5, R4        ; Subtract divisor from remainder
    ADD R1, R1, #1        ; Set quotient bit
continue_div
    SUBS R6, R6, #1       ; Decrement bit counter
    BNE divide_loop       ; Continue division if not done

    ; Pack the digit into result
    LSL R2, R2, #4        ; Make space for next digit
    ORR R2, R2, R5        ; Add current digit to result
    
    ; Check if division result is 0
    CMP R1, #0
    BNE convert_loop      ; Continue if quotient is not 0

    ; Store final result
    LDR R0, =BCD_RESULT
    STR R2, [R0]          ; Store packed BCD result

STOP
    B STOP

    AREA mydata, DATA, READWRITE
HEX_NUM DCD 0x1234        ; Example: Hexadecimal number 1234
BCD_RESULT DCD 0          ; Storage for packed BCD result

    END