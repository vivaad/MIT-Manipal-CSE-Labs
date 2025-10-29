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
    LDR R0, =PACKED_BCD    ; Load address of packed BCD number
    LDR R1, [R0]           ; Load the packed BCD number
    MOV R2, #0             ; Initialize result register to 0
    MOV R3, #7             ; Initialize position counter (8 digits - 1)
    MOV R4, #1             ; Multiplier for decimal to hex conversion
    MOV R5, #0             ; Initialize temporary result

convert_loop
    ; Extract current BCD digit
    MOV R6, R1             ; Copy packed BCD to R6
    MOV R7, R3, LSL #2     ; Calculate shift amount (position * 4)
    LSR R6, R6, R7         ; Shift right to get current digit
    AND R6, R6, #0xF       ; Mask to get only the current digit

    ; Convert BCD digit to hex (multiply by power of 10)
    MUL R7, R6, R4         ; Multiply digit by current power of 10
    ADD R5, R5, R7         ; Add to result
    MOV R8, #10            
    MUL R4, R4, R8         ; Update multiplier for next iteration

    ; Check if loop complete
    SUBS R3, R3, #1        ; Decrement counter
    BPL convert_loop       ; Branch if counter >= 0

    ; Store result
    LDR R0, =HEX_RESULT
    STR R5, [R0]           ; Store final hexadecimal result

STOP
    B STOP

    AREA mydata, DATA, READWRITE
PACKED_BCD DCD 0x12345678  ; Example: BCD number 12345678
HEX_RESULT DCD 0           ; Storage for hexadecimal result

    END