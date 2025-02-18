#include<LPC21XX.H>
#include"header.h"
void uart0_init(unsigned int baud)
{
 int a[]={15,60,30,15,15};
unsigned int pclk,result=0;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0|=0X05;
U0LCR=0X83;
U0DLL= result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0X03;
}			          

void uart0_tx(unsigned char data)
{
U0THR=data;
while(((U0LSR>>5)&1)==0);
}

 void uart0_string(unsigned char*p)
 {
 //int i;
 //for(i=0;p[i];i++)
 while(*p)
 {
 U0THR=*p;
 while(((U0LSR>>5)&1)==0);
 p++;
 }
}
 unsigned char uart0_rx()
 {
 while((U0LSR&1)==0);
 return U0RBR;
 }
	   

void uart0_integer(unsigned int num)
{
int a[10],i;
if(num==0)
{
uart0_tx('0');
}
if(num<0)
{
num=-num;
uart0_tx('-');
}
i=0;
while(num>0)
{
a[i]=num%10+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
{
uart0_tx(a[i]);
}
}   

int temp ;
void uart0_float(float num)
{
temp=num;
uart0_integer(temp);
uart0_tx('.');
num-=temp;
num*=1000;
temp=num;
uart0_integer(temp);
}
