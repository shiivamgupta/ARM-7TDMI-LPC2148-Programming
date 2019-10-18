#include<LPC214x.h>
void delay()
{
		for(int i=0;i<300;i++)
	  {
			for(int j=0;j<100;j++)
			{
			}
	  }
}
void init_serial()
{
	VPBDIV=0x02; 									//divide CCLK/2=PCLK=30MHz
	PINSEL0|=(1<<16)|(1<<18);			//UART1 p0.8 p0.9
	U1LCR=0x83; 									//8 bit word length. DLAB=1
	U1DLL=0xB7;										//DLL=183 for PCLK=30MHz
	U1FDR=0xF1;										//Mul val=15 DIVVAL=1
	U1LCR=0x03; 									//DLAB=0;
}
void putchar(char ch)
{
//	if(ch=='\n')
//	{
//		U1THR='\n'; 		//OR 0x0D
//	}
//	if(ch=='\r')
//	{
//		U1THR='\r'; 		//OR 0x0D
//	}
	while(!U1LSR&0x20);
	U1THR=ch;
	delay();
}
char getchar(void)
{
	while(!U1LSR&0x01);
	char x = U1RBR;
	return x;
}

int main()
{
	int i;
	char *str = "****HELLO UART TEST****\n\n";
	init_serial();
	i=0;
	putchar('\n');
	putchar('\r');
		while(str[i]!='\0')				//till end of string
		{
			putchar(str[i++]);//transfer string char by char
		}
			putchar('\n');
			putchar('\r');
	while(1)
	{
		
		putchar(getchar());  //echo terminal
	}
}
