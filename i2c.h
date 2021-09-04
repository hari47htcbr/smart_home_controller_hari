/* 
 * File:   i2c.h
 * Author: Hari prasath
 *
 * Created on 13 February, 2021, 8:27 PM
 */
void convert_data_from_rtc(void);
char set_value(char,char,char,char);

void rtc_init(void)
{
    TRISCbits.TRISC3=1;
    TRISCbits.TRISC4=1;
    __delay_ms(1);
    SSPCON=0x28;
    __delay_ms(1);
    SSPADD= 49;
    __delay_ms(1);
    SSPSTATbits.SMP=1;
    PIE1bits.SSPIE=1;
}
void waitmssp(void)
{
    while(!PIR1bits.SSPIF); // SSPIF is zero while TXion is progress    
    __delay_ms(1);
    PIR1bits.SSPIF=0;
}

void rtc_start()
{
    SSPCON2bits.SEN=1;
    __delay_ms(1);
    waitmssp();
}
void rtc_stop()
{
    SSPCON2bits.PEN=1;
    __delay_ms(1);
    waitmssp();
}
void rtc_res()
{
    SSPCON2bits.RSEN=1;
    __delay_ms(1);
    waitmssp();
}
void rtc_ack()
{
    SSPCON2bits.ACKDT=0;
    __delay_ms(1);
    SSPCON2bits.ACKEN=1;
    waitmssp();
}
void rtc_nak()
{
    SSPCON2bits.ACKDT=1;
    __delay_ms(1);
    SSPCON2bits.ACKEN=1;
    waitmssp();
}

void i2c_send(unsigned char a)
{
    SSPBUF=a;
    __delay_ms(1);
    waitmssp();
    while(SSPCON2bits.ACKSTAT);
}   
void i2c_send_byte(unsigned char addr,unsigned char data)
{
    rtc_start();
    __delay_ms(1);
    i2c_send(0xD0);
    __delay_ms(1);
    i2c_send(addr);
    __delay_ms(1);
    i2c_send(data);
    __delay_ms(1);
    rtc_stop();
}
unsigned char i2c_read()
{
    SSPCON2bits.RCEN=1;
    __delay_ms(1);
    waitmssp();
    __delay_ms(1);
    return SSPBUF;
}   
    
unsigned char i2c_read_byte(unsigned char addr)
{
    unsigned char rec;
L:  rtc_res();
    SSPBUF=0xD0;
    __delay_ms(1);
    waitmssp();
    while(SSPCON2bits.ACKSTAT){goto L;}
    __delay_ms(1);
    i2c_send(addr);
    __delay_ms(1);
    rtc_res();
    __delay_ms(1);
    i2c_send(0xD1);
    __delay_ms(1);
    rec=i2c_read();
    __delay_ms(1);
    rtc_nak();
    __delay_ms(1);
    rtc_stop();
    __delay_ms(1);
    return rec;
}
    


char convert_to_rtc(char decimal)
{
    
    char tens,ones;
    
    tens=decimal/10;
    tens=tens<<4;
    ones=decimal%10;
    return (tens+ones);
     
    __delay_ms(1);
    
}
char convert_from_rtc(char hex)
{
    
    unsigned char tens,ones;
    ones=hex&0x0f;
    tens=hex&0xf0;
    tens=tens>>4;
    tens=tens*10;
    return (tens+ones);
    __delay_ms(1);
}

