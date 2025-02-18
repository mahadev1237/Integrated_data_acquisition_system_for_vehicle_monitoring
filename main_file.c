#include<lpc21xx.h>
#include"header.h"
main()
{
unsigned char h,m,s,mon,date,year,day;
unsigned int temp,vtg,adcout;
float vout,temp1;
int i,f1;
uart0_init(9600);
lcd_init();
spi0_init();
adc_init();
i2c_init();

i2c_byte_write_frame(0XD0,0X0,0X45);
i2c_byte_write_frame(0XD0,0X1,0X59);
i2c_byte_write_frame(0XD0,0X2,0X23);
i2c_byte_write_frame(0XD0,0X3,0X06);
i2c_byte_write_frame(0XD0,0X4,0X25);
i2c_byte_write_frame(0XD0,0X5,0X01);
i2c_byte_write_frame(0XD0,0X6,0X25);


//read rtc time & print it on lcd///
while(1)
{
   lcd_cmd(0x80);
h=i2c_byte_read_frame(0xD0,0x2);//read hrs
if(h>=0x12)
{
	//i2c_byte_write_frame(0xD0,0x2,0x12);
	h-=0x12;
	f1=1;
}
else
	f1=0;

if(h==0)
{
	h=0x12;
}
m=i2c_byte_read_frame(0xD0,0x1);//read mins
s=i2c_byte_read_frame(0xD0,0x0);//read sec
date=i2c_byte_read_frame(0xD0,0x04);
mon=i2c_byte_read_frame(0xD0,0x05);
year=i2c_byte_read_frame(0xD0,0x06);
day=i2c_byte_read_frame(0xD0,0x03);



lcd_data((h/0x10)+48);
lcd_data((h%0x10)+48);
lcd_data(':');
lcd_data((m/0x10)+48);
lcd_data((m%0x10)+48);
lcd_data(':');
lcd_data((s/0x10)+48);
lcd_data((s%0x10)+48);

if(f1)
{
	lcd_string("AM");
}
else
{
	lcd_string("PM");
}
switch(day)
{
	case 1: lcd_cmd(0x8c);
	lcd_string("Mon");
	break;

	case 2: lcd_cmd(0x8c);
	lcd_string("tue");
	break;

	case 3: lcd_cmd(0x8c);
	lcd_string("wed");
	break;

	case 4: lcd_cmd(0x8c);
	lcd_string("thu");
	break;

	case 5: lcd_cmd(0x8c);
	lcd_string("Fri");
	break;

	case 6: lcd_cmd(0x8c);
	lcd_string("sat");
	break;

	case 7: lcd_cmd(0x8c);
	lcd_string("Sun");
	break;
}

uart0_string("TIME:");
uart0_tx((h/0x10)+48);
uart0_tx((h%0x10)+48);
uart0_tx(':');
uart0_tx((m/0x10)+48);
uart0_tx((m%0x10)+48);
uart0_tx(':');
uart0_tx((s/0x10)+48);
uart0_tx((s%0x10)+48);
uart0_string("\r\n");

lcd_cmd(0xc0);
lcd_data((date/0x10)+48);
lcd_data((date%0x10)+48);
lcd_data('/');
lcd_data((mon/0x10)+48);
lcd_data((mon%0x10)+48);
lcd_data('/');
lcd_data((year/0x10)+48);
lcd_data((year%0x10)+48);

uart0_string("DATE:");
uart0_tx((date/0x10)+48);
uart0_tx((date%0x10)+48);
uart0_tx('/');
uart0_tx((mon/0x10)+48);
uart0_tx((mon%0x10)+48);
uart0_tx('/');
uart0_tx((year/0x10)+48);
uart0_tx((year%0x10)+48);
uart0_string("\r\n");


//////////////LDR////////
lcd_cmd(0xce);
temp=read_mcp3204(2);
vtg=(4095-temp)/40.95;
lcd_integer(vtg);
uart0_string("L:");
uart0_integer(vtg);


///////////TEMP///////
lcd_data(' ');
lcd_cmd(0xca);
adcout=adc_read(1);
vout=(adcout*3.3)/1023;
temp1=(vout-0.5)/0.01;
lcd_integer(temp1);
lcd_data('C');

uart0_string("\r\n");
uart0_integer(temp1);
uart0_string("C \r\n");
uart0_string("\r\n");


for(i=0;i<1000;)
{
delay_ms(1);
i++;
}
   }
}

