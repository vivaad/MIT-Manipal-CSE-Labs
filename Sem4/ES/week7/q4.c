#include <LPC17xx.h>

// Lookup table for hexadecimal digits (0-9, A-F)
unsigned char tohex[16] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 
                           0X7F, 0X6F, 0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71}; 
                           // 0-9, A-F for 7-segment display

unsigned int counter = 0x0000;   // Start from 0000 (Hex)
unsigned int digits[4];          // Stores individual Hex digits
unsigned int direction = 1;      // 1 = Up, 0 = Down

void Timer0_Init(void) {
    LPC_SC->PCONP |= (1 << 1);    // Power up Timer0
    LPC_SC->PCLKSEL0 |= (1 << 2); // Set Timer0 clock
    LPC_TIM0->MR0 = 6250000;      // 0.25s delay (assuming 25MHz clock)
    LPC_TIM0->MCR = 3;            // Interrupt & Reset on match
    LPC_TIM0->TCR = 1;            // Enable Timer0
    NVIC_EnableIRQ(TIMER0_IRQn);  // Enable Timer0 Interrupt
}

void GPIO_Init(void) {
    LPC_PINCON->PINSEL1 &= ~(3 << 10); // Set P0.21 as GPIO (Clear bits 10-11)
    LPC_GPIO0->FIODIR &= ~(1 << 21);   // Set P0.21 as INPUT
}

int readButton(void) {
    int d;
    int buttonState = LPC_GPIO0->FIOPIN & (1 << 21); // Read button state

    for (d = 0; d < 100000; d++); // Debounce delay

    if ((LPC_GPIO0->FIOPIN & (1 << 21)) == buttonState) {
        return (buttonState == 0) ? 0 : 1; // If LOW -> Downcount, If HIGH -> Upcount
    }
    return direction; // If state is unstable, keep previous direction
}

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & 1) {  // Check if MR0 caused the interrupt
        direction = readButton(); // Always check button before updating counter

        if (direction == 1) {
            counter = (counter == 0xFFFF) ? 0x0000 : counter + 1; // Count Up (0xFFFF -> 0x0000)
        } else {
            counter = (counter == 0x0000) ? 0xFFFF : counter - 1; // Count Down (0x0000 -> 0xFFFF)
        }
        
        LPC_TIM0->IR = 1; // Clear MR0 interrupt flag
    }
}

void displayNumber(void) {
    unsigned int temp = counter;
    int i, j;  // Declare loop variables

    digits[3] = (temp >> 12) & 0xF;  // Extract highest hex digit (MSB)
    digits[2] = (temp >> 8) & 0xF;   // Extract second hex digit
    digits[1] = (temp >> 4) & 0xF;   // Extract third hex digit
    digits[0] = temp & 0xF;          // Extract lowest hex digit (LSB)

    for (i = 0; i < 4; i++) {
        LPC_GPIO1->FIOPIN = i << 23; // Select digit
        LPC_GPIO0->FIOPIN = tohex[digits[i]] << 4; // Display number

        for (j = 0; j < 500; j++); // Short delay

        LPC_GPIO0->FIOCLR = 0X00000FF0; // Clear display
    }
}

int main(void) {
    LPC_GPIO0->FIODIR |= 0XFF0;  // P0.4 to P0.11 as output (7-segment)
    LPC_GPIO1->FIODIR |= 0XF << 23; // P1.23 to P1.26 as output (digit control)

    GPIO_Init();  // Initialize button (CNC MPIN7 ? P0.21)
    Timer0_Init(); // Initialize timer

    while (1) {
        displayNumber(); // Refresh display
    }
}
