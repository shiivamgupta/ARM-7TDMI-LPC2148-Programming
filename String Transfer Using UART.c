#include	<lpc21xx.h>

int main()
{		char ch;
		PINSEL0 |= ((1<<0) | (1<<2));		//enable UART0 function
		VPBDIV = 0x02;		//PCLK @ 30MHz
		U0FDR = 0xF1;     //set MUL value to 15 and DIVADDVAL to 1
		U0LCR = 0x83;			//set DLAB bit for divisor latch, set data size 8-bits	//BAD PROGRAMMER
		U0DLL = 183;				//9600Baud
	//	U0DLM = 0;
		U0LCR = 0x03;       // reset the DLAB bit for divisor latch
		char *str1="Welcome to Electronics Wizardry\nPlease Continue typing below, to exit, hit \"Ctrl+Z\":\n"; 
		char *str2="\nEXITING....";
		do
		{		U0THR = *str1;     // Transmitting str1 to uart
				while(!(U0LSR & (1<<5)));  //
		}	while(*++str1 != '\0');    //inc str1 until found null 
		
		do
		{		while(!(U0LSR & (1<<0)));  //Recv set
				ch = U0RBR; 							//Taking character from UART Terminal to ch
				U0THR = ch;               //Transmitting ch back to terminal
		} while(ch != 0x1A);          //Execute until CTRL+Z pressed to exit from the Receiver section
		
		do
		{		U0THR = *str2;            // Transmitting str2 to uart terminal 
				while(!(U0LSR & (1<<5)));  //
		}	while(*++str2 != '\0');
		
		while(1);
}
