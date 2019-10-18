#include <lpc21xx.h>
void my_delay(void)
{
	for(int i=0;i<100000;i++);
	for(int i=0;i<100000;i++);
	for(int i=0;i<100000;i++);
	for(int i=0;i<100000;i++);
}
int main(void)
{	
	//PINSEL0 = 0x00000000;	/* Configuring P0.0 to P0.15 as GPIO */
	/* No need for this as PINSEL0 reset value is 0x00000000 */
	//IO0DIR = 0x00000001;		/* Make P0.0 bit as output bit, P0.1 bit as an input pin  */
	PINSEL0=0;
  PINSEL1=0;
	IO0DIR=0XFFFFFFFF;
  IO1DIR=0XFFFFFFFF;
	while(1)
	{		
			IOSET0=0xffffffff;
			IOSET1=0xffffffff;
	    		my_delay();
		  	IOCLR0=0xffffffff;
			IOCLR1=0xffffffff;
			my_delay();
	}	
}
