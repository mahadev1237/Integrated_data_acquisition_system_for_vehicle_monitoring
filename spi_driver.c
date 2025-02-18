#include<lpc21xx.h>
void spi0_init(void)
{
PINSEL0|=0x1500;
IODIR0|=(1<<7);
IOSET0=(1<<7);
S0SPCR=0X20;
S0SPCCR=15;
}

#define SPIF ((S0SPSR>>7)&1)
unsigned char spi0(unsigned char data)
{
S0SPDR=data;
while(SPIF==0);
return S0SPDR;
}
