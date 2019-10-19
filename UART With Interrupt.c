#include<lpc21xx.h>  //including lpc header file
//#define CR 0x0D      // enter ascii value

//void init_serial();// declaring function to initialze   
//void uart1_isr();

//char data[20];
char *str="\rwelcome to cdac acts";
 void uart_init(void)
		{
		 PINSEL0|=(1<<16)|(1<<18);
		 U1LCR= 0x83;
		 U1DLL=0xB7;
		 U1FDR=0xF1;
		 U1LCR=0x03;
		 U1IER=0x02;   // for transmit interrupt enable
		 }
/*void tx_string(char *ptr)
{
	//int i=0;
	while(*ptr!='\0')
	{
		U1THR=*ptr;
		(*ptr)++;
	}
}*/
void uart_int(void)__irq
 {
	 
   while((*str)!='\0')
	{
		U1THR=(*str++);
	//	(*str)++;
	}
		 VICVectAddr=0x00;
 }
	 
void intr_init(void)
 {
		
	 VICIntEnable=0x80; //
	 VICVectCntl0=0x20|0x07;
	 VICVectAddr0=(unsigned)uart_int;
	 U1IIR=0x20; // intr identifier for transmission 
 }
 
/* void tx_string(char data[])
{
	int i=0;
	while(data[i]!='\0')
	{
		putchar(data[i]);
		i++;
	}
}

void rx_string(char data[])
{
	int i=0;
	do
	{
	data[i]=getchar();
	}
	while(data[i++]!=0x0D);
	data[i-1]='\0';
}*/


		
 
 int main(void)
{
	 //  char *ptr="Welcome to CDAC ACTS\n\n\r"; // initialize the string to transmit
VPBDIV=0x02;  // set VPBDIV to divide 60MHZ by 2
uart_init(); // call function init_serial
intr_init();
char ch='c';
	U1THR=ch;
	while(1)  // continous loop
	{
				
	}	
		return 0;
}	
