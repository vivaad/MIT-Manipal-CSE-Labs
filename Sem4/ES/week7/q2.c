#include <LPC17xx.h>

unsigned char tohex[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 
                           0X7F, 0X6F}; // 7-segment codes for 0-9

unsigned int counter = 9999; // Start counting from 9999
unsigned int digits[4]; // Stores individual BCD digits

void Timer0_Init(void) {
    LPC_SC->PCONP |= (1 << 1);    // Power up Timer0
    LPC_SC->PCLKSEL0 |= (1 << 2); // Set Timer0 clock
    LPC_TIM0->MR0 = 1562500;     // 1-second delay (assuming 25MHz clock)
    LPC_TIM0->MCR = 3;            // Interrupt & Reset on match
    LPC_TIM0->TCR = 1;            // Enable Timer0
    NVIC_EnableIRQ(TIMER0_IRQn);  // Enable Timer0 Interrupt
}

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & 1) {  // Check if MR0 caused the interrupt
        counter = (counter == 0) ? 9999 : counter - 1; // Decrement counter
        LPC_TIM0->IR = 1; // Clear MR0 interrupt flag
    }
}

void displayNumber(void) {
    unsigned int temp = counter;
    int i, j;  // Declare loop variables

    digits[3] = temp / 1000;
    digits[2] = (temp / 100) % 10;
    digits[1] = (temp / 10) % 10;
    digits[0] = temp % 10;

    for (i = 0; i < 4; i++) {
        LPC_GPIO1->FIOPIN = i << 23; // Select digit
        LPC_GPIO0->FIOPIN = tohex[digits[i]] << 4; // Display number

        for (j = 0; j < 1000; j++); // Short delay

        LPC_GPIO0->FIOCLR = 0X00000FF0; // Clear display
    }
}

int main(void) {
    LPC_GPIO0->FIODIR |= 0XFF0;  // P0.4 to P0.11 as output (7-segment)
    LPC_GPIO1->FIODIR |= 0XF << 23; // P1.23 to P1.26 as output (digit control)

    Timer0_Init(); // Initialize timer

    while (1) {
        displayNumber(); // Refresh display
    }
}
