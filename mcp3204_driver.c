#include<lpc21xx.h>
#include"header.h"
#define cs0 (1<<7)
unsigned int read_mcp3204(unsigned char ch_num)
{
unsigned char byte_h=0,byte_l=0;
unsigned int result=0;
ch_num<<=6;
IOCLR0=cs0;
spi0(0x06);
byte_h=spi0(ch_num);
byte_l=spi0(0x00);
IOSET0=cs0;
byte_h&=0x0f;
result=(byte_h<<8)|byte_l;
return result;
}
