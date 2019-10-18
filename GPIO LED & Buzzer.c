#include <lpc21xx.h>

int main(void)
{	
	//PINSEL0 = 0x00000000;	/* Configuring P0.0 to P0.15 as GPIO */
	/* No need for this as PINSEL0 reset value is 0x00000000 */
	IO0DIR = 0x00000001;		/* Make P0.0 bit as output bit, P0.1 bit as an input pin  */
	while(1)
	{		
			PINSEL0=0X00000000;
			PINSEL1=0X00000000;
			IODIR0=0XFFFFFFFF;
			IODIR1=0XFFFFFFFF;
	}	
}