void set_time(void)
{
        __delay_ms(1);
        min=i2c_read_byte(0x01);
        __delay_ms(1);
        hour=i2c_read_byte(0x02);
        __delay_ms(1);
        date=i2c_read_byte(0x04);
        __delay_ms(1);
        month=i2c_read_byte(0x05);
        __delay_ms(1);
        year=i2c_read_byte(0x06);
        __delay_ms(1);
    
        convert_data_from_rtc();
    
        __delay_ms(1);
    lcd_clear();
    __delay_ms(10);
    
    lcd_line(1,2);
    lcd_data("Set the time");
    __delay_ms(1000);
    
    lcd_line(1,1);
    lcd_data("dd:MM:YY  HH:MM");
    
    date=set_value(2,1,date,31);
    __delay_ms(1);
    memory_write(0x02,date);
    __delay_ms(1);
    date=convert_to_rtc(date);
    __delay_ms(1);
    i2c_send_byte(0x04,date);
    __delay_ms(1);
    
    month=set_value(2,4,month,12);
    __delay_ms(1);
    memory_write(0x03,month);
    __delay_ms(1);
    month=convert_to_rtc(month);
    __delay_ms(1);
    i2c_send_byte(0x05,month);
    __delay_ms(1);
    
    year=set_value(2,7,year,99);
    __delay_ms(1);
    memory_write(0x04,year);
    __delay_ms(1);
    year=convert_to_rtc(year);
    __delay_ms(1);
    i2c_send_byte(0x06,year);
    __delay_ms(1);
    
    hour=set_value(2,11,hour,24);
    __delay_ms(1);
    hour=convert_to_rtc(hour);
    __delay_ms(1);
    i2c_send_byte(0x02,hour);
    __delay_ms(1);
    
    min=set_value(2,14,min,60);
    __delay_ms(1);
    min=convert_to_rtc(min);
    __delay_ms(1);
    i2c_send_byte(0x01,min);
    __delay_ms(10);
    
    lcd_clear();
    __delay_ms(1);
    i2c_send_byte(0x00,0x00);
    __delay_ms(10);    
    
    lcd_clear();
    lcd_line(1,4);
    lcd_data("RTC Error");
    lcd_print(2,6,error,2);
    lcd_line(2,9);
    lcd_data("sec");
    __delay_ms(10);
    error=set_value(2,6,error,60);
    __delay_ms(100);
    memory_write(0x05,error);
    __delay_ms(10);
}
 

void read_rtc(void)
{
        __delay_ms(1);
        sec=i2c_read_byte(0x00);
        __delay_ms(1);
        min=i2c_read_byte(0x01);
        __delay_ms(1);
        hour=i2c_read_byte(0x02);
        __delay_ms(1);
        date=i2c_read_byte(0x04);
        __delay_ms(1);
        month=i2c_read_byte(0x05);
        __delay_ms(1);
        year=i2c_read_byte(0x06);
        __delay_ms(1);
}

void convert_data_from_rtc(void)
{
        __delay_ms(1);
        sec=convert_from_rtc(sec);
        __delay_ms(1);
        min=convert_from_rtc(min);
        __delay_ms(1);
        hour=convert_from_rtc(hour);
        __delay_ms(1);
        date=convert_from_rtc(date);
        __delay_ms(1);
        month=convert_from_rtc(month);
        __delay_ms(1);
        year=convert_from_rtc(year);
        __delay_ms(1);
}

void rtc_error_correction(void)
{
    __delay_ms(10);
    
    if(hour==0&&min==0&&sec<5)
    {
        __delay_ms(10);
        flag=0;
        __delay_ms(10);
        memory_write(0x0A,flag);
        __delay_ms(1000);
    }
    __delay_ms(10);
    if(hour==0&&min==0&&sec==(error+5)&&flag==0)
    {
        __delay_ms(1);
        hour=0;
        min=0;
        sec=5;
        __delay_ms(1);
        hour=convert_to_rtc(hour);
        __delay_ms(1);
        min=convert_to_rtc(min);
        __delay_ms(1);
        sec=convert_to_rtc(sec);
        __delay_ms(1);
        
        
        i2c_send_byte(0x02,hour);
        __delay_ms(1);
        i2c_send_byte(0x01,min);
        __delay_ms(1);
        i2c_send_byte(0x00,sec);
        __delay_ms(1);
        flag=1;
        __delay_ms(1);
        memory_write(0x0A,flag);
        __delay_ms(100);
    }
   
    
    
}