#include<lpc21xx.h>
#include"LCD7TDMI.h"

void lcd_string(char *);

int main(void)
{
init_lcd();
timer_init();
send_cmd(0x80);
lcd_string(" Welcome To");
send_cmd(0xc0);
lcd_string(" Amol Bagh");
}

void lcd_string(char *str)
{
while(*str!='\0')
{
send_data(*str++);
}
}
-------------------------------------------------------------------------------------------
#include<lpc214x.h>

void init_lcd();
void send_data(unsigned char);
void send_cmd(unsigned char);
void user_delay(unsigned int);
void timer_init(void);
void delay(void);

void init_lcd()
{
	IODIR0 |= (1<<10)|(1<<11)|(1<<12)|(1<<13);
	IODIR1 |= (1<<22)|(1<<23)|(1<<24);
	
//	IOCLR1 |= (1<<23);		 //R/W =0; write enabled;
		send_cmd(0x28);// 0010 1000 Function Set(): interfacelength N=1 means two lines ,DL=0 means 4-bit interface 
    send_cmd(0x06);// 0000 0110 Entry Mode Set(): ID=1 means increment the cursor position after write
    send_cmd(0x0C);// 0000 1111 Display On/Off(): display =1 , cursor =1 , blinking =1
    send_cmd(0x01);// 0000 0001 Clear Display(): Clears display and returns cursor to the home position (address 0).
    send_cmd(0x02);// 0000 0010 Cursor Home(): 
}

void timer_init()
{
	VPBDIV = 0X01;
	T1TCR = (1<<1);	//0X02 BIT 1 IS TIMER RESET
	T1CTCR = 0X00; 	//BIT 0 AND BIT 1 IS 0 FOR TIMER MODE
	T1PR = 60000 - 1;	//TO MAKE DELAY EQUAL TO 1 MS
}

void user_delay(unsigned int ms)
{
	timer_init();
	T1TCR = (1<<1);	//TO MAKE TIMER RESET
	T1MCR = (1<<4);	//TO SET AS RESET MODE
	T1MR1 = ms;			//MATCH WITH ms
	T1TCR = (1<<0);	//to start counting
	while(T1TC!=ms);
	//while(T1TC<ms);
}

void delay(void)
{
	int i,j;

	for(i=0;i<=0x0FF;i++)
	for(j=0;j<=0xFF;j++);
}

void send_data(unsigned char data)
{
		unsigned char data1;
		data1=data;
		
		data1=(data1 & 0xF0);	// sending the Higher nibble First
		IO1CLR|=(1<<23); // make RW LOW
		IO1SET|=(1<<24); // make RS high
		
		IO0SET|=(data1<<6);	// sending the data	or rather '1' to the port pins (DB4-DB7: connected to pins 10,11,12,13)
		IO0CLR|=(~(data1<<6)); //we are sending the '0' value to the port pins
	
		IO1SET|=(1<<22); //Enable LCD
		delay();
		IO1CLR|=(1<<22); //
		delay();

		// sending the lower nibble
		data1=data;
		data1=(data1 & 0x0F);
		data1=(data1 << 4);
		
		IO0SET|=(data1<<6);	// sending the data
		IO0CLR|=(~(data1<<6));
	
		IO1SET|=(1<<22);
		delay();
		IO1CLR|=(1<<22);
		delay();

}

void send_cmd(unsigned char data)
{
		unsigned char data1;
		data1=data;
		
		data1=(data1 & 0xF0);	// sending the Higher nibble First
		IO1CLR|=(1<<23); // make RW LOW
		IO1CLR|=(1<<24);// make RS LOW
		
		IO0SET|=(data1<<6);	// sending the Cmd or rather '1' to the port pins (DB4-DB7: connected to pins 10,11,12,13)
		IOCLR0|=(~(data1<<6));
		
		IO1SET|=(1<<22);  // Toggle EN_LCD Pin
		delay();
		IO1CLR|=(1<<22);
		delay();
		
		// sending the lower nibble
		//data1=data;
		data1=(data & 0x0F);
		data1=(data1 << 4);
		
		IO0SET|=(data1<<6);	// sending the Cmd or rather '1' to the port pins (DB4-DB7: connected to pins 10,11,12,13)
		IOCLR0|=(~(data1<<6));
		
		IO1SET|=(1<<22);  // Toggle EN_LCD Pin
		delay();
		IO1CLR|=(1<<22);
		delay();
}
