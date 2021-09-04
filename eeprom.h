/* 
 * File:   eeprom.h
 * Author: Hari prasath
 *
 * Created on 23 February, 2021, 1:54 PM
 */

char memory_read(char address)
{
    EEADR=address;
    EEADRH=0x00;
    EECON1bits.EEPGD=0;
    EECON1bits.RD=1;
    while(EECON1bits.RD==1);
    return EEDATA;
}

void memory_write(char address,char data)
{
   EEADR=address; 
   EEADRH=0x00;
   EEDATA=data;
   INTCONbits.GIE=0;
   INTCONbits.PEIE=0;
   PIE2bits.EEIE=0;
   EECON1bits.EEPGD=0;
   EECON1bits.WREN=1;
   EECON1bits.WR=0;
   EECON2=0x55;
   EECON2=0xAA;
   EECON1bits.WR=1;
   INTCONbits.GIE=1;
   INTCONbits.PEIE=1;
   PIE2bits.EEIE=1;
   EECON1bits.WREN=0;
   
   while(1)
   {
       if(EECON1bits.WRERR==1)
       {
           EECON1bits.WR=1;
           
       }
       if(PIR2bits.EEIF==1){break;}
   }
   PIR2bits.EEIF=0;
   INTCONbits.GIE=0;
   INTCONbits.PEIE=0;
   PIE2bits.EEIE=0;
   EECON1bits.WREN=0;
   EECON1bits.WR=0;
   __delay_ms(1);
}
