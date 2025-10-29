#include <LPC17xx.h>
#include <stdio.h>

#define Ref_Vtg 3.300
#define Full_Scale 0xFFF

unsigned int i = 0;

void clear_ports()
{
    LPC_GPIO0->FIOCLR = 0xF << 23;
    LPC_GPIO0->FIOCLR = 1 << 27;
    LPC_GPIO0->FIOCLR = 1 << 28;
}

void delay_lcd(unsigned int r)
{
    unsigned int t;
    for (t = 0; t < r; t++);
}

void write(int temp2, int type)
{
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;
    if (!type)
    {
        LPC_GPIO0->FIOCLR = 1 << 27;
    }
    else
    {
        LPC_GPIO0->FIOSET = 1 << 27;
    }
    LPC_GPIO0->FIOSET = 1 << 28;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = 1 << 28;
    return;
}

void lcd_comdata(int temp1, int type)
{
    int temp2 = temp1 & 0xF0;
    temp2 <<= 19;
    write(temp2, type);
    temp2 = temp1 & 0x0F;
    temp2 <<= 23;
    write(temp2, type);
    delay_lcd(1000);
    return;
}

void lcd_init()
{
    LPC_GPIO0->FIODIR |= 0xF << 23 | 1 << 27 | 1 << 28;
    clear_ports();
    delay_lcd(3200);

    lcd_comdata(0x33, 0);
    delay_lcd(30000);

    lcd_comdata(0x32, 0);
    delay_lcd(30000);

    lcd_comdata(0x28, 0);
    delay_lcd(30000);

    lcd_comdata(0x0c, 0);
    delay_lcd(800);

    lcd_comdata(0x06, 0);
    delay_lcd(800);

    lcd_comdata(0x01, 0);
    delay_lcd(10000);

    return;
}

void lcd_puts(unsigned char* str)
{
    unsigned int temp3, i = 0;
    while (str[i])
    {
        temp3 = str[i];
        lcd_comdata(temp3, 1);
        i++;
        if (i == 16)
        {
            lcd_comdata(0xC0, 0);
        }
    }
    return;
}

// Function to perform addition and subtraction
int perform_operation(int A, char operator, int B)
{
    int result = 0;
    if (operator == '+')
    {
        result = A + B;
    }
    else if (operator == '-')
    {
        result = A - B;
    }
    return result;
}

// Function to read digit input from a button
int read_digit(void)
{
    int digit = -1; // Initialize as invalid
    // Check which button is pressed for digits 0-9
    if (!(LPC_GPIO0->FIOPIN & (1 << 3))) digit = 0;  // Check if button for digit 0 is pressed (P0.3)
    else if (!(LPC_GPIO0->FIOPIN & (1 << 4))) digit = 1; // P0.4 for 1
    else if (!(LPC_GPIO0->FIOPIN & (1 << 5))) digit = 2; // P0.5 for 2
    else if (!(LPC_GPIO0->FIOPIN & (1 << 6))) digit = 3; // P0.6 for 3
    else if (!(LPC_GPIO0->FIOPIN & (1 << 7))) digit = 4; // P0.7 for 4
    else if (!(LPC_GPIO0->FIOPIN & (1 << 8))) digit = 5; // P0.8 for 5
    else if (!(LPC_GPIO0->FIOPIN & (1 << 9))) digit = 6; // P0.9 for 6
    else if (!(LPC_GPIO0->FIOPIN & (1 << 10))) digit = 7; // P0.10 for 7
    else if (!(LPC_GPIO0->FIOPIN & (1 << 11))) digit = 8; // P0.11 for 8
    else if (!(LPC_GPIO0->FIOPIN & (1 << 12))) digit = 9; // P0.12 for 9
    return digit;
}

// Function to read the operator (+ or -)
char read_operator(void)
{
    char operator = 0;
    // Check if button for "+" or "-" is pressed
    if (!(LPC_GPIO0->FIOPIN & (1 << 13))) operator = '+';  // P0.13 for +
    else if (!(LPC_GPIO0->FIOPIN & (1 << 14))) operator = '-'; // P0.14 for - 
    return operator;
}

int main(void)
{
    int A, B, result;
    char operator;
    unsigned char msg[16];

    SystemInit();
    SystemCoreClockUpdate();
    lcd_init();

    // Configure the buttons as input
    LPC_GPIO0->FIODIR &= ~(1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 10 | 1 << 11 | 1 << 12 | 1 << 13 | 1 << 14);

    lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts("Enter Expr:");

    while (1)
    {
        // Read first digit (A)
        while ((A = read_digit()) == -1); // Wait for valid digit input for A
        sprintf(msg, "A: %d", A);
        lcd_comdata(0xC0, 0);
        delay_lcd(800);
        lcd_puts(msg);

        // Read operator (+ or -)
        while ((operator = read_operator()) == 0); // Wait for valid operator input
        sprintf(msg, "Op: %c", operator);
        lcd_comdata(0xC0, 0);
        delay_lcd(800);
        lcd_puts(msg);

        // Read second digit (B)
        while ((B = read_digit()) == -1); // Wait for valid digit input for B
        sprintf(msg, "B: %d", B);
        lcd_comdata(0xC0, 0);
        delay_lcd(800);
        lcd_puts(msg);

        // Perform operation (A operator B)
        result = perform_operation(A, operator, B);
        sprintf(msg, "Result: %d", result);

        // Display result
        lcd_comdata(0xC0, 0);
        delay_lcd(800);
        lcd_puts(msg);
    }

    return 0;
}
