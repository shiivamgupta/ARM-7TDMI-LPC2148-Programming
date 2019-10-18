#include	<lpc21xx.h>

int main()
{		//PINSEL0 |= ((1<<16) | (1<<18));		//enable UART1 function
	  PINSEL0 |= ((1<<0) | (1<<2));		//enable UART0 function
		//U0FCR = 0x01;		//FIFO EN
		VPBDIV = 0x02;		//PCLK @ 30MHz
		U0FDR = 0xF1;
		U0LCR = 0x83;			//set DLAB bit for divisor latch, set data size 8-bits	//BAD PROGRAMMER
		U0DLL = 183;				//9600Baud
		U0DLM = 0;
		U0LCR = 0x03;
		//while(1)
		{		U0THR	= 'A';
				while(!(U0LSR & (1<<5)));
				U0THR	= 'A';
				while(!(U0LSR & (1<<5)));
				U0THR	= 'A';
				while(!(U0LSR & (1<<5)));
				//for(i=0; i<1000; i++);
//				for(i=0; i<1000; i++);
//				for(i=0; i<100000; i++);
//				for(i=0; i<100000; i++);
//				for(i=0; i<100000; i++);
		}
		//while(1);
}
