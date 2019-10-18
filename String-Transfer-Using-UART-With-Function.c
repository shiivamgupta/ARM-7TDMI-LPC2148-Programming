#include<lpc21xx.h>  //including lpc header file
#define CR 0x0D      // enter ascii value
void init_serial();  // declaring function to initialze   
void putchar(int);    // declaring function to transmit 
int getchar(void);    // declairng function to receive
 
   int main(void)
	 {
	   //char *ptr="Welcome to CDAC ACTS\n\n\r"; // initialize the string to transmit
		char *str1="Welcome to Electronics Wizardry\nPlease Continue typing below, to exit, hit \"Ctrl+Z\":\n"; 
		char *str2="\nEXITING....";
		 VPBDIV=0x02;  // set VPBDIV to divide 60MHZ by 2
		  init_serial(); // call function init_serial
			while(1)  // continous loop
			{
			    while(*str1) 
					{
					putchar(*str1++);
					}
					while(*str2) 
					{
					putchar(*str2++);
					}
					putchar(getchar());
			}
					
					
		return 0;
		}	

    void init_serial()
		{
		 PINSEL0|=(1<<16)|(1<<18);
		 U1LCR= 0x83;
		 U1DLL=0xB7;
		 U1FDR=0xF1;
			U1LCR=0x03;
		 }
		 
		 void putchar(int ch)
		 {
		   if(ch=='\n')
			 {
			// while(!U1LSR & (U1LSR=1<<5))
			while(!(U1LSR & 0x20));
			U1THR=CR;
		   	}
			 while(!(U1LSR &0x20));
			U1THR=ch;
			}
	    
			  int getchar(void)
				{
				while(!(U1LSR & 0x01));
			  	return U1RBR;
				}
