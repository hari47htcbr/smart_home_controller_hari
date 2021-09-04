/* 
 * File:   functions.h
 * Author: Hari Prasath
 *
 * Created on 12 January, 2021, 10:46 AM
 */


//Display functions
void welcome_msg(void)
{
    lcd_clear();
    lcd_line(1,3);
    lcd_data("Smart light");
    lcd_line(2,4);
    lcd_data("Controller");
    __delay_ms(1000);
}

char set_value(char line,char position,char value,char range)
{
    while(1)
    {
        if(inc==0&&value<range)
        {
            __delay_ms(200);
            value++;
        }
        
        if(dec==0&&value>0)
        {
            __delay_ms(200);
            value--;
        }
       
        if(enter==0)
        {
            __delay_ms(200);
            return value;
            break;
        }
        
    }
}

//Functions which is used repeatedly to check every setting and button input
void status_check(void)
{
    char no=0;
    
    
    __delay_ms(10);
    
    backlight=memory_read(0x00);
    __delay_ms(10);
    
    ////LCD Back light////////////
    
    while(inc==0&&no<3)
    {
        __delay_ms(500);
        no++;
        __delay_ms(10);
    }
    if(no==3)
    {
        backlight=!(backlight);
        __delay_ms(10);
        no=0;
        __delay_ms(10);
        memory_write(0x00,backlight);
        __delay_ms(10);
    }
     
    __delay_ms(10);
    LED=backlight;
    __delay_ms(10);
    
    if(lux<=500)
    {
        __delay_ms(1);
        relay=1;
    }
    else if(lux>500)
    {
        __delay_ms(1);
        relay=0;
    }
    
    
    __delay_ms(1);
    out=relay;
    __delay_ms(1);
    
}
