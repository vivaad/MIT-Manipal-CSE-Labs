#include <LPC17xx.h>

unsigned int i, j;
unsigned long LED = 0x00000001;  // Start with LSB LED on

int main(void)
{
    SystemInit();              // Initialize system
    SystemCoreClockUpdate();   // Update system core clock
    
    // Configure Port0 Pins P0.4-P0.11 as GPIO function
    LPC_PINCON->PINSEL0 &= 0xFF0000FF;
    
    // Configure P0.4-P0.11 as output port
    LPC_GPIO0->FIODIR |= 0x00000FF0;
    
    while(1)
    {
        for(i = 0; i < 256; i++)  // Loop from 0x00 to 0xFF (8-bit counter)
        {
            LPC_GPIO0->FIOSET = LED;  // Turn on LED corresponding to the current bit

            for(j = 0; j < 1000; j++);  // Delay for visibility

            LPC_GPIO0->FIOCLR = LED;  // Turn off LED to reset for next bit

            LED++;  // Shift the LED pattern to next position
            if (LED > 0xFFFFFFFF) { // If LED pattern exceeds 8-bit limit (0xFF)
                LED = 0x00000001;  // Reset to the first LED (LSB)
            }
        }
    }
}
