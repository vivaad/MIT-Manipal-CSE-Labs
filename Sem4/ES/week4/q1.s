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
    LDR R0, =BCD_UNPACKED  ; Load the address of the unpacked BCD number
    MOV R1, #0             ; Initialize result register to 0
    MOV R2, #0             ; Initialize counter
    MOV R3, #4             ; Number of digits to process

pack_loop
    LDRB R4, [R0, R2]      ; Load byte at position R2
    LSL R5, R2, #4         ; Multiply counter by 4 for shift amount
    LSL R4, R4, R5         ; Shift the digit to its correct position
    ORR R1, R1, R4         ; Combine with result

    ADD R2, R2, #1         ; Increment counter
    CMP R2, R3             ; Compare counter with number of digits
    BNE pack_loop          ; If not equal, continue loop

    LDR R5, =BCD_PACKED    ; Load the address for packed result
    STR R1, [R5]           ; Store the final packed result

STOP 
    B STOP                 

    ; Unpacked BCD number (Example: 0x01 0x02 0x03 0x04)
BCD_UNPACKED DCB 0x01, 0x02, 0x03, 0x04

    AREA mydata, DATA, READWRITE
    ; Packed BCD number (output)
BCD_PACKED DCD 0x0  

    END