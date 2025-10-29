#include <LPC17xx.h>

unsigned char tohex[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 
                           0X7F, 0X6F}; // 7-segment codes for 0-9

unsigned int digits[4] = {4, 3, 2, 1}; // Number to display: "1234"
unsigned int i, j;

void delay(unsigned int time) {
    for (j = 0; j < time; j++);
}

int main(void) {
    LPC_GPIO0->FIODIR |= 0XFF0;       // Set P0.4 to P0.11 as output (segment control)
    LPC_GPIO1->FIODIR |= 0XF << 23;   // Set P1.23 to P1.26 as output (digit selection)

    while (1) {
        for (i = 0; i < 4; i++) {
            LPC_GPIO1->FIOPIN = i << 23;            // Select the active digit
            LPC_GPIO0->FIOPIN = tohex[digits[i]] << 4; // Output corresponding 7-segment value
            delay(500);                           // Delay for persistence
            LPC_GPIO0->FIOCLR = 0X00000FF0;         // Clear display before the next cycle
        }
    }
}
