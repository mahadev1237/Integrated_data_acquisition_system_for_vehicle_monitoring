   /* adc dreiver*/
   #include<lpc21xx.h>
   unsigned int result;
   void adc_init()
   {
   PINSEL1|=0X15400000;
   ADCR=0X00200400;
   }
   #define DONE  ((ADDR>>31)&1) 
    unsigned int adc_read(unsigned char ch_num)
    {
    ADCR|=(1<<ch_num);
    ADCR|=(1<<24);
    while(DONE==0);
    ADCR^=(1<<24);
    ADCR^=(1<<ch_num);
    result=(ADDR>>6)&0x3FF;
    return result;
   
    }
