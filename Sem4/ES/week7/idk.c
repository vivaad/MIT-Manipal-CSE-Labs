#include <LPC17xx.h>

unsigned char tohex[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 
                           0X7F, 0X6F};
long int arr[4] = {9, 9, 9, 9};
unsigned int i = 0, j = 0;

int main(void)
{
    LPC_GPIO0->FIODIR |= 0XFF0;  // Set P0.4 to P0.11 as output (for segments)
    LPC_GPIO1->FIODIR |= 0XF << 23;  // Set P1.23 to P1.26 as output (for digit selection)

    for (arr[3] = 9; arr[3] >= 0; arr[3]--)  // Fix: Ensure arr[3] starts at 9
    {
        for (arr[2] = 9; arr[2] >= 0; arr[2]--)
            for (arr[1] = 9; arr[1] >= 0; arr[1]--)
                for (arr[0] = 9; arr[0] >= 0; arr[0]--)
                {
                    for (i = 0; i < 4; i++)
                    {
                        LPC_GPIO1->FIOPIN = i << 23;  // Select digit
                        LPC_GPIO0->FIOPIN = tohex[arr[i]] << 4;  // Display corresponding digit
                        for (j = 0; j < 10000; j++);  // Increase delay
                    }

                    for (j = 0; j < 5000; j++);  // Delay before next digit
                    LPC_GPIO0->FIOCLR = 0X00000FF0;  // Fix: Clear without reading
                }
    }
}
