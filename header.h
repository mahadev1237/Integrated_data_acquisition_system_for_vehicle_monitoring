extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_string(unsigned char*p);
extern unsigned char uart0_rx(void);
extern void uart0_integer(unsigned int num);
extern void uart0_float(float num);
extern void adc_init(void);
extern unsigned int adc_read(unsigned char ch_num);
extern void delay_ms(unsigned int ms);
extern void delay_sec(unsigned int sec);
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_integer(int num);
extern void lcd_float(float num);
extern void lcd_string(char*ptr);
extern unsigned int read_mcp3204(unsigned char ch_num);
extern unsigned char spi0(unsigned char data);
extern void spi0_init(void);
extern void i2c_init(void);
extern void i2c_byte_write_frame(unsigned char sa, unsigned char mr, unsigned char data);
extern unsigned char i2c_byte_read_frame(unsigned char sa, unsigned char mr);
