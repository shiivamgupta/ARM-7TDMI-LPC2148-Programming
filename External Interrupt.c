#include <LPC214X.H>

void ext_int()
{
IO0DIR= (1<<31);
IO1DIR=(1<<25);
VPBDIV = 0x00;
PINSEL0 = (1<<31);
EXTMODE = (1<<0);
EXTPOLAR = (1<<2);
EXTINT = (1<<2);
}

void External_int(void)__irq
{
static int i=0;

if(i==0)
{
i=1;
IO1CLR=(1<<25);

}
else
{
i=0;
IO1SET=(1<<25);
}
EXTINT |= (1<<2);
VICVectAddr = 0x00;
}

void int_init()
{
VICIntEnable = (1<<16);
VICVectCntl0 = 0x20 | 0x10;
VICVectAddr0 = (unsigned)External_int;
}

int main(void)
{
ext_int();
int_init();
while(1);
}
