#include <LPC17xx.h>

void scan(void);

void clear_ports()
{
	LPC_GPIO0->FIOCLR =0xF<<23;
	LPC_GPIO0->FIOCLR =1<<27;
	LPC_GPIO0->FIOCLR =1<<28;
}

void delay_lcd(unsigned int r)
{
	unsigned int t;
	for(t=0;t<r;t++);
}

void write(int temp2,int type)
{
	clear_ports();
	LPC_GPIO0->FIOPIN=temp2;
	if(!type)
	{
		LPC_GPIO0->FIOCLR = 1<<27;
	}
	else
	{
		LPC_GPIO0->FIOSET = 1<<27;
	}
	LPC_GPIO0->FIOSET = 1<<28;
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = 1<<28;
	return;
}

void lcd_comdata(int temp1,int type)
{
	int temp2 = temp1&0xF0;
	temp2 <<= 19;
	write(temp2,type);
	temp2=temp1&0x0F;
	temp2 <<= 23;
	write(temp2,type);
	delay_lcd(1000);
	return ;
}

void lcd_init()
{
	LPC_GPIO0->FIODIR |= 0xF<<23|1<<27|1<<28;
	clear_ports();
	delay_lcd(3200);
	
	lcd_comdata(0x33,0);
	delay_lcd(30000);
	
	lcd_comdata(0x32,0);
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
	unsigned int temp3,i=0;
	while(str[i])
	{
		temp3=str[i];
		lcd_comdata(temp3,1);
		i++;
		if(i==16)
		{
			lcd_comdata(0xC0,0);
		}
	}
	return;
}

unsigned char Msg1[13] = "KEY PRESSED=";
unsigned char row, var, flag, key;
unsigned long int i, var1, temp, temp1, temp2, temp3;
unsigned char SCAN_CODE[16] = { 0x11,0x21,0x41,0x81,
                                0x12,0x22,0x42,0x82,
                                0x14,0x24,0x44,0x84,
                                0x18,0x28,0x48,0x88};

unsigned char ASCII_CODE[16] = {'0','1','2','3',
                                '4','5','6','7',
                                '8','9','A','B',
                                'C','D','E','F'};
int main(void){
    LPC_GPIO2->FIODIR |= 0x00003C00; //made output P2.10 to P2.13 (rows)
    LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26(cols)   //not required since it is by default
    LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;
    clear_ports();
    delay_lcd(3200);
    lcd_init();
    lcd_com(0x80); //point to first line of LCD
    delay_lcd(800);
    lcd_puts(&Msg1[0]); //display the message
    while(1){
        while(1){
            for(row=1;row<5;row++){
                if(row == 1)
                var1 = 0x00000400;
                else if(row == 2)
                var1 = 0x00000800;
                else if(row == 3)
                var1 = 0x00001000;
                else if(row == 4)
                var1 = 0x00002000;
                temp = var1;
                LPC_GPIO2->FIOCLR = 0x00003C00; //first clear the 
                port and send appropriate value for
                LPC_GPIO2->FIOSET = var1; //enabling the row
                flag = 0;
                scan(); //scan if any key pressed in the enabled row
                if(flag == 1)
                break;
            } //end for
            if(flag == 1)
                break;
        } //2nd while(1)
        for(i=0;i<16;i++){ //get the ascii code for display
            if(key == SCAN_CODE[i]){
                key = ASCII_CODE[i];
                break;
            } //end if(key == SCAN_CODE[i]) 
        }//end for(i=0;i<16;i++)
        
        lcd_com(0xc0);//display in the second line
        delay_lcd(800);
        lcd_puts(&key);
    }//end while 1
}//end main
void scan(void){
    temp3 = LPC_GPIO1->FIOPIN;
    temp3 &= 0x07800000; //check if any key pressed in the enabled row
    if(temp3 != 0x00000000){
        flag = 1;
        temp3 >>= 19;//Shifted to come at HN of byte
        temp >>= 10; //shifted to come at LN of byte
        key = temp3|temp; //get SCAN_CODE
    }//if(temp3 != 0x00000000)
}//end scan