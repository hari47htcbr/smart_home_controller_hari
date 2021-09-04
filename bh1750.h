/* 
 * File:   i2c.h
 * Author: Hari prasath
 *
 * Created on 13 February, 2021, 8:27 PM
 */

void i2c_init(void)
{
    TRISCbits.TRISC3=1;
    TRISCbits.TRISC4=1;
    __delay_ms(1);
    SSPCON=0x28;
    __delay_ms(1);
    SSPADD= 4;    //11.5 for 20MHZ, 4 for 8 MHZ
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

void i2c_start()
{
    SSPCON2bits.SEN=1;
    __delay_ms(1);
    waitmssp();
}
void i2c_stop()
{
    SSPCON2bits.PEN=1;
    __delay_ms(1);
    waitmssp();
}
void i2c_res()
{
    SSPCON2bits.RSEN=1;
    __delay_ms(1);
    waitmssp();
}
void i2c_ack()
{
    SSPCON2bits.ACKDT=0;
    __delay_ms(1);
    SSPCON2bits.ACKEN=1;
    waitmssp();
}
void i2c_nak()
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
L:  i2c_res();
    SSPBUF=0xD0;
    __delay_ms(1);
    waitmssp();
    while(SSPCON2bits.ACKSTAT){goto L;}
    __delay_ms(1);
    i2c_send(addr);
    __delay_ms(1);
    i2c_res();
    __delay_ms(1);
    i2c_send(0xD1);
    __delay_ms(1);
    rec=i2c_read();
    __delay_ms(1);
    i2c_nak();
    __delay_ms(1);
    i2c_stop();
    __delay_ms(1);
    return rec;
}
