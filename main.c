/*
 * File:   main.c
 * Author: Hari prasath
 *
 * Created on 12 January, 2021, 10:51 AM
 * Modified 04 September, 2021, 05:40 PM
 */

#include <string.h>
#include <stdlib.h>

///#define _XTAL_FREQ 20000000

#define _XTAL_FREQ 8867233

//LCD Data and Control pins ---- OUTPUT
#define RS PORTBbits.RB2
#define EN PORTBbits.RB3
#define D4 PORTBbits.RB4
#define D5 PORTBbits.RB5
#define D6 PORTBbits.RB6
#define D7 PORTBbits.RB7

//LCD Back light control pin ---- OUTPUT
#define LED PORTBbits.RB1

//Relay control pin ---- OUTPUT
#define out PORTDbits.RD2

//Tactile button ---- INPUT
#define inc PORTCbits.RC0
#define dec PORTCbits.RC1
#define enter PORTCbits.RC2

// CONFIG  PIC16F877A
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
char a,b,c,d,y,z,i;     //LCD functions variables

char j=0,k=0,l=0;      //for loop variables
char settings[8]="Settings";

char saved[5]="Saved";

char lux;
int status1,status2;

char backlight=1;     //lcd backlight flag
char relay=0;         //relay control flag


#include "lcd.h"
#include "eeprom.h"
#include "bh1750.h"
#include "functions.h"
 
void main(void) 
{
    char no=0;
    TRISB=0X01;    // LCD DISPLAY CONNECTED
    TRISC=0X17;
      
 //----------------------------------------mode select switches setting-----------------------------------------------------------
    
    TRISD=0x03;
    
    
    PORTB=0xff;
    PORTC=0xff;
    PORTD=0xff;
    
    __delay_ms(10);
    out=0;
    __delay_ms(10);
    
    status1=SSPSTAT;
    status2=SSPCON2;
    
    __delay_ms(10);
    i2c_init();
    __delay_ms(10);
    lcd_init();
    __delay_ms(10);
    lcd_clear();
    __delay_ms(10);
    
    __delay_ms(10);
    status_check();
    __delay_ms(10);
    
    out=relay;
    __delay_ms(10);
    welcome_msg();
    __delay_ms(2000);
    
    
    
    while(1)
    {
        __delay_ms(10);
        status_check();
        __delay_ms(1);
        
        
    }  
}
