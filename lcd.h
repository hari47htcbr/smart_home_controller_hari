/* 
 * File:   function.h
 * Author: Hari Prasath
 *
 * Created on January 11, 2021, 1:43 PM
 */
void Lcd_Port(unsigned char a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}
void Lcd_Cmd(unsigned char a)
{
	RS = 0;             // => RS = 0
    __delay_ms(1);
	Lcd_Port(a);
	EN  = 1;             // => E = 1
    __delay_ms(1);
    EN  = 0;             // => E = 0
}
void lcd_clear(void)
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}
void lcd_line(unsigned int a, signed int b)
{
	unsigned int temp;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
    else if(a == 3)
	{
		temp = 0x94 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
    else if(a == 4)
	{
		temp = 0xd4 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}
void lcd_init()
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x03);
	__delay_ms(5);
  Lcd_Cmd(0x03);
	__delay_ms(11);
  Lcd_Cmd(0x03);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}
void lcd_char(unsigned int a)
{
   unsigned int temp;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   Lcd_Port(y>>4);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}
void lcd_data(const char *a)
{
	 for(i=0;a[i]!='\0';i++)
	   lcd_char(a[i]);
}


char div4 (char no,char pos)
{

char a,b,c,d;

a=no/1000;

b=no/100;
b=b%10;

c=no/10;
c=c%10;

d=no%10;

if(pos==1)
{return(a);}

if(pos==2)
{return(b);}

if(pos==3)
{return(c);}

if(pos==4)
{return(d);}

return 0;
}


void lcd_print(char line,char pos,char data,char format)
{
       a=div4(data,1);       
       b=div4(data,2);
       c=div4(data,3);
       d=div4(data,4);
       
       a=a+48;
       b=b+48;
       c=c+48;
       d=d+48;
    
if(format==1)
{
    lcd_line(line,pos);
    lcd_char(d);
    __delay_ms(1);
}
if(format==2.0)
{
    lcd_line(line,pos);
    lcd_char(c);

    lcd_line(line,pos+1);
    lcd_char(d);
    __delay_ms(1);
}    
     
}   



